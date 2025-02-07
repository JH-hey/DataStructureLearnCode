#include <stdio.h>
#include <stdlib.h>
int m = 0;
void Move(int n, char X, char Z, char Y) /* n是移动的盘数，X为盘子起点，Z为目标，Y为辅助 */
{
    m++;
    if (n == 1)
    {
        printf("%c->%c\n", X, Z);
    }
    else
    {
        Move(n - 1, X, Y, Z);     /* X->Y||将n-1个盘子，从X弄到Y，  Z作为辅助 */
        printf("%c->%c\n", X, Z); /* X->Z||将第n个从X弄到Z */
        Move(n - 1, Y, Z, X);     /* Y->Z||将之前弄到Y上的n-1个弄到Z，X作为辅助 */
    }
}
int main()
{
    char A, B, C;           /* 定义三根柱子 */
    Move(3, 'A', 'C', 'B'); /*将3个盘子，从A弄到C， B作为辅助 */
    printf("%d\n", m);      /* 移动次数 */
}