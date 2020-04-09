// See License.txt

#include "image.hpp"
#include <apcomp/error.hpp>
#include <apcomp/utils/PNGEncoder.hpp>

namespace apcomp
{

void Image::Save(std::string name)
{
  int width = m_bounds.m_max_x - m_bounds.m_min_x + 1;
  int height = m_bounds.m_max_y - m_bounds.m_min_y + 1;

  if(width * height <= 0)
  {
    throw Error("Image: cannot save empty image");
  }

  PNGEncoder encoder;
  encoder.Encode(&m_pixels[0], width, height);
  encoder.Save(name +  ".png");
}

} // namespace apcomp
