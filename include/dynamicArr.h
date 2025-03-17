#pragma once

#include <stddef.h>

typedef struct {
    const char** items;
    size_t       count;
    size_t       capacity;
} DynamicArrChar;

#define da_append(xs, x)                                                   \
    do {                                                                   \
        if (xs.count >= xs.capacity) {                                     \
            if (xs.capacity == 0)                                          \
                xs.capacity = 256;                                         \
            else                                                           \
                xs.capacity *= 2;                                          \
            xs.items = realloc(xs.items, xs.capacity * sizeof(*xs.items)); \
        }                                                                  \
        xs.items[xs.count++] = x;                                          \
    } while (0)
