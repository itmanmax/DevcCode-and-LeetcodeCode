#include <stdio.h>
#include <stdlib.h>

// ���嵥��ջ�ṹ
typedef struct {
    int *data;   // ��̬����洢ջԪ��
    int top;     // ջ��ָ��
    int maxSize; // ջ����󳤶�
} MonotonicStack;

// ��ʼ��ջ
void initStack(MonotonicStack *stack, int maxSize) {
    stack->data = (int *)malloc(maxSize * sizeof(int));
    stack->top = -1;
    stack->maxSize = maxSize;
}

// �ж�ջ�Ƿ�Ϊ��
int isEmpty(MonotonicStack *stack) {
    return stack->top == -1;
}

// �ж�ջ�Ƿ���
int isFull(MonotonicStack *stack) {
    return stack->top == stack->maxSize - 1;
}

// ��ջ����
void push(MonotonicStack *stack, int value) {
    if (isFull(stack)) {
        printf("ջ�����޷���ջ\n");
        return;
    }
    stack->data[++stack->top] = value;
}

// ��ջ����
int pop(MonotonicStack *stack) {
    if (isEmpty(stack)) {
        printf("ջ�գ��޷���ջ\n");
        return -1;
    }
    return stack->data[stack->top--];
}

// ��ȡջ��Ԫ��
int top(MonotonicStack *stack) {
    if (isEmpty(stack)) {
        printf("ջ�գ��޷���ȡջ��Ԫ��\n");
        return -1;
    }
    return stack->data[stack->top];
}

// ά����������ջ
void maintainMonotonicStack(MonotonicStack *stack, int value) {
    while (!isEmpty(stack) && top(stack) > value) {
        pop(stack);
    }
    push(stack, value);
}

// �ͷ�ջ�ڴ�
void freeStack(MonotonicStack *stack) {
    free(stack->data);
    stack->data = NULL;
    stack->top = -1;
    stack->maxSize = 0;
}

int main() {
    int maxSize;
    printf("����ջ����󳤶�: ");
    scanf("%d", &maxSize);

    MonotonicStack stack;
    initStack(&stack, maxSize);

    int arr[] = {2, 1, 5, 6, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("ԭ����: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("��������ջ�Ĺ�������: \n");
    for (int i = 0; i < n; i++) {
        maintainMonotonicStack(&stack, arr[i]);
     
       
    }
    for(int i=0;i<maxSize;i++)  printf("%d ",stack.data[i]);

    freeStack(&stack);
    return 0;
}

