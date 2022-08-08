#include <conio.h>
#include <graphics.h>
#include<stdio.h>
#define High 480
#define Width 640
#define Num 10

//球和板相关定义
int ball_x, ball_y;
int ball_vx, ball_vy;
int radius;
int bar_x, bar_y;
int bar_high, bar_width;
int bar_left, bar_right, bar_top, bar_bottom;

int isBrickExisted[Num];            // 每个砖块是否存在，1为存在，0为没有
int brick_high, brick_width;        //每个砖块的高度和宽度


void startup() {	           //数据和窗口初始化
	ball_x = Width / 2;
	ball_y = High / 2;
	ball_vx = 1;
	ball_vy = 1;
	radius = 20;

	bar_high = High / 20;
	bar_width = Width / 3;
	bar_x = Width / 2;
	bar_y = High - bar_high / 2;
	bar_left = bar_x - bar_width / 2;
	bar_right = bar_x + bar_width / 2;
	bar_top = bar_y - bar_high / 2;
	bar_bottom = bar_y + bar_high / 2;

	brick_width = Width / Num;
	brick_high = High / Num;

	int i;
	for (i = 0; i < Num; i++)
		isBrickExisted[i] = 1;
	initgraph(Width, High);
	BeginBatchDraw();
}

void clean() {                   //消除画面
	setcolor(BLACK);             //绘制黑线、黑色填充的圆
	setfillcolor(BLACK);
	fillcircle(ball_x, ball_y, radius);
	bar(bar_left, bar_top, bar_right, bar_bottom);

	int i, brick_left, brick_right, brick_top, brick_bottom;
	for (i = 0; i < Num; i++) {
		brick_left = i * brick_width;
		brick_right = brick_left + brick_width;
		brick_top = 0;
		brick_bottom = brick_high;
		if (!isBrickExisted[i])         //刷新坐标若不存在绘制黑色
			fillrectangle(brick_left, brick_top, brick_right, brick_bottom);
	}
}
	
	void show() {		// 显示画面
		setcolor(RGB(0,122,204));		       // 绘制彩色的圆和挡板
		setfillcolor(RGB(0, 122, 204));
		fillcircle(ball_x, ball_y, radius);
		bar(bar_left, bar_top, bar_right, bar_bottom);

		int i, brick_left, brick_right, brick_top, brick_bottom;
		for (i = 0; i < Num; i++) {
			brick_left = i * brick_width;
			brick_right = brick_left + brick_width;
			brick_top = 0;
			brick_bottom = brick_high;
			if (isBrickExisted[i]) {				//砖块存在，绘制砖划
				setcolor(WHITE);
				setfillcolor(RGB(174,105,50));
				fillrectangle(brick_left, brick_top, brick_right, brick_bottom);
				//绘制砖块
			}
		}
		FlushBatchDraw();
		Sleep(3);
	}

	void updateWithoutInput() {		//球和砖块的更新
		// 挡板和小球碰撞，小球反弹
		if (((ball_y + radius >= bar_top) && (ball_y + radius < bar_bottom - bar_high / 3))
			|| ((ball_y - radius <= bar_bottom) && (ball_y - radius > bar_top - bar_high / 3)))
			if ((ball_x >= bar_left) && (ball_x <= bar_right))
				ball_vy = -ball_vy;
		
		//更新小球的坐标
		ball_x = ball_x + ball_vx;
		ball_y = ball_y + ball_vy;

		// 小球和边界碰撞
		if ((ball_x == radius) || (ball_x == Width - radius))
			ball_vx = -ball_vx;
		if ((ball_y == radius) || (ball_y == High - radius))
			ball_vy = -ball_vy;
		
		//判断小球是否和某个砖块碰撞
		int i, brick_left, brick_right, brick_bottom;
		for (i = 0; i < Num; i++) {
			if (isBrickExisted[i]) {
				//砖块存在才判断
				brick_left = i * brick_width;
				brick_right = brick_left + brick_width;
				brick_bottom = brick_high;
				if ((ball_y == brick_bottom + radius) && (ball_x >= brick_left) && (ball_x <=
					brick_right))
				{
					isBrickExisted[i] = 0;
					ball_vy = -ball_vy;
				}
			}
		}
	}

	//挡板操作
	void Bar()
	{
		if (_kbhit()) {                   //判断是否有键盘输入
			char input = _getch();        //获取按键信实施操作
			switch (input) {
			case 75:
			case 'a':
			case 'A':
				if (bar_left > 0) {
					bar_x = bar_x - 15;
					bar_left = bar_x - bar_width / 2;
					bar_right = bar_x + bar_width / 2;
				}break;

			case 77:
			case 'd':
			case 'D':
				if (bar_right < Width) {
					bar_x = bar_x + 15;
					bar_left = bar_x - bar_width / 2;
					bar_right = bar_x + bar_width / 2;
				}break;
			
			}
		}
	}

	int main() {
		startup();
		while (1) {
			clean();
			updateWithoutInput();
			Bar();
			show();
		}
		EndBatchDraw();
		closegraph();
		return 0;
	}