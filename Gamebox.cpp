#include <stdlib.h>

int main() {
    // 执行第一条命令
    system("cd /d C:\\CodeFile\\ideaPruduct\\桌面游戏盒子\\openJFX-17\\out\\artifacts\\openJFX_17_jar");
    
    // 执行第二条命令，并指定完整的 JAR 文件路径
    system("java --module-path C:\\soft\\javafx-sdk-21.0.2\\lib --add-modules javafx.controls -jar C:\\CodeFile\\ideaPruduct\\桌面游戏盒子\\openJFX-17\\out\\artifacts\\openJFX_17_jar\\openJFX-17.jar");
    
    return 0;
}

