#include <conio.h>
#include <graphics.h>
#include <time.h>
#define Number 9	  //�궨�巽���޸���Ҫ����	
#define Radius 20

//����С��ṹ��
struct Ball
{	int x,y;
	int xv,yv;
	int distance[2];		//��¼ĳ��С��������������С��ľ��룬�Լ����С����±�
};

int main()
{
	Ball balls[Number];     //���ýṹ�崦����������� 
	int i, j;

	//��ʼ������С��λ�ú��ٶ�
	srand((unsigned)time(NULL));             //�������������
	for (i = 0; i < Number; i++)
	{
		balls[i].x = rand() % 600 + Radius;
		balls[i].y = rand() % 380 + Radius;
		for (int j = 0; j < Number; j++)     //ʹ��ʼС�������ص�
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
		//����С��
		setcolor(RGB(218,180,119));
		setfillcolor(GREEN);
		for (int i = 0; i < Number; i++)
			fillcircle(balls[i].x, balls[i].y, Radius);

		// �������С������֮��ľ���ƽ��
		for (i = 0; i < Number; i++)
		{
			for (j = 0; j < Number; j++)
			{
				if (i != j) // �Լ����Լ�����Ҫ��
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


		// ��ײ����
		for (i = 0; i < Number; i++)
		{
			if (balls[i].distance[0] <= 4 * (Radius * Radius))    //�������м���
			{
				j = balls[i].distance[1];
				// �����ٶ�             
				int temp;
				temp = balls[i].xv; balls[i].xv = balls[j].xv; balls[j].xv = temp;
				temp = balls[i].yv; balls[i].yv = balls[j].yv; balls[j].yv = temp;

				balls[j].distance[0] = 99999999; // ���⽻�������ٶȣ�������С�����¸�ֵ
				balls[j].distance[1] = -1;

				balls[i].distance[0] = 99999999;
				balls[i].distance[1] = -1;
			}
		}

		Sleep(5);
		FlushBatchDraw();

		setcolor(BLACK);
		setfillcolor(BLACK);
		//�ı�����С�����겢����
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
