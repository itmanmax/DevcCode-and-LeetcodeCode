#include<stdio.h>
#include <stdlib.h>
#include <time.h>
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int random(int min, int max) {
    return min + rand() % (max - min + 1);
}

int partition(int arr[], int low, int high) {
   
    int pivotIndex = random(low, high);
    int pivot = arr[pivotIndex];
    swap(&arr[pivotIndex], &arr[high]); 
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void insertionSort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        if (high - low + 1 <= 10) {
            insertionSort(arr, low, high); 
        } else {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
}

// 二分查找函数
int Findx(int a[], int m, int x) {
    int left = 0;
    int right = m - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid] == x)
            return 1;
        else if (a[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return 0;
}
int main()
{  int m,n;
int x;
   scanf("%d %d",&m,&n);
   int a[m];
   for(int i=0;i<m;i++)
   {
       scanf("%d",&a[i]);
   }
   quickSort(a,0,m-1);
   for(int i=0;i<n;i++)
   {
     scanf("%d",&x);
    if(Findx(a,m,x))
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }

      
   }
	
	
	
}
