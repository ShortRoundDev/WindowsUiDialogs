#include "Vector.h"
#include <windows.h>
#include <Commdlg.h>
#include <string>
#include <iostream>

wchar_t* GetNumberInput(const wchar_t* Title, double X, double Y) {
	if (VectorWclass == NULL) {
		WNDCLASSEXW wcl = {};
		wcl.cbSize = sizeof(WNDCLASSEXA);
		wcl.style = CS_OWNDC;
		wcl.lpfnWndProc = VecWindowProc;
		wcl.cbClsExtra = 0;
		wcl.cbWndExtra = 0;
		wcl.hInstance = (HINSTANCE)GetModuleHandle(NULL);
		wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcl.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
		wcl.lpszMenuName = NULL;
		wcl.lpszClassName = L"wclClassA";
		wcl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		VectorWclass = RegisterClassExW(&wcl);
	}

	VectorHwnd = CreateWindowExW(
		WS_EX_CLIENTEDGE,
		(LPCWSTR)VectorWclass,
		L"Number",
		WS_EX_PALETTEWINDOW | WS_BORDER | WS_VISIBLE | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		200,
		140,
		NULL,
		NULL,
		(HINSTANCE)GetModuleHandle(NULL),
		NULL
	);

	if (VectorHwnd == NULL)
		return NULL;

	LabelX = GetNumberLabel(L"X", 7);
	hWndEditX = GetNumberBox(L"69", 5);
	LabelY = GetNumberLabel(L"Y", 39);
	hWndEditY = GetNumberBox(L"42", 37);

	VectorhWndOk = CreateWindow(
		L"BUTTON",
		L"OK",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		124, 70, 32, 16,
		VectorHwnd, NULL, NULL, NULL
	);

	SetWindowLong(VectorHwnd, GWL_EXSTYLE, WS_EX_TOOLWINDOW);

	ShowWindow(VectorHwnd, SW_SHOW);
	UpdateWindow(VectorHwnd);
	BOOL bRet;

	MSG Msg = { };
	while ((bRet = GetMessage(&Msg, NULL, 0, 0)) != 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return VecValue;
}

HWND GetNumberBox(const wchar_t* Name, int Y) {
	HWND Edit = CreateWindowExW(
		WS_EX_CLIENTEDGE,
		L"Edit",
		Name,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		25, Y, 150, 32,
		VectorHwnd, NULL, NULL, NULL
	);
	SetWindowLong(Edit, GWLP_WNDPROC, (LONG_PTR)&VecWindowProc);
	return Edit;
}

HWND GetNumberLabel(const wchar_t* Label, int Y) {
	return CreateWindowExW(
		0,
		L"Static",
		Label,
		WS_CHILD | WS_VISIBLE,
		5, Y, 15, 32,
		VectorHwnd, NULL, NULL, NULL
	);
}

LRESULT CALLBACK VecWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	wchar_t BufferA[512] = { 0 };
	wchar_t BufferB[512] = { 0 };
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (HIWORD(wParam)) {
		case BN_CLICKED:
			VecValue = (wchar_t*)calloc(sizeof(wchar_t), 1024);
			GetWindowText(hWndEditX, BufferA, 128);
			GetWindowText(hWndEditY, BufferB, 128);
			wcscat_s(VecValue, 1024, BufferA);
			wcscat_s(VecValue, 1024, L",");
			wcscat_s(VecValue, 1024, BufferB);
			DestroyWindow(VectorHwnd);
			break;
		case EN_UPDATE:
			wchar_t Buffer[256];
			GetWindowText((HWND)lParam, Buffer, 256);
			std::wcout << Buffer << std::endl;
			//SetWindowTextW((HWND)lParam, L"0");
			break;
		}
		break;
	case WM_CLOSE:
		VecValue = (wchar_t*)malloc(sizeof(wchar_t) * 1024);
		GetWindowText(hWndEditX, BufferA, 128);
		GetWindowText(hWndEditY, BufferB, 128);
		wcscat_s(VecValue, 1024, BufferA);
		wcscat_s(VecValue, 1024, L",");
		wcscat_s(VecValue, 1024, BufferB);		DestroyWindow(VectorHwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
