#pragma once

//included files
#include <Windows.h>
#include "Bitmap.h"
#include "GameEngine.h"
#include "Resource.h"

//Global variables
HINSTANCE g_hInstance;
GameEngine* g_pGame;
const int g_iNUMSLIDES = 6;
Bitmap* g_pSlide[g_iNUMSLIDES];
int g_iCurSlide;
