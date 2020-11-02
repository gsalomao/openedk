# Copyright (C) 2020 Gustavo Salomao
# All rights reserved.

#----------------------------------- Setup ------------------------------------
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
