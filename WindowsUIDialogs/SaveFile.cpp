#include "SaveFile.h"

wchar_t* OpenFileSaveDialog() {
	OPENFILENAME OpenFileName;
	ZeroMemory(&OpenFileName, sizeof(OpenFileName));
	OpenFileName.lStructSize = sizeof(OpenFileName);
	OpenFileName.hwndOwner = NULL;
	wchar_t* Buffer = (wchar_t*)calloc(1024, sizeof(wchar_t));
	size_t OutSize;
	//mbstowcs_s(&OutSize, Buffer, strlen(Name) + 1, Name, strlen(Name) - 1);

	OpenFileName.lpstrFile = Buffer;
	OpenFileName.nMaxFile = 1024;
	OpenFileName.lpstrFilter = L"All (*.*)\0*.*\0JSON File (*.json)\0*.json\0";
	OpenFileName.nFilterIndex = 1;
	OpenFileName.lpstrFileTitle = NULL;
	OpenFileName.nMaxFileTitle = 0;
	OpenFileName.lpstrInitialDir = NULL;
	OpenFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	GetSaveFileName(&OpenFileName);

	return OpenFileName.lpstrFile;
}
