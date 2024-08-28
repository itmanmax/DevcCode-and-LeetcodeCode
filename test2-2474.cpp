////快速排序
//#include<stdio.h>
//#include<math.h>
//#include <stdlib.h>
//#include <time.h>
//void Quicksort(int arr[],int left,int right)
//{
//
//
//	int front=left;
//	int dep=right;	
//	int index=left + rand() % (right - left + 1);
//	int temp=arr[index];
//	while(front<dep)
//	{ 
//	  while(1)
//	  { 
//	if(arr[front]>arr[index]) break;	
//       else 	front++;
//	  }
//	   while(1)
//	   { if(arr[dep]<arr[index]) 
//	   {
//	   	 int tempdex=arr[front];
//	   	 arr[front]=arr[dep];
//	   	 arr[dep]=tempdex;
//	   	 break;
//	   }
//	  else  dep--;
//	   }	
//	  front++;
//	  dep--;		
//	}
//	arr[front]=temp;
//	Quicksort(arr,left,front);
//	Quicksort(arr,front+1,right);
//	
//}
//int main()
//{   int n;
//    scanf("%d",&n);
//    int arr[n];
//    for(int i=0;i<n;i++)
//    scanf("%d",&arr[i]);
//     for(int i=0;i<n;i++)
//    printf("fir %d ",arr[i]);
//    Quicksort(arr,0,n-1);
//    for(int i=0;i<n;i++)
//    printf("%d ",arr[i]);
//    
//    
//    
//    
//    
// } 
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

void Quicksort(int arr[], int left, int right) {
    if (left >= right) {
        return; // 基本情况：如果左边索引大于或等于右边索引，结束递归
    }
    
    int front = left;
    int dep = right;
    int index = left + rand() % (right - left + 1);
    int pivot = arr[index];

    // 交换基准点和最左边的元素
    arr[index] = arr[left];
    arr[left] = pivot;
    
    while (front < dep) {
        while (front < dep && arr[dep] >= pivot) {
            dep--;
        }
        arr[front] = arr[dep];
        
        while (front < dep && arr[front] <= pivot) {
            front++;
        }
        arr[dep] = arr[front];
    }
    
    arr[front] = pivot; // 把基准点放回正确的位置
    
    Quicksort(arr, left, front - 1);
    Quicksort(arr, front + 1, right);
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Before sorting: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    Quicksort(arr, 0, n - 1);

    printf("After sorting: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

