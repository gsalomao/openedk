/*******************************************************************************
 * Copyright (C) 2020 Gustavo Salomao
 * All rights reserved.
 ******************************************************************************/

#include <catch2/catch.hpp>

extern "C"
{
#include "openedk/container/array.h"
}

SCENARIO("array: initialize")
{
    const uint32_t buffer_size{8};
    uint32_t buffer[buffer_size] = {0};

    GIVEN("a not initizlized array")
    {
        array_t array = {0};

        WHEN("initialize it")
        {
            bool result = array_init(&array, buffer, sizeof(buffer),
                                     sizeof(*buffer));

            THEN("should return true")
            {
                REQUIRE(result == true);
            }
            THEN("should set buffer")
            {
                REQUIRE(array.buffer == buffer);
            }
            THEN("should set capacity")
            {
                REQUIRE(array.capacity == buffer_size);
            }
            THEN("should set element size")
            {
                REQUIRE(array.elem_size == sizeof(*buffer));
            }
            THEN("should set size to zero")
            {
                REQUIRE(array.size == 0);
            }
        }
        WHEN("initialize it with null buffer")
        {
            bool result = array_init(&array, NULL, 10, 1);

            THEN("should return false")
            {
                REQUIRE(result == false);
            }
        }
        WHEN("initialize it with buffer size equals to zero")
        {
            bool result = array_init(&array, buffer, 0, sizeof(*buffer));

            THEN("should return false")
            {
                REQUIRE(result == false);
            }
        }
        WHEN("initialize it with element size equals to zero")
        {
            bool result = array_init(&array, buffer, sizeof(buffer), 0);

            THEN("should return false")
            {
                REQUIRE(result == false);
            }
        }
    }
    GIVEN("an invalid array")
    {
        WHEN("initialize it")
        {
            bool result = array_init(NULL, buffer, sizeof(buffer),
                                     sizeof(*buffer));

            THEN("should return false")
            {
                REQUIRE(result == false);
            }
        }
    }
}

SCENARIO("array: get buffer")
{
    const uint32_t buffer_size{8};
    uint32_t buffer[buffer_size] = {0};

    GIVEN("an initialized array")
    {
        array_t array = {0};
        array_init(&array, buffer, sizeof(buffer), sizeof(*buffer));

        WHEN("get buffer")
        {
            uint32_t* buf = static_cast<uint32_t*>(array_get_buffer(&array));

            THEN("should return the array buffer")
            {
                REQUIRE(buf == buffer);
            }
        }
    }
    GIVEN("an invalid array")
    {
        WHEN("get buffer")
        {
            uint32_t* buf = static_cast<uint32_t*>(array_get_buffer(nullptr));

            THEN("should return null pointer")
            {
                REQUIRE(buf == nullptr);
            }
        }
    }
}

SCENARIO("array: get size")
{
    const uint32_t buffer_size{8};
    uint32_t buffer[buffer_size] = {0};

    GIVEN("an initialized array")
    {
        array_t array = {0};
        array_init(&array, buffer, sizeof(buffer), sizeof(*buffer));

        WHEN("get size")
        {
            THEN("should return 3 when the array size is 3")
            {
                array.size = 3;
                REQUIRE(array_get_size(&array) == 3);
            }
            THEN("should return 5 when the array size is 5")
            {
                array.size = 5;
                REQUIRE(array_get_size(&array) == 5);
            }
        }
    }
    GIVEN("an invalid array")
    {
        WHEN("get size")
        {
            uint32_t size = array_get_size(NULL);

            THEN("should return 0")
            {
                REQUIRE(size == 0);
            }
        }
    }
}
