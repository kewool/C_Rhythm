#include "main.h"

#ifndef INIT_SIZE
#define INIT_SIZE 8
#endif


void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenRelease();
void ScreenPrint(int x, int y, char* string);
char** split(char* sentence, char separator, int* num_tokens);
char* str(int size);
void SetColor(int foreground, int background);