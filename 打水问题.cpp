#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
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
int CountTime(int arr[], int timearr[],int n,int m) {
    int time = 0;
    int i=m;
    while(i+m<n-1)
    {  
        for(int j=i;j<i+m;j++)
        {  
            timearr[j]=timearr[j-m]+arr[j-m];
    }
    i=i+m;
    

    }
    while(i<=n-1)
    { timearr[i]=timearr[i-m]+arr[i-m];
    i++;
    }
    for(int i=0;i<n;i++)
    {
        time=time+timearr[i];
    }
    return time;
}
int main() {
    int n;
    int m;
    scanf("%d %d", &n, &m);
    int arr[n];
    int timearr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        timearr[i]=0;
    }
    quickSort(arr, 0, n - 1);
    printf("%d", CountTime(arr,timearr, n,m));
}


