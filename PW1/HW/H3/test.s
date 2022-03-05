	.file	"test.c"
	.text
	.globl	ccp
	.type	ccp, @function
ccp:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	$1, -8(%rbp)
	jmp	.L2
.L4:
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	je	.L3
	movl	$2, -8(%rbp)
.L3:
	movl	$2, %eax
	subl	-8(%rbp), %eax
	movl	%eax, -8(%rbp)
	cmpl	$1, -8(%rbp)
	je	.L2
	movl	$2, -4(%rbp)
.L2:
	movl	-24(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, -24(%rbp)
	testl	%eax, %eax
	jne	.L4
	movl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	ccp, .-ccp
	.ident	"GCC: (Uos 8.3.0.3-3+rebuild) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
