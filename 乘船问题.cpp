#include <stdio.h>

// 函数原型
void bubbleSort(int array[], int size);

int main() {
	int n;
	scanf("%d",&n);
  int data[n];
  for(int i=0;i<n;i++){
    scanf("%d",&data[i]);
  }
  int maxweight=0;
  scanf("%d",&maxweight);
    // 调用冒泡排序函数
    bubbleSort(data, n);
    int count=0;
    int i=0;
    int j=n-1;
    while(i<=j){
      if(data[i]+data[j]<=maxweight){
        i++;
        j--;
        count++;
      }
      else{
        j--;
        count++;
      }
    }
    printf("%d",count);
    return 0;
}
   

// 冒泡排序函数
void bubbleSort(int array[], int size) {
    for (int step = 0; step < size - 1; ++step) {
        // 在每一轮中，最大的元素会冒泡到最后
        for (int i = 0; i < size - step - 1; ++i) {
            // 根据元素值的比较，交换位置
            if (array[i] > array[i + 1]) {
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }
}

