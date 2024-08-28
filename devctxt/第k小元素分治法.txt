#include <stdio.h>

// 交换两个数的值
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 分割函数，将数组分成两部分，并返回分割点的索引
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// 递归函数，找出数组中第 k 小的元素
int kthSmallest(int arr[], int low, int high, int k) {
    if (k > 0 && k <= high - low + 1) {
        int pos = partition(arr, low, high);

        if (pos - low == k - 1)
            return arr[pos];
        if (pos - low > k - 1)
            return kthSmallest(arr, low, pos - 1, k);
        return kthSmallest(arr, pos + 1, high, k - pos + low - 1);
    }
    return -1;
}

int main() {
    
    int n ;
    int arr[10000]; 
    int k ;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
   scanf("%d",&arr[i]);
    scanf("%d",&k);

    int result = kthSmallest(arr, 0, n - 1, k);

        printf("%d\n", result);
   

    return 0;
}

