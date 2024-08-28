#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 26
#define MAX_NODES (2 * MAX_CHAR - 1)

typedef struct {
    unsigned int weight;
    unsigned int parent, lchild, rchild;
} HTNode, *HuffmanTree;

typedef struct {
    char cd[MAX_CHAR];
    int start;
} HCode;

HCode hcd[MAX_CHAR];//全局数组； 

// 统计字符频率
void countFrequency(const char *str, int freq[MAX_CHAR]) {
    memset(freq, 0, sizeof(int) * MAX_CHAR);

    while (*str != '\0') {
        if (*str >= 'a' && *str <= 'z') {
            freq[*str - 'a']++;
        }
        str++;
    }
}

// 选择权值最小的两个节点
void selectMin(HuffmanTree ht, int n, int *s1, int *s2) {
    for (int i = 1; i <= n; ++i) {
        if (ht[i].parent == 0) {
            if (*s1 == 0) {
                *s1 = i;
            } else if (*s2 == 0) {
                *s2 = i;
                break;
            }
        }
    }
//找两个叶子 
    for (int i = 1; i <= n; i++) {
        if (ht[i].parent == 0) {
            if (ht[i].weight < ht[*s1].weight) {
                *s2 = *s1;
                *s1 = i;
            } else if ((ht[i].weight < ht[*s2].weight)&&(ht[i].weight >ht[*s1].weight)) {
                *s2 = i;
            }
        }
    }
}

// 构建哈夫曼树
void buildHuffmanTree(HuffmanTree ht, int n, int freq[MAX_CHAR]) {
    int m = 2 * n - 1;
    for (int i = 1; i <= m; ++i) {
        ht[i].parent = 0;
        ht[i].lchild = 0;
        ht[i].rchild = 0;
        if (i <= n) {
            ht[i].weight = freq[i - 1];
        } else {
            ht[i].weight = 0;
        }
    }

    for (int i = n + 1; i <= m; ++i) {
        int s1 = 0, s2 = 0;
        selectMin(ht, i - 1, &s1, &s2);

        ht[s1].parent = i;
        ht[s2].parent = i;
        ht[i].lchild = s1;
        ht[i].rchild = s2;
        ht[i].weight = ht[s1].weight + ht[s2].weight;
    }
     
}

// 生成哈夫曼编码
void generateHuffmanCode(HuffmanTree ht, int n) {
    char cd[MAX_CHAR];
    //从后面往前面找； 
    for (int i = 1; i <= n; ++i) {
        int start = MAX_CHAR - 1;
        int c = i;
        int f = ht[i].parent;

        while (f != 0) {
            if (ht[f].lchild == c) {
                cd[--start] = '0';
            } else {
                cd[--start] = '1';
            }
            c = f;
            f = ht[f].parent;
        }

        hcd[i - 1].start = start;
        strcpy(hcd[i - 1].cd, &cd[start]);//从数组cd的start开始复制直到cd数组为空 
    }
}
// 根据哈夫曼树解码字符串
void decodeHuffman(HuffmanTree ht, int n, const char *encodedStr) {
    int index = 2 * n - 1; // 从哈夫曼树的根节点开始
    int len = strlen(encodedStr);
     
    for (int i = 0; i < len; ++i) {
        if (encodedStr[i] == '0') {
            index = ht[index].lchild;
        } else if (encodedStr[i] == '1') {
            index = ht[index].rchild;
        }

        // 如果到达叶子节点，则输出对应字符并重置为根节点
        if (ht[index].lchild == 0 && ht[index].rchild == 0) {
            printf("%c", 'a' + index - 1);
            index = 2 * n - 1; // 重置为根节点
        }
    }

    printf("\n");
}
																																																																																																																																																																																																																																																																																							
// 输出结果
void printResult(int n, int freq[MAX_CHAR], HuffmanTree ht) {
    // 输出字符频率
    for (int i = 0; i < n; ++i) {
        printf("%c:%d ", 'a' + i, freq[i]);
    }
    printf("\n");

    // 输出哈夫曼树的终态
    for (int i = 1; i <= 2 * n - 1; ++i) {
        printf("%d %d %d %d %d\n", i, ht[i].weight, ht[i].parent, ht[i].lchild, ht[i].rchild);
    }
   char yuanma[MAX_NODES];
    // 输出哈夫曼编码
    for (int i = 0; i < n; ++i) {
        printf("%c:%s ", 'a' + i, hcd[i].cd);
    }
    printf("\n");
    int decodedIndex = 0; // 用于跟踪 decodedStr 中的位置

for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= freq[i - 1]; ++j) {
        // 追加编码字符串到 decodedStr
        strcpy(yuanma + decodedIndex, hcd[i - 1].cd);
        decodedIndex += strlen(hcd[i - 1].cd);
    }
}	 
	
		decodeHuffman(ht, n, yuanma);
		
}

int main() {
    char input[MAX_NODES*MAX_CHAR];
    int freq[MAX_CHAR] = {0};
    HuffmanTree ht;
    int n = 0;

    while (1) {
        printf("Enter a string (or '0' to end): ");
        scanf("%s", input);

        if (input[0] == '0') {
            break;
        }

        n = 0;
        countFrequency(input, freq);

        for (int i = 0; i < MAX_CHAR; ++i) {
            if (freq[i] > 0) {
                n++;
            }
        }

        ht = (HuffmanTree)malloc((2 * n) * sizeof(HTNode));
        buildHuffmanTree(ht, n, freq);
        generateHuffmanCode(ht, n);

        printResult(n, freq, ht);

        free(ht);
    }

    return 0;
}
 
