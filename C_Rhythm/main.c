#include "main.h"

int main()
{
    system("mode con cols=140 lines=32 | title kewool");
    ScreenInit();
    
    while (1) {
        CreateMain();
        SelectMap();
    }


    //g_numofFPS = 0;
    //FPSTextInfo = (char*)malloc(128 * sizeof(*FPSTextInfo));
    //memset(FPSTextInfo, '\0', 128);

    //ScreenInit();

    //OldTime = clock(); // �ð��� �����Ѵ�. 1�ʸ��� �����Ѵ�.

    ScreenRelease();

    return 0;
}