#include <stdio.h>
#include <stdlib.h>
int powxn(int x,int n)
{    
    int i,p=1;
    for(i=1;i<=n;i++)
    {
        p=p*x;
    }
    return p;


}

int main() {
     int x ,n;
     int num[100000];
     scanf("%d %d",&n,&x);
     for(int i=n+1;i>0;i--)
     {
         scanf("%d",&num[i]);
     }
    int sum=num[1];
    for(int i=2;i<=n+1;i++)
    { 
        sum=sum+num[i]*powxn(x,i-1);
        
    }
     
   printf("%d",sum);
   return 0;
}

