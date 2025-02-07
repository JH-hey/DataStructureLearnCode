#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
    int *data;
    int length; /* 数组的长度如何 */
    int num;    /* 用来标记数组里面现在的元素是多少&&也可以用来定位当前数组中最后一个元素的index值 */
} List;

List *initList(int length)
{
    List *list = (List *)malloc(sizeof(List));
    list->data = (int *)malloc(sizeof(int) * length);
    list->length = length;
    list->num = 0;
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
    int index;
    for (int i = 0; i < list->length; i++)
    {
        if (list->data[i] == key)
        {
            index = i;
            return index;
        }
    }
    return -1;
}
int main()
{
    int length = 4;
    List *list = initList(4);
    Addlist(list, 4);
    Addlist(list, 3);
    Addlist(list, 2);
    Addlist(list, 1);
    printList(list);
    printf("\n");
    printf("%d\n", Sequence_Search(list, 2));
    printf("%d\n", Sequence_Search(list, 6));
}
