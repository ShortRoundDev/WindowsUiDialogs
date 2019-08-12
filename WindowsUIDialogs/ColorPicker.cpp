#include "ColorPicker.h"

void Init(unsigned long Default) {	
	ZeroMemory(&ColorStructW, sizeof(ColorStructW));

	ColorStructW.lStructSize	= sizeof(ColorStructW);
	ColorStructW.hwndOwner		= NULL;
	ColorStructW.lpCustColors	= (LPDWORD) acrCustClr;
	ColorStructW.rgbResult		= Default;
	ColorStructW.Flags			= CC_FULLOPEN | CC_RGBINIT;
}

unsigned long GetColor(unsigned long Default) {
	Init(Default);
	if (ChooseColor(&ColorStructW)) {
		unsigned long Selected = ColorStructW.rgbResult;
		unsigned long Reversed = 0;
		//abgr
		Reversed |= (Selected & 0xff) << 24;		// R
		Reversed |= (Selected & 0xff00);		// G
		Reversed |= (Selected & 0xff0000);		// B
		Reversed |= (Selected & 0xff000000) >> 24;	// A
		return Reversed;
	}
	return Default;
}
