/*******************************************************************************
 * Copyright (C) 2020 Gustavo Salomao
 * All rights reserved.
 ******************************************************************************/

#ifndef FFF_HELPER_H
#define FFF_HELPER_H

/*
 * Check if the function was called in an expected number of times.
 */
#define REQUIRE_CALLED_TIMES(function, times)               \
    REQUIRE(function##_fake.call_count == times)

/*
 * Check if the function was called once.
 */
#define REQUIRE_CALLED(function)                            \
    REQUIRE_CALLED_TIMES(function, 1)

#endif // FFF_HELPER_H
