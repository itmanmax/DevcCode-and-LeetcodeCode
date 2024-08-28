#include <stdio.h>
#include <limits.h>

int max(int lmax, int rmax) {
    if (lmax >= rmax) 
        return lmax;
    else 
        return rmax;
}

int min(int lmin, int rmin) {
    if (lmin >= rmin) 
        return rmin;
    else 
        return lmin;
}

void MaxMin(int a[], int low, int high, int *Max, int *Min, int *Max2, int *Min2) {
    if (low == high) { // 只有一个元素
        *Max = a[low];
        *Min = a[low];
        *Max2 = INT_MIN;
        *Min2 = INT_MAX;
    } else if (low == high - 1) { // 只有两个元素
        if (a[low] > a[high]) {
            *Max = a[low];
            *Max2 = a[high];
            *Min = a[high];
            *Min2 = a[low];
        } else {
            *Max = a[high];
            *Max2 = a[low];
            *Min = a[low];
            *Min2 = a[high];
        }
    } else {
        int mid = (low + high) / 2; // 分为两半
        int lmax, lmin, lmax2, lmin2; // 左半边第一大、第二大
        MaxMin(a, low, mid, &lmax, &lmin, &lmax2, &lmin2);

        int rmax, rmin, rmax2, rmin2; // 右半边第一大、第二大
        MaxMin(a, mid + 1, high, &rmax, &rmin, &rmax2, &rmin2);

        // 左半边、右半边再进行比较
        *Max = max(lmax, rmax);
        *Min = min(lmin, rmin);
        *Max2 = max(min(lmax, rmax), max(lmax2, rmax2));
        *Min2 = min(max(lmin, rmin), min(lmin2, rmin2));
    }
}

int main() {
    int n;

    scanf("%d", &n);

    int a[100];
 
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int Max, Min, Max2, Min2;
    MaxMin(a, 0, n - 1, &Max, &Min, &Max2, &Min2);


	printf("%d %d\n%d %d",Max,Max2,Min2,Min);
    return 0;
}
