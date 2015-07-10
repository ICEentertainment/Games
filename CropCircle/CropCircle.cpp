#include "CropCircle.h"

BOOL GameInitialize(HINSTANCE hInstance) {
	//Create Game Engine 
	g_pGame = new GameEngine(hInstance, TEXT("Crop Circle"), TEXT("Crop Circles"), IDI_CROPCIRCLES, IDI_CROPCIRCLES_SM);
	if (g_pGame == NULL) {
		return FALSE;
	}
	g_pGame->SetFrameRate(20);
	return TRUE;
}
void GameStart(HWND hWindow) {
	//Seed the random generator
	srand(GetTickCount());

	// Setting the postion of the rectangles
	g_rcRectangle.left = g_pGame->GetWidth() * 2 / 5;
	g_rcRectangle.top = g_pGame->GetHeight() * 2 / 5;
	g_rcRectangle.right = g_rcRectangle.left + g_pGame->GetWidth() / 10;
	g_rcRectangle.bottom = g_rcRectangle.top + g_pGame->GetWidth() / 10;
}

void GameEnd()
{
	// Cleanup the game engine
	delete g_pGame;
}

void GameActivate(HWND hWindow)
{
}

void GameDeactivate(HWND hWindow)
{
}
//If the object is drawn in gamepaint then it wont be lost when repainted(aka minimized)
void GamePaint(HDC hDC) {
	//Drawing the background
	RECT rect;
	GetClientRect(g_pGame->GetWindow(), &rect);
	HBRUSH hBrush = CreateSolidBrush(RGB(128, 128, 0));
	FillRect(hDC, &rect, hBrush);
	DeleteObject(hBrush);
}
void GameCycle() {
	RECT rect;
	HDC hDC;
	HWND hWindow = g_pGame->GetWindow();
	//Remember the location of the last crop circle

	int iXLast = g_rcRectangle.left + (g_rcRectangle.right - g_rcRectangle.left) / 2;
	int iYLast = g_rcRectangle.top + (g_rcRectangle.bottom - g_rcRectangle.top) / 2;

	//Randomly alter the size and postion of the crop circle
	GetClientRect(g_pGame->GetWindow(), &rect);
	int iInflation = (rand() % 17) - 8; //increase or decreasae the size up to 8
	InflateRect(&g_rcRectangle, iInflation, iInflation);
	OffsetRect(&g_rcRectangle, rand() % (rect.right - rect.left) - g_rcRectangle.left, rand() % (rect.bottom - rect.top) - g_rcRectangle.top);

	//Draw a line to the new crop circle
	hDC = GetDC(hWindow);
	HPEN hPen = CreatePen(PS_SOLID, 5, RGB(192, 192, 0));
	SelectObject(hDC, hPen);
	MoveToEx(hDC, iXLast, iYLast, NULL);
	LineTo(hDC, g_rcRectangle.left + (g_rcRectangle.right - g_rcRectangle.left) / 2, g_rcRectangle.top + (g_rcRectangle.bottom - g_rcRectangle.top) / 2);

	//Draw the crop circle
	HBRUSH hBrush = CreateSolidBrush(RGB(192, 192, 0));
	SelectObject(hDC,hBrush);
	Ellipse(hDC, g_rcRectangle.left, g_rcRectangle.top, g_rcRectangle.right, g_rcRectangle.bottom);
	ReleaseDC(hWindow, hDC);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}