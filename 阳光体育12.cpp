#include <stdio.h>

int main() {
    float numbers[5];
    
    printf("请输入五个小数数值：\n");
    
    // 输入五个小数数值
    for (int i = 0; i < 5; i++) {
        scanf("%f", &numbers[i]);
    }
    
    printf("计算结果为：\n");
    
    // 输出每个数值由1减去的结果
    for (int i = 0; i < 5; i++) {
        float result = 1 - numbers[i];
        printf("%.3f\n", result);
    }
    
    return 0;
}

