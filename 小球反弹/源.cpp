#include <conio.h>
#include <graphics.h>
#include <time.h>
#define Number 9	  //宏定义方便修改主要参数	
#define Radius 20

//定义小球结构体
struct Ball
{	int x,y;
	int xv,yv;
	int distance[2];		//记录某个小球与距离它最近的小球的距离，以及这个小球的下标
};

int main()
{
	Ball balls[Number];     //运用结构体处理数组更方便 
	int i, j;

	//初始化所有小球位置和速度
	srand((unsigned)time(NULL));             //生成随机数种子
	for (i = 0; i < Number; i++)
	{
		balls[i].x = rand() % 600 + Radius;
		balls[i].y = rand() % 380 + Radius;
		for (int j = 0; j < Number; j++)     //使起始小球不容易重叠
			if (i != j)		
			{
				if ((balls[i].x>= balls[j].x - Radius) && (balls[i].x <= balls[j].x + Radius) &&
					(balls[i].y >= balls[j].y - Radius) && (balls[i].y <= balls[j].y + Radius))
				{
					balls[i].x = rand() % 600 + Radius;
					balls[i].y = rand() % 380 + Radius;
				}
			}
		balls[i].xv = 1;
		balls[i].yv = 1;
	}

	for (i = 0; i < Number; i++)
	{
		balls[i].distance[0] = 99999999;
		balls[i].distance[1] = -1;
	}

	initgraph(640, 480);
	
	BeginBatchDraw();
	while (1)
	{
		//绘制小球
		setcolor(RGB(218,180,119));
		setfillcolor(GREEN);
		for (int i = 0; i < Number; i++)
			fillcircle(balls[i].x, balls[i].y, Radius);

		// 求解所有小球两两之间的距离平方
		for (i = 0; i < Number; i++)
		{
			for (j = 0; j < Number; j++)
			{
				if (i != j) // 自己和自己不需要比
				{
					int dist2;
					dist2 = (balls[i].x - balls[j].x) * (balls[i].x - balls[j].x) + (balls[i].y - balls[j].y) * (balls[i].y - balls[j].y);
					if (dist2 < balls[i].distance[0])
					{
						balls[i].distance[0] = dist2;
						balls[i].distance[1] = j;
					}
				}
			}
		}		


		// 碰撞反弹
		for (i = 0; i < Number; i++)
		{
			if (balls[i].distance[0] <= 4 * (Radius * Radius))    //两球相切极限
			{
				j = balls[i].distance[1];
				// 交换速度             
				int temp;
				temp = balls[i].xv; balls[i].xv = balls[j].xv; balls[j].xv = temp;
				temp = balls[i].yv; balls[i].yv = balls[j].yv; balls[j].yv = temp;

				balls[j].distance[0] = 99999999; // 避免交换两次速度，将两个小球重新赋值
				balls[j].distance[1] = -1;

				balls[i].distance[0] = 99999999;
				balls[i].distance[1] = -1;
			}
		}

		Sleep(5);
		FlushBatchDraw();

		setcolor(BLACK);
		setfillcolor(BLACK);
		//改变所有小球坐标并绘制
		for (i = 0; i < Number; i++)
		{
			fillcircle(balls[i].x, balls[i].y, Radius);
			balls[i].x = balls[i].x + balls[i].xv;
			balls[i].y = balls[i].y + balls[i].yv;
			if (balls[i].x <= Radius || balls[i].x >= 620)
				balls[i].xv = -balls[i].xv;
			if (balls[i].y <= Radius || balls[i].y >= 400)
				balls[i].yv = -balls[i].yv;
		}
	}
	FlushBatchDraw();
	closegraph();

	return 0;
}
