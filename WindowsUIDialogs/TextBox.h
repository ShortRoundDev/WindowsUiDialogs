#pragma once
#include <windows.h>
#include <Commdlg.h>
#include <string>

ATOM        Wclass = NULL;
HWND		hWndEdit;
HWND		hWndOk;
HWND		Hwnd;

wchar_t*	TextboxValue;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

extern "C" {
	__declspec(dllexport) wchar_t* GetTextInput(const wchar_t* Title);
}
