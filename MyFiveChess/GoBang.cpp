
#include "GoBang.h"

extern int WindowWide;
extern int WindowHigh;
extern HINSTANCE hInst;
GoBang::~GoBang()
{

}
GoBang::GoBang(HWND hWnd)
{
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_Start), hWnd, StartProc);

	if (state != 1)
	{
		init();
	}

	HDC HdcShowBmp= GetDC(hWnd);

	ChessBoxHDC = CreateCompatibleDC(HdcShowBmp);
	HBITMAP hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));

	if (hBmp) {
		SelectObject(ChessBoxHDC, hBmp);
		DeleteObject(hBmp);
	}
	else {
		MessageBox(hWnd, _TEXT("º”‘ÿ∆Â≈ÃÕº∆¨ ß∞‹"), _TEXT("¥ÌŒÛ"), MB_OK);
	}
	
	BlackHDC = CreateCompatibleDC(HdcShowBmp);
	hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	if (hBmp) {
		SelectObject(BlackHDC, hBmp);
		DeleteObject(hBmp);
	}
	else {
		MessageBox(hWnd, _TEXT("º”‘ÿ∫⁄∆ÂÕº∆¨ ß∞‹"), _TEXT("¥ÌŒÛ"), MB_OK);
	}

	WhiteHDC = CreateCompatibleDC(HdcShowBmp);
	hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
	if (hBmp) {
		SelectObject(WhiteHDC, hBmp);
		DeleteObject(hBmp);
	}
	else {
		MessageBox(hWnd, _TEXT("º”‘ÿ∞◊∆ÂÕº∆¨ ß∞‹"), _TEXT("¥ÌŒÛ"), MB_OK);
	}

}
BOOL GoBang::init()
{
	Later = BLACK;

	RConnected_chess = 5;

	ChessBoxWide = 533;
	ChessBoxHigh = 533;

	Count_Black = 0;  //113;
	Count_White = 0;  //112;
	MapCount = 0;
	
	for (int i = 0; i < MAP_HIGH; i++) {
		for (int j = 0; j < MAP_WIDE; j++) {
			Map[i][j] = 0;
		}
	}
	return false;
}
BOOL GoBang::Show(HDC hdc)
{
	TCHAR Content[MAXBYTE] = { 0 };

	SetBkMode(hdc, TRANSPARENT);

	swprintf_s(Content, _TEXT("∫⁄∆Â£∫%d   ∞◊∆Â: %d     £®”“ª˜≤Àµ•—°œÓ£©"), Count_Black, Count_White);

	TransparentBlt(hdc, 0, 0, ChessBoxWide, ChessBoxHigh, ChessBoxHDC, 0, 0, ChessBoxWide, ChessBoxHigh, RGB(255, 0, 255));

	TextOut(hdc, EDGE_WIDE, 0, Content, _tcslen(Content));


	for (int i = 0; i < MAP_HIGH; i++)
	{
		for (int j = 0; j < MAP_WIDE; j++)
		{
		
				if (Map[i][j] ==WHITE)
				{
					
					TransparentBlt(hdc, EDGE_WIDE / 2 + (j * CHESSBOX_RECT_WIDE), EDGE_HIGH / 2 + (i * CHESSBOX_RECT_HIGH), 33, 33, WhiteHDC, 0, 0,
						33, 33, RGB(255, 0, 255));
				}
				else if (Map[i][j] ==BLACK)
				{
					
					TransparentBlt(hdc, EDGE_WIDE / 2 + (j * CHESSBOX_RECT_WIDE), EDGE_HIGH / 2 + (i * CHESSBOX_RECT_HIGH), 33, 33, BlackHDC, 0, 0,
						33, 33, RGB(255, 0, 255));
				}
		}
	}
	return false;
}
BOOL GoBang::Move(HWND hWnd, LPARAM lParam)
{	//‘⁄∆Â≈Ãƒ⁄µ„ª˜
	 MapCount++;

	 x[MapCount]= LOWORD(lParam) / CHESSBOX_RECT_WIDE;
	 y[MapCount]= HIWORD(lParam) / CHESSBOX_RECT_HIGH;

	 int xi = x[MapCount];
	 int yi = y[MapCount];

	if (Map[yi][xi] == 0)
	{

		Map[yi][xi] = Later;

		r.position.x = xi;
		r.position.y = yi;
		
		
		if (BLACK == Later)
		{
			Count_Black++;
	
		}else Count_White++;

		
		if (Count_Black + Count_White >= MAP_WIDE * MAP_HIGH)
		{
			MessageBox(hWnd, _TEXT("∆Ωæ÷"), _TEXT("Ã· æ"), MB_OK);
			return true;
		}
		if (Jugde())
		{
			SendMessage(hWnd, WM_ERASEBKGND, 0, 0);
			if (WHITE == Later) 
			{
				MessageBox(hWnd, _TEXT("∞◊∆Â §¿˚"), _TEXT("”Œœ∑Ω· ¯"), MB_OK);
			}
			else 
			{
				MessageBox(hWnd, _TEXT("∫⁄∆Â §¿˚"), _TEXT("”Œœ∑Ω· ¯"), MB_OK);
			}
			return true;
		}
		Later = Later == BLACK ? WHITE : BLACK;
		}
	
	return false;
}
BOOL GoBang::Jugde()
{
	Record r1;
	int j = 0;
	for (int i = 0; i < 8; i++) {
		r1 = r;
		Search((Direction)i);
		if (r1.Connected_chess >= RConnected_chess)
			return true;
		else {
			j = 7 - i;
			Search((Direction)j);
			if (r1.Connected_chess >= RConnected_chess)
				return true;
		}
	}
	return false;
}
bool GoBang::Search(Direction dir) 
{
	r.Connected_chess= 0;
	switch (dir) {
	case UP:
		while (Later == Map[r.position.y][r.position.x]) {
			r.Connected_chess++;
			r.position.y--;
		}
		r.position.y++;
		break;
	case DOWN:
		while (Later == Map[r.position.y][r.position.x]) {
			r.Connected_chess++;
			r.position.y++;
		}
		r.position.y--;
		break;
	case LEFT:
		while (Later == Map[r.position.y][r.position.x]) {
			r.Connected_chess++;
			r.position.x--;
		}
		r.position.x++;
		break;
	case RIGHT:
		while (Later == Map[r.position.y][r.position.x]) {
			r.Connected_chess++;
			r.position.x++;
		}
		r.position.x--;
		break;
	case LEFT_UP:
		while (Later == Map[r.position.y][r.position.x]) {
			r.Connected_chess++;
			r.position.y--;
			r.position.x--;
		}
		r.position.x++;
		r.position.y++;
		break;
	case RIGHT_UP:
		while (Later == Map[r.position.y][r.position.x]) {
			r.Connected_chess++;
			r.position.y--;
			r.position.x++;
		}
		r.position.x--;
		r.position.y++;
		break;
	case LEFT_DOWN:
		while (Later == Map[r.position.y][r.position.x]) {
			r.Connected_chess++;
			r.position.y++;
			r.position.x--;
		}
		r.position.y--;
		r.position.x++;
		break;
	case RIGHT_DOWN:
		while (Later == Map[r.position.y][r.position.x]) {
			r.Connected_chess++;
			r.position.y++;
			r.position.x++;
		}
		r.position.x--;
		r.position.y--;
		break;
	}
	return false ;
}
bool GoBang::retract(HWND hWnd,HDC hdc)
{
	int xi = x[MapCount];
	int yi = y[MapCount];
	
	if (Map[yi][xi]!=0)
	{
		Later = Later == BLACK ? WHITE : BLACK;
		Map[yi][xi] = 0;
		if (BLACK == Later)
			Count_Black--;
		else Count_White--;
		MapCount--;	
	}

	return false;
}
bool GoBang::Save(TCHAR* filename)
{
	fstream fs(filename, fstream::out);
	fs << MapCount;
	fs << '\n';
	fs<< Count_Black;
	fs << '\n';
	fs<< Count_White; 
	fs << '\n';
	fs<< Later;
	fs << '\n';
	for (int i = 0; i < MAP_HIGH; i++)
	{
		for (int j = 0; j < MAP_WIDE; j++)
		{
			fs << Map[i][j];
			fs << '\n';
		}
	}
	fs.close();
	return false;
}
bool GoBang::Open(TCHAR* filename)
{
	init();
	fstream fs(filename);

	fs >> MapCount;
	fs >> Count_Black;
    fs >> Count_White;
	fs >> Later;
	
	for (int i = 0; i < MAP_HIGH; i++)
	{
		for (int j = 0; j < MAP_WIDE; j++)
		{
			fs >>Map[i][j];
			
		}
	}
	fs.close();
	return true;
}
