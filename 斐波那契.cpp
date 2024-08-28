#include "stdio.h"
int fib(int n){
	if(n==1||n==2)				//
		n=1;
	else
		n=fib(n-1)+fib(n-2);

	return n;
}
int main(){
	for(int i=1;i<=15;i++)
		printf("%3d ",fib(i));

	printf("\n");
}


