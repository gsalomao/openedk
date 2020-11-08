# Copyright (C) 2020 Gustavo Salomao
# All rights reserved.

include(FetchContent)

set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/vendor)

set(REPOSITORY https://github.com/meekrosoft/fff.git)
set(VERSION v1.0)

message(STATUS "Downloading fff")

FetchContent_Declare(fff GIT_REPOSITORY ${REPOSITORY} GIT_TAG ${VERSION})
FetchContent_Populate(fff)

add_library(fff INTERFACE)
add_library(fff::fff ALIAS fff)
target_include_directories(fff INTERFACE ${fff_SOURCE_DIR})
