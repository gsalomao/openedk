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

find_package(Catch2)
find_package(fff)

#----------------------------------- Tests ------------------------------------
