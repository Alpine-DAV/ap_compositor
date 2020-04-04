#ifndef APCOMP_H_HPP
#define APCOMP_H_HPP

#include <apcomp/apcomp_exports.h>
#include <string>

namespace apcomp
{

  APCOMP_API bool IsMPIEnabled();
  APCOMP_API int  GetMPIRank();
  APCOMP_API int  GetMPISize();

  APCOMP_API void SetMPICommHandle(int mpi_comm_id);
  APCOMP_API int  GetMPICommHandle();
}
#endif
