#######################################################################
# This file takes care of configuring Strophe to build with the settings
# given in CMake. It creates the necessary config.h file and will
# also prepare package files for pkg-config and CMake.
#######################################################################

# should we build static libs?
if (Strophe_STATIC)
  set(Strophe_LIB_TYPE STATIC)
else ()
  set(Strophe_LIB_TYPE SHARED)
endif ()

# determine config values depending on build options
set(Strophe_STATIC_LIB 0)
if (Strophe_STATIC)
  set(Strophe_STATIC_LIB 1)
endif()
add_definitions(-DHAVE_Strophe_BUILDSETTINGS_H)

if (Strophe_TEST_BIG_ENDIAN)
  set(Strophe_CONFIG_BIG_ENDIAN 1)
else ()
  set(Strophe_CONFIG_LITTLE_ENDIAN 1)
endif ()

if (Strophe_STANDALONE_BUILD)
  set(CMAKE_USE_RELATIVE_PATHS true)
  set(CMAKE_SUPPRESS_REGENERATION true)
endif()
