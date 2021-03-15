#pragma once
#include"framework.h"
#include"Gobang.h"
#include "MyFiveChess.h"
int CALLBACK OptionProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

class Message
{

public:
	
	Record r;
	Message();
	~Message();
	bool WindowCreate(HWND hWnd);
	bool Paint(HWND hWnd, HDC hdc);
	void playerMove(HWND hWnd, LPARAM lParam);
	void option(HWND hWnd, LPARAM lParam);
	void save();
	void open();
};

