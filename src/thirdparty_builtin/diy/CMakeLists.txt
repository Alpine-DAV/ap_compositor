#==============================================================================
# See License.txt
#==============================================================================

########
# TODO: blt_register library support interface libs
########

add_library(apcompdiy INTERFACE)
target_include_directories(apcompdiy INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${APComp_INSTALL_INCLUDE_DIR}/apcomp/thirdparty_builtin>  # <prefix>/apcomp/thirdparty_builtin/
  )


########
# This is our DIY. There are are many like it, but this one is ours
# This is completely internal to apcomp
#######
