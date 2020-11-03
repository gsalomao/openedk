################################################################################
# Copyright (C) 2020 Gustavo Salomao
# All rights reserved.
################################################################################

#[rst
# openedk_add_test: Add test into the OpenEDK
# -------------------------------------------
#
# .. code-block:: cmake
#
# openedk_add_test(NAME <name>
#                  TIMEOUT <timeout>
#                  SOURCES <sources>
#                  LIBRARIES <libraries>)
#
# Add a test into the OpenEDK.
#
# The ``name`` is the test's name.
# The ``timeout`` is the time which the test has to complete [OPTIONAL].
# The ``sources`` is the source files that shall be compiled to the test.
# The ``libraries`` is the libraries that shall be linked to the test.
#
# Once the module is added, it creates the following target:
#   - openedk_test_<name>
#
# Example
# ^^^^^^^
#
# .. code-block: cmake
#
# openedk_add_test(NAME foo
#                  TIMEOUT 1
#                  SOURCES foo_test.cpp bar.c
#                  LIBRARIES bar::test)
#
# The above code will create a test called 'foo' with the following target:
#   - openedk_test_foo
#
#]rst
macro(openedk_add_test)
  set(options "")
  set(oneValueArgs NAME TIMEOUT)
  set(multiValueArgs LIBRARIES SOURCES)

  cmake_parse_arguments(TEST
                        "${options}"
                        "${oneValueArgs}"
                        "${multiValueArgs}"
                        ${ARGN})

  set(TEST_TARGET "openedk_test_${TEST_NAME}")
  string(TOLOWER "${TEST_TARGET}" TEST_TARGET)

  add_executable(${TEST_TARGET} ${PROJECT_TEST_RUNNER} ${TEST_SOURCES})
  target_include_directories(${TEST_TARGET} PRIVATE ${PROJECT_TEST_DIR})
  target_link_libraries(${TEST_TARGET} PRIVATE
                        ${TEST_LIBRARIES}
                        Catch2::Catch2
                        fff::fff)

  if ("${TEST_TIMEOUT}" STREQUAL "")
    set(TEST_TIMEOUT 600)
  endif ()

  if(NOT EXISTS ${PROJECT_TEST_REPORT_DIR})
    file(MAKE_DIRECTORY ${PROJECT_TEST_REPORT_DIR})
  endif()

  catch_discover_tests(${TEST_TARGET}
                       OUTPUT_PREFIX "${TEST_NAME}_"
                       PROPERTIES TIMEOUT ${TEST_TIMEOUT}
                       REPORTER junit
                       OUTPUT_DIR ${PROJECT_TEST_REPORT_DIR})
endmacro()
