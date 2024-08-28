#include <stdio.h>
 
void generateCombinations(int n, int k, int start, int depth, int *combination) {
    // ��ǰ������Ѿ���k����ʱ��������
    if (depth == k) {
        for (int i = 0; i < k; ++i) {
            printf("%d ", combination[i]);
        }
        printf("\n");
        return;
    }
 
    // ��start��ʼ������ÿ�����ܵ�����
    for (int i = start; i <= n; ++i) {
        combination[depth] = i;
        generateCombinations(n, k, i + 1, depth + 1, combination);
    }
}
 
int main() {
    int n, k;
    scanf("%d %d", &n, &k);
 
    // �洢��ǰ��ϵ�����
    int combination[k];
    generateCombinations(n, k, 1, 0, combination);
 
    return 0;
}
