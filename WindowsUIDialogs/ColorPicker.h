#pragma once
#include <windows.h>

CHOOSECOLORW ColorStructW;
static COLORREF acrCustClr[16] = {
	RGB(0,0,0),			// Black
	RGB(108, 41, 64),	// Burgundy
	RGB(64, 53, 120),	// Indigo
	RGB(217, 60, 240),	// Mauve
	RGB(19, 87, 64),	// Forest Green
	RGB(128, 128, 128),	// Grey
	RGB(38, 151, 240),	// Sky Blue
	RGB(191, 180, 248),	// Pale Blue
	RGB(64, 75, 7),		// Olive
	RGB(217, 104, 15),	// Burnt Orange
	RGB(64, 64, 64),	// Darker Grey
	RGB(236, 168, 191),	// Pink
	RGB(38, 195, 15),	// Lime
	RGB(191, 202, 135),	// Pale Green
	RGB(147, 214, 191), // Teal-ish
	RGB(255, 255, 255)	// White
};

void Init(unsigned long Default);
extern "C" {
	__declspec(dllexport) unsigned long GetColor(unsigned long Default);
}