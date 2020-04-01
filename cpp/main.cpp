#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void draw(HDC);
void drawLine(HDC, int, int, int, int);
void drawMap(HDC);
void drawBoat(HDC);
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Sample Window Class";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"SEA BATTLE",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		0, 0, 2400, 2400,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
			draw(hdc);
			drawMap(hdc);
            // All painting occurs here, between BeginPaint and EndPaint.
            EndPaint(hwnd, &ps);
        }
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void draw(HDC hdc) {
	HPEN hpen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); 
	SelectObject(hdc, hpen);
	// Создание кисти
	HBRUSH myBrush = CreateSolidBrush(RGB(0x0, 0xff, 0x0)); 
	SelectObject(hdc, myBrush);
	drawMap(hdc);	
	// CLEAR
	DeleteObject(myBrush);
	DeleteObject(hpen);
}

void drawLine(HDC hdc, int x1, int y1, int x2, int y2) {
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}
void drawMap(HDC hdc) {
	int dx1 = 0;
	int dx3 = 0;
	for (int i = 0; i <= 20; i++) {
		drawLine(hdc, dx1, 0, dx1, 1000);
		drawLine(hdc, 0, dx1, 1000, dx1);
		dx1 += 50;
	}
	dx1 = 1200;
	for (int i = 0; i <= 20; i++) {
		drawLine(hdc, dx1, 0, dx1, 1000);
		drawLine(hdc, 1200, dx3, 2200, dx3);
		dx3 += 50;
		dx1 += 50;
	}
}







