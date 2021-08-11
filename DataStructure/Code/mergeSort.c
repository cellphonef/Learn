#include <stdlib.h>  /* for malloc free */
#include <stdio.h>

void mergeSort(int arr[], int tempArr[], int start, int end);
void merge(int arr[], int tempArr[], int start, int mid, int end);


/* 主函数 */
void mSort(int arr[], int size)
{
    int* tempArr = (int*)malloc(size * sizeof(int));
    mergeSort(arr, tempArr, 0, size - 1);
    free(tempArr);
}

/* 归并排序, 递归函数 */
void mergeSort(int arr[], int tempArr[], int start, int end)
{
    if (start == end)
        return;
    int mid = (start + end) / 2;
    mergeSort(arr, tempArr, start, mid);
    mergeSort(arr, tempArr, mid + 1, end);
    merge(arr, tempArr, start, mid, end);
}


/* 合并  */
void merge(int arr[], int tempArr[], int start, int mid, int end)
{
    int i = start;
    int j = mid + 1;
    int k = start;
    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            tempArr[k] = arr[i];
            i++;
            k++;
        }
        else {
            tempArr[k] = arr[j];
            j++;
            k++;
        }
    }

    while (i <= mid) {
        tempArr[k] = arr[i];
        i++;
        k++;
    }

    while (j <= end) {
        tempArr[k] = arr[j];
        j++;
        k++;
    }

    for (int i = start; i <= end; i++)
        arr[i] = tempArr[i];

}


int main()
{
    int arr[] = { 2, 1, 3, 5, 6, 8, 9, 10, 4, 7};
    printf("before mergesort------\n");
    printf("arr:\n");
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
        printf("%d,", arr[i]);
    printf("\n");
    mSort(arr, sizeof(arr) / sizeof(int));
    printf("after mergesort------\n");
    printf("arr:\n");
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
        printf("%d,", arr[i]);

}