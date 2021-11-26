#include "game.h"

char mapList[31][100];

int mapCount = 0;
int lineNum;
int y_SelectRender;
int mapNode[10][20000];
int mapLine[8][20000];
double speed;



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

    for (int i = 0; result != -1; i++)
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
    memset(mapNode, 0, sizeof(mapNode));
    memset(mapLine, 0, sizeof(mapLine));
    ReadMapList();
    ScreenFlipping();
    ScreenClear();
    char mapName[102];
    y_SelectRender = 0;
    for (int i = 0; i < mapCount; i++) {
        /*sprintf(mapName, "  %s", mapList[i]);
        mapName[strlen(mapName) - 5] = '\n';
        mapName[strlen(mapName) - 4] = '\0';
        printf("%s", mapName);*/

        sprintf(mapName, "  %s", mapList[i]);
        mapName[strlen(mapName) - 5] = '\n';
        mapName[strlen(mapName) - 4] = '\0';

        ScreenPrint(0, i, mapName);
        ScreenFlipping();
        ScreenPrint(0, i, mapName);
    }
    //printf("%s", mapList);
    /*Gotoxy(0, 0);
    printf(">");*/
    ScreenPrint(0, 0, ">");
    ScreenFlipping();
}

void SelectRender(int y)
{
    if (y != y_SelectRender) {
        //ScreenClear();
        if (y > y_SelectRender) {
            ScreenPrint(0, y_SelectRender - 1, " ");
        }
        else if (y < y_SelectRender) {
            ScreenPrint(0, y_SelectRender + 1, " ");
        }
        ScreenPrint(0, y, ">");
        ScreenFlipping();
        y_SelectRender = y;
    }

    /*if (y != y_SelectMapRender) {
        Gotoxy(0, y_SelectMapRender);
        printf(" ");
        Gotoxy(0, y);
        printf(">");
        y_SelectMapRender = y;
    }*/

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

void StartGame(int diffNum) {
    ScreenClear();
    for (int i = 0; i < diffNum + 1; i++) {
        for (int j = 0; mapNode[i][j] != 0; j++) {
            if(!mapLine[i][j])
                for(int k = 0; k < 8; k++)
                    mapLine[k][j] = 1;
            
            if (mapNode[i][j] == 1) continue;
            else if (mapNode[i][j] > 1) {
                for (int k = 0; k < mapNode[i][j] - 1; k++) {
                    mapLine[rand() % 8][j] = 2;
                }
            }
            //mapLine[rand() % 8][j] = mapNode[i][j];
        }
    }
    /*for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 30; i++) {
            char a[10];
            itoa(mapLine[j][i], a, 10);
            ScreenPrint(j, i, a);
        }
    }
    ScreenFlipping();
    system("pause");*/

    for (int i = 0; mapLine[0][i]; i++) {

    }
}

void SelectDiff() {
    /*for (int i = 0; i < lineNum; i++) {
        char* a = "  ", *b;
        itoa(i, b, 10);
        strcat(a, b);
        ScreenPrint(0, i, a);
    }*/
    ScreenClear();
    ScreenPrint(0, 0, "난이도 선택");
    ScreenFlipping();
    ScreenClear();
    char diff[2];
    y_SelectRender = 0;
    ScreenPrint(0, 0, "난이도 선택");
    for (int i = 0; i < lineNum+1; i++) {
        char a[4] = "  ";
        itoa(i+1, diff, 10);
        strcat(a, diff);
        ScreenPrint(0, i+1, a);
        ScreenFlipping();
        ScreenPrint(0, i+1, a);
    }
    ScreenPrint(0, 1, ">");
    ScreenFlipping();
    int y = 1;
    while (1) {
        if (GetAsyncKeyState(VK_UP) & 0x0001) {
            if (y > 1)
                y--;
            SelectRender(y);
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
            if (y < lineNum+1)
                y++;
            SelectRender(y);
        }
        if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
            break;
        }
    }
    StartGame(y-1);
}

void MapLoader(int y) {
    char mapLoc[106] = ".\\map\\";
    char buffer[BARSIZE];
    char** splitText, **chordSplit;
    int spaceCount=0, rest, nodeNum, nodeCount, chord;
    strcat(mapLoc, mapList[y]);
    mapLoc[strlen(mapLoc) - 1] = '\0';
    FILE* map = fopen(mapLoc, "r");
    fgets(buffer, BARSIZE, map);
    speed = 0.125 / (double)(atoi(buffer) / 60.0);
    chordSplit = split("0n*2", '*');

    while (strcmp(buffer, "finish")) {
        fgets(buffer, BARSIZE, map);
        if (!strcmp(buffer, "\n") || !strcmp(buffer, "&"))
            continue;
        else if (strstr(buffer, "start") != NULL) {
            splitText = split(buffer, '#');
            lineNum = atoi(splitText[1]) - 1;
            nodeCount = 0;
        }
        else {
            spaceCount = 1;
            for (int i = 0; buffer[i] != '\0'; i++)
                if (buffer[i] == ' ') spaceCount++;
            splitText = split(buffer, ' ');
            for (int i = 0; i < spaceCount; i++) {
                rest = 0;
                if (strstr(splitText[i], "r") != NULL) rest = 1;
                nodeNum = atoi(splitText[i]);
                if (rest) {
                    switch (nodeNum) {
                    case 0:
                        for (int j = 0; j < 32; j++) {
                            mapNode[lineNum][nodeCount] = 1;
                            nodeCount++;
                        }
                        if (strstr(splitText[i], ".") != NULL)
                            for (int j = 0; j < 16; j++) {
                                mapNode[lineNum][nodeCount] = 1;
                                nodeCount++;
                            }
                        break;
                    case 1:
                        for (int j = 0; j < 16; j++) {
                            mapNode[lineNum][nodeCount] = 1;
                            nodeCount++;
                        }
                        if (strstr(splitText[i], ".") != NULL)
                            for (int j = 0; j < 8; j++) {
                                mapNode[lineNum][nodeCount] = 1;
                                nodeCount++;
                            }
                        break;
                    case 2:
                        for (int j = 0; j < 8; j++) {
                            mapNode[lineNum][nodeCount] = 1;
                            nodeCount++;
                        }
                        if (strstr(splitText[i], ".") != NULL)
                            for (int j = 0; j < 4; j++) {
                                mapNode[lineNum][nodeCount] = 1;
                                nodeCount++;
                            }
                        break;
                    case 3:
                        for (int j = 0; j < 4; j++) {
                            mapNode[lineNum][nodeCount] = 1;
                            nodeCount++;
                        }
                        if (strstr(splitText[i], ".") != NULL)
                            for (int j = 0; j < 2; j++) {
                                mapNode[lineNum][nodeCount] = 1;
                                nodeCount++;
                            }
                        break;
                    case 4:
                        for (int j = 0; j < 2; j++) {
                            mapNode[lineNum][nodeCount] = 1;
                            nodeCount++;
                        }
                        if (strstr(splitText[i], ".") != NULL) {
                            mapNode[lineNum][nodeCount] = 1;
                            nodeCount++;
                        }
                        break;
                    case 5:
                        mapNode[lineNum][nodeCount] = 1;
                        nodeCount++; 
                        break;
                    }
                }
                else {
                    chord = 1;
                    if (strstr(splitText[i], "*") != NULL) {
                        chordSplit = split(splitText[i], '*');
                        chord = atoi(chordSplit[1]);
                    }
                    switch (nodeNum) {
                    case 0:
                        mapNode[lineNum][nodeCount] = 1 + chord;
                        nodeCount++;
                        for (int j = 0; j < 31; j++) {
                            mapNode[lineNum][nodeCount] = 1;
                            nodeCount++;
                        }
                        if (strstr(splitText[i], ".") != NULL)
                            for (int j = 0; j < 16; j++) {
                                mapNode[lineNum][nodeCount] = 1;
                                nodeCount++;
                            }
                        break;
                    case 1:
                        mapNode[lineNum][nodeCount] = 1 + chord;
                        nodeCount++;
                        for (int j = 0; j < 15; j++) {
                            mapNode[lineNum][nodeCount] = 1;
                            nodeCount++;
                        }
                        if (strstr(splitText[i], ".") != NULL)
                            for (int j = 0; j < 8; j++) {
                                mapNode[lineNum][nodeCount] = 1;
                                nodeCount++;
                            }
                        break;
                    case 2:
                        mapNode[lineNum][nodeCount] = 1 + chord;
                        nodeCount++;
                        for (int j = 0; j < 7; j++) {
                            mapNode[lineNum][nodeCount] = 1;
                            nodeCount++;
                        }
                        if (strstr(splitText[i], ".") != NULL)
                            for (int j = 0; j < 4; j++) {
                                mapNode[lineNum][nodeCount] = 1;
                                nodeCount++;
                            }
                        break;
                    case 3:
                        mapNode[lineNum][nodeCount] = 1 + chord;
                        nodeCount++;
                        for (int j = 0; j < 3; j++) {
                            mapNode[lineNum][nodeCount] = 1;
                            nodeCount++;
                        }
                        if (strstr(splitText[i], ".") != NULL)
                            for (int j = 0; j < 2; j++) {
                                mapNode[lineNum][nodeCount] = 1;
                                nodeCount++;
                            }
                        break;
                    case 4:
                        mapNode[lineNum][nodeCount] = 1 + chord;
                        nodeCount++;
                        mapNode[lineNum][nodeCount] = 1;
                        nodeCount++; 
                        if (strstr(splitText[i], ".") != NULL) {
                            mapNode[lineNum][nodeCount] = 1;
                            nodeCount++;
                        }
                        break;
                    case 5:
                        mapNode[lineNum][nodeCount] = 1 + chord;
                        nodeCount++;
                        break;
                    }
                }
            }
        }
    }

    free(splitText);
    free(chordSplit);
    
}

void SelectMap() {
    int y = 0;
    while (1) {
        if (GetAsyncKeyState(VK_UP) & 0x0001) {
            if (y > 0)
                y--;
            SelectRender(y);
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
            if (y < mapCount - 1)
                y++;
            SelectRender(y);
        }
        if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
            break;
        }
    }

    MapLoader(y);
}