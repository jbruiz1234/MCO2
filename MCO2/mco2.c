#include "mco2.h"

void saxpy_c(size_t n, float A, const float* X, const float* Y, float* Z)
{
    for (size_t i = 0; i < n; i++)
    {
        Z[i] = A * X[i] + Y[i];
    }
}