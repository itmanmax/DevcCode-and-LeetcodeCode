#include <stdio.h>
#include <stdlib.h>

// 函数原型声明
int is_prime(int n);
void print_prime_factors(int n);

int main() {
    int n;
   
    scanf("%d", &n);

    // 打印素数或素数乘积式
    print_prime_factors(n);

    return 0;
}

// 检查一个数是否为素数
int is_prime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    }
    return 1;
}

// 打印整数n的素数因子分解
void print_prime_factors(int n) {
    // 如果n本身就是素数，直接打印
    if (is_prime(n)) {
        printf("%d\n", n);
        return;
    }

    int first = 1; // 用于格式化输出
    for (int i = 2; i <= n; i++) {
        // 对每个素数，尝试除以n，打印所有因子
        while (is_prime(i) && n % i == 0) {
            if (first) {
                printf("%d", i);
                first = 0;
            } else {
                printf("*%d", i);
            }
            n /= i;
        }
    }
    printf("\n");
}

