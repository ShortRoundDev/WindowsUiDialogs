#include "Custom.h"
#include <iostream>
#include <string>

wchar_t* CustomUI(const wchar_t** _Pairs, const wchar_t** _TypeInfo, int _PairNum) {
	Pairs		= (wchar_t**)_Pairs;
	TypeInfo	= (wchar_t**)_TypeInfo;
	PairNum		= _PairNum;
	if (CustomClass == NULL) {
		WNDCLASSEXW wcl = {};
		wcl.cbSize = sizeof(WNDCLASSEXA);
		wcl.style = CS_OWNDC;
		wcl.lpfnWndProc = CustomWindowProc;
		wcl.cbClsExtra = 0;
		wcl.cbWndExtra = 0;
		wcl.hInstance = (HINSTANCE)GetModuleHandle(NULL);
		wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcl.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
		wcl.lpszMenuName = NULL;
		wcl.lpszClassName = L"wclClassA";
		wcl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		CustomClass = RegisterClassExW(&wcl);
	}

	std::cout << "Num pairs: " << PairNum << std::endl;
	HwndCustom = CreateWindowExW(
		WS_EX_CLIENTEDGE,
		(LPCWSTR)CustomClass,
		L"Text Input",
		WS_EX_PALETTEWINDOW | WS_BORDER | WS_VISIBLE | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		300,
		62 + PairNum * 21,
		NULL,
		NULL,
		(HINSTANCE)GetModuleHandle(NULL),
		NULL
	);
	
	for (int i = 0; i < PairNum * 2; i += 2) {
		std::cout << Pairs[i] << " - " << Pairs[i + 1] << std::endl;
		if (Pairs[i] == NULL) {
			break;
		}
		hWndBoxes[i]		= CreateLabel(Pairs[i], i * 10);
		hWndBoxes[i + 1]	= CreateEditBox(Pairs[i + 1], i * 10);
	}

	CustomOk = CreateWindow(
		L"BUTTON",
		L"OK",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		300 - 64, PairNum * 21, 32, 16,
		HwndCustom, NULL, NULL, NULL
	);

	SetWindowLong(HwndCustom, GWL_EXSTYLE, WS_EX_TOOLWINDOW);

	ShowWindow(HwndCustom, SW_SHOW);
	UpdateWindow(HwndCustom);
	BOOL bRet;

	MSG Msg = { };
	while ((bRet = GetMessage(&Msg, NULL, 0, 0)) != 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return CustomValue;
}


HWND CreateEditBox(const wchar_t* Val, int Y) {
	return CreateWindowExW(
		WS_EX_CLIENTEDGE,
		L"Edit",
		Val,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		150, Y, 145, 20,
		HwndCustom, NULL, NULL, NULL
	);
}

HWND CreateLabel(const wchar_t* Label, int Y) {
	return CreateWindowExW(
		0,
		L"Static",
		Label,
		WS_CHILD | WS_VISIBLE,
		5, Y, 145, 20,
		HwndCustom, NULL, NULL, NULL
	);
}

LRESULT CALLBACK CustomWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (HIWORD(wParam)) {
		case BN_CLICKED:
			CustomValue = SaveValue();
			DestroyWindow(HwndCustom);
			break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(HwndCustom);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

wchar_t* SaveValue() {
	wchar_t* CustomValueBuff = (wchar_t*)calloc(2048, sizeof(wchar_t));
	wcscat_s(CustomValueBuff, 2048, L"{");
	wchar_t* Buffer = (wchar_t*)calloc(1024, sizeof(wchar_t));
	for (int i = 0; i < PairNum * 2; i += 2) {
		GetWindowText(hWndBoxes[i], Buffer, 128);

		//Append Key
		wcscat_s(CustomValueBuff, 2048, L"\"");
		wcscat_s(CustomValueBuff, 2048, Buffer);
		wcscat_s(CustomValueBuff, 2048, L"\": ");

		//Append Value
		GetWindowText(hWndBoxes[i + 1], Buffer, 128);
		int IsString = !wcscmp(TypeInfo[i / 2], L"String");
		if (IsString) {
			wcscat_s(CustomValueBuff, 2048, L"\"");
		}
		wcscat_s(CustomValueBuff, 2048, Buffer);
		if (IsString) {
			wcscat_s(CustomValueBuff, 2048, L"\"");
		}
		if (i != (PairNum - 1) * 2)
			wcscat_s(CustomValueBuff, 2048, L",");
	}
	wcscat_s(CustomValueBuff, 2048, L"}");
	free(Buffer);
	return CustomValueBuff;
}