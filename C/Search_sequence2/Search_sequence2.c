#include <stdio.h>
#include <stdlib.h>
/* 本次查找算法是顺序查找中的哨兵算法，即数组的第一个值放入要查找的值，数组从index=1（包括他）以后才放入数组存入的值 */
typedef struct List
{
    int *data;
    int length; /* 数组的长度如何 */
    int num;    /* 用来标记数组里面现在的元素是多少 */
} List;

List *initList(int length)
{
    List *list = (List *)malloc(sizeof(List));
    list->data = (int *)malloc(sizeof(int) * length);
    list->length = length;
    list->num = 1; /* 定位下一个要插入元素的位置，起始时第一个元素插入在index为1的位置上 */
    return list;
}

void Addlist(List *list, int data)
{
    list->data[list->num] = data;
    list->num = list->num + 1;
}

void printList(List *list)
{
    for (int i = 0; i < list->length; i++)
    {
        printf("%d\t", list->data[i]);
    }
}

int Sequence_Search(List *list, int key)
{
    int i;
    list->data[0] = key;
    for (i = (list->length) - 1; list->data[i] != key; i--)
    {
        /* 进入for循环则说明还未找到目标数值*/
    }
    return i;
}
int main()
{
    int length = 5;
    List *list = initList(5);
    Addlist(list, 4);
    Addlist(list, 3);
    Addlist(list, 2);
    Addlist(list, 1);
    printList(list);
    printf("\n");
    printf("目标数值2的index是(若是0则没有找到):%d\n", Sequence_Search(list, 2));
    printf("目标数值1的index是(若是0则没有找到):%d\n", Sequence_Search(list, 1));
    printf("目标数值6的index是(若是0则没有找到):%d\n", Sequence_Search(list, 6));
}
