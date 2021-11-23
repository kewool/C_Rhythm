#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <io.h>
#include <conio.h>
#include <string.h>


static int g_nScreenIndex;
static HANDLE g_hScreen[2];

char* mapList;
char*** map;

int mapCount = 0;
int y_SelectMapRender = 0;



void ScreenInit()
{
    CONSOLE_CURSOR_INFO cci;

    // 화면 버퍼 2개를 만든다.
    g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    // 커서를 숨긴다.
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(g_hScreen[0], &cci);
    SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void ScreenFlipping()
{
    SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
    g_nScreenIndex = !g_nScreenIndex;
}

void ScreenClear()
{
    COORD Coor = { 0, 0 };
    DWORD dw;
    FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 25, Coor, &dw);
}

void ScreenRelease()
{
    CloseHandle(g_hScreen[0]);
    CloseHandle(g_hScreen[1]);
}

void ScreenPrint(int x, int y, char* string)
{
    DWORD dw;
    COORD CursorPosition = { x, y };
    SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
    WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}


//void Release()
//{
//    free(FPSTextInfo);
//}


void Gotoxy(int x, int y) {
    COORD Pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void ReadMapList() {
    struct _finddata_t fd;
    long handle;
    int result = 0;
    handle = _findfirst(".\\map\\*.kwl", &fd);
    if (handle == -1)
    {
        sprintf(mapList[0], "No map files.\n");
    }

    for (int i = 0;result != -1;i++)
    {
        sprintf(&mapList, "  %s\n", fd.name);
        /*mapList[i][strlen(mapList[i]) - 5] = '\n';
        mapList[i][strlen(mapList[i]) - 4] = '\0';*/
        mapCount++;
        result = _findnext(handle, &fd);
        if (mapCount >= 30) {
            sprintf(&mapList, "  You can load files only 30.\n\0");
            result = -1;
        }
    }

    _findclose(handle);
}

void CreateMain() {
    ReadMapList();
    system("mode con cols=200 lines=32 | title kewool");
    for (int i = 0; i < mapCount+1; i++) {
        printf("%s", mapList[i]);
    }
    Gotoxy(0, 0);
    printf(">");
}

void SelectMap() {
    int y = 0;
    while (1) {
        if (GetAsyncKeyState(VK_UP) & 0x0001) {
            if (y > 0)
                y--;
            SelectMapRender(y);
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
            if (y < mapCount - 1)
                y++;
            SelectMapRender(y);
        }
        if (GetAsyncKeyState(VK_RETURN) & 0x0001) {

        }

        
    }
}

int SelectMapRender(int y)
{
    ScreenClear();
    ScreenPrint(0, 0, mapList);
    ScreenFlipping();

    /*Gotoxy(0, y_SelectMapRender);
    printf(" ");
    Gotoxy(0, y);
    printf(">");
    y_SelectMapRender = y;*/

    //ScreenClear();
    //if (CurTime - OldTime >= 1000) // 출력 코드
    //{
    //    sprintf(FPSTextInfo, "FPS : %d", g_numofFPS);
    //    OldTime = CurTime;
    //    g_numofFPS = 0;
    //}

    //ScreenPrint(0, 0, FPSTextInfo);
    //ScreenFlipping();
}

void Cursor()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int main()
{
    ScreenInit();
    Cursor();
    while (1) {
        CreateMain();
        SelectMap();
    }


    //g_numofFPS = 0;
    //FPSTextInfo = (char*)malloc(128 * sizeof(*FPSTextInfo));
    //memset(FPSTextInfo, '\0', 128);

    //ScreenInit();

    //OldTime = clock(); // 시간을 측정한다. 1초마다 갱신한다.

    //while (1)
    //{
    //    CurTime = clock();
    //    SelectMapRender();
    //}

    //Release();
    //ScreenRelease();

    return 0;
}