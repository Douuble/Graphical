#include <graphics.h>
#include <conio.h>
#include <math.h>
#define Length 640
#define Width 480
#define PI 3.14
int main(){
    initgraph(640, 480);

/*����ָ��λ��*/
    int center_x = Length / 2, center_y = Width / 2;
    int secondEnd_x, secondEnd_y;
    int minuteEnd_x, minuteEnd_y;
    int hourEnd_x, hourEnd_y;
    
/*����ָ�볤��*/
    int secondLength = Length / 5;
    int minuteLength = Length / 6;
    int hourLength = Length / 7;

    //�����Ӧת���Ƕ�
    float secondAngle = 0;
    //�����Ӧת���Ƕ�
    float minuteAngle = 0;
    //ʱ���Ӧת���Ƕ�
    float hourAngle = 0;

    SYSTEMTIME ti;                //��������洢ϵͳʱ��

    BeginBatchDraw();             //������ͼ��������˸

    while (1)
    {   
        /*���Ʊ���*/
        setfillcolor(LIGHTBLUE);
        setlinestyle(PS_DASHDOTDOT, 5);
        setlinecolor(WHITE);
        circle(center_x, center_y, secondLength + 30);
        setlinestyle(PS_DOT | PS_ENDCAP_SQUARE, 2);
        circle(center_x, center_y, secondLength + 15);

        for (int i = 0; i < 12; i++)
        {
            int x = center_x + cos(i * 30.0 / 360 * 2 * PI) * (secondLength + 15.0);
            int y = center_y - sin(i * 30.0 / 360 * 2 * PI) * (secondLength + 15.0);
            fillcircle(x, y, 5);
        }

        GetLocalTime(&ti);        //��ȡ��ǰʱ��

        /*ָ��ת���ĽǶȺ�λ��*/
        secondAngle = (ti.wSecond / 60.0) * (2 * PI);
        minuteAngle = (ti.wMinute / 60.0) * (2 * PI);
        hourAngle = ((ti.wHour % 12) / 12.0) * (2 * PI) + (ti.wMinute / 60.0) * (2 * PI / 12.0);
        secondEnd_x = center_x + secondLength * sin(secondAngle);
        secondEnd_y = center_y - secondLength * cos(secondAngle);
        minuteEnd_x = center_x + minuteLength * sin(minuteAngle);
        minuteEnd_y = center_y - minuteLength * cos(minuteAngle);
        hourEnd_x = center_x + hourLength * sin(hourAngle);
        hourEnd_y = center_y - hourLength * cos(hourAngle);
        
        /*��ָ��*/
        setlinestyle(PS_SOLID, 1);
        setcolor(WHITE);
        line(center_x, center_y, secondEnd_x, secondEnd_y);
        setlinestyle(PS_SOLID, 2);
        setcolor(LIGHTGREEN);
        line(center_x, center_y, minuteEnd_x, minuteEnd_y);
        setlinestyle(PS_SOLID, 5);
        setcolor(LIGHTRED);
        line(center_x, center_y, hourEnd_x, hourEnd_y);

        FlushBatchDraw();           //�����������ƣ���ʾͼ��������Ƶ��
        cleardevice();              //�õ�ǰ����ɫ��ջ�ͼ�豸
    }
    closegraph();
    return 0;
}
