#include <graphics.h>
#include <conio.h>
int main() {
	COLORREF colors[] = { RED,YELLOW,GREEN,BLUE,CYAN,MAGENTA,WHITE};    
	
	char c = '\0';
	int index = 0;

	initgraph(300, 300);
	setbkcolor(BLACK);
	cleardevice();                     //�õ�ǰ����ɫ��ջ�ͼ�豸

	while (c == '\0') {
		setlinecolor(colors[index]);
		circle(150, 150, 100);
		Sleep(200);                   //��������0.2s
		if (_kbhit()) {               //�����̣�������˳�
			c = _getch();
		}
		else {
			index++;
			index %= 7;
		}
	}
	return 0;
}