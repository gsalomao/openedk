/*******************************************************************************
 * Copyright (C) 2020 Gustavo Salomao
 * All rights reserved.
 ******************************************************************************/

#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Array structure.
 *
 * Structure representing an array.
 */
typedef struct {
    void* buffer;           /**< Underlying buffer. */
    uint32_t size;          /**< Number of elements in the array. */
    uint32_t elem_size;     /**< Size of each element. */
    uint32_t capacity;      /**< Number of elements that has space for. */
} array_t;

/**
 * @brief Initialize array.
 *
 * Initialize the given array using the given buffer.
 *
 * @param[in/out]   self            Array instance.
 * @param[in]       buffer          Array buffer.
 * @param[in]       buffer_size     Size of the buffer.
 * @param[in]       elem_size       Size of each element in the array.
 *
 * @retval true - if the array was initialized with success.
 * @retval false - in case of failure.
 */
bool array_init(array_t* self, void* buffer, uint32_t buffer_size,
                uint32_t item_size);

/**
 * @brief Get buffer.
 *
 * Get the underlying buffer.
 *
 * @param[in]   self    Array instance.
 *
 * @return Pointer to the underlying buffer.
 */
void* array_get_buffer(const array_t* self);

/**
 * @brief Get size.
 *
 * Get the number of elements in the array.
 *
 * @param[in]   self    Array instance.
 *
 * @return The number of elements in the array.
 */
uint32_t array_get_size(const array_t* self);

/**
 * @brief Get capacity.
 *
 * Get the number of elements that the array has space for.
 *
 * @param[in]   self    Array instance.
 *
 * @return The number of elements that the array has space for.
 */
uint32_t array_get_capacity(const array_t* self);

/**
 * @brief Get size of the elements.
 *
 * Get the size of the elements in the array.
 *
 * @param[in]   self    Array instance.
 *
 * @return The size of the elements.
 */
uint32_t array_get_elem_size(const array_t* self);

#endif // ARRAY_H
