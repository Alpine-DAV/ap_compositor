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
# file: src/config/CMakeLists.txt
#
###############################################################################

###############################################################################
# export everything for a cmake build to be able to import with find_package
###############################################################################

set(APCOMP_CONFIG_MK_MPI_LINK_FLAGS "")
if(MPI_FOUND)
    foreach(_lib ${MPI_C_LIBRARIES})
        set(APCOMP_CONFIG_MK_MPI_LINK_FLAGS "${APCOMP_CONFIG_MK_MPI_LINK_FLAGS} ${_lib}")
    endforeach()

    foreach(_lib ${MPI_CXX_LIBRARIES})
        set(APCOMP_CONFIG_MK_MPI_LINK_FLAGS "${APCOMP_CONFIG_MK_MPI_LINK_FLAGS} ${_lib}")
    endforeach()
endif()

# generated the config.mk
configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/apcomp_config.mk.in"
                "${CMAKE_CURRENT_BINARY_DIR}/apcomp_config.mk")

# install the config.mk
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/apcomp_config.mk" DESTINATION share/apcomp)

include(CMakePackageConfigHelpers)

# write version heler
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/APCompConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# write cmake package config file
configure_package_config_file(
  APCompConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/APCompConfig.cmake
  INSTALL_DESTINATION ${APComp_INSTALL_CONFIG_DIR}
  PATH_VARS
    APComp_INSTALL_INCLUDE_DIR
    APComp_INSTALL_LIB_DIR
    APComp_INSTALL_BIN_DIR
    APComp_INSTALL_SHARED_RESOURCES_DIR
    APComp_INSTALL_CMAKE_MODULE_DIR
    )


# install everything needed
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/APCompConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/APCompConfigVersion.cmake
    apcomp_setup_deps.cmake
    DESTINATION ${APComp_INSTALL_CMAKE_MODULE_DIR})

