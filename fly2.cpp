#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>

// 引用 Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

#define High 700  // 游戏画面尺寸
#define Width 500

IMAGE img_bg;//定义背景图片
IMAGE img_planeNormal1,img_planeNormal2; // 正常飞机图片
IMAGE img_planeExplode1,img_planeExplode2; // 爆炸飞机图片
IMAGE img_bullet1,img_bullet2; // 子弹图片
IMAGE img_enemyPlane1,img_enemyPlane2; // 敌机图片

float position_x,position_y; // 飞机位置
float bullet_x,bullet_y; // 子弹位置
float enemy_x,enemy_y; // 敌机位置

int isExpolde = 0; // 飞机是否爆炸
int score = 0; // 得分
int life =6;//生命
int regin=1;//控制粉机爆炸后重新开始
void startup()
{
	mciSendString("open C:\\imagegame\\game_music.mp3 alias bkmusic", NULL, 0, NULL);//打开背景音乐
	mciSendString("play bkmusic repeat", NULL, 0, NULL);  // 循环播放
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
	putimage(0, 0, &img_bg);	// 显示背景	
	if (isExpolde==0)
	{
	
	
	putimage(position_x-50, position_y-60, &img_planeNormal1,NOTSRCERASE); // 显示正常飞机	
	putimage(position_x-50, position_y-60, &img_planeNormal2,SRCINVERT);

	putimage(bullet_x-7, bullet_y, &img_bullet1,NOTSRCERASE); // 显示子弹	
	putimage(bullet_x-7, bullet_y, &img_bullet2,SRCINVERT);

	putimage(enemy_x, enemy_y, &img_enemyPlane1,NOTSRCERASE); // 显示敌机	
	putimage(enemy_x, enemy_y, &img_enemyPlane2,SRCINVERT);
	}
	
   else
	{
	putimage(position_x-50, position_y-60, &img_planeExplode1,NOTSRCERASE); // 显示爆炸飞机	
	putimage(position_x-50, position_y-60, &img_planeExplode2,SRCINVERT);
	
	}
	outtextxy(Width*0.25, High*0.95, "得分：");
	char s[5];
	sprintf(s, "%d", score);
	outtextxy(Width*0.3, High*0.95, s);

	outtextxy(Width*0.65, High*0.95, "生命：");
	char l[5];
	sprintf(l, "%d", life/2);
	outtextxy(Width*0.7, High*0.95, l);
	FlushBatchDraw();
	Sleep(2);

}

void updateWithoutInput()
{
	if(bullet_y>-50)
	bullet_y =bullet_y-2;//子弹上移

	if(enemy_y<High)
		enemy_y =enemy_y +0.5;
	else 
	{
		enemy_x =rand()%Width*0.5;
		enemy_y=0;
	
	}
	if (abs(bullet_x-enemy_x)+abs(bullet_y-enemy_y) < 100)  // 子弹击中敌机
		{
			enemy_x = rand()%Width;
			enemy_y = -40;
			bullet_y = -100;
			mciSendString("close gemusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open C:\\imagegame\\gotEnemy.mp3 alias gemusic", NULL, 0, NULL); // 打开音乐
			mciSendString("play gemusic", NULL, 0, NULL); // 仅播放一次
			score++;
			if (score>0 && score%5==0 && score%2!=0)
			{
				mciSendString("close 5music", NULL, 0, NULL); // 先把前面一次的音乐关闭
				mciSendString("open C:\\imagegame\\5.mp3 alias 5music", NULL, 0, NULL); // 打开音乐
				mciSendString("play 5music", NULL, 0, NULL); // 仅播放一次
			}
			if (score%10==0)
			{
				mciSendString("close 10music", NULL, 0, NULL); // 先把前面一次的音乐关闭
				mciSendString("open C:\\imagegame\\10.mp3 alias 10music", NULL, 0, NULL); // 打开音乐
				mciSendString("play 10music", NULL, 0, NULL); // 仅播放一次
			}
		}
	
	if (abs(position_x-enemy_x)+abs(position_y-enemy_y) ==150)  // 敌机击中我们
		{
			life=life-1;
		
		
		
			isExpolde = 0;

			if(life<=0)
			{
			life=0;
			isExpolde = 1;
			mciSendString("close exmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open C:\\imagegame\\explode.mp3 alias exmusic", NULL, 0, NULL); // 打开音乐
			mciSendString("play exmusic", NULL, 0, NULL); // 仅播放一次	

			}
		}
		/*	isExpolde = 1;
			mciSendString("close exmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open C:\\imagegame\\explode.mp3 alias exmusic", NULL, 0, NULL); // 打开音乐
			mciSendString("play exmusic", NULL, 0, NULL); // 仅播放一次	
	
	if (enemy_y>600)//敌人消失仍未被击中
		{
			isExpolde = 1;
			mciSendString("close exmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open C:\\imagegame\\explode.mp3 alias exmusic", NULL, 0, NULL); // 打开音乐
			mciSendString("play exmusic", NULL, 0, NULL); // 仅播放一次	
			system("pause");
			
			
		}*/
}

void updateWithInput()
{
	if(isExpolde==0)
	{
			MOUSEMSG m;		// 定义鼠标消息
		while (MouseHit())  //这个函数用于检测当前是否有鼠标消息
		{
			m = GetMouseMsg();
			if(m.uMsg == WM_MOUSEMOVE)
			{
				// 飞机的位置等于鼠标所在的位置
				position_x = m.x;
				position_y = m.y;			
			}
			else if(m.uMsg==WM_LBUTTONDOWN)//按下鼠标左键时
			{
				bullet_x=position_x;
				bullet_y=position_y-85;
				mciSendString("close fgmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
				mciSendString("open C:\\imagegame\\f_gun.mp3 alias fgmusic", NULL, 0, NULL); // 打开音乐
				mciSendString("play fgmusic", NULL, 0, NULL); // 仅播放一次
			
			}
		}
	}
	char input;
	if(kbhit())  // 判断是否有输入
	{
		input = getch();  // 根据用户的不同输入来移动，不必输入回车
		if (input == ' ')   
		system("pause"); // 位置左移
	
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
	startup();  // 数据初始化	
	while (1)  //  游戏循环执行
	{
		show();  // 显示画面
		updateWithoutInput();  // 与用户输入无关的更新
		updateWithInput();     // 与用户输入有关的更新
	}
	gameover();     // 游戏结束、后续处理
	return 0;

}
