#pragma once
#include <Windows.h>

class Bitmap {
protected:
	HBITMAP m_hBitmap;
	int m_iWidth, m_iHeight;

	//free method
	void Free();
	
public:
	Bitmap();
	Bitmap(HDC hDC, LPTSTR szFileNmae);
	Bitmap(HDC hDC, UINT uiResid, HINSTANCE hInstance);
	Bitmap(HDC hDC, int iWidth, int iHeight, COLORREF crColor = RGB(0, 0, 0));
	virtual ~Bitmap();

	//General methods
	BOOL Create(HDC hDC, LPTSTR szFileName);
	BOOL Create(HDC hDC, UINT uiResId, HINSTANCE hInstance);
	BOOL Create(HDC hDC, int iWidth, int iHeight, COLORREF crColor);
	void Draw(HDC hDC, int x, int y);
	int GetWidth() { return m_iWidth; }
	int GetHeight() { return m_iHeight; }
};