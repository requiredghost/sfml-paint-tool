#include "ColorChooserDialog.h"

ColorChooserDialog::ColorChooserDialog() {
	//initialise memory
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hwnd;
	cc.lpCustColors = (LPDWORD)acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
}


void ColorChooserDialog::Open(sf::Window* _windowRef, sf::Color* _colorRef) {
	hwnd = _windowRef->getSystemHandle();

	if (ChooseColor(&cc)) {
		cr = cc.rgbResult;

		sf::Color tempColor;
		tempColor.r = GetRValue(cr);
		tempColor.g = GetGValue(cr);
		tempColor.b = GetBValue(cr);

		*_colorRef = tempColor;

	}
}


bool ColorChooserDialog::isOpen() {
	return isPaintDialogOpen;
}
