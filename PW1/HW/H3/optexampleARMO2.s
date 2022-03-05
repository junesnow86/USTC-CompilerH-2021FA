.LC0:
        .ascii  "c = %d\000"
.LC1:
        .ascii  "d = %d\000"
exp_compute:
        push    {r3, r4, r5, lr}
        subs    r4, r0, r1
        adds    r5, r4, #2
        mov     r1, r4
        movw    r0, #:lower16:.LC0
        movt    r0, #:upper16:.LC0
        bl      printf
        mov     r1, r5
        movw    r0, #:lower16:.LC1
        movt    r0, #:upper16:.LC1
        bl      printf
        adds    r0, r4, r5
        adds    r0, r0, #32
        lsls    r0, r0, #1
        pop     {r3, r4, r5, pc}
ccp:
        movs    r0, #1
        bx      lr
squre:
        sub     sp, sp, #400
        movs    r3, #0
        sub     r2, sp, #4
.L6:
        str     r3, [r2, #4]!   // store
        adds    r3, r3, #1      // i++
        cmp     r3, #100        // 比较i和100
        bne     .L6             // i == 100时跳出循环
        ldr     r3, [sp, r0, lsl #2]    // load(r3 = num)
        mla     r0, r0, r0, r3  // r0 = r0 * r0 + r3
        add     sp, sp, #400
        bx      lr