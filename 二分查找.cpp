#include <stdio.h>

// ���η�ʵ�ֵĶ��ֲ���
void binarySearch(int arr[], int l, int r, int x) {
    if (r >= l) {
        int m = l + (r - l) / 2;

        // ����ҵ�Ԫ�أ��򷵻�
        if (arr[m] == x) {
            printf("Ԫ���ҵ�������Ϊ�� %d\n", m);
            return;
        }

        // ����м��Ԫ�ش���x��������벿�ּ�������
        if (arr[m] > x) {
            binarySearch(arr, l, m - 1, x);
        }
        // �������Ұ벿�ּ�������
        else {
            binarySearch(arr, m + 1, r, x);
        }
    }
    // ����Ҳ���Ԫ�أ��������ʾ
    else {
        printf("Ԫ��δ�ҵ�\n");
    }
}

int main() {
    int arr[] = {2, 3, 4, 10, 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 20;
    binarySearch(arr, 0, n - 1, x);
    return 0;
}

