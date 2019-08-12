#include "TextBox.h"
#include <windows.h>
#include <Commdlg.h>
#include <string>

wchar_t* GetTextInput(const wchar_t* Title) {
	if (Wclass == NULL) {
		WNDCLASSEXW wcl = {};
		wcl.cbSize = sizeof(WNDCLASSEXA);
		wcl.style = CS_OWNDC;
		wcl.lpfnWndProc = WindowProc;
		wcl.cbClsExtra = 0;
		wcl.cbWndExtra = 0;
		wcl.hInstance = (HINSTANCE)GetModuleHandle(NULL);
		wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcl.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
		wcl.lpszMenuName = NULL;
		wcl.lpszClassName = L"wclClassA";
		wcl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		Wclass = RegisterClassExW(&wcl);
	}

	Hwnd = CreateWindowExW(
		WS_EX_CLIENTEDGE,
		(LPCWSTR)Wclass,
		L"Text Input",
		WS_EX_PALETTEWINDOW | WS_BORDER | WS_VISIBLE | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		180,
		104,
		NULL,
		NULL,
		(HINSTANCE)GetModuleHandle(NULL),
		NULL
	);

	if (Hwnd == NULL)
		return NULL;

	hWndEdit = CreateWindowExW(
		WS_EX_CLIENTEDGE,
		L"Edit",
		Title,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		5, 5, 150, 32,
		Hwnd, NULL, NULL, NULL
	);

	hWndOk = CreateWindow(
		L"BUTTON",
		L"OK",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		113, 42, 32, 16,
		Hwnd, NULL, NULL, NULL
	);

	SetWindowLong(Hwnd, GWL_EXSTYLE, WS_EX_TOOLWINDOW);

	ShowWindow(Hwnd, SW_SHOW);
	UpdateWindow(Hwnd);
	BOOL bRet;

	MSG Msg = { };
	while ((bRet = GetMessage(&Msg, NULL, 0, 0)) != 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return TextboxValue;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (HIWORD(wParam)) {
		case BN_CLICKED:
			TextboxValue = (wchar_t*)malloc(sizeof(wchar_t) * 1024);
			GetWindowText(hWndEdit, TextboxValue, 128);
			DestroyWindow(Hwnd);
			break;
		}
		break;
	case WM_CLOSE:
		TextboxValue = (wchar_t*)malloc(sizeof(wchar_t) * 1024);
		GetWindowText(hWndEdit, TextboxValue, 128);
		DestroyWindow(Hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
