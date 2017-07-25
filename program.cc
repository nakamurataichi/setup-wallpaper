#include <node.h>
#include <windows.h>
#include <winuser.h>

HWND workerw;
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
	HWND h = FindWindowEx(hWnd, NULL, TEXT("SHELLDLL_DefView"), NULL);
	if (h != NULL) workerw = FindWindowEx(NULL, hWnd, TEXT("WorkerW"), NULL);
	return TRUE;
};

namespace wallpaper {
  void main(const v8::FunctionCallbackInfo<v8::Value>& args) {
    HWND progman = FindWindow(TEXT("Progman"), NULL);
    SendMessage(progman, 0x052C, NULL, NULL);

    EnumWindows(EnumWindowsProc, NULL);
    //ShowWindowAsync(workerw, SW_HIDE);

    if (workerw == NULL) {
      MessageBox(NULL, TEXT("Error : Failed to retrieve workerw!"), TEXT("wallpaper"), MB_OK | MB_ICONERROR);
    };
    HWND myhWnd = FindWindow(NULL, TEXT("wallpaper"));
    if (progman == NULL) {
      MessageBox(NULL, TEXT("Error : Failed to retrieve progman!"), TEXT("wallpaper"), MB_OK | MB_ICONERROR);
    };
    if (myhWnd == NULL) {
      MessageBox(NULL, TEXT("Error : Failed to retrieve myhWnd!"), TEXT("wallpaper"), MB_OK | MB_ICONERROR);
    };
    if (SetParent(myhWnd, progman) == NULL) {
      MessageBox(NULL, TEXT("Error : Failed to set Parent!"), TEXT("wallpaper"), MB_OK | MB_ICONERROR);
    };

    ShowWindowAsync(myhWnd, SW_SHOWNORMAL);
  }

  void init(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "start", main);
  }
  NODE_MODULE(setup_wallpaper, init)
}
