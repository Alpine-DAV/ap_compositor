#==============================================================================
# See License.txt
#==============================================================================

set(apcomp_compositing_headers
  apcomp.hpp
  Bounds.hpp
  Error.hpp
  Image.hpp
  ImageCompositor.hpp
  Compositor.hpp
  PartialCompositor.hpp
  PayloadCompositor.hpp
  PayloadImage.hpp
  AbsorptionPartial.hpp
  EmissionPartial.hpp
  VolumePartial.hpp
  utils/PNGEncoder.hpp
  utils/lodepng.h
  )

set(apcomp_compositing_sources
  apcomp.cpp
  Image.cpp
  Compositor.cpp
  PartialCompositor.cpp
  PayloadCompositor.cpp
  utils/PNGEncoder.cpp
  utils/lodepng.cpp
  )

if (ENABLE_SERIAL)
    set(apcomp_compositing_deps apcomp_core apcomp_utils)

    if(ENABLE_OPENMP)
        list(APPEND apcomp_compositing_deps openmp)
    endif()

    blt_add_library(
      NAME apcomp_compositing
      SOURCES ${apcomp_compositing_sources}
      HEADERS ${apcomp_compositing_headers}
      DEPENDS_ON ${apcomp_compositing_deps}
      )

    target_compile_definitions(apcomp_compositing PRIVATE APCOMP_COMPILING_FLAG)
    if(ENABLE_OPENMP)
        target_compile_definitions(apcomp_compositing PRIVATE APCOMP_USE_OPENMP)
    endif()

    # Install libraries
    install(TARGETS apcomp_compositing
      EXPORT ${APComp_EXPORT_NAME}
      ARCHIVE DESTINATION ${APComp_INSTALL_LIB_DIR}
      LIBRARY DESTINATION ${APComp_INSTALL_LIB_DIR}
      RUNTIME DESTINATION ${APComp_INSTALL_BIN_DIR}
      )

    # Install headers
    install(FILES ${apcomp_compositing_headers}
      DESTINATION ${APComp_INSTALL_INCLUDE_DIR}/apcomp)
endif()

#------------------------------------------------------------------------------
# Handle parallel library
#------------------------------------------------------------------------------
set(apcomp_compositing_mpi_headers
  PartialCompositor.hpp
  PayloadCompositor.hpp
  PayloadImage.hpp

  internal/DirectSendCompositor.hpp
  internal/MPICollect.hpp
  internal/RadixKCompositor.hpp
  internal/apcomp_diy_collect.hpp
  internal/apcomp_diy_image_block.hpp
  internal/apcomp_diy_utils.hpp
  )

set(apcomp_compositing_mpi_sources
  internal/DirectSendCompositor.cpp
  internal/RadixKCompositor.cpp
  PartialCompositor.cpp
  PayloadCompositor.cpp
  )

if (MPI_FOUND)

    set(apcomp_compositing_mpi_deps mpi)

    if(ENABLE_OPENMP)
         list(APPEND apcomp_compositing_mpi_deps openmp)
    endif()


    blt_add_library(
        NAME apcomp_compositing_mpi
        SOURCES ${apcomp_compositing_sources} ${apcomp_compositing_mpi_sources}
        HEADERS ${apcomp_compositing_headers} ${apcomp_compositing_mpi_headers}
        DEPENDS_ON ${apcomp_compositing_mpi_deps}
    )

    #this is a workaround for a cmake issue linking an interface header only library statically
    target_include_directories(apcomp_compositing_mpi PRIVATE $<TARGET_PROPERTY:apcompdiy,INTERFACE_INCLUDE_DIRECTORIES>)

    target_compile_definitions(apcomp_compositing_mpi PRIVATE APCOMP_PARALLEL)
    target_compile_definitions(apcomp_compositing_mpi PRIVATE APCOMP_COMPILING_FLAG)

    if(ENABLE_OPENMP)
      target_compile_definitions(apcomp_compositing_mpi PRIVATE APCOMP_USE_OPENMP)
    endif()


    # Install libraries
    install(TARGETS apcomp_compositing_mpi
            EXPORT ${APComp_EXPORT_NAME}
            ARCHIVE DESTINATION ${APComp_INSTALL_LIB_DIR}
            LIBRARY DESTINATION ${APComp_INSTALL_LIB_DIR}
            RUNTIME DESTINATION ${APComp_INSTALL_BIN_DIR})

    # Install headers
    install(FILES ${apcomp_compositing_mpi_headers}
            DESTINATION ${APComp_INSTALL_INCLUDE_DIR}/apcomp)

endif()
