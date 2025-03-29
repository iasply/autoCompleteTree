#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
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

int comp(char *a, char *b) { return strcmp((const char *)a, (const char *)b); }

bool stringToInt(const char *str, int *num) {
    char *endptr;
    errno       = 0;
    long result = strtol(str, &endptr, 10);

    if (errno == ERANGE || result > INT_MAX || result < INT_MIN) {
        return false;
    }

    if (*endptr != '\0') {
        return false;
    }

    *num = (int)result;
    return true;
}

double getElapsedTime(clock_t start) {
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

void printDebug(const char *format, ...) {
#ifdef DEBUG_ON
    va_list args;
    va_start(args, format);
    printf("[DEBUG] ");
    vprintf(format, args);
    printf("\n");
    va_end(args);
#endif
}
