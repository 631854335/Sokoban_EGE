#include"founction.h"

void mainloop()
{

	int level;
	int level_option;
	int scenes;
	char option;
	int isEnd;

	level = 0;
	level_option = 1;
	scenes = 0;
	isEnd = 0;

	while (is_run()) {
		switch (scenes) {
		case 0:
			main_interface1();
			break;
		case 1:
			main_interface2();
			break;
		case 2:
			selectLevel(level_option);
			break;
		default:
			break;
		}

		if (scenes < 3) {
			option = getch();
			option = tolower(option);
		}

		switch (scenes) {
		case 0:
			if (option == 's')
				scenes = 1;
			else if (option == 27) {
				isEnd = 1;
			}
			break;
		case 1:
			if (option == 'r' || option == 27)
				scenes = 0;
			else if (option == 'a') {
				scenes = 3;
			}
			else if (option == 'x') {
				scenes = 2;
			}
			break;
		case 2:
			if ((option == 'a') && level_option > 1)
				level_option--;
			else if ((option == 'd') && level_option < maps_num)
				level_option++;
			else if ((option == 13 || option == 32)) {
				level = level_option - 1;
				scenes = 4;
			}
			else if (option == 27)
				scenes = 1;
			break;
		case 3:
			level = 0;
			scenes = gameloop(level);
			break;
		case 4:
			scenes = gameloop(level);
			break;
		case 5:
			level++;
			scenes = 4;
			break;
		case 6:
			scenes = 0;
			level = 0;
			break;
		default:
			break;
		}

		if (isEnd)
			break;
	}

}

void main_interface1()
{
	PIMAGE pimg_logo = newimage();
	getimage(pimg_logo, "../../source/image\\logo.jpg", 0, 0);

	cleardevice();

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	setbkmode(TRANSPARENT);
	putimage(280, 50, pimg_logo);
	setfont(48, 0, "楷体");
	outtextxy(400, 300, "开始(S)");
	outtextxy(380, 400, "退出(ESC)");

	delimage(pimg_logo);
}

void main_interface2()
{
	PIMAGE pimg_logo = newimage();
	getimage(pimg_logo, "../../source/image\\logo.jpg", 0, 0);
	cleardevice();

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	setfont(80, 0, "楷体");

	setbkmode(TRANSPARENT);
	putimage(280, 50, pimg_logo);

	setfont(48, 0, "楷体");
	outtextxy(360, 300, "从头开始(A)");
	outtextxy(400, 350, "选关(X)");
	outtextxy(400, 400, "返回(R)");

	delimage(pimg_logo);
}

void selectLevel(int level)
{
	cleardevice();

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	setfont(48, 0, "楷体");

	setbkmode(TRANSPARENT);
	outtextxy(340, 200, "按A，D键选关");
	char str[20];
	sprintf(str, "关卡:%d", level);
	outtextxy(400, 300, str);
	outtextxy(400, 400, "返回(ESC)");
}