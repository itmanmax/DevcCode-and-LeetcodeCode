#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getMaxlength(int arr[], int n) {
      int dp[n];        
     for(int i=0;i<n;i++) dp[i]=1;
     for(int i=1;i<n;i++)
     {
         for(int j=0;j<i;j++)
         {
             if(arr[i]>arr[j])
             {
                 dp[i]=(dp[i] > dp[j] + 1) ? dp[i] : (dp[j] + 1);
             }
         }
     }
    int max=0;
    for(int i=0;i<n;i++)
    {
        if(dp[i]>max)
        {
            max=dp[i];
        }
    }
    return max;
    }


int main()
{  int n;
   scanf("%d",&n);
   int arrWeight[n];
   for(int i=0;i<n;i++)
   {
      scanf("%d",&arrWeight[i]);
   }
  int maxvalue=getMaxlength(arrWeight,n);
  printf("%d",maxvalue);

}
