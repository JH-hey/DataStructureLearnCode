#include <stdio.h>
#include <stdlib.h>
typedef struct String
{
    char *data;
    int len;
} String;

/* 初始化结构体 */
String *initString()
{
    String *S = (String *)malloc(sizeof(String));
    S->data = NULL;
    S->len = 0;
    return S;
}

/* 给字符串赋值 */
void StringAssign(String *S, char *data)
{
    /* 计算输入的字符串有多长 */
    int len = 0;
    char *temp = data;
    while (*temp)
    {
        len++;
        temp++;
    }
    /* 开辟字符串空间 */
    S->data = (char *)malloc(sizeof(char) * (len + 1));
    S->len = len;
    temp = data;
    /* 进行赋值 */
    for (int i = 0; i < len; i++)
    {
        S->data[i] = *temp;
        temp++;
    }
}

/* 获得next数组，这里的next数组就是最长相等前后缀长度 */
int *getnext(String *S) /* S是模式串 */
{
    int *next = (int *)malloc(sizeof(int) * S->len); /* 为next数组开辟空间 */
    int j = 0;                                       /* 指向前缀的末尾位置，即代表最长相等前后缀长度 */
    next[0] = 0;                                     /* 第一个的公共前后缀长度为0 */
    for (int i = 1; i < S->len; i++)                 /* i指向后缀的末尾位置 */
    {
        /* 前后缀不同时 */
        while (j > 0 && S->data[i] != S->data[j]) /* j>0的条件是因为，如果j退回到data[0]时，不再继续往后退 */
        {
            j = next[j - 1];
        }
        /* 前后缀相同时 */
        if (S->data[i] == S->data[j])
        {
            j++;
        }
        /*更新next值  */
        next[i] = j;
    }
    return next;
}
/* 遍历打印字符串 */
void printString(String *S)
{
    for (int i = 0; i < S->len; i++)
    {
        printf(i == 0 ? "%c" : "->%c", S->data[i]);
    }
    printf("\n");
}

/* 遍历打印next */
void printnext(int *next, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf(i == 0 ? "%d" : "%d", next[i]);
    }
    printf("\n");
}
/* KMP算法 */
void KMP(String *master, String *sub, int *next)
{
    int i = 0; /* 指向主串的第一位 */
    int j = 0; /* 指向子串的第一位 */
    while (i < master->len || j < sub->len)
    {
        if (j == 0 || master->data[i] == sub->data[j]) /* 这里要注意条件j==0，虽然我也不知道为啥... */
        {
            i++;
            j++;
        }
        else
        {
            j = next[j - 1]; /* kmp算法体现 */
        }
    }
    if (j == sub->len)
    {
        printf("success\n");
    }
    else
    {
        printf("unsuccess\n");
    }
}

int main()
{
    /* 主串 */
    String *master = initString();
    StringAssign(master, "ababcabcacbab");
    printString(master);
    /* 子串 */
    String *sub = initString();
    StringAssign(sub, "abcac");
    printString(sub);
    int *next = getnext(sub);
    printnext(next, sub->len);
    KMP(master, sub, next);
    return 0;
}