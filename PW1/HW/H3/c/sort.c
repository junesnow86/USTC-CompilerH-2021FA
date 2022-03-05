#include <stdio.h>
#include <stdlib.h>
int sort(int *array, int size)
{
    for (int i = 1; i < size; ++i)
    {
        int j = i - 1;
        int key = array[i];
        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
    return 0;
}

int main(int argc, char **argv)
{
    int size;
    scanf("%d", &size);
    int *array = (int *)malloc(size * sizeof(int));
    if (!array)
        exit(-1);
    for (int i = 0; i < size; ++i)
        scanf("%d", &array[i]);
    sort(array, size);
    for (int i = 0; i < size; ++i)
        printf("%d ", array[i]);
    return 0;
}