.text
        .file   "sort.c"
        .globl  sort                    # -- Begin function sort
        .p2align        4, 0x90
        .type   sort,@function
sort:                                   # @sort
# %bb.0:
        pushl   %ebp 	                # 将ebp的值(main的栈底地址)存进esp-4
        movl    %esp, %ebp              # 开辟sort的“小栈”，其栈底地址就是main的栈顶地址-4
        subl    $16, %esp               # 将sort的栈顶往低地址移动16字节
        movl    12(%ebp), %eax          
        movl    8(%ebp), %ecx
        movl    $1, -4(%ebp)            # int i = 1
.LBB0_1:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_3 Depth 2
        movl    -4(%ebp), %eax          # 移动i的值到eax寄存器
        cmpl    12(%ebp), %eax          # 比较i和传入的size
        jge     .LBB0_9                 # 如果i>=size就跳转至.LBB0_9
# %bb.2:                                #   in Loop: Header=BB0_1 Depth=1
        movl    -4(%ebp), %eax          # 开始执行for循环体
        subl    $1, %eax
        movl    %eax, -8(%ebp)          # int j = i - 1
        movl    8(%ebp), %eax           # 取传入的数组array的首地址
        movl    -4(%ebp), %ecx          # 索引i
        movl    (%eax,%ecx,4), %eax     # 取array[i]
        movl    %eax, -12(%ebp)         # int key = array[i]
.LBB0_3:                                #   Parent Loop BB0_1 Depth=1
                                # =>  This Inner Loop Header: Depth=2
        xorl    %eax, %eax              # eax置0
                                        # kill: def $al killed $al killed $eax
        cmpl    $0, -8(%ebp)            # 比较0和j
        movb    %al, -13(%ebp)          # 1-byte Spill
        jl      .LBB0_5                 # jump and link，跳转至.LBB0_5
# %bb.4:                                #   in Loop: Header=BB0_3 Depth=2
        movl    8(%ebp), %eax
        movl    -8(%ebp), %ecx
        movl    (%eax,%ecx,4), %eax
        cmpl    -12(%ebp), %eax
        setg    %dl
        movb    %dl, -13(%ebp)          # 1-byte Spill
.LBB0_5:                                #   in Loop: Header=BB0_3 Depth=2
        movb    -13(%ebp), %al          # 1-byte Reload
        testb   $1, %al
        jne     .LBB0_6
        jmp     .LBB0_7
.LBB0_6:                                #   in Loop: Header=BB0_3 Depth=2
        movl    8(%ebp), %eax           # 取传入的数组array的首地址
        movl    -8(%ebp), %ecx          # 取索引j
        movl    (%eax,%ecx,4), %eax     # 取array[j]
        movl    8(%ebp), %ecx           # 取array首地址
        movl    -8(%ebp), %edx          # 取索引j
        movl    %eax, 4(%ecx,%edx,4)    # array[j+1] = array[j]
        movl    -8(%ebp), %eax          
        addl    $-1, %eax               # j--
        movl    %eax, -8(%ebp)          # j自减后存回栈中对应位置
        jmp     .LBB0_3                 # 跳转至while循环入口
.LBB0_7:                                #   in Loop: Header=BB0_1 Depth=1
        movl    -12(%ebp), %eax         # 取key
        movl    8(%ebp), %ecx           # 取array首地址
        movl    -8(%ebp), %edx          # 取j
        movl    %eax, 4(%ecx,%edx,4)    # array[j+1] = key
# %bb.8:                                #   in Loop: Header=BB0_1 Depth=1
        movl    -4(%ebp), %eax          # 取i
        addl    $1, %eax                # ++i
        movl    %eax, -4(%ebp)          # i自增后存回栈中对应位置
        jmp     .LBB0_1                 # 跳转回for循环入口
.LBB0_9:
        xorl    %eax, %eax              # eax置0
        addl    $16, %esp               # 处理栈顶指针
        popl    %ebp                    # 处理栈底指针
        retl                            # return 0
.Lfunc_end0:
        .size   sort, .Lfunc_end0-sort
                                        # -- End function
        .globl  main                    # -- Begin function main
        .p2align        4, 0x90
        .type   main,@function
main:                                   # @main
# %bb.0:
        pushl   %ebp			# 将main函数之前一个函数的栈底地址入栈
        movl    %esp, %ebp		# 把main之前的函数的栈顶地址值赋给栈底寄存器，开辟main函数的"小栈"
        subl    $40, %esp		# 栈顶地址向低地址移动40字节，分配栈空间
        movl    12(%ebp), %eax		# ebp+12所指地址的内容赋给eax
        movl    8(%ebp), %ecx		# ebp+8所指地址的内容赋给ecx
        movl    $0, -4(%ebp)		# 将0存进ebp-4所指地址(该地址分配给变量size，并初始化为0)
        leal    .L.str, %edx		# 把.L.str地址的内容存进edx	
        movl    %edx, (%esp)            # 把edx的内容存进esp所指地址(栈顶)
        leal    -8(%ebp), %edx          # 把ebp-8所指地址的内容存进edx
        movl    %edx, 4(%esp)           # 把edx的内容存进esp+4所指地址
        movl    %eax, -24(%ebp)         # 4-byte Spill 把eax内容存进ebp-24所指地址
        movl    %ecx, -28(%ebp)         # 4-byte Spill 把ecx内容存进ebp-28所指地址
        calll   __isoc99_scanf          # 调用scanf()
        movl    -8(%ebp), %ecx          # 把ebp-8所指地址的内容存进ecx
        shll    $2, %ecx                # 将ecx所存的值左移2位
        movl    %ecx, (%esp)            # 把ecx内容存进栈顶
        movl    %eax, -32(%ebp)         # 4-byte Spill 把eax内容存进ebp-32所指地址
        calll   malloc                  # 调用malloc()，分配到的指针值会存进eax
        movl    %eax, -12(%ebp)         # 把eax内容存进ebp-12所指地址(即变量array)
        cmpl    $0, -12(%ebp)           # 比较ebp-12所指地址的内容(malloc分配的指针值)和0的大小
        jne     .LBB1_2                 # 如果不等于就跳转到.LBB1_2
# %bb.1:
        movl    $-1, (%esp)             # 如果malloc分配的指针值等于0(malloc失败)，就将-1赋给栈顶
        calll   exit                    # 调用exit()
.LBB1_2:
        movl    $0, -16(%ebp)           # 将0赋给ebp-16所指地址(对应int i = 0)
.LBB1_3:                                # =>This Inner Loop Header: Depth=1
        movl    -16(%ebp), %eax         # 把ebp-16地址的内容(0)赋给eax
        cmpl    -8(%ebp), %eax          # 比较ebp-8地址的内容(size)与eax(0)的大小
        jge     .LBB1_6                 # 如果eax >= -8(%ebp) (即i>=size)就跳转到.LBB1_6
# %bb.4:                                #   in Loop: Header=BB1_3 Depth=1
        movl    -12(%ebp), %eax         # 开始执行第一个for循环体 取array首地址
        movl    -16(%ebp), %ecx         # 取偏移量(数组下标i)
        shll    $2, %ecx                # 左移2位，以4字节(int型大小)为单位偏移
        addl    %ecx, %eax              # 数组首地址加偏移量得到array[i]的地址
        leal    .L.str, %ecx
        movl    %ecx, (%esp)
        movl    %eax, 4(%esp)
        calll   __isoc99_scanf          # 调用scanf()
# %bb.5:                                #   in Loop: Header=BB1_3 Depth=1
        movl    -16(%ebp), %eax         # 取i
        addl    $1, %eax                # ++i
        movl    %eax, -16(%ebp)         # i自增后存回栈对应位置
        jmp     .LBB1_3                 # 跳转回到.LBB1_3，准备开始下一轮循环
.LBB1_6:
        movl    -12(%ebp), %eax         # for循环退出后跳转到这里
        movl    -8(%ebp), %ecx
        movl    %eax, (%esp)
        movl    %ecx, 4(%esp)
        calll   sort                    # 调用sort
        movl    $0, -20(%ebp)           # 将0赋给ebp-20所指地址(int i = 0)
.LBB1_7:                                # =>This Inner Loop Header: Depth=1
        movl    -20(%ebp), %eax         # 把0取出来，开始第二个for循环(print数组)
        cmpl    -8(%ebp), %eax          # 比较size和i
        jge     .LBB1_10                # 如果i>=size就退出循环，跳转到.LBB1_10
# %bb.8:                                #   in Loop: Header=BB1_7 Depth=1
        movl    -12(%ebp), %eax         # 开始执行for循环体，取array首地址
        movl    -20(%ebp), %ecx         # 索引i
        movl    (%eax,%ecx,4), %eax     # 取出array[i]
        leal    .L.str.1, %ecx
        movl    %ecx, (%esp)
        movl    %eax, 4(%esp)
        calll   printf                  # 调用printf
# %bb.9:                                #   in Loop: Header=BB1_7 Depth=1
        movl    -20(%ebp), %eax         # 索引i
        addl    $1, %eax                # ++i
        movl    %eax, -20(%ebp)         # i自增后存回栈对应位置
        jmp     .LBB1_7                 # 跳转回执行下一轮循环
.LBB1_10:
        xorl    %eax, %eax              # 将eax置为0(return的返回值)
        addl    $40, %esp
        popl    %ebp
        retl                            # 退出main函数
.Lfunc_end1:
        .size   main, .Lfunc_end1-main
                                        # -- End function
        .type   .L.str,@object          # @.str
        .section        .rodata.str1.1,"aMS",@progbits,1
.L.str:
        .asciz  "%d"
        .size   .L.str, 3

        .type   .L.str.1,@object        # @.str.1
.L.str.1:
        .asciz  "%d "
        .size   .L.str.1, 4

        .ident  "clang version 10.0.1 "
        .section        ".note.GNU-stack","",@progbits
        .addrsig
        .addrsig_sym sort
        .addrsig_sym __isoc99_scanf
        .addrsig_sym malloc
        .addrsig_sym exit
        .addrsig_sym printf
