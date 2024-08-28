#include <stdio.h>

#define packagemax 3.00
struct Wod {
    double weight;
};
void quickSort(struct Wod wod[], int low, int high) {
    if (low < high) {
        double pivot = wod[high].weight;
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (wod[j].weight < pivot) {
                i++;
                struct Wod temp = wod[i];
                wod[i] = wod[j];
                wod[j] = temp;
            }
        }
        
        struct Wod temp = wod[i + 1];
        wod[i + 1] = wod[high];
        wod[high] = temp;

        int pi = i + 1;

        quickSort(wod, low, pi - 1);
        quickSort(wod, pi + 1, high);
    }
}

int findMaxPairs(struct Wod arr[], int n) {
    int i = 0, j = n - 1; // ��ʼ��˫ָ��
    int count = 0; // ��¼�����
    int remainder = 0; // ��¼ʣ����

    while (i < j) {
        // ����������ĺ�С�ڵ���3.00�������ǿ������һ�����
        if (arr[i].weight + arr[j].weight <= 3.00) {
            count++; // ���������
            i++; // �ƶ���ָ��
            j--; // �ƶ���ָ��
        } else {
            // �����ǰ��ָ��ָ���������1.01��Ȼ����3.00�������������κ���������
            if (arr[j].weight > 1.99) {
                remainder++; // ʣ��������
            }
            j--; // �ƶ���ָ��
        }
    }

    // �����ָ��û���ƶ������Ҷˣ���ʣ�µ�����������������������
    remainder += (i - j);

    return count ;
}
  
int main() {
    struct Wod wod[100000];
    int n;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++) {
        scanf("%lf", &wod[i].weight);
    }

  quickSort(wod, 0, n - 1);
  int count = findMaxPairs(wod, n); 
  int left = 0; 
  int right =n-1;
  findMaxPairs(wod, n);
 printf("%d",n-count);

    return 0;
}

