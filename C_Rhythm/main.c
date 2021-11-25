#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <io.h>
#include <conio.h>
#include <string.h>


static int g_nScreenIndex;
static HANDLE g_hScreen[2];

char mapList[31][100];
char*** map;

int mapCount = 0;
int y_SelectMapRender;



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
    mapCount = 0;
    if (handle == -1)
    {
        sprintf(mapList[0], "No map files.\n");
    }
    
    for (int i = 0;result != -1;i++)
    {

        /*strcat(mapList[i], "  ");
        strcat(mapList[i], fd.name);
        strcat(mapList[i], "\n\0");*/

        /*strcat(mapList, "  ");
        strcat(mapList, fd.name);
        strcat(mapList, "\n");*/

        sprintf(mapList[i], "%s\n", fd.name);
        /*mapList[i][strlen(mapList[i]) - 5] = '\n';
        mapList[i][strlen(mapList[i]) - 4] = '\0';*/

        mapCount++;
        result = _findnext(handle, &fd);
        if (mapCount >= 30) {
            sprintf(mapList, "  You can load files only 30.\n");
            result = -1;
        }
    }

    _findclose(handle);
}

void CreateMain() {
    ReadMapList();
    char mapName[102];
    y_SelectMapRender = 0;
    for (int i = 0; i < mapCount; i++) {
        sprintf(mapName, "  %s", mapList[i]);
        mapName[strlen(mapName) - 5] = '\n';
        mapName[strlen(mapName) - 4] = '\0';
        printf("%s", mapName);
        /*sprintf(mapName, "  %s", mapList[i]);
        mapName[strlen(mapName) - 5] = '\n';
        mapName[strlen(mapName) - 4] = '\0';

        ScreenPrint(0, i, mapName);
        ScreenFlipping();
        ScreenPrint(0, i, mapName);*/
    }
    //printf("%s", mapList);
    Gotoxy(0, 0);
    printf(">");
    /*ScreenPrint(0, 0, ">");
    ScreenFlipping();*/
}

void SelectMapRender(int y)
{
    //if (y != y_SelectMapRender) {
    //    //ScreenClear();
    //    if (y > y_SelectMapRender) {
    //        ScreenPrint(0, y_SelectMapRender - 1, " ");
    //    }
    //    else if (y < y_SelectMapRender) {
    //        ScreenPrint(0, y_SelectMapRender + 1, " ");
    //    }
    //    ScreenPrint(0, y, ">");
    //    ScreenFlipping();
    //    y_SelectMapRender = y;
    //}

    if (y != y_SelectMapRender) {
        Gotoxy(0, y_SelectMapRender);
        printf(" ");
        Gotoxy(0, y);
        printf(">");
        y_SelectMapRender = y;
    }

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


void MapLoader(int y) {
    char mapLoc[108] = ".\\map\\";
    char buffer[256];
    strcat(mapLoc, mapList[y]);
    mapLoc[strlen(mapLoc)-1] = '\0';
    FILE* map = fopen(mapLoc, "r");
    fgets(buffer, 256, map);
    ScreenClear();
    ScreenPrint(0, 0, buffer);
    ScreenFlipping();
    system("pause");
    system("resume");
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
            break;
        }
    }

    MapLoader(y);
}


void Cursor()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int main()
{
    system("mode con cols=200 lines=32 | title kewool");
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