**任务3-1**

* Clang编译产生的32位汇编码

    ```assembly
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
            movl    12(%ebp), %eax          # 把ebp+12地址所存的内容(参数size)赋给eax
            movl    8(%ebp), %ecx			# 把ebp+8地址所存的内容(参数array首地址)赋给ecx
            movl    $1, -4(%ebp)            # int i = 1
    .LBB0_1:                                # =>This Loop Header: Depth=1
                                            #     Child Loop BB0_3 Depth 2
            movl    -4(%ebp), %eax          # 移动i的值到eax寄存器
            cmpl    12(%ebp), %eax          # 比较i和传入的size(位于ebp+12)
            jge     .LBB0_9                 # 如果i>=size就跳转至.LBB0_9
    # %bb.2:                                #   in Loop: Header=BB0_1 Depth=1
            movl    -4(%ebp), %eax          # 开始执行for循环体
            subl    $1, %eax				# i - 1
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
            movl    8(%ebp), %eax			# eax = array首地址
            movl    -8(%ebp), %ecx			# ecx = j
            movl    (%eax,%ecx,4), %eax		# eax = array[j]
            cmpl    -12(%ebp), %eax			# 比较key和array[j]
            setg    %dl						# key > array[j]时设置dl标志位为1
            movb    %dl, -13(%ebp)          # 1-byte Spill
    .LBB0_5:                                #   in Loop: Header=BB0_3 Depth=2
            movb    -13(%ebp), %al          # 1-byte Reload
            testb   $1, %al					# 两个操作数进行AND运算但不改变操作数的值，并设置标志位
            jne     .LBB0_6					# 不等于时跳转至.LBB0_6
            jmp     .LBB0_7num + num + a[num]	# 跳转
    .LBB0_6:                                #   in Loop: Header=BB0_3 Depth=2
            movl    8(%ebp), %eax           # 取传入的数组array的首地址
            movl    -8(%ebp), %ecx          # 取索引j
            movl    (%eax,%ecx,4), %eax     # 取array[j]
            movl    8(%ebp), %ecx           # 取array首地址
            movl    -8(%ebp), %edx          # 取索引j
            movl    %eax, 4(%ecx,%edx,4)    # array[j+1] = array[j]
            movl    -8(%ebp), %eax          # eax = j
            addl    $-1, %eax               # j--
            movl    %eax, -8(%ebp)          # j自减后存回栈中对应位置
            jmp     .LBB0_3                 # 跳转至while循环入口
    .LBB0_7:                                #   in Loop: Header=BB0_1 Depth=1
            movl    -12(%ebp), %eax         # 取keynum + num + a[num]
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
            leal    .L.str, %ecx			# 把.L.str字符串("%d")的首地址放进ecx
            movl    %ecx, (%esp)			# 把ecx的内容放进esp所指的位置(传递给scanf的参数)
            movl    %eax, 4(%esp)			# 把eax的内容放进esp+4所指的位置(传递给scanf的参数)
            calll   __isoc99_scanf          # 调用scanf()
    # %bb.5:                                #   in Loop: Header=BB1_3 Depth=1
            movl    -16(%ebp), %eax         # 取i
            addl    $1, %eax                # ++i
            movl    %eax, -16(%ebp)         # i自增后存回栈对应位置
            jmp     .LBB1_3                 # 跳转回到.LBB1_3，准备开始下一轮循环
    .LBB1_6:
            movl    -12(%ebp), %eax         # for循环退出后跳转到这里 eax = array首地址
            movl    -8(%ebp), %ecx			# ecx = size
            movl    %eax, (%esp)			# 将eax的内容存进esp所指位置(传递给sort的参数array首地址)
            movl    %ecx, 4(%esp)			# 把ecx的内容存进esp+4所指位置(传递给sort的参数size)
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
            leal    .L.str.1, %ecx			# 把字符串"%d "的首地址赋给ecx
            movl    %ecx, (%esp)			# 把ecx的内容放到esp所指位置(传递参数"%d "给printf)
            movl    %eax, 4(%esp)			# 把eax的内容放到esp+4所指位置(传递参数array[i]给printf)
            calll   printf                  # 调用printf
    # %bb.9:                                #   in Loop: Header=BB1_7 Depth=1
            movl    -20(%ebp), %eax         # 索引i
            addl    $1, %eax                # ++i
            movl    %eax, -20(%ebp)         # i自增后存回栈对应位置
            jmp     .LBB1_7                 # 跳转回执行下一轮循环
    .LBB1_10:
            xorl    %eax, %eax              # 将eax置为0(return的返回值)
            addl    $40, %esp				# esp += 40
            popl    %ebp					# 出栈，栈顶内容赋给ebp
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
    
    ```

**任务3-2**

不同编译选项( `-O2`, `-O0` )下输出汇编文件的区别和原因：
* `-O2` 编译出来的汇编代码少很多(只有36行)，而 `-O0` 编译出来的汇编代码相比之下就很多(129行)。

* 对于 `exp_compute()` 函数，不优化时会为 m, n, x, y 分配栈空间、用寄存器赋值等，使用时需要进行地址计算、移动到寄存器后再使用等需要较多指令，但运行时这四个变量的实际作用是作为整数值32和2来使用，所以编译器 `-O2` 优化直接不进行变量定义(分配栈空间、赋值)，而是在需要用到 x 和 y 的地方直接用立即数32和2来代替，可以减少很多指令。

* 对于 `ccp()` 函数，`-O0` 生成的汇编代码将近40行，而 `-O2` 生成的只有两行

    ```assembly
    movs r0, #1
    bx lr
    ```

    只有给一个寄存器赋值为1然后退出函数(返回)，是因为这个函数里面的 if 分支实际上都不会执行，x 的值保持为1不变到最后返回，编译器识别出来就进行优化，两条指令就可以表示这个函数的功能。

* 对于 `square()` 函数，其内部定义了一个含100个 int 元素的数组，然后用了一个 for 循环给每个元素赋值，最后要计算 num + num + a[num]；不优化时会有大量的 store 和 load 在栈空间和寄存器之间存取，计算时也是使用最基本的 add、sub 和 mul，`-O2` 优化时减少了很多 store 和 load 指令，通过两个寄存器(一个用于暂存索引，另一个用于存放数组首地址)就可以实现整个数组的初始化，最后也是使用一条 `mla` 指令就完成了num + num + a[num] 的计算。



