#include <stdio.h>
#include <string.h>

#define MAX_CHAR 26
long factorial(int n) {
    long fact = 1;
    for (int i = 2; i <= n; i++) {
        fact *= i;
    }
    return fact;
}


long count_unique_permutations(char *str) {
    int length = strlen(str);
    int count[MAX_CHAR] = {0};
    long result = factorial(length);

    // 统计所有字符的出现次数
    for (int i = 0; i < length; i++) {
        count[(int)(str[i])]++;
    }

    // 除以每个字符出现次数的阶乘
    for (int i = 0; i < MAX_CHAR; i++) {
        if (count[i] > 1) {
            result /= factorial(count[i]);
        }
    }

    return result;
}

int main() {
    char str[MAX_CHAR];
  
    scanf("%s", str);

    long count = count_unique_permutations(str);
    printf("%llu\n", count);

    return 0;
}
