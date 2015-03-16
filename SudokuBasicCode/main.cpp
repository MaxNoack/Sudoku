#include <iostream>
#include <vector>
#include <fstream>
#include "windows.h"
#include <time.h>
#include <cstdlib>
#include <iomanip>
#include <algorithm>

using namespace std;
vector<vector<int>> board(9, vector<int>(9));
vector<vector<int>> sBoard(9, vector<int>(9));
int boardIndexCounter=0;

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

vector<int> generateRandomNumbers(int tiles) {    //genererar slumpad vector med tiles antal brickor.
    srand (time(NULL));
    vector<int> numbers;
    for (int i=1; i<=tiles; i++) numbers.push_back(i);    //lägger till i vektorn 0-15
    random_shuffle (numbers.begin(), numbers.end());   //blandar.
    return numbers;
}


bool in3x3Box(int row, int col, int value) {
    int startRow = row / 3 * 3;
    int startCol = col / 3 * 3;

    for (int i = startRow; i < startRow + 3; i++)
        for (int j = startCol; j < startCol + 3; j++) {
            if (!(i == row && j == col)) {
                if (sBoard[i][j] == value) {
                    return true;
                }
            }
        }
    return false;
}

bool inRowCol(int row, int col, int value) {
    for (int i = 0; i < 9; i++) {

        if (i != col)
            if (sBoard[row][i] == value)
                return true;
        if (i != row)
            if (sBoard[i][col] == value)
                return true;
    }
    return false;
}

void setEquals(vector<vector<int>> &a, vector<vector<int>> &b) {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            b[i][j]= a[i][j];
        }
    }
}

//solves sBoard
bool solve(int row = 0, int col = 0) {
    if (row == 9)
        return true;

    if (sBoard[row][col] != 0) {
        if (solve(col == 8? (row + 1): row, (col + 1) % 9))
            return true;
    } else {
        //Random numbers 1 - 9
        vector<int> randoms = generateRandomNumbers(9);
        for (int i = 0; i < 9; i++) {

            if (!inRowCol(row, col, randoms[i]) &&
                    !in3x3Box(row, col, randoms[i])) {
                sBoard[row][col] = randoms[i];

                if (solve(col == 8? (row + 1) : row, (col + 1) % 9))
                    return true;
                else {
                    sBoard[row][col] = 0;
                }
            }
        }
    }
    return false;
}

void hint() {
    setEquals(board, sBoard);
    if(solve()){
    srand (time(NULL));
    int randrow;
    int randcol;
    bool found = false;
    while(!found) {
        randrow = rand()%9 + 1;
        randcol = rand()%9 + 1;
        if(board[randrow][randcol]==0) {
            board[randrow][randcol] = sBoard[randrow][randcol];
            found = true;
        }
    }
}
else cout << "No solution";
}

bool check() {
    setEquals(board, sBoard);
    return solve();
}

int main() {

    //Creates and prints the board from file.
    setBoard(board);
    cout << "Random board from file:" << endl << endl;
    for(int row=0; row<9; row++) {
        for(int col=0; col<9; col++) {
            cout << board[row][col];
            if(col == 8) cout << endl;
        }
    }
    cout << endl;

    //Set a random cell to a correct value
    hint();
    cout << "Board after hint (one cell is changed):" << endl << endl;
    for(int row=0; row<9; row++) {
        for(int col=0; col<9; col++) {
            cout << board[row][col];
            if(col == 8) cout << endl;

        }
    }
    cout << endl;

    //solving the puzzle
    setEquals(board, sBoard);
    cout << "Solution (if any): " << endl << endl;

    if(solve()) {
        for(int row=0; row<9; row++) {
            for(int col=0; col<9; col++) {
                cout << sBoard[row][col];
                if(col == 8) cout << endl;

            }
        }
    } else cout << "No solution!";
}


