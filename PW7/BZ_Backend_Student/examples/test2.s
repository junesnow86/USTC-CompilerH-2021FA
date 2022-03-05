	.arch armv8 -a
	.file "test.sy"
	.data
	.global maxn.glo
	.align	2
	.type	maxn, %object
	.size	maxn, 4
maxn.glo:
	.word 18
	.global mod.glo
	.align	2
	.type	mod, %object
	.size	mod, 4
mod.glo:
	.word 1000000007
	.global dp.glo
	.align	2
	.type	dp, %object
	.size	dp, 52907904
dp.glo:
	.space	52907904
	.global list.glo
	.align	2
	.type	list, %object
	.size	list, 800
list.glo:
	.space	800
	.global cns.glo
	.align	2
	.type	cns, %object
	.size	cns, 80
cns.glo:
	.space	80
	.text
	.global main
	.global equal
	.global dfs
main:
main.init:
	b	main.label_entry
main.label_entry:
	bl	getint
	mov	v76,	r0
	mov	v294,	#0
	mov	v295,	#0
	mov	v296,	#0
	mov	v297,	#0
	mov	v298,	#0
	b	main.label_lb32
main.label_lb32:
	mov	v81,	v298
	mov	v80,	v297
	mov	v79,	v296
	mov	v78,	v295
	mov	v77,	v294
	ldr	v238,	=maxn.glo
	ldr	v82,	[v238]
	cmp	v81,	v82
	mov	v299,	v77
	mov	v300,	v78
	mov	v301,	v79
	mov	v302,	v80
	mov	v303,	#0
	mov	v314,	#0
	blt	main.label_lb37
	b	main.label_lb62
main.label_lb37:
	mov	v88,	v303
	mov	v87,	v302
	mov	v86,	v301
	mov	v85,	v300
	mov	v84,	v299
	ldr	v239,	=maxn.glo
	ldr	v89,	[v239]
	cmp	v88,	v89
	mov	v304,	v84
	mov	v305,	v85
	mov	v306,	v86
	mov	v307,	#0
	blt	main.label_lb42
	b	main.label_lb39
main.label_lb42:
	mov	v94,	v307
	mov	v93,	v306
	mov	v92,	v305
	mov	v91,	v304
	ldr	v240,	=maxn.glo
	ldr	v95,	[v240]
	cmp	v94,	v95
	mov	v308,	v91
	mov	v309,	v92
	mov	v310,	#0
	blt	main.label_lb47
	b	main.label_lb44
main.label_lb47:
	mov	v99,	v310
	mov	v98,	v309
	mov	v97,	v308
	ldr	v241,	=maxn.glo
	ldr	v100,	[v241]
	cmp	v99,	v100
	mov	v311,	v97
	mov	v312,	#0
	blt	main.label_lb52
	b	main.label_lb49
main.label_lb52:
	mov	v103,	v312
	mov	v102,	v311
	ldr	v242,	=maxn.glo
	ldr	v104,	[v242]
	cmp	v103,	v104
	mov	v313,	#0
	blt	main.label_lb57
	b	main.label_lb54
main.label_lb57:
	mov	v106,	v313
	cmp	v106,	#7
	blt	main.label_lb58
	b	main.label_lb59
main.label_lb58:
	mov	v243,	#734832
	mul	v244,	v81,	v243
	mov	v245,	#40824
	mul	v246,	v88,	v245
	mov	v247,	#2268
	mul	v248,	v94,	v247
	mov	v249,	#126
	mul	v250,	v99,	v249
	mov	v251,	#7
	mul	v252,	v103,	v251
	mov	v253,	#1
	mul	v254,	v106,	v253
	add	v255,	v244,	v246
	add	v256,	v255,	v248
	add	v257,	v256,	v250
	add	v258,	v257,	v252
	add	v259,	v258,	v254
	mov	v260,	#-1
	lsl	v261,	v259,	#2
	ldr	v262,	=dp.glo
	str	v260,	[v262,	v261]
	add	v109,	v106,	#1
	mov	v313,	v109
	b	main.label_lb57
main.label_lb59:
	add	v110,	v103,	#1
	mov	v311,	v106
	mov	v312,	v110
	b	main.label_lb52
main.label_lb54:
	add	v111,	v99,	#1
	mov	v308,	v102
	mov	v309,	v103
	mov	v310,	v111
	b	main.label_lb47
main.label_lb49:
	add	v112,	v94,	#1
	mov	v304,	v97
	mov	v305,	v98
	mov	v306,	v99
	mov	v307,	v112
	b	main.label_lb42
main.label_lb44:
	add	v113,	v88,	#1
	mov	v299,	v91
	mov	v300,	v92
	mov	v301,	v93
	mov	v302,	v94
	mov	v303,	v113
	b	main.label_lb37
main.label_lb62:
	mov	v114,	v314
	cmp	v114,	v76
	blt	main.label_lb63
	b	main.label_lb64
main.label_lb39:
	add	v116,	v81,	#1
	mov	v294,	v84
	mov	v295,	v85
	mov	v296,	v86
	mov	v297,	v87
	mov	v298,	v116
	b	main.label_lb32
main.label_lb63:
	mov	v263,	#1
	mul	v264,	v114,	v263
	bl	getint
	mov	v118,	r0
	lsl	v265,	v264,	#2
	ldr	v266,	=list.glo
	str	v118,	[v266,	v265]
	mov	v267,	#1
	mul	v268,	v114,	v267
	lsl	v269,	v268,	#2
	ldr	v270,	=list.glo
	ldr	v120,	[v270,	v269]
	mov	v271,	#1
	mul	v272,	v120,	v271
	mov	v273,	#1
	mul	v274,	v114,	v273
	lsl	v275,	v274,	#2
	ldr	v276,	=list.glo
	ldr	v123,	[v276,	v275]
	mov	v277,	#1
	mul	v278,	v123,	v277
	lsl	v279,	v278,	#2
	ldr	v280,	=cns.glo
	ldr	v125,	[v280,	v279]
	add	v126,	v125,	#1
	lsl	v281,	v272,	#2
	ldr	v282,	=cns.glo
	str	v126,	[v282,	v281]
	add	v127,	v114,	#1
	mov	v314,	v127
	b	main.label_lb62
main.label_lb64:
	ldr	v283,	=cns.glo
	ldr	v129,	[v283,	#4]
	ldr	v284,	=cns.glo
	ldr	v131,	[v284,	#8]
	ldr	v285,	=cns.glo
	ldr	v133,	[v285,	#12]
	ldr	v286,	=cns.glo
	ldr	v135,	[v286,	#16]
	ldr	v287,	=cns.glo
	ldr	v137,	[v287,	#20]
	mov	v288,	#0
	str	v288,	[sp,	#-4]
	str	v137,	[sp,	#-8]
	mov	r3,	v135
	mov	r2,	v133
	mov	r1,	v131
	mov	r0,	v129
	sub	sp,	sp,	#8
	bl	dfs
	add	sp,	sp,	#8
	mov	v138,	r0
	mov	r0,	v138
	bl	putint
	mov	r0,	v138
	b	main.exit
main.exit:
equal:
equal.init:
	mov	v0,	r0
	mov	v1,	r1
	b	equal.label_entry
equal.label_entry:
	cmp	v0,	v1
	beq	equal.label_lb0
	b	equal.label_lb1
equal.label_lb0:
	mov	r0,	#1
	b	equal.exit
equal.label_lb1:
	mov	r0,	#0
	b	equal.exit
equal.exit:
dfs:
dfs.init:
	mov	v3,	r0
	mov	v4,	r1
	mov	v5,	r2
	mov	v6,	r3
	ldr	v7,	[sp,	#0]
	ldr	v8,	[sp,	#0]
	b	dfs.label_entry
dfs.label_entry:
	mov	v139,	#734832
	mul	v140,	v3,	v139
	mov	v141,	#40824
	mul	v142,	v4,	v141
	mov	v143,	#2268
	mul	v144,	v5,	v143
	mov	v145,	#126
	mul	v146,	v6,	v145
	mov	v147,	#7
	mul	v148,	v7,	v147
	mov	v149,	#1
	mul	v150,	v8,	v149
	add	v151,	v140,	v142
	add	v152,	v151,	v144
	add	v153,	v152,	v146
	add	v154,	v153,	v148
	add	v155,	v154,	v150
	lsl	v156,	v155,	#2
	ldr	v157,	=dp.glo
	ldr	v10,	[v157,	v156]
	cmp	v10,	#-1
	bne	dfs.label_lb4
	b	dfs.label_lb5
dfs.label_lb4:
	mov	v158,	#734832
	mul	v159,	v3,	v158
	mov	v160,	#40824
	mul	v161,	v4,	v160
	mov	v162,	#2268
	mul	v163,	v5,	v162
	mov	v164,	#126
	mul	v165,	v6,	v164
	mov	v166,	#7
	mul	v167,	v7,	v166
	mov	v168,	#1
	mul	v169,	v8,	v168
	add	v170,	v159,	v161
	add	v171,	v170,	v163
	add	v172,	v171,	v165
	add	v173,	v172,	v167
	add	v174,	v173,	v169
	lsl	v175,	v174,	#2
	ldr	v176,	=dp.glo
	ldr	v13,	[v176,	v175]
	mov	r0,	v13
	b	dfs.exit
dfs.label_lb5:
	add	v14,	v3,	v4
	add	v15,	v14,	v5
	add	v16,	v15,	v6
	add	v17,	v16,	v7
	cmp	v17,	#0
	beq	dfs.label_lb8
	b	dfs.label_lb9
dfs.label_lb8:
	mov	r0,	#1
	b	dfs.exit
dfs.label_lb9:
	cmp	v3,	#0
	mov	v289,	#0
	bne	dfs.label_lb12
	b	dfs.label_lb13
dfs.label_lb12:
	mov	r1,	#2
	mov	r0,	v8
	bl	equal
	mov	v20,	r0
	sub	v21,	v3,	v20
	sub	v22,	v3,	#1
	mov	v177,	#1
	str	v177,	[sp,	#-4]
	str	v7,	[sp,	#-8]
	mov	r3,	v6
	mov	r2,	v5
	mov	r1,	v4
	mov	r0,	v22
	sub	sp,	sp,	#8
	bl	dfs
	add	sp,	sp,	#8
	mov	v23,	r0
	mul	v24,	v21,	v23
	add	v25,	v24,	#0
	ldr	v178,	=mod.glo
	ldr	v26,	[v178]
	sdiv	v179,	v25,	v26
	mul	v180,	v179,	v26
	sub	v27,	v25,	v180
	mov	v289,	v27
	b	dfs.label_lb13
dfs.label_lb13:
	mov	v28,	v289
	cmp	v4,	#0
	mov	v290,	v28
	bne	dfs.label_lb16
	b	dfs.label_lb17
dfs.label_lb16:
	mov	r1,	#3
	mov	r0,	v8
	bl	equal
	mov	v30,	r0
	sub	v31,	v4,	v30
	add	v32,	v3,	#1
	sub	v33,	v4,	#1
	mov	v181,	#2
	str	v181,	[sp,	#-4]
	str	v7,	[sp,	#-8]
	mov	r3,	v6
	mov	r2,	v5
	mov	r1,	v33
	mov	r0,	v32
	sub	sp,	sp,	#8
	bl	dfs
	add	sp,	sp,	#8
	mov	v34,	r0
	mul	v35,	v31,	v34
	add	v36,	v28,	v35
	ldr	v182,	=mod.glo
	ldr	v37,	[v182]
	sdiv	v183,	v36,	v37
	mul	v184,	v183,	v37
	sub	v38,	v36,	v184
	mov	v290,	v38
	b	dfs.label_lb17
dfs.label_lb17:
	mov	v39,	v290
	cmp	v5,	#0
	mov	v291,	v39
	bne	dfs.label_lb20
	b	dfs.label_lb21
dfs.label_lb20:
	mov	r1,	#4
	mov	r0,	v8
	bl	equal
	mov	v41,	r0
	sub	v42,	v5,	v41
	add	v43,	v4,	#1
	sub	v44,	v5,	#1
	mov	v185,	#3
	str	v185,	[sp,	#-4]
	str	v7,	[sp,	#-8]
	mov	r3,	v6
	mov	r2,	v44
	mov	r1,	v43
	mov	r0,	v3
	sub	sp,	sp,	#8
	bl	dfs
	add	sp,	sp,	#8
	mov	v45,	r0
	mul	v46,	v42,	v45
	add	v47,	v39,	v46
	ldr	v186,	=mod.glo
	ldr	v48,	[v186]
	sdiv	v187,	v47,	v48
	mul	v188,	v187,	v48
	sub	v49,	v47,	v188
	mov	v291,	v49
	b	dfs.label_lb21
dfs.label_lb21:
	mov	v50,	v291
	cmp	v6,	#0
	mov	v292,	v50
	bne	dfs.label_lb24
	b	dfs.label_lb25
dfs.label_lb24:
	mov	r1,	#5
	mov	r0,	v8
	bl	equal
	mov	v52,	r0
	sub	v53,	v6,	v52
	add	v54,	v5,	#1
	sub	v55,	v6,	#1
	mov	v189,	#4
	str	v189,	[sp,	#-4]
	str	v7,	[sp,	#-8]
	mov	r3,	v55
	mov	r2,	v54
	mov	r1,	v4
	mov	r0,	v3
	sub	sp,	sp,	#8
	bl	dfs
	add	sp,	sp,	#8
	mov	v56,	r0
	mul	v57,	v53,	v56
	add	v58,	v50,	v57
	ldr	v190,	=mod.glo
	ldr	v59,	[v190]
	sdiv	v191,	v58,	v59
	mul	v192,	v191,	v59
	sub	v60,	v58,	v192
	mov	v292,	v60
	b	dfs.label_lb25
dfs.label_lb25:
	mov	v61,	v292
	cmp	v7,	#0
	mov	v293,	v61
	bne	dfs.label_lb28
	b	dfs.label_lb29
dfs.label_lb28:
	add	v63,	v6,	#1
	sub	v64,	v7,	#1
	mov	v193,	#5
	str	v193,	[sp,	#-4]
	str	v64,	[sp,	#-8]
	mov	r3,	v63
	mov	r2,	v5
	mov	r1,	v4
	mov	r0,	v3
	sub	sp,	sp,	#8
	bl	dfs
	add	sp,	sp,	#8
	mov	v65,	r0
	mul	v66,	v7,	v65
	add	v67,	v61,	v66
	ldr	v194,	=mod.glo
	ldr	v68,	[v194]
	sdiv	v195,	v67,	v68
	mul	v196,	v195,	v68
	sub	v69,	v67,	v196
	mov	v293,	v69
	b	dfs.label_lb29
dfs.label_lb29:
	mov	v70,	v293
	mov	v197,	#734832
	mul	v198,	v3,	v197
	mov	v199,	#40824
	mul	v200,	v4,	v199
	mov	v201,	#2268
	mul	v202,	v5,	v201
	mov	v203,	#126
	mul	v204,	v6,	v203
	mov	v205,	#7
	mul	v206,	v7,	v205
	mov	v207,	#1
	mul	v208,	v8,	v207
	add	v209,	v198,	v200
	add	v210,	v209,	v202
	add	v211,	v210,	v204
	add	v212,	v211,	v206
	add	v213,	v212,	v208
	ldr	v214,	=mod.glo
	ldr	v72,	[v214]
	sdiv	v215,	v70,	v72
	mul	v216,	v215,	v72
	sub	v73,	v70,	v216
	lsl	v217,	v213,	#2
	ldr	v218,	=dp.glo
	str	v73,	[v218,	v217]
	mov	v219,	#734832
	mul	v220,	v3,	v219
	mov	v221,	#40824
	mul	v222,	v4,	v221
	mov	v223,	#2268
	mul	v224,	v5,	v223
	mov	v225,	#126
	mul	v226,	v6,	v225
	mov	v227,	#7
	mul	v228,	v7,	v227
	mov	v229,	#1
	mul	v230,	v8,	v229
	add	v231,	v220,	v222
	add	v232,	v231,	v224
	add	v233,	v232,	v226
	add	v234,	v233,	v228
	add	v235,	v234,	v230
	lsl	v236,	v235,	#2
	ldr	v237,	=dp.glo
	ldr	v75,	[v237,	v236]
	mov	r0,	v75
	b	dfs.exit
dfs.exit:

