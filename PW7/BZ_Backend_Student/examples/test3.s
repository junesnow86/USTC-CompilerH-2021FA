	.arch armv8 -a
	.file "test.sy"
	.data
	.global TAPE_LEN.glo
	.align	2
	.type	TAPE_LEN, %object
	.size	TAPE_LEN, 4
TAPE_LEN.glo:
	.word 65536
	.global BUFFER_LEN.glo
	.align	2
	.type	BUFFER_LEN, %object
	.size	BUFFER_LEN, 4
BUFFER_LEN.glo:
	.word 32768
	.global tape.glo
	.align	2
	.type	tape, %object
	.size	tape, 262144
tape.glo:
	.space	262144
	.global program.glo
	.align	2
	.type	program, %object
	.size	program, 131072
program.glo:
	.space	131072
	.global ptr.glo
	.align	2
	.type	ptr, %object
	.size	ptr, 4
ptr.glo:
	.word 0
	.text
	.global main
	.global read_program
	.global interpret
main:
main.init:
	b	main.label_entry
main.label_entry:
	bl	read_program
	ldr	v114,	=program.glo
	add	v115,	v114,	#0
	mov	r0,	v115
	bl	interpret
	mov	r0,	#0
	b	main.exit
main.exit:
read_program:
read_program.init:
	b	read_program.label_entry
read_program.label_entry:
	bl	getint
	mov	v0,	r0
	mov	v116,	#0
	b	read_program.label_lb0
read_program.label_lb0:
	mov	v1,	v116
	cmp	v1,	v0
	blt	read_program.label_lb1
	b	read_program.label_lb2
read_program.label_lb1:
	mov	v63,	#1
	mul	v64,	v1,	v63
	bl	getch
	mov	v4,	r0
	lsl	v65,	v64,	#2
	ldr	v66,	=program.glo
	str	v4,	[v66,	v65]
	add	v5,	v1,	#1
	mov	v116,	v5
	b	read_program.label_lb0
read_program.label_lb2:
	mov	v67,	#1
	mul	v68,	v1,	v67
	mov	v69,	#0
	lsl	v70,	v68,	#2
	ldr	v71,	=program.glo
	str	v69,	[v71,	v70]
read_program.exit:
interpret:
interpret.init:
	mov	v7,	r0
	b	interpret.label_entry
interpret.label_entry:
	mov	v117,	#0
	mov	v118,	#0
	b	interpret.label_lb5
interpret.label_lb5:
	mov	v9,	v118
	mov	v8,	v117
	lsl	v72,	v8,	#2
	ldr	v11,	[v7,	v72]
	cmp	v11,	#0
	bne	interpret.label_lb6
	b	interpret.label_lb7
interpret.label_lb6:
	lsl	v73,	v8,	#2
	ldr	v14,	[v7,	v73]
	cmp	v14,	#62
	beq	interpret.label_lb10
	b	interpret.label_lb11
interpret.label_lb10:
	ldr	v74,	=ptr.glo
	ldr	v16,	[v74]
	add	v17,	v16,	#1
	ldr	v75,	=ptr.glo
	str	v17,	[v75]
	mov	v119,	v8
	mov	v120,	v9
	b	interpret.label_lb12
interpret.label_lb11:
	cmp	v14,	#60
	beq	interpret.label_lb15
	b	interpret.label_lb16
interpret.label_lb15:
	ldr	v76,	=ptr.glo
	ldr	v19,	[v76]
	sub	v20,	v19,	#1
	ldr	v77,	=ptr.glo
	str	v20,	[v77]
	mov	v119,	v8
	mov	v120,	v9
	b	interpret.label_lb12
interpret.label_lb16:
	cmp	v14,	#43
	beq	interpret.label_lb20
	b	interpret.label_lb21
interpret.label_lb20:
	ldr	v78,	=ptr.glo
	ldr	v22,	[v78]
	mov	v79,	#1
	mul	v80,	v22,	v79
	ldr	v81,	=ptr.glo
	ldr	v24,	[v81]
	mov	v82,	#1
	mul	v83,	v24,	v82
	lsl	v84,	v83,	#2
	ldr	v85,	=tape.glo
	ldr	v26,	[v85,	v84]
	add	v27,	v26,	#1
	lsl	v86,	v80,	#2
	ldr	v87,	=tape.glo
	str	v27,	[v87,	v86]
	mov	v119,	v8
	mov	v120,	v9
	b	interpret.label_lb12
interpret.label_lb21:
	cmp	v14,	#45
	beq	interpret.label_lb25
	b	interpret.label_lb26
interpret.label_lb25:
	ldr	v88,	=ptr.glo
	ldr	v29,	[v88]
	mov	v89,	#1
	mul	v90,	v29,	v89
	ldr	v91,	=ptr.glo
	ldr	v31,	[v91]
	mov	v92,	#1
	mul	v93,	v31,	v92
	lsl	v94,	v93,	#2
	ldr	v95,	=tape.glo
	ldr	v33,	[v95,	v94]
	sub	v34,	v33,	#1
	lsl	v96,	v90,	#2
	ldr	v97,	=tape.glo
	str	v34,	[v97,	v96]
	mov	v119,	v8
	mov	v120,	v9
	b	interpret.label_lb12
interpret.label_lb26:
	cmp	v14,	#46
	beq	interpret.label_lb30
	b	interpret.label_lb31
interpret.label_lb30:
	ldr	v98,	=ptr.glo
	ldr	v36,	[v98]
	mov	v99,	#1
	mul	v100,	v36,	v99
	lsl	v101,	v100,	#2
	ldr	v102,	=tape.glo
	ldr	v38,	[v102,	v101]
	mov	r0,	v38
	bl	putch
	mov	v119,	v8
	mov	v120,	v9
	b	interpret.label_lb12
interpret.label_lb31:
	cmp	v14,	#44
	beq	interpret.label_lb35
	b	interpret.label_lb36
interpret.label_lb35:
	ldr	v103,	=ptr.glo
	ldr	v40,	[v103]
	mov	v104,	#1
	mul	v105,	v40,	v104
	bl	getch
	mov	v42,	r0
	lsl	v106,	v105,	#2
	ldr	v107,	=tape.glo
	str	v42,	[v107,	v106]
	mov	v119,	v8
	mov	v120,	v9
	b	interpret.label_lb12
interpret.label_lb36:
	cmp	v14,	#93
	mov	v119,	v8
	mov	v120,	v9
	beq	interpret.label_lb44
	b	interpret.label_lb12
interpret.label_lb44:
	ldr	v108,	=ptr.glo
	ldr	v44,	[v108]
	mov	v109,	#1
	mul	v110,	v44,	v109
	lsl	v111,	v110,	#2
	ldr	v112,	=tape.glo
	ldr	v46,	[v112,	v111]
	cmp	v46,	#0
	mov	v119,	v8
	mov	v120,	v9
	mov	v121,	v8
	mov	v122,	#1
	bne	interpret.label_lb47
	b	interpret.label_lb12
interpret.label_lb47:
	mov	v49,	v122
	mov	v48,	v121
	cmp	v49,	#0
	mov	v119,	v48
	mov	v120,	v49
	bgt	interpret.label_lb48
	b	interpret.label_lb12
interpret.label_lb48:
	sub	v51,	v48,	#1
	lsl	v113,	v51,	#2
	ldr	v53,	[v7,	v113]
	cmp	v53,	#91
	beq	interpret.label_lb52
	b	interpret.label_lb53
interpret.label_lb52:
	sub	v55,	v49,	#1
	mov	v121,	v51
	mov	v122,	v55
	b	interpret.label_lb47
interpret.label_lb53:
	cmp	v53,	#93
	mov	v121,	v51
	mov	v122,	v49
	beq	interpret.label_lb57
	b	interpret.label_lb47
interpret.label_lb57:
	add	v57,	v49,	#1
	mov	v121,	v51
	mov	v122,	v57
	b	interpret.label_lb47
interpret.label_lb12:
	mov	v59,	v120
	mov	v58,	v119
	add	v60,	v58,	#1
	mov	v117,	v60
	mov	v118,	v59
	b	interpret.label_lb5
interpret.label_lb7:
interpret.exit:

