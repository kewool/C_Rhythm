#include "game.h"

char mapList[31][100];

int mapCount = 0;
int lineNum;
int y_SelectRender;
int mapNode[10][10000];
int mapLine[6][10000];
double speed;
int gameScreen[19][6];
int nodeArray[8][5] = { {2,4,6,8,10},{14,16,18,20,22},{26,28,30,32,34},{38,40,42,44,46},{50,52,54,56,58},{62,64,66,68,70},{74,76,78,80,82},{86,88,90,92,94} };
char musicName[106]= ".\\map\\";
wchar_t musicLoc[106];

void push(int queue[]) {
    for (int i = 18; i > 0; i--) {
        for (int j = 0; j < 6; j++) {
            gameScreen[i][j] = gameScreen[i - 1][j] ? gameScreen[i - 1][j] : gameScreen[i - 1][j] + 1;
            /*if (i == 1 && gameScreen[i][j] > 1 && queue[j] == 1)
                queue[j] = 0;
            else if (gameScreen[i][j] > 1 && gameScreen[i - 2][j] == 1)
                gameScreen[i - 1][j] = 0;*/
        }
    }for (int i = 18; i > 0; i--) {
        for (int j = 0; j < 6; j++) {
            if (i == 1 && gameScreen[i][j] > 1 && queue[j] == 1)
                queue[j] = 0;
            else if (gameScreen[i][j] == 2 && gameScreen[i - 1][j] != 2)
                gameScreen[i - 1][j] = 0;
        }
    }
    for(int i = 0; i < 6; i++)
        gameScreen[0][i] = queue[i];
}

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
    ScreenClear();
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

void CreateFrame() {
    for (int a = 0; a < 2; a++) {
        ScreenClear();
        ScreenPrint(0, 0, "┌");
        int x = 2;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 5; j++) {
                ScreenPrint(x, 0, "▣");
                x += 2;
            }
            if (i != 5) {
                ScreenPrint(x, 0, "─");
                x += 2;
            }
        }
        ScreenPrint(x, 0, "┐");
        for (int y = 1; y < 16; y++) {
            x = 0;
            ScreenPrint(x, y, "│");
            x += 2;
            for (int i = 0; i < 35; i++, x += 2) {
                ScreenPrint(x, y, "　");
            }
            ScreenPrint(x, y, "│");
        }
        ScreenPrint(0, 16, "└");
        x = 2;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 5; j++) {
                ScreenPrint(x, 16, "□");
                x += 2;
            }
            if (i != 5) {
                ScreenPrint(x, 16, "─");
                x += 2;
            }
        }
        ScreenPrint(x, 16, "┘");
        /*ScreenPrint(0, 0, "┌");
        ScreenPrint(2, 0, "▣");
        ScreenPrint(4, 0, '▣');*/
        ScreenFlipping();
    }
}

void Result() {
    ScreenPrintFront(0, 18, "계속하려면 공백을 눌러주세요.");
    while (1) {
        if (GetAsyncKeyState(VK_SPACE) & 0x0001) {
            break;
        }
    }
}

void StartGame(int diffNum) {
    ScreenClear();
    for (int i = 0; i < diffNum + 1; i++) {
        for (int j = 0; mapNode[i][j] != 0; j++) {
            if(!mapLine[i][j])
                for(int k = 0; k < 6; k++)
                    mapLine[k][j] = 1;
            
            if (mapNode[i][j] == 1) continue;
            else if (mapNode[i][j] > 1) {
                for (int k = 0; k < mapNode[i][j] - 1; k++) {
                    mapLine[rand() % 6][j] = 2;
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

    /*ScreenClear();
    ScreenPrint(0, 0, "┌▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣┐");
    ScreenFlipping();*/
    
    //wchar_t* a = L"┌▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣┐";
    
    CreateFrame();

    /*ScreenClear();
    ScreenPrint(0, 0, "##@@@@@#@@@@@#@@@@@#@@@@@#@@@@@#@@@@@#@@@@@#@@@@@##");
    for (int i = 0; i < 30; i++) {
        ScreenPrint(0, i+1, "#                                                 #");
    }
    ScreenFlipping();*/

    //ScreenRelease();
    /*wchar_t ws1[20] = L"■";
    wprintf(L"%s",ws1);*/

    //printf("%s", 0xa3);
    //printf(L"┌▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣─▣▣▣▣▣┐");
    for (int i = 0; i < 17; i++)
        for (int j = 0; j < 6; j++)
            gameScreen[i][j] = 1;
    
    int line[6], start, end;
    speed = speed * 1000.0;
    //Sleep(speed * 2*20);
    /*if (strstr(musicName, "밀크 크라운 온 소네치카 - nameless.wav"))
        PlaySound(L".\\map\\밀크 크라운 온 소네치카 - nameless.wav", NULL, SND_FILENAME | SND_ASYNC);*/
    PlaySound(musicLoc, NULL, SND_FILENAME | SND_ASYNC);
    char accuracy[20];
    int accuracyAll = 1;
    int accuracyRight = 0;
    //Sleep(speed * 2);
        
    for (int i = 0; mapLine[0][i]; i++) {
        start = clock();
        for (int j = 0; j < 6; j++) {
            line[j] = mapLine[j][i];
        }
        push(line);
        for (int j = 17; j > 0; j--) {
            for (int k = 0; k < 6; k++) {
                /*if (!gameScreen[j][k])
                    for (int l = 0; l < 5; l++)
                        ScreenPrint(j, nodeArray[k][l], "　");
                else if(gameScreen[j][k] > 1)
                    for (int l = 0; l < 5; l++) {

                    }*/
                switch (gameScreen[j][k]) {
                case 0:
                    for (int l = 0; l < 5; l++) {
                        /*if(!gameScreen[0][l])
                            for (int j = 0; j < 5; j++)
                                ScreenPrint(nodeArray[l][j], 0, "▣");*/
                        if (j != 1 && j != 17)
                            ScreenPrint(nodeArray[k][l], j - 1, "　");
                        else if(j == 17)
                            ScreenPrint(nodeArray[k][l], j - 1, "□");
                        //if (!gameScreen[1][l])
                        //    for (int j = 0; j < 5; j++)
                        //        ScreenPrint(nodeArray[k][j], 0, "▣");
                    }
                    break;
                case 2:
                    for (int l = 0; l < 5; l++) {
                        ScreenPrint(nodeArray[k][l], j, "■");
                        if (j == 17)
                            ScreenPrint(nodeArray[k][l], j, "　");
                    }
                    break;
                }
                
                /*char a[2];
                itoa(gameScreen[j][k], a, 10);
                ScreenPrint(k, j, a);*/
            }
            
        }
        if (gameScreen[16][0] == 2 || gameScreen[16][1] == 2 || gameScreen[16][2] == 2 || gameScreen[16][3] == 2 || gameScreen[16][4] == 2 || gameScreen[16][5] == 2) {
            accuracyAll++;
        }
        //if (_kbhit()) {
            if (GetAsyncKeyState(0x53) & 0x0001) {
                /*for (int i = 2; i < 11; i += 2) {
                    ScreenPrintFront(i, 16, "▣");
                }*/
                if (gameScreen[14][0] == 2 || gameScreen[15][0] == 2 || gameScreen[16][0] == 2) {
                    accuracyRight++;
                }
                else {
                    accuracyAll++;
                }
            }
            /*else if (GetAsyncKeyState(0x53) & 0x0001) {
                for (int i = 2; i < 11; i += 2) {
                    ScreenPrintFront(i, 16, "□");
                }
            }*/
            if (GetAsyncKeyState(0x44) & 0x0001) {
                if (gameScreen[14][1] == 2 || gameScreen[15][1] == 2 || gameScreen[16][1] == 2) {
                    accuracyRight++;
                }
                else {
                    accuracyAll++;
                }
            }
            if (GetAsyncKeyState(0x46) & 0x0001) {
                if (gameScreen[14][2] == 2 || gameScreen[15][2] == 2 || gameScreen[16][2] == 2) {
                    accuracyRight++;
                }
                else {
                    accuracyAll++;
                }
            }
            if (GetAsyncKeyState(0x4A) & 0x0001) {
                if (gameScreen[14][3] == 2 || gameScreen[15][3] == 2 || gameScreen[16][3] == 2) {
                    accuracyRight++;
                }
                else {
                    accuracyAll++;
                }
            }
            if (GetAsyncKeyState(0x4B) & 0x0001) {
                if (gameScreen[14][4] == 2 || gameScreen[15][4] == 2 || gameScreen[16][4] == 2) {
                    accuracyRight++;
                }
                else {
                    accuracyAll++;
                }
            }
            if (GetAsyncKeyState(0x4C) & 0x0001) {
                if (gameScreen[14][5] == 2 || gameScreen[15][5] == 2 || gameScreen[16][5] == 2) {
                    accuracyRight++;
                }
                else {
                    accuracyAll++;
                }
            }
            if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
                PlaySound(NULL, 0, 0);
                break;
            }
        //}
        if (accuracyAll) {
            sprintf(accuracy, "정확도: %.1lf", (double)accuracyRight / (double)accuracyAll * 100.0);
            ScreenPrintFront(0, 17, accuracy);
            ScreenPrint(0, 17, accuracy);
        }
        else {
            ScreenPrintFront(0, 17, "정확도: 0.0");
        }
        ScreenFlipping();
        end = clock();
        Sleep(speed - (end - start)-10);
        //Sleep(500);
    }
    PlaySound(NULL, 0, 0);
}

void SelectDiff() {
    /*for (int i = 0; i < lineNum; i++) {
        char* a = "  ", *b;
        itoa(i, b, 10);
        strcat(a, b);
        ScreenPrint(0, i, a);
    }*/
    /*ScreenClear();
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
        StartGame(y-1);
    }*/
    ScreenClear();
    ScreenFlipping();
    ScreenClear();
    char diff[2];
    y_SelectRender = 0;

    for (int i = 0; i < lineNum + 1; i++) {
        char a[4] = "  ";
        itoa(i + 1, diff, 10);
        strcat(a, diff);
        ScreenPrint(0, i, a);
        ScreenFlipping();
        ScreenPrint(0, i, a);
    }
    ScreenPrint(0, 0, ">");
    ScreenFlipping();
    int y = 0;
    while (1) {
        if (GetAsyncKeyState(VK_UP) & 0x0001) {
            if (y > 0)
                y--;
            SelectRender(y);
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
            if (y < lineNum)
                y++;
            SelectRender(y);
        }
        if (GetAsyncKeyState(VK_RETURN) & 0x0001) {

            break;
        }
        /*f (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
            break;
        }*/
    }
    StartGame(y);
}

void MapLoader(int y) {
    musicLoc[0] = L'\0';
    wcscat(musicLoc, L".\\music\\");
    char mapLoc[106] = ".\\map\\";
    char buffer[BARSIZE];
    char** splitText, **chordSplit;
    int spaceCount=0, rest, nodeNum, nodeCount, chord;
    wchar_t loc[100];
    strcat(mapLoc, mapList[y]);/*
    strcat(musicName, mapList[y]);
    musicName[strlen(musicName) - 5] = '\0';
    strcat(musicName, ".wav");*/
    //swprintf(musicLoc, 106, "%hs", musicName);
    mapLoc[strlen(mapLoc) - 1] = '\0';
    FILE* map = fopen(mapLoc, "r");
    fgets(buffer, BARSIZE, map);
    //speed = 0.125 / ((double)atoi(buffer) / 60.0);
    speed = 60.0 / (8.0 * (double)atoi(buffer));
    chordSplit = split("0n*2", '*');
    fgetws(loc, 100, map);
    wcscat(musicLoc, loc);
    musicLoc[wcslen(musicLoc) - 1] = L'\0';

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
    fclose(map);
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