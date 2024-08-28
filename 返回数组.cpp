#include <stdio.h>

int main() {
   int num1;
   int num2;
   for (int i = 0; i < 10; i++) {
     
       scanf("%d %d", &num1, &num2); 
       printf(" %d\n", num1 - num2);
   }
   return 0;
}
