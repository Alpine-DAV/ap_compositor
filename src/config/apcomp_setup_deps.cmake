# Copyright (c) Lawrence Livermore National Security, LLC and other APComp
# Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
# other details. No copyright assignment is required to contribute to APComp.


if(APCOMP_OPENMP_ENABLED)
    # config openmp if not already found
    if(NOT TARGET OpenMP::OpenMP_CXX)
        find_package(OpenMP REQUIRED)
    endif()
endif()

