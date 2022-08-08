#include<graphics.h>
#include<conio.h>

int main() {
	initgraph(640, 480);
	setbkcolor(RGB(138,31,255));
	cleardevice();

	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE) 
		{
			putpixel(m.x, m.y, WHITE);
		}
	}
}
