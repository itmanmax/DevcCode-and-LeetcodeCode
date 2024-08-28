#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return a > b ? a : b;
}

void getMaxNum(int arr[][100], int size1, int size2, char str1[], char str2[]) {
    int i, j;
    for (i = 1; i <= size1; i++) {
        for (j = 1; j <= size2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                arr[i][j] = arr[i - 1][j - 1] + 1;
            } else {
                arr[i][j] = max(arr[i - 1][j], arr[i][j - 1]);
            }
        }
    }
    printf("%d\n", arr[size1][size2]);
}

int main() {
    // 输入两个字符串
    char str1[100], str2[100];
    scanf("%s", str1);
    scanf("%s", str2);
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // 初始化全为0的二维数组
    int arr[len1 + 1][100] ;
	  memset(arr,0,sizeof(arr));
    getMaxNum(arr, len1, len2, str1, str2);

    return 0;
}

