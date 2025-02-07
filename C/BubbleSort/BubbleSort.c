#include <stdlib.h>
#include <stdio.h>

void printArray(int *array, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d\t", array[i]);
    }
    printf("\n");
}
void Bubblesort(int *array, int length)
{
    for (int i = 0; i < length - 1; i++) /* 外层循环n-1次，代表总共要循环n-1次 */
    {
        for (int j = 0; j < length - 1 - i; j++) /* 外层每循环一次，内层就要循环n-1-i次。例如第一次内层要循环7（8-1），第二次循环6次（8-1-1），第三次循环5次（8-1-2） */
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
        printArray(array, length);
    }
}

int main()
{
    int array[8] = {49, 38, 65, 97, 76, 13, 27, 49};
    printArray(array, 8);
    printf("开始冒泡:\n");
    Bubblesort(array, 8);
    return 0;
}