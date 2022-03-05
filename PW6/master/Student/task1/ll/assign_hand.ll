define i32 @main() {													;main function
	%1 = alloca float, align 4											;float b
	store float 0x3FFCCCCCC0000000, float* %1, align 4					;b = 1.8
	%2 = alloca [2 x i32], align 4										;int a[2]
	%3 = getelementptr inbounds [2 x i32], [2 x i32]* %2, i32 0, i32 0	;a[0]'s addr
	%4 = getelementptr inbounds [2 x i32], [2 x i32]* %2, i32 0, i32 1	;a[1]'s addr
	store i32 2, i32 *%3, align 4										;initialize a[0]
	%5 = load i32, i32 *%3, align 4										;a[0]'s value
	%6 = sitofp i32 %5 to float											;a[0] -> float
	%7 = load float, float *%1, align 4 								;b's value
	%8 = fmul float %6, %7												;a[0] * b
	%9 = fptosi float %8 to i32											;a[0] * b -> i32
	store i32 %9, i32* %4, align 4										;a[1] = a[0] * b
	%10 = load i32,i32 *%4, align 4										;a[1]'s value
	ret i32 %10															;return a[1]
}
