#include <graphics.h>
#include <conio.h>
int main() {
	COLORREF colors[] = { RED,YELLOW,GREEN,BLUE,CYAN,MAGENTA,WHITE};    
	
	char c = '\0';
	int index = 0;

	initgraph(300, 300);
	setbkcolor(BLACK);
	cleardevice();                     //用当前背景色清空绘图设备

	while (c == '\0') {
		setlinecolor(colors[index]);
		circle(150, 150, 100);
		Sleep(200);                   //函数滞留0.2s
		if (_kbhit()) {               //检测键盘，任意键退出
			c = _getch();
		}
		else {
			index++;
			index %= 7;
		}
	}
	return 0;
}