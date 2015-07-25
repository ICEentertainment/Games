
#include "Slideshow.h"

BOOL GameInitialize(HINSTANCE hInstance) {
	//create the game engine
	g_pGame = new GameEngine(hInstance, TEXT("Slideshow"), TEXT("Slideshow"), IDI_SLIDESHOW, IDI_SLIDESHOW_SM);
	if (g_pGame == NULL) {
		return FALSE;
	}
	

	//Setting the framerate
	g_pGame->SetFrameRate(1);

	//store the instance handle
	g_hInstance = hInstance;

	return TRUE;
}
void GameStart(HWND hWindow) {
	//Create and laod the slide bitmaps
	HDC hDC = GetDC(hWindow);
	g_pSlide[0] = new Bitmap(hDC, TEXT("Image1.bmp"));
	g_pSlide[1] = new Bitmap(hDC, TEXT("Image2.bmp"));
	g_pSlide[2] = new Bitmap(hDC, TEXT("Image3.bmp"));
	g_pSlide[3] = new Bitmap(hDC, IDB_IMAGE4, g_hInstance);
	g_pSlide[4] = new Bitmap(hDC, IDB_IMAGE5, g_hInstance);
	g_pSlide[5] = new Bitmap(hDC, 640, 480, RGB(0,100,0));
	
	//Set first slide
	g_iCurSlide =0;
}
void GameEnd() {
	//Cleanup the slides of bitmaps
	for (int i = 0; i < g_iNUMSLIDES; i++) {
		delete g_pSlide[i];
	}
	delete g_pGame;
}

void GamePaint(HDC hDC) {
	//draw to the current device context
	g_pSlide[g_iCurSlide]->Draw(hDC,0,0);
}
void GameCycle() {
	static int iDelay = 0;
	
	//Establish a 3-second delay
	if (++iDelay > 3) {
		//set the counter back to 0
		iDelay = 0;

		//Move to the next slide
		if (++g_iCurSlide == g_iNUMSLIDES) {
			g_iCurSlide = 0;
		}
		// Force a repaint to draw next lside
		InvalidateRect(g_pGame->GetWindow(), NULL, FALSE);
	}
}
void GameActivate(HWND hWindow)
{
}

void GameDeactivate(HWND hWindow)
{
}
