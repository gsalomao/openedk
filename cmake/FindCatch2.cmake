################################################################################
# Copyright (C) 2020 Gustavo Salomao
# All rights reserved.
################################################################################

#------------------------------------------------------------------------------
# The following targets will be created:
#   - Catch2::Catch2          -> Target for the Catch2 library
#
# The following variables will be set:
#   - Catch2_FOUND            -> Indicate that the package has been found
#------------------------------------------------------------------------------

include(FetchContent)

set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/vendor)

set(REPOSITORY https://github.com/catchorg/Catch2.git)
set(VERSION v2.13.3)

message(STATUS "Downloading Catch2")

FetchContent_Declare(catch2 GIT_REPOSITORY ${REPOSITORY} GIT_TAG ${VERSION})
FetchContent_Populate(catch2)

add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
include(${catch2_SOURCE_DIR}/contrib/Catch.cmake)
set(Catch2_FOUND true)
