.LC0:
        .ascii  "c = %d\000"
.LC1:
        .ascii  "d = %d\000"
exp_compute:
        push    {r7, lr}
        sub     sp, sp, #32
        add     r7, sp, #0
        str     r0, [r7, #4]
        str     r1, [r7]
        movs    r3, #4
        str     r3, [r7, #28]
        movs    r3, #8
        str     r3, [r7, #24]
        ldr     r3, [r7, #28]
        ldr     r2, [r7, #24]
        mul     r3, r2, r3
        str     r3, [r7, #20]
        ldr     r1, [r7, #28]
        ldr     r0, [r7, #24]
        bl      __aeabi_idiv
        mov     r3, r0
        str     r3, [r7, #16]
        ldr     r2, [r7, #4]
        ldr     r3, [r7]
        subs    r3, r2, r3
        str     r3, [r7, #12]
        ldr     r2, [r7, #4]
        ldr     r3, [r7]
        subs    r3, r2, r3
        ldr     r2, [r7, #16]
        add     r3, r3, r2
        str     r3, [r7, #8]
        ldr     r1, [r7, #12]
        movw    r0, #:lower16:.LC0
        movt    r0, #:upper16:.LC0
        bl      printf
        ldr     r1, [r7, #8]
        movw    r0, #:lower16:.LC1
        movt    r0, #:upper16:.LC1
        bl      printf
        ldr     r2, [r7, #12]
        ldr     r3, [r7, #8]
        add     r2, r2, r3
        ldr     r3, [r7, #20]
        add     r3, r3, r2
        lsls    r3, r3, #1
        mov     r0, r3
        adds    r7, r7, #32
        mov     sp, r7
        pop     {r7, pc}
ccp:
        push    {r7}
        sub     sp, sp, #20
        add     r7, sp, #0
        str     r0, [r7, #4]
        str     r1, [r7]
        ldr     r3, [r7, #4]
        str     r3, [r7, #12]
        movs    r3, #1
        str     r3, [r7, #8]
        b       .L4
.L6:
        ldr     r2, [r7, #12]
        ldr     r3, [r7, #4]
        cmp     r2, r3
        beq     .L5
        movs    r3, #2
        str     r3, [r7, #8]
.L5:
        ldr     r3, [r7, #8]
        rsb     r3, r3, #2
        str     r3, [r7, #8]
        ldr     r3, [r7, #8]
        cmp     r3, #1
        beq     .L4
        movs    r3, #2
        str     r3, [r7, #12]
.L4:
        ldr     r3, [r7]
        subs    r2, r3, #1
        str     r2, [r7]
        cmp     r3, #0
        bne     .L6
        ldr     r3, [r7, #8]
        mov     r0, r3
        adds    r7, r7, #20
        mov     sp, r7
        ldr     r7, [sp], #4
        bx      lr
squre:
        push    {r7}
        sub     sp, sp, #420
        add     r7, sp, #0
        add     r3, r7, #416
        sub     r3, r3, #412
        str     r0, [r3]
        movs    r3, #0
        str     r3, [r7, #412]
        b       .L9
.L10:
        add     r3, r7, #416
        sub     r3, r3, #404
        ldr     r2, [r7, #412]
        ldr     r1, [r7, #412]
        str     r1, [r3, r2, lsl #2]
        ldr     r3, [r7, #412]
        adds    r3, r3, #1
        str     r3, [r7, #412]
.L9:
        ldr     r3, [r7, #412]
        cmp     r3, #99
        ble     .L10
        add     r3, r7, #416
        sub     r3, r3, #412
        ldr     r3, [r3]
        mul     r2, r3, r3
        add     r3, r7, #416
        sub     r3, r3, #404
        add     r1, r7, #416
        sub     r1, r1, #412
        ldr     r1, [r1]
        ldr     r3, [r3, r1, lsl #2]
        add     r3, r3, r2
        mov     r0, r3
        add     r7, r7, #420
        mov     sp, r7
        ldr     r7, [sp], #4
        bx      lr