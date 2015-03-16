#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <algorithm>
#include "BoardPanel.h"
//#include "BoardData.h"


BoardPanel::BoardPanel(wxFrame *parent/*, BoardData &data*/)
    : wxPanel(parent, wxID_ANY)/*, model(data)*/, currentsquare(nullptr)
{
    CreateBoard();
}

void BoardPanel::CreateBoard()
{

	// sizers for the layout of bricks and buttons
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);	// overall layout
	// 9 rows and 9 columns with fixed height and width
	wxGridSizer *gs = new wxGridSizer(9, 9, 1, 1);
	wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);		// button commands

	// Define font and font size for the text in the squares
	// Define valid input values for the text in the squares
	csCharCtrl::Initialize(wxT("123456789"), sz);

	// Create the squares
    for (int i = 0; i < 81; i++) {
        m_square[i] = CreateSquare(this, i+1, i/9, i%9);
		// install an event handler for Set Focus event for the square
		gs->Add(m_square[i], 0, wxEXPAND);
    }
    Bind(wxEVT_CHILD_FOCUS, &BoardPanel::OnChildFocus, this);

	// buttons commands
	// Check command
	wxButton *btnnew = new wxButton(this, ID_New, wxT("New board"));
    btnnew->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &BoardPanel::OnNew, this);

	hbox2->Add(btnnew, 2, wxEXPAND);

	// buttons commands
	// Check command
	wxButton *btncheck = new wxButton(this, ID_Check, wxT("Check"));
    btncheck->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &BoardPanel::OnCheck, this);

	hbox2->Add(btncheck, 2, wxEXPAND);

    // buttons commands
	// Hint command
	wxButton *btnhint = new wxButton(this, ID_Hint, wxT("Hint"));
    btnhint->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &BoardPanel::OnHint, this);


	hbox2->Add(btnhint, 2, wxEXPAND);

    // buttons commands
	// Solve command
	wxButton *btnsolve = new wxButton(this, ID_Solve, wxT("Solve"));
    btnsolve->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &BoardPanel::OnSolve, this);


	hbox2->Add(btnsolve, 2, wxEXPAND);

    // buttons commands
	// Clear command
	wxButton *btnclear = new wxButton(this, ID_Clear, wxT("Clear"));
    btnclear->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &BoardPanel::OnClear, this);


	hbox2->Add(btnclear, 2, wxEXPAND);

	// buttons commands
	// Close command
	wxButton *btnclose = new wxButton(this, ID_Close, wxT("Close"));
    btnclose->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &BoardPanel::OnClose, this);

	hbox2->Add(btnclose, 2, wxEXPAND);

    vbox->Add(gs, 1, wxALIGN_CENTER | wxALL, 20);
	vbox->Add(hbox2, 0, wxALIGN_CENTER | wxALL, 20);


	SetSizer(vbox);

}

void setBoard(vector<vector<int>> &board) {
    ifstream boardsfile("sudokus.txt");
    srand (time(NULL));
    vector<int> numbers;
    for (int i=0; i<10; i++) numbers.push_back(i);
    random_shuffle (numbers.begin(), numbers.end());

    for(int k=0; k<=numbers[boardIndexCounter]; k++) {
        for(int row=0; row<9; row++) {
            for(int col=0; col<9; col++) {
                boardsfile >> board[row][col];
            }
        }
    }
    if(boardIndexCounter>=9)boardIndexCounter==0;
    else boardIndexCounter++;
}


csCharCtrl *BoardPanel::CreateSquare(wxPanel *panel, int nbr, int row, int col)
{
    setBoard(board);
    bool isBlack = true;
    bool lock = false;
    string value = "";
    if((col==3) && (row==0) ||
       (col==4) && (row==0) ||
       (col==5) && (row==0) ||
       (col==3) && (row==1) ||
       (col==4) && (row==1) ||
       (col==5) && (row==1) ||
       (col==3) && (row==2) ||
       (col==4) && (row==2) ||
       (col==5) && (row==2) ||
       (col==0) && (row==3) ||
       (col==1) && (row==3) ||
       (col==2) && (row==3) ||
       (col==0) && (row==4) ||
       (col==1) && (row==4) ||
       (col==2) && (row==4) ||
       (col==0) && (row==5) ||
       (col==1) && (row==5) ||
       (col==2) && (row==5) ||
       (col==6) && (row==3) ||
       (col==7) && (row==3) ||
       (col==8) && (row==3) ||
       (col==6) && (row==4) ||
       (col==7) && (row==4) ||
       (col==8) && (row==4) ||
       (col==6) && (row==5) ||
       (col==7) && (row==5) ||
       (col==8) && (row==5) ||
       (col==3) && (row==6) ||
       (col==4) && (row==6) ||
       (col==5) && (row==6) ||
       (col==3) && (row==7) ||
       (col==4) && (row==7) ||
       (col==5) && (row==7) ||
       (col==3) && (row==8) ||
       (col==4) && (row==8) ||
       (col==5) && (row==8))  isBlack=false;

    for(int x=0; x<9; x++)
    {
        for(int y=0; y<9; y++)
        {
            if(board[x][y] != 0){
                if(row == x && col == y){
                        lock = true;
                        value = "" + board[x][y];
                }
            }
        }
    }
	// Create the text input field - white squares are read only
	csCharCtrl *field = new csCharCtrl(panel, ID_Square_Start + row*9 + col, lock, value);

	// Color the squares "black" or white
	field->SetBackgroundColour(isBlack ? *wxLIGHT_GREY : *wxWHITE);

    return field;
}

// Input focus has changed
void BoardPanel::OnChildFocus(wxChildFocusEvent& event)
{
	if ((currentsquare != nullptr) && currentsquare->IsModified()) {
		char charvalue;
		if (currentsquare->GetCharValue(charvalue)) {
			int sqnbr = currentsquare->GetId() - ID_Square_Start;
			int row = sqnbr / 9;
			int col = sqnbr % 9;
			// update model with new value
			// wxLogDebug(wxString::Format("OnChildFocus: row %d, col %d, char '%c'", row, col, charvalue));
// TO DO: Update the model with new value
			// model->SetXX(row, col, charvalue);
		}
	}
	// new current text input field (nullptr if not a csCharCtrl)
	currentsquare = dynamic_cast<csCharCtrl *>(wxWindow::FindFocus());
}

void BoardPanel::OnNew(wxCommandEvent& WXUNUSED(event))
{

}

void BoardPanel::OnCheck(wxCommandEvent& WXUNUSED(event))
{

}

void BoardPanel::OnHint(wxCommandEvent& WXUNUSED(event))
{

}

void BoardPanel::OnClear(wxCommandEvent& WXUNUSED(event))
{

}

void BoardPanel::OnSolve(wxCommandEvent& WXUNUSED(event))
{

}

void BoardPanel::OnClose(wxCommandEvent& WXUNUSED(event))
{
	// Assume that the parent window is the main frame window
	GetParent()->Close(true);
}

// Display text in the status bar
void BoardPanel::SetStatusText(const wxString &text, int number) {
	wxFrame * frame = dynamic_cast<wxFrame*> (GetParent());
	if (frame != nullptr)
		frame->SetStatusText(text, number);
}

