// ApiTest.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "windows.h"
#include "winuser.h"

HWND workerw;
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
	HWND h = FindWindowEx(hWnd, NULL, _T("SHELLDLL_DefView"), NULL);
	if (h != NULL) workerw = FindWindowEx(NULL, hWnd, _T("WorkerW"), NULL);
	return TRUE;
};

int main()
{
	HWND progman = FindWindow(_T("Progman"), NULL);
	SendMessage(progman, 0x052C, NULL, NULL);

	EnumWindows(EnumWindowsProc, NULL);
	//ShowWindowAsync(workerw, SW_HIDE);

	if (workerw == NULL) {
		MessageBox(NULL, _T("Error : Failed to retrieve workerw!"), _T("wallpaper"), MB_OK | MB_ICONERROR);
	};
	HWND myhWnd = FindWindow(NULL, _T("wallpaper"));
	if (progman == NULL) {
		MessageBox(NULL, _T("Error : Failed to retrieve progman!"), _T("wallpaper"), MB_OK | MB_ICONERROR);
	};
	if (myhWnd == NULL) {
		MessageBox(NULL, _T("Error : Failed to retrieve myhWnd!"), _T("wallpaper"), MB_OK | MB_ICONERROR);
	};
	if (SetParent(myhWnd, progman) == NULL) {
		MessageBox(NULL, _T("Error : Failed to set Parent!"), _T("wallpaper"), MB_OK | MB_ICONERROR);
	};

	ShowWindowAsync(myhWnd, SW_SHOWNORMAL);
    return 0;
}