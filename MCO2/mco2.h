#ifndef MCO2_H
#define MCO2_H

#include <stddef.h>

void saxpy_c(size_t n, float A, const float* X, const float* Y, float* Z);

void saxpy_asm(size_t n, float A, const float* X, const float* Y, float* Z);

#endif