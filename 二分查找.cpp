#include <stdio.h>

// 分治法实现的二分查找
void binarySearch(int arr[], int l, int r, int x) {
    if (r >= l) {
        int m = l + (r - l) / 2;

        // 如果找到元素，则返回
        if (arr[m] == x) {
            printf("元素找到，索引为： %d\n", m);
            return;
        }

        // 如果中间的元素大于x，则在左半部分继续查找
        if (arr[m] > x) {
            binarySearch(arr, l, m - 1, x);
        }
        // 否则在右半部分继续查找
        else {
            binarySearch(arr, m + 1, r, x);
        }
    }
    // 如果找不到元素，则输出提示
    else {
        printf("元素未找到\n");
    }
}

int main() {
    int arr[] = {2, 3, 4, 10, 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 20;
    binarySearch(arr, 0, n - 1, x);
    return 0;
}

