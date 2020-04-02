#==============================================================================
# See License.txt
#==============================================================================
set(Headers
  lodepng.h
  )

set(Sources
  lodepng.cpp
  )




blt_add_library(
  NAME vtkh_lodepng
  SOURCES ${Sources}
  )

# install target for vtkh_lodepng
install(TARGETS apcomp_lodepng
  EXPORT ${VTKh_EXPORT_NAME}
  ARCHIVE DESTINATION ${VTKh_INSTALL_LIB_DIR}
  LIBRARY DESTINATION ${VTKh_INSTALL_LIB_DIR}
  RUNTIME DESTINATION ${VTKh_INSTALL_BIN_DIR}
  )

# Install headers
install(FILES ${Headers}
  DESTINATION ${VTKh_INSTALL_INCLUDE_DIR}/apcomp/thirdparty_builtin/lodepng
  )

# Install others files.
install(FILES License.txt README.md
  DESTINATION ${VTKh_INSTALL_SHARED_RESOURCES_DIR}/thirdparty_builtin/lodepng
  )
