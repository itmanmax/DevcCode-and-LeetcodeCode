#include <stdio.h>
#include <stdlib.h>
//引用正无穷
#define INF 0x3f3f3f3f

int MinNum(int a, int b,int n,int arr[])
{    if (a==b)
        return 0;
    else 
    {  //递归求最小的矩阵连乘
        int k;
        int min=INF;
        for(k=a+1;k<=b;k++)
        {    if(MinNum(a,k-1,n,arr)+MinNum(k,b,n,arr)+arr[a]*arr[k]*arr[b+1]<min)
                min=MinNum(a,k-1,n,arr)+MinNum(k,b,n,arr)+arr[a]*arr[k]*arr[b+1];
  
        }
      return min;

    }


}
int main()
{  
   int n;
   scanf("%d",&n);
   int arr[n+1];
   for(int i=0;i<=n;i++)
     scanf("%d",&arr[i]);
     int Num=MinNum(0,n-1,n,arr);
     printf("%d",Num);



}
