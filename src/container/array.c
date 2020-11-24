/*******************************************************************************
 * Copyright (C) 2020 Gustavo Salomao
 * All rights reserved.
 ******************************************************************************/

#include <stddef.h>
#include <string.h>

#include "openedk/container/array.h"

static int32_t get_elem_pos(const array_t* self, const void* elem);
static inline void copy_elem(array_t* self, uint32_t cur_pos, uint32_t new_pos);


bool array_init(array_t* self, void* buffer, uint32_t buffer_size,
                uint32_t elem_size)
{
    if (!self || !buffer || !buffer_size || !elem_size)
    {
        return false;
    }

    self->buffer = buffer;
    self->size = 0;
    self->capacity = (buffer_size / elem_size);
    self->elem_size = elem_size;

    return true;
}

void* array_get_buffer(const array_t* self)
{
    return (self) ? self->buffer : NULL;
}

uint32_t array_get_size(const array_t* self)
{
    return (self) ? self->size : 0;
}

uint32_t array_get_capacity(const array_t* self)
{
    return (self) ? self->capacity : 0;
}

uint32_t array_get_elem_size(const array_t* self)
{
    return (self) ? self->elem_size : 0;
}

bool array_add(array_t* self, const void* element)
{
    if (!element || !self || !self->buffer || (self->size == self->capacity))
    {
        return false;
    }

    uint8_t* dst_ptr = (uint8_t*) self->buffer;
    const uint8_t* src_ptr = (const uint8_t*) element;

    dst_ptr += (self->size * self->elem_size);
    memcpy(dst_ptr, src_ptr, self->elem_size);
    self->size++;

    return true;
}

bool array_remove(array_t* self, const void* element)
{
    if (!element || !self || !self->buffer || !self->size)
    {
        return false;
    }

    int32_t position = get_elem_pos(self, element);

    if (position < 0)
    {
        return false;
    }

    while (position >= 0)
    {
        while (position < (self->size - 1))
        {
            copy_elem(self, position + 1, position);
            ++position;
        }

        --self->size;
        position = get_elem_pos(self, element);
    }

    return true;
}

/**
 * @brief Get element position.
 *
 * @param[in]   self    Array instance.
 * @param[in]   elem    Element to get its position.
 *
 * @return The element position if the element is in the array. Otherwise, it
 *         returns -1.
 */
static int32_t get_elem_pos(const array_t* self, const void* elem)
{
    for (uint32_t idx = 0; idx < self->size; ++idx)
    {
        uint8_t* ptr = ((uint8_t*) self->buffer) + (idx * self->elem_size);
        if (!memcmp(ptr, elem, self->elem_size))
        {
            return idx;
        }
    }

    return -1;
}

/**
 * @brief Copy element.
 *
 * @param[in/out]   self        Array instance.
 * @param[in]       cur_pos     Current position.
 * @param[in]       new_pos     New position.
 */
static inline void copy_elem(array_t* self, uint32_t cur_pos, uint32_t new_pos)
{
    uint8_t* src_ptr = ((uint8_t*) self->buffer) + (cur_pos * self->elem_size);
    uint8_t* dst_ptr = ((uint8_t*) self->buffer) + (new_pos * self->elem_size);

    memcpy(dst_ptr, src_ptr, self->elem_size);
}
