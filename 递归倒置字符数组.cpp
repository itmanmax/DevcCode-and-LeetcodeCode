
#include <stdio.h>
#include <string.h>
void reverse(char *s,int left,int right,int n)
{
    if(left==right||left>(n-1)/2)
		return ;
    char temp=s[left];
    s[left]=s[right];
    s[right]=temp;
    puts(s); 
    reverse(s,left+1,right-1,n);
}
int main()
{
    char s[1000];
    int n;
    scanf("%d%s",&n,&s);
    reverse(s,0,n-1,n);
    printf("\n%s",s);    
    return 0;
}
