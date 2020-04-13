###############################################################################
# Copyright (c) 2015-2019, Lawrence Livermore National Security, LLC.
#
# Produced at the Lawrence Livermore National Laboratory
#
# LLNL-CODE-716457
#
# All rights reserved.
#
# Please also read ascent/LICENSE
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the disclaimer below.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the disclaimer (as noted below) in the
#   documentation and/or other materials provided with the distribution.
#
# * Neither the name of the LLNS/LLNL nor the names of its contributors may
#   be used to endorse or promote products derived from this software without
#   specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL SECURITY,
# LLC, THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
# IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
###############################################################################

###############################################################################
#
# Example that shows how to use an installed instance of Ascent in another
# CMake-based build system.
#
# To build:
#  mkdir build
#  cd build
#  cmake -DAPCOMP_DIR={apcomp install path} ../
# make
# ./apcomp_example
#
# If run in sub directory below using-with-cmake in an apcomp install,
# APCOMP_DIR will be defaulted to ../../..
#
#  mkdir build
#  cd build
#  cmake ..
#  make
#  ./apcomp_example
#
###############################################################################

cmake_minimum_required(VERSION 3.9)

project(using_with_cmake)

#
# Provide default for APCOMP_DIR that works for an apcomp install
#
if(NOT APCOMP_DIR)
    set(APCOMP_DIR "../../..")
endif()

#
# Check for valid apcomp install
#
get_filename_component(APCOMP_DIR ${APCOMP_DIR} ABSOLUTE)
if(NOT EXISTS ${APCOMP_DIR}/lib/cmake/APCompConfig.cmake)
    MESSAGE(FATAL_ERROR "Could not find APComp CMake include file (${APCOMP_DIR}/lib/cmake/APCompConfig.cmake)")
endif()

#
# Use CMake's find_package to import apcomps targets
#
find_package(APComp REQUIRED
             NO_DEFAULT_PATH
             PATHS ${APCOMP_DIR}/lib/cmake)

# create our example
add_executable(apcomp_example apcomp_example.cpp)

# link to ascent
target_link_libraries(apcomp_example apcomp)
