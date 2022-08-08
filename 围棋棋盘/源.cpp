#include<graphics.h>
#include<conio.h>
int main()
{
	int step = 30;
	initgraph(600, 600);
	setbkcolor(YELLOW);
	cleardevice();

	setlinestyle(PS_SOLID, 2);  
	setcolor(BLACK);

	int i;                               //∆Â≈Ã
	for (i = 1; i <= 19; i++)           
	{
		line(i * step, 1 * step, i * step, 19 * step);
		line(1 * step, i * step, 19 * step, i * step);
	}

	int x ,y;                            //–«Œª
	setfillcolor(BLACK);                    
	for (x = 4* step; x <= 16 * step; x=x + 6 * step) 
		for (y = 4 * step; y <= 16 * step; y=y + 6 * step) 
			fillcircle(x, y, 5);

	_getch();
	closegraph();
	return 0;
}
