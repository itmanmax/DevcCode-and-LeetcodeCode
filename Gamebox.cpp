#include <stdlib.h>

int main() {
    // ִ�е�һ������
    system("cd /d C:\\CodeFile\\ideaPruduct\\������Ϸ����\\openJFX-17\\out\\artifacts\\openJFX_17_jar");
    
    // ִ�еڶ��������ָ�������� JAR �ļ�·��
    system("java --module-path C:\\soft\\javafx-sdk-21.0.2\\lib --add-modules javafx.controls -jar C:\\CodeFile\\ideaPruduct\\������Ϸ����\\openJFX-17\\out\\artifacts\\openJFX_17_jar\\openJFX-17.jar");
    
    return 0;
}

