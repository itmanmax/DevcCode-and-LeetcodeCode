#include <stdio.h>
int binarySearch(int arr[], int x, int low, int high) {
    while (low <= high) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;
        if (arr[mid1] == x)
            return mid1;
        if (arr[mid2] == x)
            return mid2;
        if (x < arr[mid1])
            high = mid1 - 1;
        else if (x > arr[mid2])
            low = mid2 + 1;
        else
            low = mid1 + 1, high = mid2 - 1;
    }
    return -1;
}
int main() {
    int n, x;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &x);
    int result = binarySearch(arr, x, 0, n - 1);
    if (result != -1)
        printf("%d\n", result);
    else
        printf("-1\n");
    return 0;
}

