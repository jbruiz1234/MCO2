# SAXPY (A * X + Y) using C and x86-64 Assembly

## Student Information

**Name:** Joseph Benjamin P. Ruiz

**Course:** LBYARCH

**Machine Problem:** SAXPY using C and x86-64 Assembly

---

# Objective

The objective of this project is to implement the SAXPY (Single-Precision A·X Plus Y) kernel in both C and x86-64 Assembly Language using scalar SIMD registers and scalar SIMD floating-point instructions. The implementations are compared in terms of correctness and execution time.

The SAXPY operation is defined as:

```
Z[i] = A × X[i] + Y[i]
```

where

- A is a scalar single-precision floating-point value
- X, Y, and Z are single-precision floating-point vectors

---

# Files

```
MCO2/
│
├── main.c
├── mco2.c
├── mco2.h
├── saxpy.asm
├── MCO2.sln
├── MCO2.vcxproj
└── README.md
```

---

# Compilation

Platform:

- Visual Studio 2022
- Release Mode
- x64

The assembly implementation was written using MASM and functional scalar SIMD floating-point instructions.

---

# Correctness Verification

The C implementation was used as the reference (sanity check).

The assembly implementation was executed using the same input vectors.

The outputs of both implementations were compared element-by-element.

All tests passed successfully.

---

# Sample Output (C)

<img width="403" height="226" alt="image" src="https://github.com/user-attachments/assets/af63a52e-a9e8-4267-bc58-7efe306694b7" />


Example:

```
C kernel first 10 results:

Z[0] = 13.000000
Z[1] = 16.000000
Z[2] = 19.000000
Z[3] = 22.000000
Z[4] = 25.000000
Z[5] = 28.000000
Z[6] = 31.000000
Z[7] = 34.000000
Z[8] = 37.000000
Z[9] = 40.000000
```

---

# Sample Output (Assembly)

<img width="422" height="256" alt="image" src="https://github.com/user-attachments/assets/33c2ef0a-5806-432a-ab6e-cd2b1112a9a9" />


Example:

```
Assembly kernel first 10 results:

Z[0] = 13.000000
Z[1] = 16.000000
Z[2] = 19.000000
Z[3] = 22.000000
Z[4] = 25.000000
Z[5] = 28.000000
Z[6] = 31.000000
Z[7] = 34.000000
Z[8] = 37.000000
Z[9] = 40.000000

Assembly correctness check: PASSED
```

---

# Average Execution Time

Each kernel was executed **30 times**.

Only the kernel execution was timed.

| Vector Size | C Kernel (seconds) | x86-64 Assembly (seconds) | C / ASM Ratio |
|-------------|-------------------:|--------------------------:|--------------:|
| 2²⁰ | 0.000299583 | 0.000851307 | 0.352x |
| 2²⁴ | 0.009160547 | 0.014224270 | 0.644x |
| 2²⁸ | 0.147124627 | 0.228112370 | 0.645x |

---

# Performance Analysis

Both implementations produced identical outputs, indicating that the assembly implementation is functionally correct.

The benchmark results show that the C implementation consistently achieved lower execution times than the handwritten x86-64 assembly implementation for all tested vector sizes. As the vector size increased, the execution time of both implementations increased proportionally due to the larger amount of data being processed. However, the C implementation remained faster across all test cases.

One possible reason for this behavior is that modern C compilers perform aggressive optimizations during compilation. Although the assembly implementation uses the required scalar SIMD registers (XMM registers) and scalar SIMD floating-point instructions (`MOVSS`, `MULSS`, and `ADDSS`), it processes one element at a time. The compiler-generated C code may benefit from additional optimizations such as instruction scheduling and efficient register allocation, resulting in better performance.

Despite the slower execution time of the assembly implementation, it satisfied all assignment requirements by using functional scalar SIMD instructions and producing results identical to the C implementation.

---

# Scalar SIMD Instructions Used

The assembly implementation uses the following scalar SIMD instructions:

- MOVSS
- MULSS
- ADDSS

Scalar SIMD registers used:

- XMM0
- XMM1
- XMM2

---

# Correctness Check

The outputs of the C implementation and the x86-64 assembly implementation matched exactly for every tested vector size.

Status:

```
Assembly correctness check: PASSED
```

---

# Video Demonstration

Include links to the required videos:

- Video 1 – Source Code Walkthrough
- Video 2 – Compilation
- Video 3 – Program Execution

---

# Conclusion

The project successfully implemented the SAXPY kernel in both C and x86-64 Assembly Language. Both implementations produced identical numerical results for all tested vector sizes, confirming the correctness of the assembly implementation. Performance measurements showed that the C implementation executed faster than the handwritten assembly implementation on the test system. This demonstrates that modern optimizing compilers can generate highly efficient machine code even when compared with manually written scalar SIMD assembly, while the assembly implementation still fulfills the requirement of using scalar SIMD registers and floating-point instructions.
