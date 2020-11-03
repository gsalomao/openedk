/*******************************************************************************
 * Copyright (C) 2020 Gustavo Salomao
 * All rights reserved.
 ******************************************************************************/

#include <stddef.h>

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
