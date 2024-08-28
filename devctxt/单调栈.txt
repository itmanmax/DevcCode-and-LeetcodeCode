#include <stdio.h>
#include <stdlib.h>

// 定义单调栈结构
typedef struct {
    int *data;   // 动态数组存储栈元素
    int top;     // 栈顶指针
    int maxSize; // 栈的最大长度
} MonotonicStack;

// 初始化栈
void initStack(MonotonicStack *stack, int maxSize) {
    stack->data = (int *)malloc(maxSize * sizeof(int));
    stack->top = -1;
    stack->maxSize = maxSize;
}

// 判断栈是否为空
int isEmpty(MonotonicStack *stack) {
    return stack->top == -1;
}

// 判断栈是否满
int isFull(MonotonicStack *stack) {
    return stack->top == stack->maxSize - 1;
}

// 入栈操作
void push(MonotonicStack *stack, int value) {
    if (isFull(stack)) {
        printf("栈满，无法入栈\n");
        return;
    }
    stack->data[++stack->top] = value;
}

// 出栈操作
int pop(MonotonicStack *stack) {
    if (isEmpty(stack)) {
        printf("栈空，无法出栈\n");
        return -1;
    }
    return stack->data[stack->top--];
}

// 获取栈顶元素
int top(MonotonicStack *stack) {
    if (isEmpty(stack)) {
        printf("栈空，无法获取栈顶元素\n");
        return -1;
    }
    return stack->data[stack->top];
}

// 维护单调递增栈
void maintainMonotonicStack(MonotonicStack *stack, int value) {
    while (!isEmpty(stack) && top(stack) > value) {
        pop(stack);
    }
    push(stack, value);
}

// 释放栈内存
void freeStack(MonotonicStack *stack) {
    free(stack->data);
    stack->data = NULL;
    stack->top = -1;
    stack->maxSize = 0;
}

int main() {
    int maxSize;
    printf("输入栈的最大长度: ");
    scanf("%d", &maxSize);

    MonotonicStack stack;
    initStack(&stack, maxSize);

    int arr[] = {2, 1, 5, 6, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("原数组: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("单调递增栈的构建过程: \n");
    for (int i = 0; i < n; i++) {
        maintainMonotonicStack(&stack, arr[i]);
     
       
    }
    for(int i=0;i<maxSize;i++)  printf("%d ",stack.data[i]);

    freeStack(&stack);
    return 0;
}

