#include <stdio.h>
#include <stdlib.h>
typedef struct String
{
    char *data; /* data代表字符串数组的首地址，通过data指针来操作字符串数组*/
    int length; /* 字符串内元素的长度 */
} String;
/* 初始化结构体 */
String *initString()
{
    String *S = (String *)malloc(sizeof(String)); /* 开辟出空间，将该空间的地址传给指针Q */
    S->data = NULL;
    S->length = 0;
    return S;
}
/* 将字符串传入字符串数组 */
void StringAssign(String *S, char *data) /* 这里面的data指被传入字符串的首地址 ，因为要将字符串传进来，传其首地址即可。此处的char*data的另外一种表达形式是char data[],同样data代表首地址  */
{
    /* 将系统分配给data的地址删除掉 */
    if (S->data)
    {
        free(S->data);
    }
    /* 计算被传入的字符串的长度 */
    int len = 0;       /* 代表字符串长度 */
    char *temp = data; /* 另设指针temp，保存传进来的字符串的首地址 */
    while (*temp)
    {
        len++;
        temp++;
    }
    /* 进行给字符串数组传入字符串 */
    if (len == 0)
    {
        S->length = 0;
        S->data = NULL;
    }
    else
    {
        S->data = (char *)malloc(sizeof(char) * (len + 1)); /* 为字符串数组开辟空间,len+1是因为字符串以“\0”作为标志结尾 */
        S->length = len;
        temp = data;
        for (int i = 0; i < len; i++)
        {
            S->data[i] = *temp;
            temp++;
        }
    }
}
/* 打印字符串 */
void printString(String *S)
{
    for (int i = 0; i < S->length; i++)
    {
        printf(i == 0 ? "%c" : "->%c", S->data[i]); /* 看这个printf的应用 */
    }
    printf("\n");
}

/* 暴力匹配 */
void forcematch(String *master, String *sub)
{
    int i = 0; /* i为指向主串的指针 */
    int j = 0; /* j为指向子串的指针 */
    while (i < master->length && j < sub->length)
    {
        if (master->data[i] == sub->data[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1; /* 回溯 */
            j = 0;
        }
    }
    if (j >= sub->length)
    {
        printf("匹配成功\n");
    }
    else
    {
        printf("匹配未成功\n");
    }
}

int main()
{
    String *master = initString();
    String *sub = initString();
    StringAssign(master, "hello"); /* 这里在函数中，实际上是,data指针接收hello的首地址 */
    StringAssign(sub, "he");
    printString(master);
    printString(sub);
    forcematch(master, sub);
    return 0;
}