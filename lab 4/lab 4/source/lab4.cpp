#include <windows.h>
#include "resource.h"

//Ugly global variables! 
// todo:move to a class!
int preMousePos[2];
HPEN pen = CreatePen(PS_SOLID,1,RGB(0,0,0));
HBRUSH brush = CreateSolidBrush(RGB(0,0,0));
bool drawRects = false;
bool drawEllipse = false;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_ACTIVATE:
		{
			if (LOWORD(wParam) == WA_ACTIVE || LOWORD(wParam) == WA_CLICKACTIVE) {
				preMousePos[0] = 0;
				preMousePos[1] = 0;
			}
			return 0;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
		
			EndPaint(hwnd, &ps);
			return 0;
		}
		case WM_LBUTTONDOWN: 
		{
			//HDC hdc = GetDC(hwnd);
			//for (int index = 0; index < 100; index++)
			//{
			//	int x = rand() % 1000;
			//	int y = rand() % 700;
			//	COLORREF color = RGB(rand() % 255, rand() % 255, rand() % 255);
			//	SetPixel(hdc, x, y, color);
			//}
			return 0;
		}
		case WM_KEYDOWN: {
			HDC hdc = GetDC(hwnd);
			switch (wParam)
			{
			case VK_LEFT:
			{
				int left = rand() % 1000;
				int top = rand() % 700;
				Ellipse(hdc, left, left + 50, top, top + 50);
				break;
			}
			case VK_RIGHT:
			{
				int left = rand() % 2000;
				int top = rand() % 700;
				Rectangle(hdc, left, left +  100, top, top + 50);
				break;
			}
			case VK_UP:
			{

				break;
			}
			case VK_DOWN:
			{
				break;
			}
			case 0x41: //a key
			{
				break;
			}
			case 0x42: //b key
			{
				break;
			}
			default:
				break;
			};
			ReleaseDC(hwnd, hdc);
			return 0;
		}
		case WM_MOUSEMOVE:
		{
			if (wParam == MK_LBUTTON) { //If left mouse down
				HDC hdc = GetDC(hwnd);
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);
				if (preMousePos[0] == 0 && preMousePos[1] == 0) {
					MoveToEx(hdc,x, y, NULL);
				}
				else {
					MoveToEx(hdc, preMousePos[0], preMousePos[1], NULL);
				}
				SelectObject(hdc, pen);
				if (drawEllipse)
				{
					SelectObject(hdc, brush);
					Ellipse(hdc, x - 10, y - 10, x + 10, y + 10);
				} 
				else if (drawRects)
				{
					SelectObject(hdc, brush);
					Rectangle(hdc, x - 20, y - 10, x + 20, y + 10);
				} 
				else
				{
					SelectObject(hdc, pen);
					LineTo(hdc, x, y);
				}
				preMousePos[0] = x;
				preMousePos[1] = y;
				ReleaseDC(hwnd, hdc);
			}
			return 0;
		}
		case WM_LBUTTONUP:
		{
			preMousePos[0] = 0;
			preMousePos[1] = 0;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case ID_COLOURS_RED: 
			{
				DeleteObject(pen);
				pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				DeleteObject(brush);
				brush = CreateSolidBrush(RGB(255, 0, 0));
				break;
			}
			case ID_COLOURS_BLUE:
			{
				DeleteObject(pen);
				pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				DeleteObject(brush);
				brush = CreateSolidBrush(RGB(0, 0, 255));
				break;
			}
			case ID_COLOURS_GREEN:
			{
				DeleteObject(pen);
				pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
				DeleteObject(brush);
				brush = CreateSolidBrush(RGB(0, 255, 0));
				break;
			}
			case ID_SHAPES_RECTA:
			{
				drawRects = true;
				drawEllipse = false;
				break;
			}
			case ID_SHAPES_ELLIPSE:
			{
				drawRects = false;
				drawEllipse = true;
				break;
			}
			case ID_SHAPES_LINE:
			{
				drawRects = false;
				drawEllipse = false;
			}
			default:
				return 0;
			}
			return 0;
		}
		
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_SAVEBITS;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = L"MyMenu";
	wndclass.lpszClassName = L"My Windows Application";
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, L"Warning!", L"My Windows Application", MB_ICONERROR);
		return 0;
	}
	HWND hwnd = CreateWindow(L"My Windows Application", L"Title!",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, LoadMenu(hInstance, MAKEINTRESOURCE(101)), hInstance, NULL);
	ShowWindow(hwnd, ncmdshow);
	UpdateWindow(hwnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
