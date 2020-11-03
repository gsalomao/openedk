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
            THEN("should return 3")
            {
                array.size = 3;
                REQUIRE(array_get_size(&array) == 3);
            }
            THEN("should return 5")
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

SCENARIO("array: get capacity")
{
    const uint32_t buffer_size{8};
    uint32_t buffer[buffer_size] = {0};

    GIVEN("an initialized array")
    {
        array_t array = {0};
        array_init(&array, buffer, sizeof(buffer), sizeof(*buffer));

        WHEN("get capacity")
        {
            THEN("should return 2")
            {
                array.capacity = 2;
                REQUIRE(array_get_capacity(&array) == 2);
            }
            THEN("should return 15")
            {
                array.capacity = 15;
                REQUIRE(array_get_capacity(&array) == 15);
            }
        }
    }
    GIVEN("an invalid array")
    {
        WHEN("get capacity")
        {
            uint32_t size = array_get_capacity(NULL);

            THEN("should return 0")
            {
                REQUIRE(size == 0);
            }
        }
    }
}

SCENARIO("array: get element size")
{
    const uint32_t buffer_size{8};
    uint32_t buffer[buffer_size] = {0};

    GIVEN("an initialized array")
    {
        array_t array = {0};
        array_init(&array, buffer, sizeof(buffer), sizeof(*buffer));

        WHEN("get element size")
        {
            THEN("should return 6")
            {
                array.elem_size = 6;
                REQUIRE(array_get_elem_size(&array) == 6);
            }
            THEN("should return 25")
            {
                array.elem_size = 25;
                REQUIRE(array_get_elem_size(&array) == 25);
            }
        }
    }
    GIVEN("an invalid array")
    {
        WHEN("get element size")
        {
            uint32_t size = array_get_elem_size(NULL);

            THEN("should return 0")
            {
                REQUIRE(size == 0);
            }
        }
    }
}

SCENARIO("array: add element")
{
    const uint32_t buffer_size{8};
    uint32_t buffer[buffer_size] = {0};
    array_t array = {0};

    array_init(&array, buffer, sizeof(buffer), sizeof(*buffer));

    GIVEN("an initialized array")
    {
        WHEN("add an element")
        {
            uint32_t element = 0xA55AA55A;
            bool result = array_add(&array, &element);

            THEN("should return true")
            {
                REQUIRE(result == true);
            }
            THEN("should add the element")
            {
                REQUIRE(buffer[0] == element);
            }
            THEN("should not touch the next element")
            {
                REQUIRE(buffer[1] == 0);
            }
            THEN("should increment size once")
            {
                REQUIRE(array.size == 1);
            }
        }
        WHEN("add multiple elements")
        {
            uint32_t element0 = 0xA55AA55A;
            array_add(&array, &element0);

            uint32_t element1 = 0xDEADBEEF;
            bool result = array_add(&array, &element1);

            THEN("should return true")
            {
                REQUIRE(result == true);
            }
            THEN("should add the elements")
            {
                REQUIRE(buffer[0] == element0);
                REQUIRE(buffer[1] == element1);
            }
            THEN("should increment size twice")
            {
                REQUIRE(array.size == 2);
            }
        }
        WHEN("add the same element twice")
        {
            uint32_t element = 0xA55AA55A;

            array_add(&array, &element);
            bool result = array_add(&array, &element);

            THEN("should return true")
            {
                REQUIRE(result == true);
            }
            THEN("should add the elements")
            {
                REQUIRE(buffer[0] == element);
                REQUIRE(buffer[1] == element);
            }
            THEN("should increment size twice")
            {
                REQUIRE(array.size == 2);
            }
        }
        WHEN("add an invalid element")
        {
            bool result = array_add(&array, NULL);

            THEN("should return false")
            {
                REQUIRE(result == false);
            }
        }
    }
    GIVEN("an invalid array")
    {
        WHEN("add an element")
        {
            uint32_t element = 0xA55AA55A;
            bool result = array_add(NULL, &element);

            THEN("should return false")
            {
                REQUIRE(result == false);
            }
        }
    }
    GIVEN("an array with invalid buffer")
    {
        array.buffer = NULL;

        WHEN("add an element")
        {
            uint32_t element = 0xA55AA55A;
            bool result = array_add(&array, &element);

            THEN("should return false")
            {
                REQUIRE(result == false);
            }
        }
    }
    GIVEN("an array already full")
    {
        uint32_t capacity = array.capacity;
        array.size = array.capacity;

        WHEN("add an element")
        {
            uint32_t element = 0xA55AA55A;
            bool result = array_add(&array, &element);

            THEN("should return false")
            {
                REQUIRE(result == false);
            }
            THEN("should not change the size")
            {
                REQUIRE(array.size == capacity);
            }
            THEN("should not change the capacity")
            {
                REQUIRE(array.capacity == capacity);
            }
        }
    }
}
