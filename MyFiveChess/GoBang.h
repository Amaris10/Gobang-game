#pragma once
#include "framework.h"
#include "MyFiveChess.h"
#include <iostream>
#include <fstream>
using namespace std;

#define WHITE	1
#define BLACK	2
#define MAP_WIDE	15
#define MAP_HIGH	15
#define EDGE_WIDE	10
#define EDGE_HIGH	10
#define CHESSBOX_RECT_WIDE	35
#define CHESSBOX_RECT_HIGH	35

int CALLBACK StartProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

struct Record
{
	POINT position;
	int Connected_chess;//连子数
	Record() { Connected_chess = 0; }
	Record(const Record& r)
	{
		position.x = r.position.x;
		position.y = r.position.y;
		Connected_chess = r.Connected_chess;
	}
	Record operator=(const Record tr)
	{
		position.x = tr.position.x;
		position.y = tr.position.y;
		Connected_chess = tr.Connected_chess;
		return *this;
	}

};

class GoBang
{
	HDC BlackHDC;//黑棋子dc
	HDC WhiteHDC;//白棋子dc
	HDC ChessBoxHDC;//棋盘dc

	int RConnected_chess;//记录了多少连即胜利
	
	int FileCount;
	int x[225];
	int y[225];
	int ChessBoxWide;
	int ChessBoxHigh;

	int Count_Black;//113
	int Count_White;//112

	int Map[MAP_HIGH][MAP_WIDE];//棋盘数组
	int MapCount;
	
	int Later;//下子人
	Record r;

	TCHAR filename;
	TCHAR File[MAXBYTE];//该变量不为空则将存档保存到此文件
	
	enum Direction {
		UP,
		LEFT,
		LEFT_UP,
		RIGHT_UP,
		LEFT_DOWN,
		RIGHT_DOWN,
		RIGHT,
		DOWN,
	};


public:
	int state;
	friend class Message;
	GoBang(HWND hWnd);
	~GoBang();
	BOOL init();
	BOOL Show(HDC hdc);
	BOOL Move(HWND hWnd, LPARAM lParam);
	BOOL Jugde();
	bool Search( Direction dir);
	bool retract(HWND hWnd,HDC hdc);
	bool Save(TCHAR* filename);
	bool Open(TCHAR* filename);

};

