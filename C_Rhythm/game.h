#include "main.h"

#ifndef BARSIZE
#define BARSIZE 256
#define LINE 6
#endif

void Gotoxy(int x, int y);
void ReadMapList();
void CreateMain();
void SelectRender(int y);
void MapLoader(int y);
void SelectMap();
void StartGame(int diffNum);
void CreateFrame();
void SelectDiff();
void push(int queue[]);
void Result(int accuracy);