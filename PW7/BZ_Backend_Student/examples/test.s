	.arch armv8 -a
	.file "test.sy"
	.data
	.global ans.glo
	.align	2
	.type	ans, %object
	.size	ans, 200
ans.glo:
	.space	200
	.global sum.glo
	.align	2
	.type	sum, %object
	.size	sum, 4
sum.glo:
	.word 0
	.global n.glo
	.align	2
	.type	n, %object
	.size	n, 4
n.glo:
	.word 0
	.global row.glo
	.align	2
	.type	row, %object
	.size	row, 200
row.glo:
	.space	200
	.global line1.glo
	.align	2
	.type	line1, %object
	.size	line1, 200
line1.glo:
	.space	200
	.global line2.glo
	.align	2
	.type	line2, %object
	.size	line2, 400
line2.glo:
	.space	400
	.text
	.global main
	.global printans
	.global f
main:
main.init:
	b	main.label_entry
main.label_entry:
	bl	getint
	mov	v47,	r0
	mov	v116,	v47
	b	main.label_lb29
main.label_lb29:
	mov	v48,	v116
	cmp	v48,	#0
	bgt	main.label_lb30
	b	main.label_lb31
main.label_lb30:
	bl	getint
	mov	v50,	r0
	ldr	v112,	=n.glo
	str	v50,	[v112]
	mov	r0,	#1
	bl	f
	sub	v51,	v48,	#1
	mov	v116,	v51
	b	main.label_lb29
main.label_lb31:
	ldr	v113,	=sum.glo
	ldr	v52,	[v113]
	mov	r0,	v52
	b	main.exit
main.exit:
printans:
printans.init:
	b	printans.label_entry
printans.label_entry:
	ldr	v53,	=sum.glo
	ldr	v0,	[v53]
	add	v1,	v0,	#1
	ldr	v54,	=sum.glo
	str	v1,	[v54]
	mov	v114,	#1
	b	printans.label_lb0
printans.label_lb0:
	mov	v2,	v114
	ldr	v55,	=n.glo
	ldr	v3,	[v55]
	cmp	v2,	v3
	ble	printans.label_lb1
	b	printans.label_lb2
printans.label_lb1:
	mov	v56,	#1
	mul	v57,	v2,	v56
	lsl	v58,	v57,	#2
	ldr	v59,	=ans.glo
	ldr	v6,	[v59,	v58]
	mov	r0,	v6
	bl	putint
	ldr	v60,	=n.glo
	ldr	v7,	[v60]
	cmp	v2,	v7
	beq	printans.label_lb5
	b	printans.label_lb6
printans.label_lb6:
	mov	r0,	#32
	bl	putch
	add	v9,	v2,	#1
	mov	v114,	v9
	b	printans.label_lb0
printans.label_lb5:
	mov	r0,	#10
	bl	putch
	b	printans.exit
printans.label_lb2:
printans.exit:
f:
f.init:
	mov	v10,	r0
	b	f.label_entry
f.label_entry:
	mov	v115,	#1
	b	f.label_lb10
f.label_lb10:
	mov	v11,	v115
	ldr	v61,	=n.glo
	ldr	v12,	[v61]
	cmp	v11,	v12
	ble	f.label_lb11
	b	f.label_lb12
f.label_lb11:
	mov	v62,	#1
	mul	v63,	v11,	v62
	lsl	v64,	v63,	#2
	ldr	v65,	=row.glo
	ldr	v15,	[v65,	v64]
	cmp	v15,	#1
	bne	f.label_lb19
	b	f.label_lb16
f.label_lb19:
	add	v17,	v10,	v11
	mov	v66,	#1
	mul	v67,	v17,	v66
	lsl	v68,	v67,	#2
	ldr	v69,	=line1.glo
	ldr	v19,	[v69,	v68]
	cmp	v19,	#0
	beq	f.label_lb22
	b	f.label_lb16
f.label_lb22:
	ldr	v70,	=n.glo
	ldr	v21,	[v70]
	add	v22,	v21,	v10
	sub	v23,	v22,	v11
	mov	v71,	#1
	mul	v72,	v23,	v71
	lsl	v73,	v72,	#2
	ldr	v74,	=line2.glo
	ldr	v25,	[v74,	v73]
	cmp	v25,	#0
	moveq	v26,	#1
	movne	v26,	#0
	cmp	v26,	#0
	bne	f.label_lb15
	b	f.label_lb16
f.label_lb15:
	mov	v75,	#1
	mul	v76,	v10,	v75
	lsl	v77,	v76,	#2
	ldr	v78,	=ans.glo
	str	v11,	[v78,	v77]
	ldr	v79,	=n.glo
	ldr	v29,	[v79]
	cmp	v10,	v29
	beq	f.label_lb25
	b	f.label_lb26
f.label_lb25:
	bl	printans
	b	f.label_lb26
f.label_lb26:
	mov	v80,	#1
	mul	v81,	v11,	v80
	mov	v82,	#1
	lsl	v83,	v81,	#2
	ldr	v84,	=row.glo
	str	v82,	[v84,	v83]
	add	v32,	v10,	v11
	mov	v85,	#1
	mul	v86,	v32,	v85
	mov	v87,	#1
	lsl	v88,	v86,	#2
	ldr	v89,	=line1.glo
	str	v87,	[v89,	v88]
	ldr	v90,	=n.glo
	ldr	v34,	[v90]
	add	v35,	v34,	v10
	sub	v36,	v35,	v11
	mov	v91,	#1
	mul	v92,	v36,	v91
	mov	v93,	#1
	lsl	v94,	v92,	#2
	ldr	v95,	=line2.glo
	str	v93,	[v95,	v94]
	add	v38,	v10,	#1
	mov	r0,	v38
	bl	f
	mov	v96,	#1
	mul	v97,	v11,	v96
	mov	v98,	#0
	lsl	v99,	v97,	#2
	ldr	v100,	=row.glo
	str	v98,	[v100,	v99]
	add	v40,	v10,	v11
	mov	v101,	#1
	mul	v102,	v40,	v101
	mov	v103,	#0
	lsl	v104,	v102,	#2
	ldr	v105,	=line1.glo
	str	v103,	[v105,	v104]
	ldr	v106,	=n.glo
	ldr	v42,	[v106]
	add	v43,	v42,	v10
	sub	v44,	v43,	v11
	mov	v107,	#1
	mul	v108,	v44,	v107
	mov	v109,	#0
	lsl	v110,	v108,	#2
	ldr	v111,	=line2.glo
	str	v109,	[v111,	v110]
	b	f.label_lb16
f.label_lb16:
	add	v46,	v11,	#1
	mov	v115,	v46
	b	f.label_lb10
f.label_lb12:
f.exit:

