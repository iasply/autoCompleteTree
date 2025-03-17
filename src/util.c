#include <stdio.h>
#include <util.h>

void print_int(int x) { printf("%d\n", x); }

void print_uint(unsigned int x) { printf("%u\n", x); }

void print_long(long x) { printf("%ld\n", x); }

void print_ulong(unsigned long x) { printf("%zu\n", x); }

void print_float(float x) { printf("%f\n", x); }

void print_double(double x) { printf("%lf\n", x); }

void print_str(char *x) { printf("%s\n", x); }

void print_c_str(const char *x) { printf("%s\n", x); }

void print_ptr(size_t *x) { printf("%p\n", (void *)x); }
