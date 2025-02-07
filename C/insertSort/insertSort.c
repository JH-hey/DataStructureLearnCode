#include <stdio.h>
#include <stdlib.h>

void printArray(int *array, int length)
{
    printf("\n");
    for (int i = 0; i < length; i++)
    {
        printf("%d\t", array[i]);
    }
}
void InsertSort(int *array, int length)
{
    int temp;                        /* 用来保存值 */
    for (int i = 1; i < length; i++) /* 外层循环，默认第0位是有序的，从第一位开始遍历 */
    {
        for (int j = 0; j < i; j++) /* 内层循环，依次比较外层循环当前值与j=0->j=i-1的值大小 */
        {
            if (array[i] < array[j])
            { /* 则array[i]用插入到array[j]的前面,那么array[j]至array[i-1]的值全部后移 */

                temp = array[i];

                for (int k = i - 1; k >= j; k--)
                {
                    array[k + 1] = array[k]; /* 依次后移 */
                }
                array[j] = temp;
            }
        }
        printArray(array, length);
    }
}
int main()
{
    int length = 6;
    int array[6] = {4, 3, 5, 1, 9, 6};
    printArray(array, 6);
    InsertSort(array, 6);
    return 0;
}
