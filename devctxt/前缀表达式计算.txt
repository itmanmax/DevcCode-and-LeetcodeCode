#include<stdio.h>
#include<stdlib.h>
double fun(){
	char a[100];
	scanf("%s",a);
	switch(a[0]){
		case '*':return fun()*fun();
		case '+':return fun()+fun();
		case '-':return fun()-fun();
		case '/':return fun()/fun();
		default: return atof(a);
	}
}
int main(){
	printf("%f",fun()); 
	return 0;
}
