#include <stdio.h>
#include <stdlib.h>
#define NUM 5
typedef struct List
{
    int num;
    char *data;
} List;

List *initHash()
{
    List *list = (List *)malloc(sizeof(List));
    list->num = 0;
    list->data = (char *)malloc(sizeof(char) * NUM);
    for (int i = 0; i < NUM; i++)
    {
        list->data[i] = 0;
    }
    return list;
}

int HashValue(int data)
{
    return data % NUM;
}

void put(List *list, char data)
{
    int index = HashValue(data);
    if (list->data[index] != 0)
    {
        int count = 1;
        while (list->data[index] != 0)
        {
            index = HashValue(HashValue(data) + count);
            count++;
        }
        list->data[index] = data;
    }
    else
    {
        list->data[index] = data;
    }
    list->num++;
}

int main()
{
    List *list = initHash();
    put(list, 'A');
    put(list, 'F');
    put(list, 'C');
    printf("index=0:%c\n", list->data[0]);
    printf("index=1:%c\n", list->data[1]);
    printf("index=2:%c\n", list->data[2]);
    return 0;
}