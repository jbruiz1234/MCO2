#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <windows.h>

#include "mco2.h"

#define RUNS 30

static double get_time_seconds(void)
{
    static LARGE_INTEGER frequency;
    LARGE_INTEGER counter;

    if (frequency.QuadPart == 0)
        QueryPerformanceFrequency(&frequency);

    QueryPerformanceCounter(&counter);

    return (double)counter.QuadPart / (double)frequency.QuadPart;
}

static void initialize_vectors(
    size_t n,
    float A,
    float* X,
    float* Y)
{
    for (size_t i = 0; i < n; i++)
    {
        X[i] = (float)((i % 100) + 1);
        Y[i] = (float)((i % 100) + 11);
    }
}

static int compare_vectors(
    size_t n,
    const float* reference,
    const float* test)
{
    const float tolerance = 1e-5f;

    for (size_t i = 0; i < n; i++)
    {
        if (fabsf(reference[i] - test[i]) > tolerance)
        {
            printf("Mismatch at index %zu: C = %.9f, ASM = %.9f\n",
                i, reference[i], test[i]);

            return 0;
        }
    }

    return 1;
}

static double benchmark_c(
    size_t n,
    float A,
    const float* X,
    const float* Y,
    float* Z)
{
    double total = 0.0;

    for (int run = 0; run < RUNS; run++)
    {
        double start = get_time_seconds();

        saxpy_c(n, A, X, Y, Z);

        double end = get_time_seconds();

        total += end - start;
    }

    return total / RUNS;
}

static double benchmark_asm(
    size_t n,
    float A,
    const float* X,
    const float* Y,
    float* Z)
{
    double total = 0.0;

    for (int run = 0; run < RUNS; run++)
    {
        double start = get_time_seconds();

        saxpy_asm(n, A, X, Y, Z);

        double end = get_time_seconds();

        total += end - start;
    }

    return total / RUNS;
}

static void print_first_ten(
    size_t n,
    const float* Z)
{
    size_t count = n < 10 ? n : 10;

    for (size_t i = 0; i < count; i++)
    {
        printf("Z[%zu] = %.6f\n", i, Z[i]);
    }
}

static void run_test(size_t n)
{
    printf("\n============================================\n");
    printf("Vector size: n = %zu (2^%d)\n",
        n,
        (int)log2((double)n));
    printf("============================================\n");

    float A = 2.0f;

    /*
        Three arrays:
        X
        Y
        Z

        Each float = 4 bytes.
    */

    float* X = (float*)malloc(n * sizeof(float));
    float* Y = (float*)malloc(n * sizeof(float));
    float* Z_C = (float*)malloc(n * sizeof(float));
    float* Z_ASM = (float*)malloc(n * sizeof(float));

    if (!X || !Y || !Z_C || !Z_ASM)
    {
        printf("Memory allocation failed for n = %zu\n", n);

        free(X);
        free(Y);
        free(Z_C);
        free(Z_ASM);

        return;
    }

    initialize_vectors(n, A, X, Y);

    /*
        First C execution.
        This acts as the reference/sanity-check result.
    */

    saxpy_c(n, A, X, Y, Z_C);

    printf("\nC kernel first 10 results:\n");
    print_first_ten(n, Z_C);

    /*
        Run assembly once before benchmarking.
        This generates the assembly result for correctness checking.
    */

    saxpy_asm(n, A, X, Y, Z_ASM);

    printf("\nAssembly kernel first 10 results:\n");
    print_first_ten(n, Z_ASM);

    /*
        Correctness check.
    */

    if (compare_vectors(n, Z_C, Z_ASM))
        printf("\nAssembly correctness check: PASSED\n");
    else
        printf("\nAssembly correctness check: FAILED\n");

    /*
        Benchmark only the kernel.
    */

    double c_time =
        benchmark_c(n, A, X, Y, Z_C);

    double asm_time =
        benchmark_asm(n, A, X, Y, Z_ASM);

    printf("\nAverage execution time over %d runs:\n", RUNS);

    printf("C kernel   : %.9f seconds\n", c_time);
    printf("ASM kernel : %.9f seconds\n", asm_time);

    if (asm_time > 0.0)
    {
        printf("C / ASM speed ratio: %.3fx\n",
            c_time / asm_time);
    }

    free(X);
    free(Y);
    free(Z_C);
    free(Z_ASM);
}

int main(void)
{
    printf("SAXPY: Z[i] = A * X[i] + Y[i]\n");

    /*
        Test sizes:
        2^20 = 1,048,576
        2^24 = 16,777,216
        2^28 = 268,435,456

        2^30 requires approximately:
        4 arrays * 2^30 * 4 bytes
        = 16 GB

        We use 2^28 as the large test size
        to avoid excessive memory requirements.
    */

    run_test((size_t)1 << 20);
    run_test((size_t)1 << 24);
    run_test((size_t)1 << 28);

    return 0;
}