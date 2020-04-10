#######
# using ibm clang
#######

# c compiler
set("CMAKE_C_COMPILER" "/usr/tce/packages/clang/clang-ibm-2019.10.03/bin/clang" CACHE PATH "")

# cpp compiler
set("CMAKE_CXX_COMPILER" "/usr/tce/packages/clang/clang-ibm-2019.10.03/bin/clang++" CACHE PATH "")

# OPENMP Support
set("ENABLE_OPENMP" "ON" CACHE PATH "")

# MPI Support
set("ENABLE_MPI" "ON" CACHE PATH "")

set("MPI_C_COMPILER" "/usr/tce/packages/spectrum-mpi/spectrum-mpi-rolling-release-clang-ibm-2019.10.03/bin/mpicc" CACHE PATH "")

set("MPI_CXX_COMPILER" "/usr/tce/packages/spectrum-mpi/spectrum-mpi-rolling-release-clang-ibm-2019.10.03/bin/mpic++" CACHE PATH "")
