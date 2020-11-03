/*******************************************************************************
 * Copyright (C) 2020 Gustavo Salomao
 * All rights reserved.
 ******************************************************************************/

#include <stddef.h>
#include <string.h>

#include "openedk/container/array.h"

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
