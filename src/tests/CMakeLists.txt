###############################################################################
# Copyright (c) 2015-2019, Lawrence Livermore National Security, LLC.
#
# Produced at the Lawrence Livermore National Laboratory
#
# LLNL-CODE-716457
#
# All rights reserved.
#
# This file is part of Ascent.
#
# For details, see: http://ascent.readthedocs.io/.
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


################################
# Unit Tests
################################

################################
# Core Ascent Unit Tests
################################
set(BASIC_TESTS t_apcomp_smoke
                t_apcomp_zbuffer
                t_apcomp_c_order)

set(MPI_TESTS t_apcomp_mpi_smoke
              t_apcomp_zbuffer_mpi
              t_apcomp_c_order_mpi)

if(ENABLE_OPENMP)
  set(apcomp_deps openmp)
endif()
################################
# Add main tests
################################
if (ENABLE_SERIAL)
    message(STATUS "Adding  lib unit tests")
    foreach(TEST ${BASIC_TESTS})
        add_cpp_test(TEST ${TEST} DEPENDS_ON apcomp ${apcomp_deps})
    endforeach()
endif()
################################
# Add optional tests
################################

if(MPI_FOUND AND ENABLE_MPI)
    message(STATUS "MPI enabled: Adding related unit tests")
    foreach(TEST ${MPI_TESTS})
        # this uses 4 procs
        add_cpp_mpi_test(TEST ${TEST} NUM_PROCS 4 DEPENDS_ON apcomp_mpi ${apcomp_deps})
    endforeach()
else()
    message(STATUS "MPI disabled: Skipping related tests")
endif()

configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/t_config.hpp.in"
                "${CMAKE_CURRENT_BINARY_DIR}/t_config.hpp")

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# for t_utils.hpp
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
