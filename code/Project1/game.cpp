#include"founction.h"

void game_face(int level, int step_num, int restep_num);
void pause();
void lastlevel();
void passlevel(int step_num);


int gameloop(int level)
{
	mciSendString(TEXT("open Boxmove.wav alias Boxmove"), NULL, 0, NULL);

	PIMAGE pimg_wall = newimage();
	PIMAGE pimg_land = newimage();
	PIMAGE pimg_BoxYellow = newimage();
	PIMAGE pimg_BoxRed = newimage();
	PIMAGE pimg_aim = newimage();
	PIMAGE pimg_ManUP1 = newimage();
	PIMAGE pimg_ManDOWN1 = newimage();
	PIMAGE pimg_ManRIGHT1 = newimage();
	PIMAGE pimg_ManLEFT1 = newimage();
	PIMAGE pimg_black = newimage();

	getimage(pimg_wall, "../../source/image\\wall.jpg", 0, 0);
	getimage(pimg_land, "../../source/image\\land.jpg", 0, 0);
	getimage(pimg_BoxYellow, "../../source/image\\box.jpg", 0, 0);
	getimage(pimg_BoxRed, "../../source/image\\box.jpg", 0, 0);
	getimage(pimg_aim, "../../source/image\\aim.jpg", 0, 0);
	getimage(pimg_ManUP1, "../../source/image\\up.jpg", 0, 0);
	getimage(pimg_ManDOWN1, "../../source/image\\down.jpg", 0, 0);
	getimage(pimg_ManRIGHT1, "../../source/image\\right.jpg", 0, 0);
	getimage(pimg_ManLEFT1, "../../source/image\\left.jpg", 0, 0);
	getimage(pimg_black, "../../source/image\\block.jpg", 0, 0);

	int x = 0;
	int y = 0;
	char key = 0;
	int isEnd = 0;
	int scenes = 0;
	int step_num = 0;
	int restep_num = 3;
	int reValue = 0;
	int high = 0;
	int wide = 0;
	int count = 0;

	MUSIC mus;
	mus.OpenFile("../../source/music\\Boxmove.wav");

	int aim_x[50] = { 0 }, aim_y[50] = { 0 }, xnum = 0, ynum = 0;

	int isUndo = 0;
	int lastStep_num;
	int box_x, box_y;
	int box_nx, box_ny;
	int last_x, last_y;

	Map*map;
	map = LoadMap(level);
	x = map->x;
	y = map->y;

	wide = strlen(map->map[0]);

	for (int i = 0; i < 20; i++) {
		for (int t = 0; map->map[i][t] != '\0'; t++)
			if (map->map[i][t] == '@') {
				x = i;
				y = t;
				i = 99;
				break;
			}
	}

	for (int i = 2; i < 20; i++) {
		for (int t = 2; map->map[i][t] != '\0'; t++) {
			if (map->map[i][t] == 'X' || map->map[i][t] == 'Q') {
				aim_x[xnum] = i;
				aim_y[ynum] = t;
				xnum++;
				ynum++;
			}
			if (map->map[i][1] == '|') {
				i = 99;
				break;
			}
		}
	}

	wide = strlen(map->map[0]);

	for (int i = 0; i < 20; i++) {
		for (int t = 0; map->map[i][t] != '\0'; t++)
			if (map->map[i][t] == '@') {
				x = i;
				y = t;
				i = 99;
				break;
			}
	}

	for (int i = 2; i < 20; i++) {
		for (int t = 2; map->map[i][t] != '\0'; t++) {
			if (map->map[i][t] == 'X' || map->map[i][t] == 'Q') {
				aim_x[xnum] = i;
				aim_y[ynum] = t;
				xnum++;
				ynum++;
			}
			if (map->map[i][1] == '|') {
				high = i;
				i = 99;
				break;
			}
		}
	}

	high = (13 - high) / 2;
	wide = (16 - strlen(map->map[0])) / 2;

	for (; is_run(); delay_fps(60)) {
		if (count > 60)
			count = 0;
		count += 2;

		switch (scenes) {
		case 0:
			game_face(level, step_num, restep_num);

			for (int i = 1; i <= 17; i++)
			{
				for (int t = 0; t < strlen(map->map[0]); t++)
				{
					if (map->map[i][t] == '|' || map->map[i][t] == '=')
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 15, pimg_black);
					if (map->map[i][t] == ' ')
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 15, pimg_land);
					if (map->map[i][t] == 'O')
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 15, pimg_BoxYellow);
					if (map->map[i][t] == 'Q')
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 15, pimg_BoxRed);
					if (map->map[i][t] == '#')
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 15, pimg_wall);
					if (map->map[i][t] == 'X')
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 15, pimg_aim);
					if (map->map[i][t] == '@')
						if (key == 'd')
						{
							if (count > 30)
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 15, pimg_ManRIGHT1);
							else
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 15, pimg_ManRIGHT1);
						}
						else if (key == 'a')
						{
							if (count > 30)
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 15, pimg_ManLEFT1);
							else
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 15, pimg_ManLEFT1);
						}
						else if (key == 'w')
						{
							if (count > 30)
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 15, pimg_ManUP1);
							else
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 15, pimg_ManUP1);
						}
						else
						{
							if (count > 30)
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 15, pimg_ManDOWN1);
							else
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 15, pimg_ManDOWN1);
						}
				}
				if (map->map[i][1] == '|')
					break;
			}
			break;
		case 1:
			pause();
			break;
		case 2:
			if (level == maps_num - 1)
				lastlevel();
			else
				passlevel(step_num);
			break;
		default:
			break;
		}

		if (kbhit()) {
			key = getch();
			key = tolower(key);

			switch (scenes) {
			case 0:
				if (key == 's') {
					if (map->map[x + 1][y] == ' ' || map->map[x + 1][y] == 'X') {
						map->map[x][y] = ' ';
						x++;
						map->map[x][y] = '@';
						step_num++;
					}
					else if ((map->map[x + 1][y] == 'O' || map->map[x + 1][y] == 'Q') && map->map[x + 2][y] != 'O' && map->map[x + 2][y] != 'Q' && map->map[x + 2][y] != '#') {
						map->map[x][y] = ' ';

						last_x = x;
						last_y = y;

						x++;

						box_nx = x;
						box_ny = y;

						map->map[x][y] = '@';
						map->map[x + 1][y] = 'O';
						isUndo = 1;

						box_x = x + 1;
						box_y = y;

						lastStep_num = step_num;
						step_num++;

						mus.Play(0);
					}
				}
				else if (key == 'w') {
					if (map->map[x - 1][y] == ' ' || map->map[x - 1][y] == 'X') {
						map->map[x][y] = ' ';
						x--;
						map->map[x][y] = '@';
						step_num++;
					}
					else if ((map->map[x - 1][y] == 'O' || map->map[x - 1][y] == 'Q') && map->map[x - 2][y] != 'O' && map->map[x - 2][y] != 'Q' && map->map[x - 2][y] != '#') {
						map->map[x][y] = ' ';

						last_x = x;
						last_y = y;

						x--;

						box_nx = x;
						box_ny = y;

						map->map[x][y] = '@';
						map->map[x - 1][y] = 'O';
						isUndo = 1;

						box_x = x - 1;
						box_y = y;

						lastStep_num = step_num;
						step_num++;

						mus.Play(0);
					}
				}
				else if (key == 'a') {
					if (map->map[x][y - 1] == ' ' || map->map[x][y - 1] == 'X') {
						map->map[x][y] = ' ';
						y--;
						map->map[x][y] = '@';
						step_num++;
					}
					else if ((map->map[x][y - 1] == 'O' || map->map[x][y - 1] == 'Q') && map->map[x][y - 2] != 'O' && map->map[x][y - 2] != 'Q' && map->map[x][y - 2] != '#') {
						map->map[x][y] = ' ';

						last_x = x;
						last_y = y;

						y--;

						box_nx = x;
						box_ny = y;

						map->map[x][y] = '@';
						map->map[x][y - 1] = 'O';
						isUndo = 1;

						box_x = x;
						box_y = y - 1;

						lastStep_num = step_num;
						step_num++;

						mus.Play(0);
					}
					break;
				}
				else if (key == 'd') {
					if (map->map[x][y + 1] == ' ' || map->map[x][y + 1] == 'X') {
						map->map[x][y] = ' ';
						y++;
						map->map[x][y] = '@';
						step_num++;
					}
					else if ((map->map[x][y + 1] == 'O' || map->map[x][y + 1] == 'Q') && map->map[x][y + 2] != 'O' && map->map[x][y + 2] != 'Q'&&map->map[x][y + 2] != '#') {
						map->map[x][y] = ' ';

						last_x = x;
						last_y = y;

						y++;

						box_nx = x;
						box_ny = y;

						map->map[x][y] = '@';
						map->map[x][y + 1] = 'O';
						isUndo = 1;

						box_x = x;
						box_y = y + 1;

						lastStep_num = step_num;
						step_num++;

						mus.Play(0);
					}
				}
				else if (key == 'u') {
					if (isUndo && restep_num > 0) {

						map->map[x][y] = ' ';
						x = last_x;
						y = last_y;
						map->map[x][y] = '@';

						map->map[box_x][box_y] = ' ';
						map->map[box_nx][box_ny] = 'O';

						step_num = lastStep_num;

						isUndo = 0;
						restep_num--;
					}
				}
				else if (key == 'q') {
					reValue = 4;
					isEnd = 1;
				}
				else if (key == 27) {
					scenes = 1;
				}
				break;
			case 1:
				if (key == 'r' || key == 27) {
					scenes = 0;
				}
				else if (key == 'x') {
					reValue = 2;
					isEnd = 1;
				}
				else if (key == 'q') {
					reValue = 4;
					isEnd = 1;
				}
				else if (key == 'n' && level != maps_num - 1) {
					reValue = 5;
					isEnd = 1;
				}
				else if (key == 'm') {
					reValue = 1;
					isEnd = 1;
				}
				break;
			case 2:
				if (key == 'x') {
					reValue = 2;
					isEnd = 1;
				}
				else if (key == 'q') {
					reValue = 4;
					isEnd = 1;
				}
				else if (key == 'n'&&level != maps_num - 1) {
					reValue = 5;
					isEnd = 1;
				}
				else if (key == 'm') {
					reValue = 1;
					isEnd = 1;
				}
				break;
			default:
				break;
			}
		}

		for (int i = 0; aim_x[i] != 0; i++) {
			if (map->map[aim_x[i]][aim_y[i]] == ' ')
				map->map[aim_x[i]][aim_y[i]] = 'X';
			if (map->map[aim_x[i]][aim_y[i]] == 'O')
				map->map[aim_x[i]][aim_y[i]] = 'Q';
		}

		int count = 0;
		for (int i = 0; aim_x[i] != 0; i++) {
			if (map->map[aim_x[i]][aim_y[i]] == 'Q')
				count++;
		}
		if (count == xnum) {
			scenes = 2;
		}

		if (isEnd)
			break;
	}

	mus.Close(); 

	delimage(pimg_wall);
	delimage(pimg_land);
	delimage(pimg_BoxYellow);
	delimage(pimg_BoxRed);
	delimage(pimg_aim);
	delimage(pimg_ManUP1);
	delimage(pimg_ManDOWN1);
	delimage(pimg_ManRIGHT1);
	delimage(pimg_ManLEFT1);
	delimage(pimg_black);
	return reValue;
}

void game_face(int level, int step_num, int restep_num)
{
	cleardevice();

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfillcolor(WHITE);
	bar(750, 0, 755, 700);

	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));
	setfont(48, 0, "楷体");
	setbkmode(TRANSPARENT);
	char str[20];
	sprintf(str, "第%d关", level + 1);
	outtextxy(800, 100, str);
	setfont(24, 0, "楷体");
	sprintf(str, "步数：%d", step_num);
	outtextxy(780, 250, str);

	sprintf(str, "剩余撤销次数：%d", restep_num);
	outtextxy(780, 300, str);

	outtextxy(780, 350, "重玩本关(Q)");
	outtextxy(780, 400, "撤销(U)");
	outtextxy(780, 450, "暂停(ESC)");
}

void pause()
{
	cleardevice();

	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));
	setfont(48, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(400, 200, "继续(R)");

	setfont(40, 0, "楷体");
	outtextxy(140, 300, "选关(X)");
	outtextxy(320, 300, "重玩(Q)");
	outtextxy(480, 300, "下一关(N)");
	outtextxy(700, 300, "主菜单(M)");
}

void lastlevel()
{
	cleardevice();

	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));
	setfont(48, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(280, 250, "这已经是最后一关了！");
}

void passlevel(int step_num)
{
	cleardevice();

	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));
	setfont(60, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(420, 150, "过关！");

	setfont(40, 0, "楷体");
	char str[20];
	sprintf(str, "本关总计步数:%d", step_num);
	outtextxy(350, 250, str);

	setfont(40, 0, "楷体");
	outtextxy(140, 350, "选关(X)");
	outtextxy(320, 350, "重玩(Q)");
	outtextxy(480, 350, "下一关(N)");
	outtextxy(700, 350, "菜单(M)");
}

	Map *LoadMap(int level) {
		Map*temp = (Map*)malloc(sizeof(Map));
		char buffer[256];
		FILE*fp;
		sprintf(buffer, "../../source/map/%d.txt", level + 1);
		fp = fopen(buffer, "r");
		temp->level = level;
		temp->aim_count = 0;
		for (int i = 0;; i++) {
			fgets(temp->map[i], 256, fp);
			temp->map[i][strlen(temp->map[i]) - 1] = '\0';
			for (int j = 0; temp->map[i][j] != '\0'; j++) {
				switch (temp->map[i][j]) {
				case'@':
					temp->x = i;
					temp->y = j;
					break;
				case'X':
				case'Q':
					temp->aimx[temp->aim_count] = j;
					temp->aimy[temp->aim_count] = i;
					temp->aim_count++;
					break;
				}
			}
			if (temp->map[i][1] == '|') {
				temp->map[i][1] = '=';
				temp->h = i + 1;
				break;
			}
		}
		fclose(fp);
		return temp;
	}