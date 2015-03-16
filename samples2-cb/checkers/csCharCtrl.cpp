#include "csCharCtrl.h"

bool csCharCtrl::initialized = false;
int csCharCtrl::sz = 50;
wxTextAttr csCharCtrl::textstyle;
wxTextValidator csCharCtrl::textvalidator;

void csCharCtrl::Initialize(const wxString &chars, int size, const wxFont &font, int fontsize)
{
	if (!initialized) {
		initialized = true;
		sz = size;
		// Define font and font size for the text in the squares
		textstyle.SetFont(font);
		textstyle.SetFontPixelSize(fontsize == 0 ? sz/2 : fontsize);
		textstyle.SetBackgroundColour(wxTransparentColour);
		// Define valid input values for the text in the squares
		// NB. Allow blank to prevent control to reset to small font
		textvalidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
		textvalidator.SetCharIncludes(chars + wxT(" "));
	}
}


bool csCharCtrl::Create(wxWindow *parent, wxWindowID id,
			bool readOnly,
            const wxString& value,
            const wxPoint& pos,
            const wxSize& size,
            long style
			)
{
	if (readOnly) style |= wxTE_READONLY;
	bool ok = wxTextCtrl::Create(parent, id, value, pos, (size == wxDefaultSize ? wxSize(sz,sz) : size), style | defaultstyles, wxTextValidator(textvalidator));
	if (ok) {
		// Prevent editing of read only fields
		SetEditable(!readOnly);

		// At most 1 char per square
		SetMaxLength(1);

		// Set the larger font
		SetDefaultStyle(textstyle);

		// Must use WriteText() to make the text input field use the larger font
		SelectAll();
		WriteText(value.empty() ? wxT(" ") : value);
		SetModified(false);

		// Intercept Set Focus event for the input field
	    Bind(wxEVT_SET_FOCUS, &csCharCtrl::OnSetFocus, this);
		// Intercept Kill Focus event for the input field
	    Bind(wxEVT_KILL_FOCUS, &csCharCtrl::OnKillFocus, this);
		// Intercept Set Focus event for the input field
	    Bind(wxEVT_CHAR, &csCharCtrl::OnChar, this);
	}
	return ok;
}

bool csCharCtrl::SetBackgroundColour(const wxColour& colour)
{
	bool ok = wxTextCtrl::SetBackgroundColour(colour);
	if (ok) {
		// Set the text background colour also
		wxTextAttr style = GetDefaultStyle();
		style.SetBackgroundColour(colour);
		ok = SetDefaultStyle(style);
	}
	
	return ok;
}

// Set and get data as char values
bool csCharCtrl::SetCharValue(const char charval) {
	wxString val(charval);
	if (textvalidator.GetIncludes().Index(val) == wxNOT_FOUND)
		return false;
	SetValue(val);	// Sets control as not-modified
	NormalizeText();
	return true;
}

bool csCharCtrl::GetCharValue(char &charval) {
	wxString val = GetValue();
	if (val.length() != 1) 
		return false;
	charval = val[0];
	return true;
}


void csCharCtrl::OnSetFocus(wxFocusEvent &event)
{
	// Intercept Set Focus event for the input field

	//wxLogDebug(wxString::Format("OnSetFocus: %d !%S!", GetId(), GetValue()));

	NormalizeText();

	// Allow default handling of the event 
	event.Skip();
}

void csCharCtrl::OnKillFocus(wxFocusEvent &event)
{
	// Intercept Kill Focus event for the input field

	//wxLogDebug(wxString::Format("OnKillFocus: %d !%S!", GetId(), GetValue()));

	NormalizeText();

	if (IsModified()) {
		// TODO:
		// Get the modified value
		// wxString val = GetValue();
		// validate the modified value and transfer it to the data model
		// SetModified(false);
	}

	// Allow default handling of the event 
	event.Skip();
}

void csCharCtrl::OnChar(wxKeyEvent &event)
{
	// Intercept Char event for the input field

	//wxLogDebug(wxString::Format("OnChar: %d, %d !%S!", GetId(), event.GetKeyCode(), GetValue()));

	NormalizeText();
	// Select the existing text to make sure that it is overwritten
	SelectAll();

	// Allow default handling of the event 
	event.Skip();
}

void csCharCtrl::NormalizeText() {
	bool modified = IsModified();
	wxString val = GetValue();
	if (val.empty()) {
		SetValue(wxT(" "));
	}
	SetStyle(0, 1, GetDefaultStyle());
	SetModified(modified);
}