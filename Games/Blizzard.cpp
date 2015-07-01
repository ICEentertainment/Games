#include "Blizzard.h"

int g_xPostion;
int g_YPostion;
POINT pos;



BOOL GameInitialize(HINSTANCE hInstance) {
	// Create the game Engine
	g_pGame = new GameEngine(hInstance, TEXT("Blizzard"), TEXT("Blizzard"), IDI_BLIZZARD, IDI_BLIZZARD_SM);
	if (g_pGame == NULL) {
		return FALSE;
	}
	//setting the frame rate
	g_pGame->SetFrameRate(15);

	return true;
}
void GameStart(HWND hWindow) {
	//Seeding random number generator for snow placement
	srand(GetTickCount());
	pos.x = rand() % g_pGame->GetWidth();
	pos.y = rand() % g_pGame->GetHeight();
}
void GameEnd() {
	//cleanup the game
	delete g_pGame;
}
void GameActivate(HWND hWindow) {
	HDC hDC;
	RECT rect;
	//Draw activation text on the game screen 
	GetClientRect(hWindow, &rect);
	hDC = GetDC(hWindow);
	DrawText(hDC, TEXT("Here comes the Blizzard!!!!"), -1, &rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	ReleaseDC(hWindow, hDC);
}
void GameDeactivate(HWND hWindow) {
	HDC hDC;
	RECT rect;

	//Draw deactivation on the screen
	GetClientRect(hWindow, &rect);
	hDC = GetDC(hWindow);
	DrawText(hDC, TEXT("The Blizzard has passed!!!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	ReleaseDC(hWindow, hDC);
}
void GamePaint(HDC hDC){}

void GameCycle() {
	HDC hDC;
	HWND hWindow = g_pGame->GetWindow();

	//Draw the snowflake icon at random places on the screen 
	hDC = GetDC(hWindow);
	DrawIcon(hDC,pos.x, pos.y,(HICON)(WORD)GetClassLong(hWindow, GCL_HICON));
	ReleaseDC(hWindow, hDC);
	pos.x += 4;
	pos.y += 4;
}