#include <stdio.h>
#include <stdlib.h>

void printfSort(int *array, int length)
{

    for (int i = 0; i < length; i++)
    {
        printf("%d\t", array[i]);
    }
}

int partation(int *array, int i, int j) /*具体操作比较大小在此函数，i取数组的第一个值的index，j取数组最后一个值的index */
{
    int x = array[i]; /* 每一次函数操作，均是取第一个值作为枢纽 */
    while (i < j)     /* 当i=j时，进行操作 */
    {
        /* 数组左边空缺，从数组右边找大于x值补上，故从后往前遍历 */
        while (i < j && array[j] >= x)
        {
            j--;
        }
        /* 此时找到数组右边比x小的值了，插入到左边的空位 */
        if (i < j)
        {
            array[i] = array[j];
            i++;
        }
        /* 此时数组右边空缺了，应从左边遍历找到比x大的值 */
        while (i < j && array[i] <= x)
        {
            i++;
        }
        /*  此时找到数组左边比x大的值了，插入到右边的空位*/
        if (i < j)
        {
            array[j] = array[i];
            j--;
        }
    }

    array[i] = x;
    return i;
}

void quickSort(int *array, int i, int j) /* 递归 */
{
    if (i < j)
    {
        int index = partation(array, i, j); /* 取到枢纽操作后的index值，便于划分开 */
        quickSort(array, i, index - 1);     /* 操作左子表 */
        quickSort(array, index + 1, j);     /* 操作右子表 */
    }
}

int main()
{
    int array[8] = {27, 38, 13, 49, 76, 97, 65, 49};
    quickSort(array, 0, 7);
    printfSort(array, 8);
    return 0;
}