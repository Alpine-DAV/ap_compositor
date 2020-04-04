#include "apcomp.hpp"
#include "Error.hpp"
#include <sstream>

#ifdef APCOMP_PARALLEL
#include <mpi.h>
#endif

namespace apcomp
{

static int g_mpi_comm_id = -1;


//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
#ifdef APCOMP_PARALLEL // mpi case
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
void
CheckCommHandle()
{
  if(g_mpi_comm_id == -1)
  {
    std::stringstream msg;
    msg<<"VTK-h internal error. There is no valid MPI comm available. ";
    msg<<"It is likely that VTKH.SetMPICommHandle(int) was not called.";
    throw Error(msg.str());
  }
}

//---------------------------------------------------------------------------//
void
SetMPICommHandle(int mpi_comm_id)
{
  g_mpi_comm_id = mpi_comm_id;
#ifdef VTKH_ENABLE_LOGGING
  DataLogger::GetInstance()->SetRank(GetMPIRank());
#endif
}

//---------------------------------------------------------------------------//
int
GetMPICommHandle()
{
  CheckCommHandle();
  return g_mpi_comm_id;
}

//---------------------------------------------------------------------------//
int
GetMPIRank()
{
  int rank;
  MPI_Comm comm = MPI_Comm_f2c(GetMPICommHandle());
  MPI_Comm_rank(comm, &rank);
  return rank;
}

//---------------------------------------------------------------------------//
int
GetMPISize()
{
  int size;
  MPI_Comm comm = MPI_Comm_f2c(GetMPICommHandle());
  MPI_Comm_size(comm, &size);
  return size;
}

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
#else // non-mpi case
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
void
CheckCommHandle()
{
  std::stringstream msg;
  msg<<"APComp internal error. Trying to access MPI comm in non-mpi lib.";
  msg<<"Are you using the right library (apcomp vs apcomp_mpi)?";
  throw Error(msg.str());
}

//---------------------------------------------------------------------------//
void
SetMPICommHandle(int mpi_comm_id)
{
  std::stringstream msg;
  msg<<"APComp internal error. Trying to access MPI comm in non-mpi lib.";
  msg<<"Are you using the right library (apcomp vs apcomp_mpi)?";
  throw Error(msg.str());
}

//---------------------------------------------------------------------------//
int
GetMPICommHandle()
{
  std::stringstream msg;
  msg<<"APComp internal error. Trying to access MPI comm in non-mpi lib.";
  msg<<"Are you using the right library (apcomp vs apcomp_mpi)?";
  throw Error(msg.str());
  return g_mpi_comm_id;
}

//---------------------------------------------------------------------------//
int
GetMPIRank()
{
  return 0;
}

//---------------------------------------------------------------------------//
int
GetMPISize()
{
  return 1;
}
//---------------------------------------------------------------------------//
#endif
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
bool
IsMPIEnabled()
{
#ifdef APCOMP_PARALLEL
  return true;
#else
  return false;
#endif
}


}
