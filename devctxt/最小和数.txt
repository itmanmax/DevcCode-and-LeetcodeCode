#include <stdio.h>

int gcd(int a,int b){          
    return (b==0)?a:gcd(b,a%b);
}

int main()
{
    int a,b;
    int count=0,min=10000;
    int sum[10000];
    for(int i=0;i<10000;i++) sum[i]=0;
    scanf("%d%d",&a,&b);
    if(b%a==0){                   
        int c=b/a;                
        for(int x=1;x<=c;x++){   
            if(c%x==0) {         
                int m=x*a;       
                int n=c/x*a;      
                if(a==gcd(m,n)){  
                sum[count]=m+n;
                    count++;    
                    
                }
            }
        } 
    }else count=0;                
    for(int i=0;i<count;i++){
        if(sum[i]<min)
        min=sum[i];
    }
    printf("%d\n",min);
    return 0;
}

