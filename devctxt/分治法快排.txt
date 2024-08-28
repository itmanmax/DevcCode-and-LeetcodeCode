#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void swap(int a[],int c,int b)
{   int temp=a[c];
    a[c]=a[b];
    a[b]=temp;
}
int FindMiddle(int a[],int left,int right)
{   int mid=a[left];
    int dex=left;
    left++;
    while(left<=right)
    {  if(a[left]<mid)
        {   
            left++;
        }
        else 
        {  swap(a,left,right);
            right--;
        }
    }
    swap(a,dex,right);
 return right; 
}
void QuickSort(int a[],int left,int right)
{   if(left<right)
    {   int mid=FindMiddle(a,left,right);
        QuickSort(a,left,mid-1);
        QuickSort(a,mid+1,right);
    }
}
int main()
{ int a[100000];
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {   scanf("%d",&a[i]);
    }
    QuickSort(a,0,n-1);
    for(int i=0;i<n;i++)
    {   printf("%d ",a[i]);
    }




}

