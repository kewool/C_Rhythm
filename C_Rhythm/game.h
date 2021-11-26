#include "main.h"

#ifndef BARSIZE
#define BARSIZE 256
#endif

void Gotoxy(int x, int y);
void ReadMapList();
void CreateMain();
void SelectRender(int y);
void MapLoader(int y);
void SelectMap();
void StartGame(int diffNum);
