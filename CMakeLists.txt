################################################################################
# Copyright (C) 2020 Gustavo Salomao
# All rights reserved.
################################################################################

#----------------------------------- Setup -------------------------------------
cmake_minimum_required(VERSION 3.13)
project(openedk LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Prevent in-source build
if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. "
          "Please make a new directory (called build directory) and run "
          "CMake from there.")
endif ()

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif ()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if (${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
  include(cmake/ModuleHelper.cmake)
endif ()

if (${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
  include(cmake/TestHelper.cmake)
endif ()

if (ENABLE_COVERAGE AND ${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
  set(CMAKE_C_OUTPUT_EXTENSION_REPLACE 1)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
  set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
endif ()

#---------------------------------- Sources ------------------------------------
add_subdirectory(src)

#----------------------------------- Tests -------------------------------------
if (${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
  enable_testing()
  add_subdirectory(test/unit)
endif ()

#------------------------------ Static Analysis --------------------------------
find_program(CPPCHECK cppcheck)

if (CPPCHECK AND ${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
  message(STATUS "Adding cppcheck")

  add_custom_target(cppcheck)
  add_custom_command(TARGET cppcheck
    COMMAND ${CPPCHECK} -q
      --std=c99
      --enable=all
      --suppress=unusedFunction
      --suppress=missingIncludeSystem
      -I${PROJECT_SOURCE_DIR}/include
      -I${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/)
else ()
  message(WARNING "cppcheck not found! Static check disabled.")
endif ()
