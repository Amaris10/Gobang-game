#include "Message.h"
#include <Commdlg.h>
extern HINSTANCE hInst;
extern int WindowWide;
extern int WindowHigh;
 GoBang *gobang;

Message::Message()
{
}
Message::~Message()
{
}
bool Message::WindowCreate( HWND hWnd)
{
	gobang = new GoBang(hWnd);
	return false;
}
bool Message::Paint(HWND hWnd, HDC hdc)
{
	HDC hLoadBmpDC = CreateCompatibleDC(hdc);
	HBITMAP hBmp = CreateCompatibleBitmap(hdc, WindowWide, WindowHigh);
	SelectObject(hLoadBmpDC, hBmp);
	DeleteObject(hBmp);

	gobang->Show(hLoadBmpDC);

	BitBlt(hdc, 0, 0, WindowWide, WindowHigh, hLoadBmpDC, 0, 0, SRCCOPY);
	DeleteDC(hLoadBmpDC);
	ReleaseDC(hWnd,hdc);
	return false;
}
void Message::playerMove(HWND hWnd, LPARAM lParam)
{
	gobang->Move(hWnd, lParam);
	SendMessage(hWnd, WM_ERASEBKGND, 0, 0);
	return;
}
void Message::option(HWND hWnd, LPARAM lParam)
{
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_OPTION), hWnd, OptionProc);
	SendMessage(hWnd, WM_ERASEBKGND, 0, 0);
}
void  Message::save()
{
	
	OPENFILENAME ofn;
	TCHAR szFileName[MAX_PATH] = { 0 };
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = (LPCWSTR)L"Chess Files (*.chess)\0*.chess\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = (LPWSTR)szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = (LPCWSTR)L"txt";
	int ret = GetSaveFileName(&ofn);

	gobang->Save(szFileName);
}
void Message::open()
{

	OPENFILENAME ofn;
	TCHAR szFileName[MAX_PATH] = { 0 };
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = sizeof(szFileName);
	ofn.lpstrFilter = L"Chess Files (*.chess)\0*.chess\0All Files (*.*)\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	int ret = GetOpenFileName(&ofn);

	gobang->Open(szFileName);
	
}