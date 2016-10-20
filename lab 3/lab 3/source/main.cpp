
#include <windows.h>
#include <cmath>
#define NUM 1000
#define TWOPI (2 * 3.14159)
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("SineWave");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("Program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(szAppName, TEXT("Sine Wave Using Polyline"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int cxClient, cyClient, prevX, prevY;
	HDC hdc;
	int i;
	PAINTSTRUCT ps;
	POINT apt[NUM];
	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		MoveToEx(hdc, 0, cyClient / 2, NULL);
		LineTo(hdc, cxClient, cyClient / 2);

		for (i = 0; i < NUM; i++)
		{
			apt[i].x = i * cxClient / NUM;
			int yValue = (int)(log(i * cxClient / NUM));
			//int yValue = (int)(pow(apt[i].x, 2));
			//int yValue = (int)(cyClient / 2 * (1 - sin(TWOPI * i / NUM)));
			//if (yValue < cyClient / 2) //If yvalue is above midpoint
			apt[i].y = (cyClient / 2) - (yValue);
			//else //Else just set to midpoint
			//	apt[i].y = cyClient / 2;
		}

		Polyline(hdc, apt, NUM);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}


//int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
//{
//	//MessageBox(NULL, TEXT("HERE WE GO!!!"), TEXT("MY FIRST WINDOWS PROGRAM"), MB_OK | MB_ICONEXCLAMATION);
//	int returnCode = MessageBox(NULL, TEXT("HERE WE GO!!!"), TEXT("MY FIRST WINDOWS PROGRAM"), MB_YESNOCANCEL | MB_ICONERROR);
//	switch (returnCode) {
//	case IDYES :
//		MessageBox(NULL, TEXT("You pressed Yes"), TEXT("Yes"), MB_OK);
//		break;
//	case IDNO : 
//		MessageBox(NULL, TEXT("You pressed No"), TEXT("No"), MB_OK);
//		break;
//	case IDCANCEL :
//		MessageBox(NULL, TEXT("You pressed Cancel"), TEXT("Cancel"), MB_OK);
//		break;
//	};
//	return(0);
//}

