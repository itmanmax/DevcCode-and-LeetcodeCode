#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100

// �ṹ�����ڱ���ؼ��ʺͶ�Ӧ��Ƶ��
typedef struct {
    char word[MAX_WORD_LENGTH];
    int frequency;
} KeywordFrequency;

// ��������
void writeToFile(KeywordFrequency *keywords, int keywordCount, const char *filename);

int main() {
    FILE *keywordFile, *textFile;
    char keywordFilename[] = "C:\\Users\\86147\\Desktop\\quest\\Key.txt";
    char textFilename[] = "C:\\Users\\86147\\Desktop\\quest\\InFile.txt";
    char outFile[] = "C:\\Users\\86147\\Desktop\\quest\\OutFile1.txt";
    char buffer[1000];
    KeywordFrequency *keywords;
    int keywordCount = 0;

    // ���Դ򿪹ؼ����ļ�
    keywordFile = fopen(keywordFilename, "r");

    // ���ؼ����ļ��Ƿ�ɹ���
    if (keywordFile == NULL) {
        printf("�޷��򿪹ؼ����ļ� %s\n", keywordFilename);
        return 1;
    }

    // ͳ�ƹؼ��ʵ�����
    while (fgets(buffer, sizeof(buffer), keywordFile) != NULL) {
        keywordCount++;
    }

    // �ص��ļ���ʼ��
    rewind(keywordFile);

    // ����洢�ؼ��ʺ�Ƶ�ʵ�����
    keywords = (KeywordFrequency *)malloc(keywordCount * sizeof(KeywordFrequency));

    // ���ж�ȡ�ؼ����ļ�������ؼ��ʵ�������
    for (int i = 0; i < keywordCount; i++) {
        fgets(keywords[i].word, sizeof(keywords[i].word), keywordFile);
        // �Ƴ�ĩβ�Ļ��з�
        keywords[i].word[strcspn(keywords[i].word, "\n")] = '\0';
        keywords[i].frequency = 0;
    }

    // �رչؼ����ļ�
    fclose(keywordFile);

    // ���Դ��ı��ļ�
    textFile = fopen(textFilename, "r");

    // ����ı��ļ��Ƿ�ɹ���
    if (textFile == NULL) {
        printf("�޷����ı��ļ� %s\n", textFilename);
        free(keywords); // �ͷŹؼ��������ڴ�
        return 1;
    }

    // ���ж�ȡ�ı��ļ���ͳ�ƹؼ��ʳ��ֵ�Ƶ��
    while (fgets(buffer, sizeof(buffer), textFile) != NULL) {
        // ����ÿ���ؼ���
        for (int i = 0; i < keywordCount; i++) {
            char *pos = buffer;
            // �ڵ�ǰ�в��ҹؼ���
            while ((pos = strstr(pos, keywords[i].word)) != NULL) {
                keywords[i].frequency++;
                pos += strlen(keywords[i].word);
            }
        }
    }

    // ���ͳ�ƽ��
    for (int i = 0; i < keywordCount; i++) {
        printf("�ؼ��� '%s' ���ֵ�Ƶ��: %d\n", keywords[i].word, keywords[i].frequency);
    }

    // �ر��ı��ļ�
    fclose(textFile);

    // д�������ļ�
    writeToFile(keywords, keywordCount, outFile);

    // �ͷŹؼ��������ڴ�
    free(keywords);

    return 0;
}

// ���ؼ���Ƶ��д���ļ�
void writeToFile(KeywordFrequency *keywords, int keywordCount, const char *filename) {
    FILE *outfile = fopen(filename, "w");

    // ����ļ��Ƿ�ɹ���
    if (outfile == NULL) {
        printf("�޷�������ļ� %s\n", filename);
        return;
    }

    // ����ļ�����
    fclose(outfile);
    outfile = fopen(filename, "w");

    // д��ؼ���Ƶ�ʵ��ļ�
    for (int i = 0; i < keywordCount; i++) {
        fprintf(outfile, "�ؼ��� '%s' ���ֵ�Ƶ��: %d\n", keywords[i].word, keywords[i].frequency);
    }

    // �ر��ļ�
    fclose(outfile);
}

