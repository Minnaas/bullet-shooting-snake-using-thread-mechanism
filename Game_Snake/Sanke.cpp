#include"myliv.h"
#include<iostream>
#include<string>
using namespace std;
int Length = 4;
int X_coordinates[200] = {0};
int Y_coordinates[200] = { 0 };
int X_Dan = 0;
int Y_Dan = 0;
int X=55;
int Y = 8;
int x_hat = 63;
int y_hat = 8;
int Score = 0;
int Speed = 100;
bool Temp[150][50];
mutex a;
void Score_Output()
{
	a.lock();
	textcolor(100);
	gotoXY(60, 4);
	SetColor(7);
	cout << "Diem: " << Score;
	a.unlock();
}
void ThanhSang(int x,int y,int w,int h,int b_color,string ndung)
{
	textcolor(b_color);
	for (int iy = y + 1; iy <= y + h - 1; iy++)
	{
		for (int ix = x + 1; ix <= x + w - 1; ix++)
		{
			gotoXY(ix, iy); cout << " ";
		}
	}
	gotoXY(x + 1, y + 1);
	SetColor(5);
	cout << ndung;
}
void box(int x, int y, int w, int h, int t_color, int b_color, string nd)
{
	textcolor(b_color);
	for (int iy = y + 1; iy <= y + h - 1; iy++)
	{
		for (int ix = x + 1; ix <= x + w - 1; ix++)
		{
			gotoXY(ix, iy); cout << " ";
		}
	}
	SetColor(7);
	gotoXY(x + 1, y + 1);
	cout << nd;
	//============= ve vien =============
	textcolor(1);
	SetColor(t_color);//update
	if (h <= 1 || w <= 1)return;
	for (int ix = x; ix <= x + w; ix++)
	{
		gotoXY(ix, y);
		cout << char(196);
		gotoXY(ix, y + h);
		cout << char(196);
	}
	for (int iy = y; iy <= y + h; iy++)
	{
		gotoXY(x, iy);
		cout << char(179);
		gotoXY(x + w, iy);
		cout << char(179);
	}
	gotoXY(x, y); cout << char(218);
	gotoXY(x + w, y); cout << char(191);
	gotoXY(x, y + h); cout << char(192);
	gotoXY(x + w, y + h); cout << char(217);

}
void n_box(int x, int y, int w, int h, int t_color, int b_color, string nd, int sl)
{
	for (int i = 0; i < sl; i++)
	{
		box(x, y + (i * 2), w, h, t_color, b_color, nd);//i = 0 => x,y, i = 1: x,y+2
		if (i != 0)
		{
			gotoXY(x, y + (i * 2)); cout << char(195);
			gotoXY(x + w, y + (i * 2)); cout << char(180);
		}
	}
}
void thanh_sang(int x, int y, int w, int h,int t_color, int b_color, string nd)
	{
		textcolor(b_color);
		for (int iy = y + 1; iy <= y + h - 1; iy++)
		{
			for (int ix = x + 1; ix <= x + w - 1; ix++)
			{
				gotoXY(ix, iy); cout << " ";
			}
		}
		SetColor(t_color);
		gotoXY(x + 1, y + 1);
		cout << nd;
	}
void menu()
	{
		ShowCur(0);
		//----- setting ----
		int w = 20;
		int h = 2;
		int t_color = 11;
		int b_color = 1;
		int b_color_sang = 75;
		string nd = "hello";
		int sl = 4;
		n_box(X, Y, w, h, t_color, b_color, nd, sl);
		//-------------
		int xp = X; int yp = Y;//tọa độ thanh sáng
		int xcu = xp; int ycu = yp;
		bool kt = true;
		//thanh_sang(xp, yp, w, h, t_color, b_color_sang, nd);
		while (true)
		{
			if (kt == true) {
		
				thanh_sang(xcu, ycu, w, h, t_color, b_color, nd);//rs thanh sang cu
				xcu = xp;
				ycu = yp;
				thanh_sang(xp, yp, w, h, t_color, b_color_sang, nd);
				kt = false;
			}
			if (_kbhit())
			{
				char c = _getch();
				if (c == -32)
				{
					kt = true;// đã bấm
					c = _getch();
					if (c == 72)
					{
						if (yp != Y )yp -= 2;
					}
					else if (c == 80)
					{
						if (yp != Y + h * (sl - 1))yp += 2;
					}
				}
			}
	
			//---- speed ----
		}
	}
bool GameOver()
{
	if(X<=x_Fall||X>=x_Fall+WIDTH||Y==y_fall||Y==y_fall+HEIGHT)
		return true;
	return false;
}
void Init()
{
	int X_Init = X;
	int Y_Init = Y;
	for (int i = 0; i < Length; i++)
	{
		Temp[X_Init][Y_Init] = true;
		X_coordinates[i] = X_Init--;
		Y_coordinates[i] = Y_Init;
		
	}
}
void generateFood()
{
	while (true)
	{
		x_hat = rand() % (WIDTH - 2) + x_Fall + 1;
		y_hat = rand() % (HEIGHT - 2) + y_fall + 1;
		bool kt = false;
		for (int i = 0; i > Length; i++)
		{
			if (X_coordinates[i] == x_hat && Y_coordinates[i] == y_hat)
			{
				kt = true;
				break;
			}
		}
		if (kt == false)
			break;
	}
	
}
void DrawingFood()
{
	textcolor(120);
	gotoXY(x_hat, y_hat);
	cout << "$";
}
void OutPut_Dn(int x_cu,int y_cu)
{
	a.lock();
	textcolor(1);
	gotoXY(x_cu, y_cu);
	cout << " ";
	gotoXY(X_Dan, Y_Dan);
	SetColor(17);
	cout << "*";
	a.unlock();
}
void Banan(int Direction)
{
	
	int c = 1;
	int x_cu = -1;
	int y_cu = -1;
	if (Direction == 0)
	{
		X_Dan = X;
		Y_Dan = Y -4;
	}
	else if (Direction==1)
	{
		X_Dan = X;
		Y_Dan = Y+4;
	}
	else if (Direction == 2)
	{
		X_Dan = X+4;
		Y_Dan = Y ;
	}
	else if (Direction == 3)
	{
		X_Dan = X-4;
		Y_Dan = Y;
	}

	while (c < 20)
	{
		OutPut_Dn(x_cu,y_cu);
		x_cu = X_Dan;
		y_cu = Y_Dan;
		if (c < 19&&Y_Dan>y_fall)
		{
			if (Direction == 0)
			{
				Y_Dan = Y_Dan -1;
			}
			else if (Direction == 1)
			{
				Y_Dan = Y_Dan + 1;
			}
			else if (Direction == 2)
			{
				X_Dan = X_Dan + 2;
			}
			else if (Direction == 3)
			{
				X_Dan = X_Dan - 2;
			}
		}
		else
		{
			c = 19;
		}
		c++;
		Sleep(30);
	}
	a.lock();
	gotoXY(X_Dan, Y_Dan);
	textcolor(1);
	cout << " ";
	a.unlock();

}
void Display(int x_last,int Y_last)
{
	a.lock();
	textcolor(1);
	gotoXY(x_last, Y_last);
	cout << " ";
	textcolor(75);
	for (int i = 0; i < Length; i++)
	{
		gotoXY(X_coordinates[i], Y_coordinates[i]);
		if (i == 0)
		{
			cout << "0";
		}
		else {
			cout << "o";
		}
	}
	a.unlock();
}
void PaintingFall(int t_color)
{

	//============= ve vien =============
	textcolor(1);
	SetColor(t_color);//update
	for (int ix = x_Fall; ix <= x_Fall + WIDTH; ix++)
	{
		gotoXY(ix, y_fall);
		cout << char(196);
		gotoXY(ix, y_fall + HEIGHT);
		cout << char(196);
	}
	for (int iy = y_fall; iy <=y_fall+HEIGHT ; iy++)
	{
		gotoXY(x_Fall, iy);
		cout << char(179);
		gotoXY(x_Fall + WIDTH, iy);
		cout << char(179);
	}
	gotoXY(x_Fall, y_fall); cout << char(218);
	gotoXY(x_Fall + WIDTH, y_fall); cout << char(191);
	gotoXY(x_Fall, y_fall + HEIGHT); cout << char(192);
	gotoXY(x_Fall + WIDTH, y_fall + HEIGHT); cout << char(217);
}
void Move(int x,int y)
{
	for (int i = Length-1; i > 0; i--)
	{
		X_coordinates[i] = X_coordinates[i - 1];
		Y_coordinates[i] = Y_coordinates[i - 1];
	}
	X_coordinates[0] = x;
	Y_coordinates[0] = y;
}
bool Reach()
{
	if ((X == x_hat||X==x_hat+1||X==x_hat-1) && Y == y_hat)
		return true;
	return false;
}
void InitGame()
{
	srand(time(NULL));
	ShowCur(0);
	Init();
	PaintingFall(7);
	generateFood();
	DrawingFood();
}
void Handle_Reach()
{
	gotoXY(x_hat, y_hat);
	textcolor(1);
	cout << " ";
	generateFood();
	DrawingFood();
	Score++;
	Length++;
}
void Game()
{
	InitGame();
	int Check = 2;
	int x_cu = -1;
	int y_cu =- 1;
	while (true)
	{
		Score_Output();
		Display(x_cu,y_cu);
		if (_kbhit())
		{
			char c = _getch();
			if (c == -32)
			{
				c = _getch();
				if (c == 72&&Check!=1)
				{
					Check = 0;
				}
				else if (c == 80&&Check!=0)
				{	
					Check = 1;
				}
				else if (c == 75&&Check!=2) 
					Check = 3;
				else if (c == 77&&Check!=3)
					Check = 2;
			}
			else
			{
				thread BAnDan(Banan,Check);
				BAnDan.detach();
			}
		}
	/*	if (Temp[X][Y] == true)
			return;*/
		if (Check == 0)
		{
			Y = Y - 1;
			/*Temp[X][Y] = true;*/
		}
		else if (Check == 1)
		{
			Y = Y + 1;
	/*		Temp[X][Y] = true;*/
		}
		else if (Check == 2)
		{
			X = X + 2;
			/*Temp[X][Y] = true;*/
			/*Temp[X-1][Y] = true;*/
		}
		else if (Check == 3)
		{
			X = X - 2;
		/*	Temp[X][Y] = true;
			Temp[X +1][Y] = true;*/
		}
		x_cu = X_coordinates[Length-1];
		y_cu = Y_coordinates[Length - 1];
		if (Reach() == true)
		{
			Handle_Reach();
		}
		if (GameOver())
			break;
		Move(X,Y);
		Sleep(Speed);
	}
}

int main()
{
	SetScreenBufferSize(170, 60);
	Game();
	gotoXY(0, 0);
	textcolor(1);
} 