# Copyright (c) 2017–2020 Antti Kivi
# Licensed under the Effective Elegy Licence

cmake_minimum_required(VERSION 2.8.12)
project(anthem)

# TODO: Use target_compile_features

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#===------------------------------------------------------------------------===#
#==- Modules ---------------------------------------------------------------===#
#===------------------------------------------------------------------------===#

include(CompilerFlags)
include(Definitions)
include(ExternalSources)
include(Install)
include(StdDefinitions)
include(Targets)
include(Variables)

#===------------------------------------------------------------------------===#
#==- CMake Variables -------------------------------------------------------===#
#===------------------------------------------------------------------------===#

set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)

#===------------------------------------------------------------------------===#
#==- Options ---------------------------------------------------------------===#
#===------------------------------------------------------------------------===#

#==- Build Options Added by the Composer -----------------------------------===#

option(COMPOSER_BUILD_TEST "Build the tests" OFF)
option(COMPOSER_BUILD_BENCHMARK "Build the benchmarkings" OFF)
option(COMPOSER_BUILD_DOCS "Build the documentation" OFF)
option(COMPOSER_CODE_COVERAGE "Enable code coverage reporting" OFF)

#==- Obliging Ode Build Options --------------------------------------------===#

option(ODE_BUILD_STATIC "Build the static Obliging Ode library" OFF)
option(ODE_BUILD_SHARED "Build the shared Obliging Ode library" OFF)
# # option(ODE_USE_SDL_DEBUG_SUFFIX
# #     "Link Obliging Ode against SDL with debug suffix on Windows builds" OFF)
# # option(ODE_ADD_GOOGLE_TEST_SOURCE
#     "Build Google Test source files with the Obliging Ode sources" OFF)
# option(ODE_SKIP_BUILD
#     "Indicate that the binaries won't be actually compiled" OFF)

#==- Unsung Anthem Build Options -------------------------------------------===#

# option(ANTHEM_BUILD_STATIC "Build the static Unsung Anthem library" OFF)
# option(ANTHEM_BUILD_SHARED "Build the shared Unsung Anthem library" OFF)

#==- Obliging Ode Feature Options ------------------------------------------===#

option(ENABLE_ASSERTIONS "Option for enabling assertions" ON)
option(DEVELOPER_BUILD "Enable developer mode" OFF)
option(STD_CLOCK
    "Use the C++ standard library clock instead of the SDL clock" OFF)
option(NULL_TEST_SINK "Log the tests to a null sink" ON)
option(MULTITHREADING "Enable multithreading in the product" ON)
option(DISABLE_GL_CALLS "Disable the OpenGL calls in Obliging Ode" OFF)

#===------------------------------------------------------------------------===#
#==- Variable Assertions ---------------------------------------------------===#
#===------------------------------------------------------------------------===#

#==- Composer Variable Assertions ------------------------------------------===#

assert_variable(COMPOSER_CPP_STD "C++ standard version" "c++2a and c++17")
assert_variable(COMPOSER_LOCAL_PREFIX "dependency installation directory")
assert_variable(COMPOSER_ODE_VERSION "Obliging Ode version")
assert_variable(COMPOSER_ANTHEM_VERSION "Unsung Anthem version")
assert_variable(COMPOSER_OPENGL_VERSION_MAJOR "OpenGL major version")
assert_variable(COMPOSER_OPENGL_VERSION_MINOR "OpenGL minor version")

#==- Obliging Ode Variable Assertions --------------------------------------===#

assert_variable(SCRIPTS_DIRECTORY "Lua scripts base directory name")

#===------------------------------------------------------------------------===#
#==- Conditional Variable Assertions ---------------------------------------===#
#===------------------------------------------------------------------------===#

# if(ODE_ADD_GOOGLE_TEST_SOURCE)
#   assert_variable(ODE_GOOGLE_TEST_DIRECTORY "Google Test source directory")
# endif()

#===------------------------------------------------------------------------===#
#==- Variable Statuses -----------------------------------------------------===#
#===------------------------------------------------------------------------===#

default_value(COMPOSER_ODE_NAME ode_name_not_set "Obliging Ode name")
default_value(COMPOSER_ODE_TARGET ode_name_not_set "Obliging Ode binaries name")
# default_value(ODE_STATIC_NAME
#     ${ODE_NAME}-static "Obliging Ode static library name")
# default_value(ODE_SHARED_NAME
#     ${ODE_NAME}-shared "Obliging Ode shared library name")

default_value(COMPOSER_ANTHEM_NAME anthem_name_not_set "name")
default_value(COMPOSER_ANTHEM_TARGET anthem_name_not_set "executable name")
# default_value(ANTHEM_STATIC_NAME
#     ${ANTHEM_NAME}-static "Unsung Anthem static library name")
# default_value(ANTHEM_SHARED_NAME
#     ${ANTHEM_NAME}-shared "Unsung Anthem shared library name")
default_value(COMPOSER_ANTHEM_TEST_TARGET test-${COMPOSER_ANTHEM_TARGET}
    "Unsung Anthem test executable name")

# print_status_if_defined(ODE_STDLIB "C++ standard library")
# print_status_if_defined(ODE_RPATH "the rpath")

# print_status_if_defined(ODE_MSVC_RUNTIME_LIBRARY "the MSVC runtime library")

#===------------------------------------------------------------------------===#
#==- Definitions and Flags -------------------------------------------------===#
#===------------------------------------------------------------------------===#

set(CPP_STD)

set_cpp_definitions(${COMPOSER_CPP_STD})
set_cpp_feature_definitions()

print_status(CPP_STD "Obliging Ode C++ standard")

set_cpp_std_flags(${CPP_STD})
set_linker_flags()

if(COMPOSER_CODE_COVERAGE)
  set_coverage_flags()
endif()

add_version_definitions()
add_opengl_definitions()
add_directory_definitions()
add_feature_definitions()

#===------------------------------------------------------------------------===#
#==- Tools -----------------------------------------------------------------===#
#===------------------------------------------------------------------------===#

if(COMPOSER_BUILD_DOCS)
  find_package(Doxygen REQUIRED)
endif()

#===------------------------------------------------------------------------===#
#==- Libraries -------------------------------------------------------------===#
#===------------------------------------------------------------------------===#

set(ODE_LIBRARIES)

if(NOT WIN32)
  message(STATUS "Looking for SDL libraries")
  find_package(SDL2 REQUIRED HINTS ${COMPOSER_LOCAL_PREFIX})
  list(APPEND ODE_LIBRARIES ${SDL2_LIBRARIES})
endif()

if(COMPOSER_BUILD_TEST AND NOT ODE_ADD_GOOGLE_TEST_SOURCE)
  message(STATUS "Looking for Google Test libraries")
  find_library(GTEST_LIBRARY gtestd HINTS "${COMPOSER_LOCAL_PREFIX}/lib")
  list(APPEND ODE_LIBRARIES ${GTEST_LIBRARY})
elseif(COMPOSER_BUILD_TEST AND ODE_ADD_GOOGLE_TEST_SOURCE)
  list(APPEND ODE_LIBRARIES "gtest")
endif()

if(ODE_TEST_BENCHMARKING)
  if(WIN32)
    list(APPEND ODE_LIBRARIES "shlwapi")
  endif()
  message(STATUS "Looking for Google Benchmark libraries")
  find_library(BENCHMARK_LIBRARY benchmark
      HINTS "${COMPOSER_LOCAL_PREFIX}/lib")
  list(APPEND ODE_LIBRARIES ${BENCHMARK_LIBRARY})
endif()

if(UNIX)
  if(NOT APPLE)
    message(STATUS "Setting threading libraries manually")
    list(APPEND ODE_LIBRARIES "dl" "pthread")
  endif()
else()
  if(WIN32)
    message(STATUS "Setting SDL libraries manually")
    if(ODE_USE_SDL_DEBUG_SUFFIX)
      message(STATUS "Linking against SDL libraries with debug suffix")
      list(APPEND ODE_LIBRARIES "opengl32" "SDL2maind" "SDL2d")
    else()
      list(APPEND ODE_LIBRARIES "opengl32" "SDL2main" "SDL2")
    endif()
  endif()
endif()

find_library(LUA_LIBRARY lua HINTS "${COMPOSER_LOCAL_PREFIX}/lib")

list(APPEND ODE_LIBRARIES ${LUA_LIBRARY})

print_status_plural(ODE_LIBRARIES "libraries")

#===------------------------------------------------------------------------===#
#==- Search Paths ----------------------------------------------------------===#
#===------------------------------------------------------------------------===#

if(WIN32)
  link_directories(${COMPOSER_LOCAL_PREFIX}/lib)
endif()

if(NOT WIN32)
  include_directories(${SDL2_INCLUDE_DIRS})
endif()

include_directories(${COMPOSER_LOCAL_PREFIX}/include)

include_directories(include)
include_directories(lib)
include_directories(src)

if(COMPOSER_BUILD_TEST)
  include_directories(test)
endif()

#===------------------------------------------------------------------------===#
#==- Source Files ----------------------------------------------------------===#
#===------------------------------------------------------------------------===#

set(ODE_INCLUDES)
set(ODE_LIB_INCLUDES)
set(ODE_TEST_INCLUDES)
set(ODE_SOURCES)
set(ODE_TEST_SOURCES)
set(ODE_BENCHMARK_SOURCES)

set(ANTHEM_INCLUDES)
set(ANTHEM_LIB_INCLUDES)
set(ANTHEM_SOURCES)
set(ANTHEM_LIB_SOURCES)
set(ANTHEM_TEST_SOURCES)
set(ANTHEM_BENCHMARK_SOURCES)

set(ODE_SCRIPTS)
set(ODE_TEST_SCRIPTS)

set(ANTHEM_SCRIPTS)
set(ANTHEM_LIB_SCRIPTS)
set(ANTHEM_TEST_SCRIPTS)

add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(script)
add_subdirectory(test)

if(NOT CMAKE_EXPORT_COMPILE_COMMANDS AND NOT ODE_SKIP_BUILD)
  set_glad_sources()
endif()

if(ODE_ADD_GOOGLE_TEST_SOURCE)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  add_subdirectory(${ODE_GOOGLE_TEST_DIRECTORY})
endif()

#===------------------------------------------------------------------------===#
#==- Targets ---------------------------------------------------------------===#
#===------------------------------------------------------------------------===#

if(DEFINED ODE_RPATH AND APPLE)
  set(CMAKE_MACOSX_RPATH 1)
endif()

create_targets()

#===------------------------------------------------------------------------===#
#==- Install Targets -------------------------------------------------------===#
#===------------------------------------------------------------------------===#

if(NOT WIN32)
  create_install_targets()
endif()

#===------------------------------------------------------------------------===#
#==- Documentation ---------------------------------------------------------===#
#===------------------------------------------------------------------------===#

add_subdirectory(docs)

#===------------------------------------------------------------------------===#
#==- Compilation and Linking -----------------------------------------------===#
#===------------------------------------------------------------------------===#

# TODO Consider adding the option
if(ODE_VERBOSE_BUILD)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -v")
endif()

message(STATUS "The CMake build type is set to ${CMAKE_BUILD_TYPE}")
message(STATUS
    "The CMake installation prefix is set to ${CMAKE_INSTALL_PREFIX}")
message(STATUS
    "The CMake library installation prefix is set to ${CMAKE_INSTALL_LIBDIR}")
message(STATUS "The C++ compile flags are set to ${CMAKE_CXX_FLAGS}")
message(STATUS
    "The C++ executable linker flags are set to ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "The C compiler flag is set to ${CMAKE_C_COMPILER}")
message(STATUS "The C++ compiler flag is set to ${CMAKE_CXX_COMPILER}")
message(STATUS "The C compiler environment variable is set to $ENV{CC}")
message(STATUS "The C++ compiler environment variable is set to $ENV{CXX}")

get_directory_property(COMPILE_DEFS COMPILE_DEFINITIONS)

message(STATUS "The compile definitions are ${COMPILE_DEFS}")
