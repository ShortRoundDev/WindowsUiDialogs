#pragma once
#include <windows.h>
#include <Commdlg.h>
#include "DeclSpec.h"
#include <string>

ATOM        VectorWclass = NULL;
HWND		hWndEditX;
HWND		hWndEditY;
HWND		LabelX;
HWND		LabelY;
HWND		VectorhWndOk;
HWND		VectorHwnd;

wchar_t*	VecValue;

LRESULT CALLBACK VecWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern "C" {
	DECLSPEC wchar_t* GetNumberInput(const wchar_t* Title, double X, double Y);
}

HWND GetNumberBox(const wchar_t* Name, int Y);
HWND GetNumberLabel(const wchar_t* Label, int Y);