//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) 2015-2017, Lawrence Livermore National Security, LLC.
//
// Produced at the Lawrence Livermore National Laboratory
//
// LLNL-CODE-716457
//
// All rights reserved.
//
// This file is part of AP Compositor.
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
/// file: t_test_utils.cpp
///
//-----------------------------------------------------------------------------

#include <vector>

void
gen_float32_image(std::vector<float> &pixels,
                  std::vector<float> &depths,
                  int width,
                  int height,
                  float depth,
                  int bottom_x,
                  int bottom_y,
                  int size,
                  float color[4])
{
  pixels.resize(width * height * 4);
  depths.resize(width * height);
  for(int y = 0; y < height; ++y)
  {
    for(int x = 0; x < width; ++x)
    {
      pixels[(y * width + x) * 4 + 0] = 0.f;
      pixels[(y * width + x) * 4 + 1] = 0.f;
      pixels[(y * width + x) * 4 + 2] = 0.f;
      pixels[(y * width + x) * 4 + 3] = 0.f;
      depths[y * width + x] = 1.01f;
    }
  }

  for(int y = bottom_y ; y < bottom_y + size; ++y)
  {
    for(int x = bottom_x; x < bottom_x + size; ++x)
    {
      pixels[(y * width + x) * 4 + 0] = color[0];
      pixels[(y * width + x) * 4 + 1] = color[1];
      pixels[(y * width + x) * 4 + 2] = color[2];
      pixels[(y * width + x) * 4 + 3] = color[3];
      depths[y * width + x] = depth;
    }
  }

}
