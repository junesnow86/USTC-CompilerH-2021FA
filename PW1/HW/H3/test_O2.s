	.file	"test.c"
	.text
	.p2align 4,,15
	.globl	ccp
	.type	ccp, @function
ccp:
.LFB0:
	.cfi_startproc
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	ccp, .-ccp
	.ident	"GCC: (Uos 8.3.0.3-3+rebuild) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
