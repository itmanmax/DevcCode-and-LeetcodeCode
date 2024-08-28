#include <stdio.h>

int find(int arr[], int n) {
    int max_index = -1, max_value = -1;
    int count=0; 
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
            max_index = i;
        }
        
    }
     for (int i = 0; i < n; i++) { 
	  if(arr[i] == max_value) count++;
    }	
    if(count>1) return -1;
    if (max_index == -1 || max_index == 0 || max_index == n - 1)
        return 0; // 若数组为空或只有一个元素或全部元素相同，没有山峰，返回0

    int start = 0;
    while (start < n - 1) {
        if (arr[start] > arr[start + 1]) {
            start++;
        } else {
            break;
        }
    }
    if (start == n - 2)
        return max_index; // 如果在最大值之前找到下降，则山峰在最大值

    int index = max_index;
    while (start < n - 1) {
        if (arr[start] > arr[start + 1]) {
            index = start;
            break;
        }
        start++;
    }
    return index;
}

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    printf("%d\n", find(a, n) + 1); // 加1是为了从1开始计数
    return 0;
}

