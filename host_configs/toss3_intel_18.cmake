#######
# using intel 19
#######

# c compiler
set("CMAKE_C_COMPILER" "/usr/tce/packages/intel/intel-18.0.2/bin/icc" CACHE PATH "")

# cpp compiler
set("CMAKE_CXX_COMPILER" "/usr/tce/packages/intel/intel-18.0.2/bin/icpc" CACHE PATH "")

# OPENMP Support
set("ENABLE_OPENMP" "ON" CACHE PATH "")

# MPI Support
set("ENABLE_MPI" "ON" CACHE PATH "")

set("MPI_C_COMPILER" "/usr/tce/packages/mvapich2/mvapich2-2.3-intel-18.0.2/bin/mpicc" CACHE PATH "")

set("MPI_CXX_COMPILER" "/usr/tce/packages/mvapich2/mvapich2-2.3-intel-18.0.2/bin/mpic++" CACHE PATH "")
