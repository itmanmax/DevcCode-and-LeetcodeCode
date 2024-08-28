#include <stdio.h>

// �ݹ麯��������ŷ�����
int countWays(int n, int m) {
    // ���û�������ֻ��һ�����ӣ�ֻ��һ�ַŷ�
    if (n == 0 || m == 1) {
        return 1;
    }
    // ����������С�ں��ӵ��������Ͳ��ܱ�֤���к��Ӷ�����
    // �൱����Щ����һ���ǿյģ������Ϊn�������n������
    if (n < m) {
        return countWays(n, n);
    }
    // ����������ܺ�
    // ��һ�������������һ�������ǿյ�
    // �ڶ�����������еĺ��Ӷ�������һ����
    return countWays(n, m - 1) + countWays(n - m, m);
}

int main() {
    int T, n, m;
    scanf("%d", &T); // ��ȡ�������ݵ���Ŀ
    while (T--) {
        scanf("%d %d", &n, &m); // ��ȡÿ�����ݵ�n��m
        printf("%d\n", countWays(n, m)); // ����ŷ�����
    }
    return 0;
}
