#include"founction.h"

#define Win_L 1000
#define Win_H 600

int main(void)
{
	ege::setinitmode(ege::INIT_ANIMATION);
	ege::initgraph(Win_L, Win_H);
	setcaption("ÍÆÏä×Ó2.0"); 
	ege::randomize();
	mainloop();
	ege::closegraph();
	return 0;
}