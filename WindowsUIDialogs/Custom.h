#pragma once
#include <windows.h>
#include <Commdlg.h>
#include <string>

ATOM        CustomClass = NULL;
HWND		hWndBoxes[20];
HWND		HwndCustom;
HWND		CustomOk;
wchar_t**	Pairs;
wchar_t**	TypeInfo;
int			PairNum;
wchar_t*	CustomValue;

LRESULT CALLBACK CustomWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

extern "C" {
	__declspec(dllexport) wchar_t* CustomUI(const wchar_t** Pairs, const wchar_t** _TypeInfo, int PairNum);
}

HWND CreateEditBox(const wchar_t* Val, int Y);
HWND CreateLabel(const wchar_t* Label, int Y);
wchar_t* SaveValue();