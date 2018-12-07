#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include<ege.h>
#include<graphics.h>

#include<mmsystem.h>
#include<string>
#pragma comment(lib,"winmm.lib")

#define maps_num 35

typedef struct Map {
	char map[50][50];
	int level;
	int h;
	int x;
	int y;
	int aim_count;
	int aimx[50];
	int aimy[50];
}Map;

void main_interface1();
void main_interface2();
void selectLevel(int level);
void mainloop();
int gameloop(int level);
Map *LoadMap(int level);
