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

    //OldTime = clock(); // 시간을 측정한다. 1초마다 갱신한다.

    ScreenRelease();

    return 0;
}