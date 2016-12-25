#include <stdio.h>
#include <stdlib.h>

int example(int argc, char* argv[])
{
    return 0;
}

#if defined(__arm__)
void example_1()
{
    __asm__ __volatile__(
        "ADD R0,R0,#1 \n"
        "SUB R0,R0,#1"
    );
}

/*
__inline void endable_IRQ(void)
{
    int tmp;
    __asm{
        MRS tmp,CPSR
        BIC tmp,tmp,#0x80
        MSR CPSR_c,tmp
    }
}
*/

void example_2()
{
    __asm__ __volatile__(
        "mov r0,r0\n"
        "mov r1,r1\n"
        "mov r2,r2"
    );
}

/* 使用占位符 */
void example_3()
{
    int a = 100;
    int b = 200;
    int result;
    __asm__ __volatile__(
        "mov %0, %3\n"
        "ldr r0, %1\n"
        "ldr r1, %2\n"
        "str r0, %2\n"
        "str r1, %1\n"
        :"=r"(result),"+m"(a),"+m"(b)
        :"i"(123)
    );
}

/* 引用占位符 */
void example_4()
{
    int num = 100;
    __asm__ __volatile__(
        "add %0,%1,#100\n"
        :"=r"(num)
        :"0"(num) /* 0 就是%0，引用时不必加% */
    );
    
    /* &修饰符 */
    __asm__ __volatile__(
        "mov %0,%1\n"
        :"=r"(num)
        :"r"(123)
    );
    
    __asm__ __volatile__(
        "mov %0,%1\n"
        :"=&r"(num)
        :"r"(123)
    );
    
    /* changed */
    __asm__ __volatile__(
        "mov r4,#123"
    
    );
    __asm__ __volatile__(
        "mov r4,#123"
        :
        :
        :"r4"
    );
}
#endif