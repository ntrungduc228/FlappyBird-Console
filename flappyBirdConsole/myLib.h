
#pragma once
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <dos.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include<ctime>

using namespace std;

const int clblack = 0;
const int clblue = 1;
const int clgreen = 2;
const int claqua = 3;
const int clred = 4;
const int clpurple = 5;
const int clyellow = 6;
const int clwhite = 7;
const int clgray = 8;
const int cllightblue = 9;
const int cllightgreen = 10;
const int cllightaqua = 11;
const int cllightred = 12;
const int cllightpurple = 13;
const int cllightyellow = 14;
const int cllightwhite = 15;
const int maxx = 80;
const int maxy = 25;

// base function lower level

HANDLE handle;


void initlibrary(); 
void hidecursor();
void resizeConsole(SHORT width, SHORT height);
void XoaManHinh();
void SetFontApp(int x, int y);
void MaximizeWindow();
void SetConsoleColor(int textcolor, int backgroundcolor);
void gotoxy(int x, int y);
void createwindow(int tx, int ty, int dx, int dy, string tittle, int bgcolor);
void showmessage(string noidung, int mauchu, int maunen);
int messagedlg(string noidung, int mauchu, int maunen);
void setfont();


void initlibrary()
{
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
}


// Ham thay doi kich co man hinh console.
void resizeConsole(SHORT width, SHORT height)
{
	/*HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);*/

	COORD crd = { width, height };
	SMALL_RECT rec = { 0, 0, width - 1, height - 1 };
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(hConsoleOutput, TRUE, &rec);
	SetConsoleScreenBufferSize(hConsoleOutput, crd);
}

// Hàm xóa màn hình.
void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void hidecursor() // an con tro man hinh 
//http://cboard.cprogramming.com/cplusplus-programming/75074-hide-cursor.html
{
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;

	SetConsoleCursorInfo(hOut, &ConCurInf);
}

void SetFontApp(int x, int y) //dat font cho chuong trinh
//https://msdn.microsoft.com/en-us/library/windows/desktop/ms686200(v=vs.85).aspx
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = x;
	cfi.dwFontSize.Y = y;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Raster Fonts");
	//SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	SetCurrentConsoleFontEx(handle, FALSE, &cfi);
}


void clrscr(int color)//Xoa man hinh
//http://www.cplusplus.com/forum/windows/69678/
{
	//HANDLE hConsoleColor;
	//hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	color = color * 16 + 7;
	SetConsoleTextAttribute(handle, color);
	//SetConsoleTextAttribute(hConsoleColor, color);
	system("cls");
	
}

void MaximizeWindow() //chinh man hinh sang che do Maximize
//http://www.cplusplus.com/forum/general/7258/
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	SMALL_RECT rc;
	rc.Left = rc.Top = 0;
	rc.Right = (short)(min(info.dwMaximumWindowSize.X, info.dwSize.X) - 1);
	rc.Bottom = (short)(min(info.dwMaximumWindowSize.Y, info.dwSize.Y) - 1);
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &rc);
}

void SetConsoleColor(int textcolor, int backgroundcolor)
//https://www.daniweb.com/programming/software-development/code/216345/add-a-little-color-to-your-console-text
{
	int color;
	//HANDLE hConsoleColor;
	//hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	color = backgroundcolor * 16 + textcolor;
	SetConsoleTextAttribute(handle, color);
	//SetConsoleTextAttribute(hConsoleColor, color);	
}

void gotoxy(int x, int y)
//http://www.nguyenvanquan7826.com/2013/08/22/cc-gotoxy-trong-dev-c-gotoxy-in-dev-c/
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
// second level, use function from base level

void createwindow(int tx, int ty, int dx, int dy, string tittle, int bgcolor)
{
	int i, j;
	gotoxy(tx, ty);
	SetConsoleColor(cllightwhite, bgcolor);
	printf("%c", 201);
	printf("%c", 205);
	printf("%s", tittle.c_str());
	for (i = tx + 1 + strlen(tittle.c_str()) + 1; i < dx; i++)
		printf("%c", 205);
	printf("%c", 187);
	for (i = 1 + ty; i < dy; i++)
	{
		gotoxy(tx, i);
		printf("%c", 186);
		for (j = 1 + tx; j < dx; j++)
			printf(" ");
		printf("%c", 186);
	}
	gotoxy(tx, dy);
	printf("%c", 200);
	for (i = 1 + tx; i < dx; i++)
		printf("%c", 205);
	printf("%c", 188);
}

void showmessage(string noidung, int mauchu, int maunen)
{
	int msgw, msgh;
	msgw = 4 + strlen(noidung.c_str());
	msgh = 6;
	int cx = maxx / 2;
	int cy = maxy / 2 - 3;
	createwindow(cx - msgw / 2, cy - msgh / 2, cx + msgw / 2, cy + msgh / 2, "Thong bao", maunen);
	createwindow(cx - msgw / 2, cy - msgh / 2, cx + msgw / 2, cy + msgh / 2, "Thong bao", maunen);
	gotoxy(cx - msgw / 2 + 2, cy - msgh / 2 + 2);
	SetConsoleColor(mauchu, maunen);
	printf("%s", noidung.c_str());
	gotoxy(cx - msgw / 2 + 2, cy - msgh / 2 + 3);
	SetConsoleColor(cllightred, maunen);
	printf("Enter");
	do
	{
	} while (_getch() != 13);


}

int messagedlg(string noidung, int mauchu, int maunen)
{
	int msgw, msgh;
	char key, sel;
	noidung = noidung + "[C,K]";
	msgw = 4 + strlen(noidung.c_str());
	msgh = 6;
	int cx = maxx / 2;
	int cy = maxy / 2 - 3;
	createwindow(cx - msgw / 2, cy - msgh / 2, cx + msgw / 2, cy + msgh / 2, "Thong bao", maunen);
	gotoxy(cx - msgw / 2 + 2, cy - msgh / 2 + 2);
	SetConsoleColor(mauchu, maunen);
	printf("%s", noidung.c_str());
	key = ' ';
	sel = ' ';

	SetConsoleColor(cllightred, maunen);
	do
	{

		gotoxy(cx - msgw / 2 + 2, cy - msgh / 2 + 3);
		key = _getch();
		if (key == ('c') || (key == 'C') || (key == 'k') || (key == 'K'))
		{
			printf("%c", key);
			if ((key == 'c') || (key == 'C')) sel = 'C';
			else if ((key == 'k') || (key == 'K')) sel = 'K';
		}
	} while ((key != 13) && (sel != ' '));
	return sel == 'C';
}

void setfont()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 20;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Raster Font");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
