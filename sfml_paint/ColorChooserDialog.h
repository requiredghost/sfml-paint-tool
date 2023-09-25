#include <SFML/Graphics.hpp>
#include <windows.h>
#include <wingdi.h>

class ColorChooserDialog
{
public:
	ColorChooserDialog();
	~ColorChooserDialog();
	void Open(sf::Window*, sf::Color*);
	bool isOpen();

private:
	CHOOSECOLOR cc;	// common dialog box structure
	COLORREF acrCustClr[16];	//array pf custom colors
	HWND hwnd;	// owner window
	HBRUSH hbrush;	// brush handle
	DWORD rgbCurrent;	//initial color selection
	COLORREF cr;
	bool isPaintDialogOpen = false;	//true while the dialog is open


};

