#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>

// ���� Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

#define High 700  // ��Ϸ����ߴ�
#define Width 500

IMAGE img_bg;//���屳��ͼƬ
IMAGE img_planeNormal1,img_planeNormal2; // �����ɻ�ͼƬ
IMAGE img_planeExplode1,img_planeExplode2; // ��ը�ɻ�ͼƬ
IMAGE img_bullet1,img_bullet2; // �ӵ�ͼƬ
IMAGE img_enemyPlane1,img_enemyPlane2; // �л�ͼƬ

float position_x,position_y; // �ɻ�λ��
float bullet_x,bullet_y; // �ӵ�λ��
float enemy_x,enemy_y; // �л�λ��

int isExpolde = 0; // �ɻ��Ƿ�ը
int score = 0; // �÷�
int life =6;//����
int regin=1;//���Ʒۻ���ը�����¿�ʼ
void startup()
{
	mciSendString("open C:\\imagegame\\game_music.mp3 alias bkmusic", NULL, 0, NULL);//�򿪱�������
	mciSendString("play bkmusic repeat", NULL, 0, NULL);  // ѭ������
	initgraph(Width,High);
	loadimage(&img_bg, "C:\\imagegame\\bg.jpg");

	loadimage(&img_planeNormal1, "C:\\imagegame\\planeNormal_1.jpg");
	loadimage(&img_planeNormal2, "C:\\imagegame\\planeNormal_2.jpg");

	loadimage(&img_bullet1, "C:\\imagegame\\bullet1.jpg");
	loadimage(&img_bullet2, "C:\\imagegame\\bullet2.jpg");

	loadimage(&img_enemyPlane1, "C:\\imagegame\\enemyPlane1.jpg");
	loadimage(&img_enemyPlane2, "C:\\imagegame\\enemyPlane2.jpg");

	loadimage(&img_planeExplode1, "C:\\imagegame\\planeExplode_1.jpg");
	loadimage(&img_planeExplode2, "C:\\imagegame\\planeExplode_2.jpg");
	
	

	position_x = Width*0.5;
	position_y = High*0.7;

	bullet_x = position_x;
	bullet_y = -85;

	enemy_x = Width*0.5;
	enemy_y = 10;	
	
	BeginBatchDraw();

}

void show()
{
	putimage(0, 0, &img_bg);	// ��ʾ����	
	if (isExpolde==0)
	{
	
	
	putimage(position_x-50, position_y-60, &img_planeNormal1,NOTSRCERASE); // ��ʾ�����ɻ�	
	putimage(position_x-50, position_y-60, &img_planeNormal2,SRCINVERT);

	putimage(bullet_x-7, bullet_y, &img_bullet1,NOTSRCERASE); // ��ʾ�ӵ�	
	putimage(bullet_x-7, bullet_y, &img_bullet2,SRCINVERT);

	putimage(enemy_x, enemy_y, &img_enemyPlane1,NOTSRCERASE); // ��ʾ�л�	
	putimage(enemy_x, enemy_y, &img_enemyPlane2,SRCINVERT);
	}
	
   else
	{
	putimage(position_x-50, position_y-60, &img_planeExplode1,NOTSRCERASE); // ��ʾ��ը�ɻ�	
	putimage(position_x-50, position_y-60, &img_planeExplode2,SRCINVERT);
	
	}
	outtextxy(Width*0.25, High*0.95, "�÷֣�");
	char s[5];
	sprintf(s, "%d", score);
	outtextxy(Width*0.3, High*0.95, s);

	outtextxy(Width*0.65, High*0.95, "������");
	char l[5];
	sprintf(l, "%d", life/2);
	outtextxy(Width*0.7, High*0.95, l);
	FlushBatchDraw();
	Sleep(2);

}

void updateWithoutInput()
{
	if(bullet_y>-50)
	bullet_y =bullet_y-2;//�ӵ�����

	if(enemy_y<High)
		enemy_y =enemy_y +0.5;
	else 
	{
		enemy_x =rand()%Width*0.5;
		enemy_y=0;
	
	}
	if (abs(bullet_x-enemy_x)+abs(bullet_y-enemy_y) < 100)  // �ӵ����ел�
		{
			enemy_x = rand()%Width;
			enemy_y = -40;
			bullet_y = -100;
			mciSendString("close gemusic", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString("open C:\\imagegame\\gotEnemy.mp3 alias gemusic", NULL, 0, NULL); // ������
			mciSendString("play gemusic", NULL, 0, NULL); // ������һ��
			score++;
			if (score>0 && score%5==0 && score%2!=0)
			{
				mciSendString("close 5music", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
				mciSendString("open C:\\imagegame\\5.mp3 alias 5music", NULL, 0, NULL); // ������
				mciSendString("play 5music", NULL, 0, NULL); // ������һ��
			}
			if (score%10==0)
			{
				mciSendString("close 10music", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
				mciSendString("open C:\\imagegame\\10.mp3 alias 10music", NULL, 0, NULL); // ������
				mciSendString("play 10music", NULL, 0, NULL); // ������һ��
			}
		}
	
	if (abs(position_x-enemy_x)+abs(position_y-enemy_y) ==150)  // �л���������
		{
			life=life-1;
		
		
		
			isExpolde = 0;

			if(life<=0)
			{
			life=0;
			isExpolde = 1;
			mciSendString("close exmusic", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString("open C:\\imagegame\\explode.mp3 alias exmusic", NULL, 0, NULL); // ������
			mciSendString("play exmusic", NULL, 0, NULL); // ������һ��	

			}
		}
		/*	isExpolde = 1;
			mciSendString("close exmusic", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString("open C:\\imagegame\\explode.mp3 alias exmusic", NULL, 0, NULL); // ������
			mciSendString("play exmusic", NULL, 0, NULL); // ������һ��	
	
	if (enemy_y>600)//������ʧ��δ������
		{
			isExpolde = 1;
			mciSendString("close exmusic", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString("open C:\\imagegame\\explode.mp3 alias exmusic", NULL, 0, NULL); // ������
			mciSendString("play exmusic", NULL, 0, NULL); // ������һ��	
			system("pause");
			
			
		}*/
}

void updateWithInput()
{
	if(isExpolde==0)
	{
			MOUSEMSG m;		// ���������Ϣ
		while (MouseHit())  //����������ڼ�⵱ǰ�Ƿ��������Ϣ
		{
			m = GetMouseMsg();
			if(m.uMsg == WM_MOUSEMOVE)
			{
				// �ɻ���λ�õ���������ڵ�λ��
				position_x = m.x;
				position_y = m.y;			
			}
			else if(m.uMsg==WM_LBUTTONDOWN)//����������ʱ
			{
				bullet_x=position_x;
				bullet_y=position_y-85;
				mciSendString("close fgmusic", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
				mciSendString("open C:\\imagegame\\f_gun.mp3 alias fgmusic", NULL, 0, NULL); // ������
				mciSendString("play fgmusic", NULL, 0, NULL); // ������һ��
			
			}
		}
	}
	char input;
	if(kbhit())  // �ж��Ƿ�������
	{
		input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
		if (input == ' ')   
		system("pause"); // λ������
	
	}

}

void gameover()
{

	EndBatchDraw();
	getch();
	closegraph();
	
}

int main()
{
	startup();  // ���ݳ�ʼ��	
	while (1)  //  ��Ϸѭ��ִ��
	{
		show();  // ��ʾ����
		updateWithoutInput();  // ���û������޹صĸ���
		updateWithInput();     // ���û������йصĸ���
	}
	gameover();     // ��Ϸ��������������
	return 0;

}
