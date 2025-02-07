#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
    int *data;
    int length;
    int num;
} List;

List *initList(int length)
{
    List *list = (List *)malloc(sizeof(List));
    list->data = (int *)malloc(sizeof(int) * length);
    list->length = length;
    list->num = 0;
    return list;
}

void addlist(List *list, int data)
{
    list->data[list->num] = data;
    list->num = list->num + 1;
}

void printlist(List *list)
{
    for (int i = 0; i < list->num; i++)
    {
        printf("%d\t", list->data[i]);
    }
}

int BinarySearch(List *list, int key)
{
    int start = 0;
    int end = (list->num) - 1;
    int mid;
    while (start <= end)
    {
        mid = (start + end) / 2;
        if (key > list->data[mid])
        {
            start = mid + 1;
        }
        else if (key < list->data[mid])
        {
            end = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}
int BinarySearch_recursion(List *list, int start, int end, int key)
{

    if (start == end)
    {
        if (list->data[start] == key)
        {
            return start;
        }
        else
        {
            return -1;
        }
    }
    int mid = (start + end) / 2;
    if (list->data[mid] < key)
    {
        return BinarySearch_recursion(list, mid + 1, end, key);
    }
    else if (list->data[mid] > key)
    {
        return BinarySearch_recursion(list, start, mid - 1, key);
    }
    else
        return mid;
}

int main()
{
    List *list = initList(9);
    addlist(list, 1);
    addlist(list, 2);
    addlist(list, 3);
    addlist(list, 4);
    addlist(list, 5);
    addlist(list, 6);
    addlist(list, 7);
    addlist(list, 8);
    addlist(list, 9);
    printlist(list);
    printf("\n");
    /* printf("8的index是(结果是-1表示没有找到):%d\n", BinarySearch(list, 8));
    printf("10的index是(结果是-1表示没有找到):%d\n", BinarySearch(list, 10)); */
    printf("8的index是(结果是-1表示没有找到):%d\n", BinarySearch_recursion(list, 0, (list->num) - 1, 8));
    printf("10的index是(结果是-1表示没有找到):%d\n", BinarySearch_recursion(list, 0, (list->num) - 1, 10));
}
