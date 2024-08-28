#include <stdio.h>

#define packagemax 3.00
struct Wod {
    double weight;
};
void quickSort(struct Wod wod[], int low, int high) {
    if (low < high) {
        double pivot = wod[high].weight;
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (wod[j].weight < pivot) {
                i++;
                struct Wod temp = wod[i];
                wod[i] = wod[j];
                wod[j] = temp;
            }
        }
        
        struct Wod temp = wod[i + 1];
        wod[i + 1] = wod[high];
        wod[high] = temp;

        int pi = i + 1;

        quickSort(wod, low, pi - 1);
        quickSort(wod, pi + 1, high);
    }
}

int findMaxPairs(struct Wod arr[], int n) {
    int i = 0, j = n - 1; // 初始化双指针
    int count = 0; // 记录组合数
    int remainder = 0; // 记录剩余数

    while (i < j) {
        // 如果两个数的和小于等于3.00，则它们可以组成一个组合
        if (arr[i].weight + arr[j].weight <= 3.00) {
            count++; // 组合数增加
            i++; // 移动左指针
            j--; // 移动右指针
        } else {
            // 如果当前右指针指向的数加上1.01仍然大于3.00，则它不能与任何数组成组合
            if (arr[j].weight > 1.99) {
                remainder++; // 剩余数增加
            }
            j--; // 移动右指针
        }
    }

    // 如果左指针没有移动到最右端，则剩下的数都不能与其他数组成组合
    remainder += (i - j);

    return count ;
}
  
int main() {
    struct Wod wod[100000];
    int n;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++) {
        scanf("%lf", &wod[i].weight);
    }

  quickSort(wod, 0, n - 1);
  int count = findMaxPairs(wod, n); 
  int left = 0; 
  int right =n-1;
  findMaxPairs(wod, n);
 printf("%d",n-count);

    return 0;
}

