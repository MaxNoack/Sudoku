// wxWidgets "Ccechers Edit Demo" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

//#include "boarddata.h"
#include "BoardPanel.h"

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

class BoardPanel;

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void SetupMenuBar();
    void CreateBoardPanel();
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    BoardPanel *panel;
//	BoardData model;
//	wxLogWindow logger;  // Uncomment here and initialization in constructor below
						 // to get logging output in a separate window
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Sudoko game!", wxPoint(50, 50), wxSize(700, 700) );
    frame->Show( true );
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size) /*, logger(NULL, wxT("Log Window"))*/
{
    SetupMenuBar();
    CreateBoardPanel();
    CreateStatusBar();
    SetStatusText( "Welcome to the sudoku game! Allowed input are digits between 1-9" );
}

void MyFrame::SetupMenuBar()
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::OnExit, this, wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MyFrame::OnAbout, this, wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
}

void MyFrame::CreateBoardPanel()
{
    panel = new BoardPanel(this/*, model*/);
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is a sudoku game created by Ramo Mislimi, Andre Jönsson and Max Noack",
                  "About the sudoku game", wxOK | wxICON_INFORMATION );
}



