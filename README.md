# BigInteger_MUL
This is a note which records my research process.记录大数运算相关的研究
最近在研究ARM底层大数运算相关的问题，想要复现《Multiprecision Multiplication on ARM v8》中的算法。
在复现过程中发现了计算机底层一些容易忽视的问题，比如计算2个64位无符号整数相乘的结果，在通过MUL或者UMUL指令运算时，128位的结果中只有低64位是正确的的，而高64位是缺失进位以及中间值的。
通过再次重新用School-method进行计算，结果正确。说明了计算机在计算超出寄存器储存长度的结果时，是能够在内存中获得真正结果的，而ARMv8不能直接对内存进行操作，导致一直出现这个问题。最好的方法就是老实的用school-method计算。
	-2023年8月19日20:22🕠
In recently, I'm studying the operations of unsigned big integers. I want to recurrent the result of the paper 'Multiprecision Multiplication on ARM v8'.
And here is a question. When I calculate the result of multiplying 2 unsigned big integers, only low 64 bits of the result are correct. High 64 bits are wrong and lost many values.
Try to use school-method to calculate this problem. And the result is right.
This means CPU can get the right result of this problem. But we don't have this kind of registers like 128 bits. 
So CPU stores a part of the right result into 64 bits register.

# 更新Update 2023-8-20 14:42:20
在将程序直接放到ARM运行时，有趣的事情发生了，在X86平台下，程序段carry1=carry1>>64时，采用的是算术右移，由0填充。而在ARM下，经过测试，当取移位为64以下时才是正常的算术移位，比如63，而采用64时，程序会使用逻辑右移，且直接移动64位，导致carry1的值并没有变化，从而得出错误的进位结果。目前的解决方法为右移一位取最高或者右移63位取次低。
但是通过对carry1和carry2的观察，发现无论何时这两项都为0，移位是否能够起到保留进位的效果？
