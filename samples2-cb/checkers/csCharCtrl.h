#ifndef _CS_CHAR_CTRL_H_
#define _CS_CHAR_CTRL_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

class csCharCtrl : public wxTextCtrl
{
public:
	static bool IsInitialized() { return initialized;}
	static void Initialize(const wxString &chars = wxT("0123456789"), int size = 50, const wxFont &font = *wxNORMAL_FONT, int fontsize = 0);

    // creation
    // --------
    csCharCtrl() { Init(); }
    csCharCtrl(wxWindow *parent, wxWindowID id,
			   bool readOnly = false,
               const wxString& value = wxEmptyString,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = 0
			 )
    {
        Init();
        Create(parent, id,  readOnly, value, pos, size, style);
    }

    bool Create(wxWindow *parent, wxWindowID id,
			   bool readOnly = false,
               const wxString& value = wxEmptyString,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = 0
			   );

	bool SetBackgroundColour(const wxColour& colour);

	// Set and get data as char values
	bool SetCharValue(const char charval);
	bool GetCharValue(char &charval);

protected:
	void Init() { Initialize(); }

private:
	static bool initialized;
	static int sz;
	static const long defaultstyles = wxTE_CENTRE | wxTE_RICH2;
	static wxTextAttr textstyle;
	static wxTextValidator textvalidator;

	// event handlers for char input fields
    void OnSetFocus(wxFocusEvent& event);
    void OnKillFocus(wxFocusEvent& event);
    void OnChar(wxKeyEvent& event);

	void NormalizeText();

};


#endif // _CS_CHAR_CTRL_H_