#include "WindowsUiDialogs.hh"

void FreeString(void* StrPtr) {
	if (StrPtr == NULL) {
		return;
	}
	free(StrPtr);
}
