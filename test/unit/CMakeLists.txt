# Copyright (C) 2020 Gustavo Salomao
# All rights reserved.

#----------------------------------- Setup ------------------------------------
project(${PROJECT_NAME} LANGUAGES C CXX)

# C++ for Catch2 (Unit Test Framework)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_TEST_RUNNER ${PROJECT_TEST_DIR}/test_runner.cpp)
set(PROJECT_TEST_REPORT_DIR ${CMAKE_BINARY_DIR}/test-results)

find_package(Catch2)
find_package(fff)

file(GLOB_RECURSE COVERAGE_FILES "${CMAKE_BINARY_DIR}/*.gcda"
  "${CMAKE_BINARY_DIR}/*.gcdO")

if (NOT COVERAGE_FILES STREQUAL "")
  file(REMOVE ${COVERAGE_FILES})
endif ()

#--------------------------------- Coverage -----------------------------------
if (ENABLE_COVERAGE)
  message(STATUS "Adding code coverage")
  find_program(GCOVR gcovr)

  if ("${GCOVR}" STREQUAL "GCOVR-NOTFOUND")
    message(FATAL_ERROR "gcovr not found!")
  endif ()

  add_custom_target(coverage)
  add_custom_command(TARGET coverage
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/coverage
    COMMAND ${GCOVR} -r ${CMAKE_SOURCE_DIR}
      -e vendor
      -e CMakeFiles/
      -e ${CMAKE_SOURCE_DIR}/test/
      --html-details coverage/index.html
      --html-title "OpenEDK Code Coverage Report"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif ()

#----------------------------------- Tests ------------------------------------
