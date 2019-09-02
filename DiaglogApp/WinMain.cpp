#include <Windows.h>  
#include "resource.h"  
#pragma comment(linker,"\"/manifestdependency:type='win32' name = 'Microsoft.Windows.Common-Controls' version = '6.0.0.0' \
processorArchitecture = '*' publicKeyToken = '6595b64144ccf1df' language = '*'\"")

#if 0
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

HINSTANCE hgInst;
int WINAPI WinMain(HINSTANCE hThisApp, HINSTANCE hPrevApp, LPSTR lpCmd, int nShow)
{
	hgInst = hThisApp;
	HWND hdlg = CreateDialog(hThisApp, MAKEINTRESOURCE(IDD_Main), GetDesktopWindow(), (DLGPROC)DlgProc);
	if (!hdlg) {
		return 0;
	}
	ShowWindow(hdlg, SW_SHOW);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hgInst, MAKEINTRESOURCE(IDI_AppICON)));
		return 0;
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE) {
			PostQuitMessage(0);
		}
		return 0;
	}
	return (INT_PTR)FALSE;
}

#else
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam);

HINSTANCE hgAppInst;
int WINAPI WinMain(HINSTANCE hThisApp, HINSTANCE hPrevApp, LPSTR lpCmd, int nShow)
{
	WNDCLASS wc = {};
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	wc.lpszClassName = L"supper_man";
	wc.hInstance = hThisApp;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);

	hgAppInst = hThisApp;
	HWND hwnd = CreateWindow(L"supper_man", L"Application", WS_OVERLAPPEDWINDOW, 40, 25, 380, 300, NULL, NULL, hThisApp, NULL);
	if (!hwnd) {
		return 0;
	}

	ShowWindow(hwnd, nShow);
	UpdateWindow(hwnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		case WM_CREATE: {
			HWND hdlg = CreateDialog(hgAppInst, MAKEINTRESOURCE(IDD_Main), hwnd, (DLGPROC)DlgProc);
			ShowWindow(hdlg, SW_SHOWNA);
			return 0;
		}

		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return (INT_PTR)FALSE;
}
#endif
