#######
# using xlc
#######

# c compiler
set("CMAKE_C_COMPILER" "/usr/tce/packages/xl/xl-2020.03.18/bin/xlc" CACHE PATH "")

# cpp compiler
set("CMAKE_CXX_COMPILER" "/usr/tce/packages/xl/xl-2020.03.18/bin/xlc++" CACHE PATH "")

# OPENMP Support
set("ENABLE_OPENMP" "ON" CACHE PATH "")

# MPI Support
set("ENABLE_MPI" "ON" CACHE PATH "")

set("MPI_C_COMPILER" "/usr/tce/packages/spectrum-mpi/spectrum-mpi-rolling-release-xl-2020.03.18/bin/mpicc" CACHE PATH "")

set("MPI_CXX_COMPILER" "/usr/tce/packages/spectrum-mpi/spectrum-mpi-rolling-release-xl-2020.03.18/bin/mpic++" CACHE PATH "")
