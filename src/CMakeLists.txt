#==============================================================================
# See License.txt
#==============================================================================

################################
# apcomp
################################

################################
# cmake policy selections
################################
# avoid warnings for project commands w/o VERSION
cmake_policy(SET CMP0048 NEW)

project(APComp VERSION "0.0.1")

set(APComp_EXPORT_NAME "APCompTargets")
if (NOT DEFINED APComp_INSTALL_INCLUDE_DIR)
  set(APComp_INSTALL_INCLUDE_DIR "include")
endif()
if (NOT DEFINED APComp_INSTALL_CONFIG_DIR)
  set(APComp_INSTALL_CONFIG_DIR "lib")
endif()
if (NOT DEFINED APComp_INSTALL_LIB_DIR)
  set(APComp_INSTALL_LIB_DIR "lib")
endif()
if (NOT DEFINED APComp_INSTALL_BIN_DIR)
  set(APComp_INSTALL_BIN_DIR "bin")
endif()
if (NOT DEFINED APComp_INSTALL_SHARED_RESOURCES_DIR)
  set(APComp_INSTALL_SHARED_RESOURCES_DIR "share/apcomp")
endif()
if (NOT DEFINED APComp_INSTALL_CMAKE_MODULE_DIR)
  set(APComp_INSTALL_CMAKE_MODULE_DIR "${APComp_INSTALL_SHARED_RESOURCES_DIR}/cmake")
endif()

set(APComp_CMAKE_MODULE_PATH ${APComp_SOURCE_DIR}/cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${APComp_CMAKE_MODULE_PATH})

################################
# Some CMake module includes.
################################
include(CMakeDependentOption)

# Set default build types
include(APCompBuildType)

################################
# Build Options
################################
option(BUILD_SHARED_LIBS  "Build shared libraries"    ON)
option(ENABLE_TESTS       "Build tests"               ON)
option(ENABLE_MPI         "Build MPI Support"         ON)
option(ENABLE_SERIAL      "Build Non-MPI Support"     ON)

if(NOT ENABLE_SERIAL AND NOT ENABLE_MPI)
  message(FATAL_ERROR "No libraries are built. "
    "Please set ENABLE_SERIAL, ENABLE_MPI or both to ON")
endif()


cmake_minimum_required(VERSION 3.9)

################################
# Set BLT Options
################################

# don't use BLT's all warnings feature
set(ENABLE_ALL_WARNINGS OFF CACHE INTERNAL "")

################################
# Init BLT
################################
if (NOT BLT_CXX_STD)
  set(BLT_CXX_STD "c++11" CACHE STRING "")
endif()

# if BLT_SOURCE_DIR is not set - use "blt" as default
if(NOT BLT_SOURCE_DIR)
    set(BLT_SOURCE_DIR "blt")
endif()

# init blt using BLT_SOURCE_DIR
include(${BLT_SOURCE_DIR}/SetupBLT.cmake)

################################
# Basic CMake Setup
################################
include(cmake/CMakeBasics.cmake)

################################
# Setup tests helpers
################################
include(cmake/SetupTests.cmake)

################################
# Setup project wide includes
################################
include(cmake/SetupIncludes.cmake)

#------------------------------------------------------------------------------
# Determine source version.
include(APCompDetermineVersion)
find_package(Git QUIET)
file(STRINGS version.txt version_txt)
extract_version_components("${version_txt}" "APComp")
determine_version(${APComp_SOURCE_DIR} "${GIT_EXECUTABLE}" "APComp")
#------------------------------------------------------------------------------

add_subdirectory(thirdparty_builtin)

add_subdirectory(apcomp)

if(ENABLE_TESTS)
  add_subdirectory(tests)
endif()

################################
# Add examples
################################
add_subdirectory(examples)

################################
# Add our config helpers
################################
add_subdirectory(config)

################################
# Create CMake importable
# exports for all of our targets
################################
install(EXPORT ${APComp_EXPORT_NAME} DESTINATION lib/cmake)
