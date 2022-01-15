#include <stdio.h>

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int start = 0;
    int end = 5;

    /*
    // calculate size in bytes
    int arraySize = sizeof(arr);
    int intSize = sizeof(arr[0]);

    int size = arraySize / intSize;
    printf("size: %d", size);
    */

    //Method 1
    /*
    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
    */

    //Method 2
    int temp = 0;
    for (int i = 0; i < end; i++)
    {
        temp = arr[i];
        arr[i] = arr[end];
        arr[end] = temp;
        end--;
    }


    for (int j = 0; j < 6; j++)
    {
        printf("%i\n", arr[j]);
    }

}