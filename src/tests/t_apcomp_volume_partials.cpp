//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) 2015-2017, Lawrence Livermore National Security, LLC.
//
// Produced at the Lawrence Livermore National Laboratory
//
// LLNL-CODE-716457
//
// All rights reserved.
//
// This file is part of APCompositor.
//
// For details, see: http://software.llnl.gov/ascent/.
//
// Please also read ascent/LICENSE
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the disclaimer below.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the disclaimer (as noted below) in the
//   documentation and/or other materials provided with the distribution.
//
// * Neither the name of the LLNS/LLNL nor the names of its contributors may
//   be used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL SECURITY,
// LLC, THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
// IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//-----------------------------------------------------------------------------
///
/// file: t_apcomp_zbuffer.cpp
///
//-----------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "t_test_utils.h"

#include <apcomp/apcomp.hpp>
#include <apcomp/partial_compositor.hpp>

#include <iostream>

using namespace std;


//-----------------------------------------------------------------------------
TEST(apcomp_partials, apcomp_volume_partial)
{
  std::string output_dir = prepare_output_dir();
  std::string file_name = "volume_partial";
  std::string output_file = apcomp::join_file_path(output_dir,file_name);
  remove_test_file(output_file);

  apcomp::PartialCompositor<apcomp::VolumePartial<float>> compositor;

  const int width  = 1024;
  const int height = 1024;
  const int square_size = 300;
  const int num_images  = 4;
  const int y = 500;
  float colors[4][4] = { {1.f, 0.f, 0.f, 0.5f},
                         {0.f, 1.f, 0.f, 0.5f},
                         {0.f, 0.f, 1.f, 0.5f},
                         {0.f, 1.f, 1.f, 0.5f} } ;

  std::vector<std::vector<apcomp::VolumePartial<float>>> in_partials;
  in_partials.resize(num_images);

  for(int i = 0; i < num_images; ++i)
  {
    std::vector<apcomp::VolumePartial<float>> partials;
    gen_float32_partials(in_partials[i],
                         width,
                         height,
                         float(i) * 0.05f,
                         200 + 100*i,
                         y - i * 50,
                         square_size,
                         colors[i]);

  }
  std::vector<apcomp::VolumePartial<float>> output;
  compositor.composite(in_partials, output);

  partials_to_png(output, width, height, output_file);

  EXPECT_TRUE(check_test_image(output_file));
}

