#pragma once
#define _EXPORTING
#ifdef _EXPORTING
	#define DECLSPEC    __declspec(dllexport)
#else
	#define DECLSPEC
#endif