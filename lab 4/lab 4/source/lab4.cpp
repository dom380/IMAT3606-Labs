#include <windows.h>
#include <memory>
#include "resource.h"
#include "PaintTool.h"

int preMousePos[2];

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	std::shared_ptr<PaintTool> paintTool = PaintTool::getInstance();
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
				paintTool->draw(hdc, x, y);
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
				paintTool->setColour(RGB(255, 0, 0));
				break;
			}
			case ID_COLOURS_BLUE:
			{
				paintTool->setColour(RGB(0, 0, 255));
				break;
			}
			case ID_COLOURS_GREEN:
			{
				paintTool->setColour(RGB(0, 255, 0));
				break;
			}
			case ID_SHAPES_RECTA:
			{
				paintTool->setBrushStyle(BrushStyle::RECTANGLE);
				break;
			}
			case ID_SHAPES_ELLIPSE:
			{
				paintTool->setBrushStyle(BrushStyle::ELLIPSE);
				break;
			}
			case ID_SHAPES_LINE:
			{
				paintTool->setBrushStyle(BrushStyle::LINE);
				break;
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
