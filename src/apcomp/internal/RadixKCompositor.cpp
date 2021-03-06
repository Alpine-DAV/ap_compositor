#include <apcomp/internal/ImageCompositor.hpp>
#include <apcomp/internal/ScalarImageCompositor.hpp>
#include <apcomp/internal/MPICollect.hpp>
#include <apcomp/internal/RadixKCompositor.hpp>
#include <apcomp/internal/apcomp_diy_collect.hpp>
#include <apcomp/internal/apcomp_diy_utils.hpp>

#include <diy/master.hpp>
#include <diy/mpi.hpp>
#include <diy/partners/swap.hpp>
#include <diy/reduce.hpp>
#include <diy/reduce-operations.hpp>

namespace apcomp
{

template<typename ImageType>
void DepthComposite(ImageType &front, ImageType &back);

template<>
void DepthComposite<ScalarImage>(ScalarImage &front, ScalarImage &back)
{
  apcomp::ScalarImageCompositor compositor;
  compositor.ZBufferComposite(front, back);
}

template<>
void DepthComposite<Image>(Image &front, Image &back)
{
  apcomp::ImageCompositor compositor;
  compositor.ZBufferComposite(front, back);
}

template<typename ImageType>
void reduce_images(void *b,
                   const apcompdiy::ReduceProxy &proxy,
                   const apcompdiy::RegularSwapPartners &partners)
{
  ImageBlock<ImageType> *block = reinterpret_cast<ImageBlock<ImageType>*>(b);
  unsigned int round = proxy.round();
  ImageType &image = block->m_image;
  // count the number of incoming pixels
  if(proxy.in_link().size() > 0)
  {
      for(int i = 0; i < proxy.in_link().size(); ++i)
      {
        int gid = proxy.in_link().target(i).gid;
        if(gid == proxy.gid())
        {
          //skip revieving from self since we sent nothing
          continue;
        }
        ImageType incoming;
        proxy.dequeue(gid, incoming);
        DepthComposite(image, incoming);
      } // for in links
  }

  if(proxy.out_link().size() == 0)
  {
    return;
  }
  // do compositing?? intermediate stage?
  const int group_size = proxy.out_link().size();
  const int current_dim = partners.dim(round);

  //create balanced set of ranges for current dim
  apcompdiy::DiscreteBounds image_bounds = BoundsToDIY(image.m_bounds);
  int range_length = image_bounds.max[current_dim] - image_bounds.min[current_dim];
  int base_step = range_length / group_size;
  int rem = range_length % group_size;
  std::vector<int> bucket_sizes(group_size, base_step);
  for(int i  = 0; i < rem; ++i)
  {
    bucket_sizes[i]++;
  }

  int count = 0;
  for(int i  = 0; i < group_size; ++i)
  {
    count += bucket_sizes[i];
  }
  assert(count == range_length);

  std::vector<apcompdiy::DiscreteBounds> subset_bounds(group_size, BoundsToDIY(image.m_bounds));
  int min_pixel = image_bounds.min[current_dim];
  for(int i = 0; i < group_size; ++i)
  {
    subset_bounds[i].min[current_dim] = min_pixel;
    subset_bounds[i].max[current_dim] = min_pixel + bucket_sizes[i];
    min_pixel += bucket_sizes[i];
  }

  //debug
  if(group_size > 1)
  {
    for(int i = 1; i < group_size; ++i)
    {
      assert(subset_bounds[i-1].max[current_dim] == subset_bounds[i].min[current_dim]);
    }

    assert(subset_bounds[0].min[current_dim] == image_bounds.min[current_dim]);
    assert(subset_bounds[group_size-1].max[current_dim] == image_bounds.max[current_dim]);
  }

  std::vector<ImageType> out_images(group_size);
  for(int i = 0; i < group_size; ++i)
  {
    out_images[i].SubsetFrom(image, DIYToBounds(subset_bounds[i]));
  } //for

  for(int i = 0; i < group_size; ++i)
  {
      if(proxy.out_link().target(i).gid == proxy.gid())
      {
        image.Swap(out_images[i]);
      }
      else
      {
        proxy.enqueue(proxy.out_link().target(i), out_images[i]);
      }
  } //for

} // reduce images

RadixKCompositor::RadixKCompositor()
{

}

RadixKCompositor::~RadixKCompositor()
{

}

template<typename ImageType>
void
RadixKCompositor::CompositeImpl(apcompdiy::mpi::communicator &diy_comm, ImageType &image)
{
    apcompdiy::DiscreteBounds global_bounds = BoundsToDIY(image.m_orig_bounds);

    // tells diy to use one thread
    const int num_threads = 1;
    const int num_blocks = diy_comm.size();
    const int magic_k = 8;

    //apcompdiy::Master master(diy_comm, num_threads);
    apcompdiy::Master master(
        diy_comm, num_threads,
        -1, 0,
        [](void * b){
        ImageBlock<ImageType> *block = reinterpret_cast<ImageBlock<ImageType>*>(b);
        delete block;
        });

    // create an assigner with one block per rank
    apcompdiy::ContiguousAssigner assigner(num_blocks, num_blocks);
    AddImageBlock<ImageType> create(master, image);
    const int num_dims = 2;
    apcompdiy::RegularDecomposer<apcompdiy::DiscreteBounds> decomposer(num_dims, global_bounds, num_blocks);
    decomposer.decompose(diy_comm.rank(), assigner, create);
    apcompdiy::RegularSwapPartners partners(decomposer,
                                      magic_k,
                                      false); // false == distance halving
    apcompdiy::reduce(master,
                assigner,
                partners,
                reduce_images<ImageType>);


    //MPICollect(image, diy_comm);
    apcompdiy::all_to_all(master,
                    assigner,
                    CollectImages<ImageType>(decomposer),
                    magic_k);

    if(diy_comm.rank() == 0)
    {
      master.prof.output(m_timing_log);
    }
}

void
RadixKCompositor::CompositeSurface(apcompdiy::mpi::communicator &diy_comm,
                                   Image &image)
{
  CompositeImpl(diy_comm, image);
}

void
RadixKCompositor::CompositeSurface(apcompdiy::mpi::communicator &diy_comm,
                                   ScalarImage &image)
{
  CompositeImpl(diy_comm, image);
}

std::string
RadixKCompositor::GetTimingString()
{
  std::string res(m_timing_log.str());
  m_timing_log.str("");
  return res;
}

} // namespace alpine
