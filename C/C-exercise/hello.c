/* #include <stdio.h>
int main()
{
    int a[3] = {4, 5, 6}; // 数组的a就是首地址
    int *p = a;
    printf("%d%d%d\n", a[0], a[1], a[2]);
    printf("%d%d%d\n", *a, *(a + 1), *(a + 2));
    printf("%d%d%d\n", p[0], p[1], p[2]);
    printf("%d%d%d\n", *p, *(p + 1), *(p + 2));
} */

/* #include <stdio.h>
int main()
{
    int a[3] = {3, 4, 5};
    int *p = a;
    printf("%d%d%d\n", (a + 1)[0], (a + 1)[1], (a + 2)[0]);
    printf("%d%d%d\n", (p + 1)[0], (p + 1)[1], (p + 2)[0]);
    return 0;
} */

/* #include <stdio.h>
int main()
{
    int a[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int(*p)[3] = a;
    printf("%d\n", (*(p + 1))[0]);
    printf("%d\n", *(*p + 2));
    printf("%d\n", (*a)[2]);
    return 0;
} */
/* #include <stdio.h>
int main()
{
    int a = 6;
    printf("%d\n", ++a);
    printf("%d", a);
    return 0;
} */

/* #include <stdio.h>
int main()
{
    char grade;
    printf("enter your grades:");
    scanf("%c", &grade);
    switch (grade)
    {
    case 'A':
        printf("Good\n");
        break;
    case 'B':
        printf("Not bad\n");
        break;
    case 'C':
        printf("Come on!\n");
        break;
    default:
        printf("Error!\n");
        break;
    }
    return 0;
}
 */

/* #include <stdio.h>
int main()
{
    int a, b;
    printf("请输入两个数：\n");
    scanf("%d", &a);
    scanf("%d", &b);
    computing(a, b);
}

int computing(int a, int b)
{
    int n, max;
    printf("1----相加\n");
    printf("2----相乘\n");
    printf("3----相除\n");
    printf("4----相减\n");
    printf("5----得大\n");
    printf("输入你的需求：\n");
    scanf("%d", &n);
    switch (n)
    {
    case 1:
        printf("%d", a + b);
        break;
    case 2:
        printf("%d", a * b);
        break;
    case 3:
        printf("%d", a / b);
        break;
    case 4:
        printf("%d", a - b);
        break;
    case 5:
        printf("%d", max = a > b ? a : b);
        break;
    default:
        printf("error!");
        break;
    }
}
 */

/* #include <stdio.h>
int main()
{
    int i;
    int sum = 0;
    int k = -1;
    for (i = 1; i <= 100; i++)
    {
        k = -1 * k;
        sum = sum + k * i;
    }
    printf("%d\n", sum);
    return 0;
} */

/* #include <stdio.h>
int main()
{
    int x, y;
    int min, i;
    printf("请输入两个数：\n");
    scanf("%d", &x);
    scanf("%d", &y);
    min = x < y ? x : y;
    for (i = min; i >= 1; i--)
    {
        if (x % i == 0 && y % i == 0)
        {
            break;
        }
    }
    printf("最大公约数为：%d\n", i);
} */

/* 求三位数的水仙花数 */
/* #include <stdio.h>
int main()
{

    for (int n = 100; n < 999; n++)
    {
        if (n == water(n))
        {
            printf("%d\n", n);
        }
    }

    return 0;
}
int water(int x)
{
    int i, j, z, y, sum;
    i = x / 100; // i为百位数
    j = x % 100; // j拿到后面两个
    z = j / 10;  // z为十位数
    y = j % 10;  // y为个位数
    sum = i * i * i + z * z * z + y * y * y;
    return sum;
} */

/* #include <stdio.h>
int main()
{

    int n = 4;
    int a = 3;
    int y = a;
    int s = 0;
    for (int count = 1; count <= n; count++)
    {
        s = s + a;
        a = a * y;
    }
    printf("%d\n", s);

    return 0;
} */
/* #include <stdio.h>
int main()
{
    int a;
    int n;
    int s = 0;
    int y;
    printf("给a赋值:\n");
    scanf("%d", &a);
    printf("给n赋值:\n");
    scanf("%d", &n);
    y = a;
    for (int count = 1; count <= n; count++)
    {
        s = s + a;
        a = a * 10 + y;
    }
    printf("%d", s);
    return 0;
} */

 #include <stdio.h>
int main()
{
    int a = 3;
    printf("%d", fact(a));
    return 0;
}
int fact(int n)
{
    if (n <= 1)
    {
        return 1;
    }
    else
    {
        return n * fact(n - 1);
    }
} 
