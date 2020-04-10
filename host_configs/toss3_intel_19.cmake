##################################
# uberenv host-config
##################################
# chaos_5_x86_64_ib-gcc@4.9.3
##################################

# cmake from uberenv
# cmake exectuable path: /usr/workspace/wsa/visit/alpine/uberenv_libs/spack/opt/spack/chaos_5_x86_64_ib/gcc-4.9.3/cmake-3.8.2-cjuiep5cinfy7q6khr7hpsb3utzs34cd/bin/cmake

#######
# using intel 19
#######

# c compiler
set("CMAKE_C_COMPILER" "/usr/tce/packages/intel/intel-19.0.4/bin/icc" CACHE PATH "")

# cpp compiler
set("CMAKE_CXX_COMPILER" "/usr/tce/packages/intel/intel-19.0.4/bin/icpc" CACHE PATH "")

# OPENMP Support
set("ENABLE_OPENMP" "ON" CACHE PATH "")

# MPI Support
set("ENABLE_MPI" "ON" CACHE PATH "")

set("MPI_C_COMPILER" "/usr/tce/packages/mvapich2/mvapich2-2.3-intel-19.0.4/bin/mpicc" CACHE PATH "")

set("MPI_CXX_COMPILER" "/usr/tce/packages/mvapich2/mvapich2-2.3-intel-19.0.4/bin/mpic++" CACHE PATH "")
