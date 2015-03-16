#ifndef BOARDPANEL_H
#define BOARDPANEL_H

#include <fstream>
#include <vector>
#include "csCharCtrl.h"

using namespace std;
//class BoardData;

// window id's for handling of squares and buttons events
const int ID_Square_Start = 10000; // First window id for the squares
const int ID_Square_End = ID_Square_Start + 81; // Last window id for the squares

const int ID_Buttons_Start = ID_Square_End + 1;
const int ID_Check   = ID_Buttons_Start + 1;
const int ID_Clear   = ID_Buttons_Start + 2;
const int ID_Close   = ID_Buttons_Start + 3;
const int ID_Solve   = ID_Buttons_Start + 4;
const int ID_Hint    = ID_Buttons_Start + 5;
const int ID_New    = ID_Buttons_Start + 6;
static vector<vector<int>> board(9, vector<int>(9));
static int boardIndexCounter=0;
class BoardPanel: public wxPanel {
    public:
        BoardPanel(wxFrame *parent/*, BoardData &data*/);
    private:
        void CreateBoard();
        csCharCtrl *CreateSquare(wxPanel *panel, int nbr, int row, int col);

        // event handlers for text input fields
        void OnChildFocus(wxChildFocusEvent& event);

        // event handlers for buttons
        void OnNew(wxCommandEvent& WXUNUSED(event));
        void OnCheck(wxCommandEvent& WXUNUSED(event));
        void OnHint(wxCommandEvent& WXUNUSED(event));
        void OnSolve(wxCommandEvent& WXUNUSED(event));
        void OnClear(wxCommandEvent& WXUNUSED(event));
        void OnClose(wxCommandEvent& WXUNUSED(event));


        // Logging to the status bar
        void SetStatusText(const wxString &text, int number = 0);

        // text input fields
        csCharCtrl *m_square[81]; // index by row, col
        static const int sz = 50;

        // current text input field
        csCharCtrl *currentsquare;

        void setBoard(vector<vector<int>> &board);
//	BoardData &model;
    };


#endif // BOARDPANEL_H
