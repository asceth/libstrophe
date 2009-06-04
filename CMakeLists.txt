######################################################################
# Strophe Build System
# Welcome to the CMake build system for Strophe.
######################################################################

cmake_minimum_required(VERSION 2.6)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
cmake_policy(SET CMP0003 NEW)

project(Strophe)

# Include necessary submodules
set(CMAKE_MODULE_PATH
  "${Strophe_SOURCE_DIR}/cmake"
)
include(CMakeDependentOption)
set(Strophe_WORK_DIR ${Strophe_BINARY_DIR})


#####################################################################
# Set up the basic build environment
#####################################################################

if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()
set(CONFIGURATION ${CMAKE_BUILD_TYPE})

if (NOT APPLE)
  # Create debug libraries with _d postfix
  set(CMAKE_DEBUG_POSTFIX "_d")
endif ()

# Set compiler specific build flags
if (CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-msse)
endif ()
if (MSVC)
  add_definitions(/fp:fast)
endif ()

if (CMAKE_COMPILER_IS_GNUCXX)
  # Test for GCC visibility
  include(CheckCXXCompilerFlag)
  check_cxx_compiler_flag(-fvisibility=hidden Strophe_GCC_VISIBILITY)
  if (Strophe_GCC_VISIBILITY)
    # determine gcc version
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion
      OUTPUT_VARIABLE Strophe_GCC_VERSION)
    message(STATUS "Detected g++ ${Strophe_GCC_VERSION}")
    message(STATUS "Enabling GCC visibility flags")
    set(Strophe_GCC_VISIBILITY_FLAGS "-DStrophe_GCC_VISIBILITY -fvisibility=hidden")

    # check if we can safely add -fvisibility-inlines-hidden
    string(TOLOWER "${CMAKE_BUILD_TYPE}" Strophe_BUILD_TYPE)
    if (Strophe_BUILD_TYPE STREQUAL "debug" AND Strophe_GCC_VERSION VERSION_LESS "4.2")
      message(STATUS "Skipping -fvisibility-inlines-hidden due to possible bug in g++ < 4.2")
    else ()
      set(Strophe_GCC_VISIBILITY_FLAGS "${Strophe_GCC_VISIBILITY_FLAGS} -fvisibility-inlines-hidden")
    endif ()
  endif (Strophe_GCC_VISIBILITY)
endif (CMAKE_COMPILER_IS_GNUCXX)

# determine system endianess
include(TestBigEndian)
test_big_endian(Strophe_TEST_BIG_ENDIAN)

# Add Strophe engine include path
include_directories("${Strophe_SOURCE_DIR}/")
include_directories("${Strophe_BINARY_DIR}/include")

# definitions for samples
set(Strophe_LIBRARIES LibStrophe)

# Specify build paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${Strophe_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${Strophe_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${Strophe_BINARY_DIR}/bin")
if (WIN32 OR APPLE)
  if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    # We don't want to install in default system location, install is really for the SDK, so call it that
    SET(CMAKE_INSTALL_PREFIX
	  "${Strophe_BINARY_DIR}/sdk" CACHE PATH "Strophe install prefix" FORCE
    )
  endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
endif(WIN32 OR APPLE)



######################################################################
# Provide user options to customise the build process
######################################################################

# Customise what to build
option(Strophe_STATIC "Static build" FALSE)
if (APPLE)
  option(Strophe_NO_FRAMEWORK "Do not build Strophe as a framework" TRUE)
endif ()
option(Strophe_BUILD_SAMPLES "Build Strophe demos" TRUE)

option(Strophe_FULL_RPATH "Build executables with the full required RPATH to run from their install location." FALSE)
option(Strophe_STANDALONE_BUILD "Generate build files that do not reference CMake (e.g. source distro)" FALSE)



###################################################################
# configure global build settings based on selected build options
###################################################################
include(ConfigureBuild)


##################################################################
# Now setup targets
##################################################################

# Setup Expat
add_subdirectory(deps)

# Setup Strophe engine project
add_subdirectory(src)

# Setup samples
if(Strophe_BUILD_SAMPLES)
  add_subdirectory(examples)
endif()

# Install CMake modules
add_subdirectory(cmake)



