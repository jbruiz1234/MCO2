OPTION CASEMAP:NONE

.code

PUBLIC saxpy_asm

saxpy_asm PROC

    ; RCX = n
    ; XMM1 = A
    ; R8  = X
    ; R9  = Y
    ; [RSP+28h] = Z

    mov     r10, [rsp + 28h]

    test    rcx, rcx
    jz      done

loop_start:

    movss   xmm0, DWORD PTR [r8]
    mulss   xmm0, xmm1

    movss   xmm2, DWORD PTR [r9]
    addss   xmm0, xmm2

    movss   DWORD PTR [r10], xmm0

    add     r8, 4
    add     r9, 4
    add     r10, 4

    dec     rcx
    jnz     loop_start

done:
    ret

saxpy_asm ENDP

END