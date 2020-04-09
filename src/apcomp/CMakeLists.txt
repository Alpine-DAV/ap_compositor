#==============================================================================
# See License.txt
#==============================================================================

set(apcomp_headers
  apcomp.hpp
  bounds.hpp
  error.hpp
  image.hpp
  compositor.hpp
  partial_compositor.hpp
  payload_compositor.hpp
  payload_image.hpp
  absorption_partial.hpp
  emission_partial.hpp
  volume_partial.hpp
  utils/PNGEncoder.hpp
  utils/lodepng.h
  )

set(apcomp_sources
  apcomp.cpp
  image.cpp
  Compositor.cpp
  partial_compositor.cpp
  payload_compositor.cpp
  utils/PNGEncoder.cpp
  utils/lodepng.cpp
  )

if (ENABLE_SERIAL)
    set(apcomp_deps )

    if(ENABLE_OPENMP)
        list(APPEND apcomp_deps openmp)
    endif()

    blt_add_library(
      NAME apcomp
      SOURCES ${apcomp_sources}
      HEADERS ${apcomp_headers}
      DEPENDS_ON ${apcomp_deps}
      )

    target_compile_definitions(apcomp PRIVATE APCOMP_COMPILING_FLAG)
    if(ENABLE_OPENMP)
        target_compile_definitions(apcomp PRIVATE APCOMP_USE_OPENMP)
    endif()

    # Install libraries
    install(TARGETS apcomp
      EXPORT ${APComp_EXPORT_NAME}
      ARCHIVE DESTINATION ${APComp_INSTALL_LIB_DIR}
      LIBRARY DESTINATION ${APComp_INSTALL_LIB_DIR}
      RUNTIME DESTINATION ${APComp_INSTALL_BIN_DIR}
      )

    # Install headers
    install(FILES ${apcomp_headers}
      DESTINATION ${APComp_INSTALL_INCLUDE_DIR}/apcomp)
endif()

#------------------------------------------------------------------------------
# Handle parallel library
#------------------------------------------------------------------------------
set(apcomp_mpi_headers
  internal/DirectSendCompositor.hpp
  internal/MPICollect.hpp
  internal/RadixKCompositor.hpp
  internal/apcomp_diy_collect.hpp
  internal/apcomp_diy_image_block.hpp
  internal/apcomp_diy_utils.hpp
  )

list(APPEND apcomp_mpi_headers ${apcomp_headers})

set(apcomp_mpi_sources
  internal/DirectSendCompositor.cpp
  internal/RadixKCompositor.cpp
  )

list(APPEND apcomp_mpi_sources ${apcomp_sources})

if (MPI_FOUND)

    set(apcomp_mpi_deps mpi)

    if(ENABLE_OPENMP)
         list(APPEND apcomp_mpi_deps openmp)
    endif()


    blt_add_library(
        NAME apcomp_mpi
        SOURCES ${apcomp_sources} ${apcomp_mpi_sources}
        HEADERS ${apcomp_headers} ${apcomp_mpi_headers}
        DEPENDS_ON ${apcomp_mpi_deps}
    )

    #this is a workaround for a cmake issue linking an interface header only library statically
    target_include_directories(apcomp_mpi PRIVATE $<TARGET_PROPERTY:apcompdiy,INTERFACE_INCLUDE_DIRECTORIES>)

    target_compile_definitions(apcomp_mpi PRIVATE APCOMP_PARALLEL)
    target_compile_definitions(apcomp_mpi PRIVATE APCOMP_COMPILING_FLAG)

    if(ENABLE_OPENMP)
      target_compile_definitions(apcomp_mpi PRIVATE APCOMP_USE_OPENMP)
    endif()


    # Install libraries
    install(TARGETS apcomp_mpi
            EXPORT ${APComp_EXPORT_NAME}
            ARCHIVE DESTINATION ${APComp_INSTALL_LIB_DIR}
            LIBRARY DESTINATION ${APComp_INSTALL_LIB_DIR}
            RUNTIME DESTINATION ${APComp_INSTALL_BIN_DIR})

    # Install headers
    install(FILES ${apcomp_mpi_headers}
            DESTINATION ${APComp_INSTALL_INCLUDE_DIR}/apcomp)

endif()
