#pragma once

#include <stddef.h>

void print_int(int x);
void print_uint(unsigned int x);
void print_long(long x);
void print_ulong(unsigned long x);
void print_float(float x);
void print_double(double x);
void print_str(char *x);
void print_c_str(const char *x);
void print_ptr(size_t *x);

#define print(x) \
    _Generic((x),               \
    int: print_int,             \
    unsigned int: print_uint,   \
    long: print_long,           \
    unsigned long: print_ulong, \
    float: print_float,         \
    double: print_double,       \
    char *: print_str,          \
    const char *: print_c_str,    \
    size_t *: print_ptr)(x)
