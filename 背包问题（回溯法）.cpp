#include <stdio.h>
#include <stdlib.h>

int n;          // ��Ʒ����
int M;          // �����������
int *w;         // ��Ʒ��������
int *p;         // ��Ʒ��������
int *x;         // ��ǰ�⣨�����Ʒ�Ƿ�װ�뱳����
int *bestx;     // ���ս⣨�����Ʒ�Ƿ�װ�뱳����
int bestP = 0;  // �������

// �����Ͻ纯��
int bound(int i, int currentW, int currentP) {
    int maxP = currentP;
    int j, totWeight = currentW;
    // ����λ������ֵ����װ�뱳��
    for (j = i; j < n; j++) {
        if (totWeight + w[j] <= M) { // ������װ��
            totWeight += w[j];
            maxP += p[j];
        } else { // ��������װ�£�������װ��
            maxP += (M - totWeight) * p[j] / w[j];
            break;
        }
    }
    return maxP;
}

// ���ݷ����0/1��������
void backtrack(int i, int currentW, int currentP) {
    if (i == n) { // ����Ҷ�ӽڵ�
        if (currentP > bestP) {
            bestP = currentP;
            for (int j = 0; j < n; j++) {
                bestx[j] = x[j];
            }
        }
        return;
    }
    // ������������װ�뱳����
    if (currentW + w[i] <= M) { // ��֦����
        x[i] = 1;
        backtrack(i + 1, currentW + w[i], currentP + p[i]);
    }
    // ��������������װ�뱳����
    if (bound(i + 1, currentW, currentP) > bestP) { // ��֦����
        x[i] = 0;
        backtrack(i + 1, currentW, currentP);
    }
}

int main() {
    scanf("%d %d", &n, &M);
    w = (int *)malloc(n * sizeof(int));
    p = (int *)malloc(n * sizeof(int));
    x = (int *)malloc(n * sizeof(int));
    bestx = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }
    
    backtrack(0, 0, 0); // �Ӹ��ڵ㿪ʼ����
    
    // ������װ�ط�����������
    printf("%d\n", bestP);
    // ������װ�ط���
    for (int i = 0; i < n; i++) {
        printf("%d ", bestx[i]);
    }
    printf("\n");
    
    free(w);
    free(p);
    free(x);
    free(bestx);
    
    return 0;
}
