#include "main.h"



int main()
{
    srand(time(NULL));
    system("mode con cols=74 lines=34 | title kewool");
    ScreenInit();
    
    while (1) {
        CreateMain();
        SelectMap();
        SelectDiff();
        Result();
    }


    //g_numofFPS = 0;
    //FPSTextInfo = (char*)malloc(128 * sizeof(*FPSTextInfo));
    //memset(FPSTextInfo, '\0', 128);

    //ScreenInit();

    //OldTime = clock(); // �ð��� �����Ѵ�. 1�ʸ��� �����Ѵ�.

    ScreenRelease();

    return 0;
}