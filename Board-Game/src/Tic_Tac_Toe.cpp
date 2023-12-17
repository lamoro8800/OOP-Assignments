#include <bits/stdc++.h>
#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
#include "../include/BoardGame_Classes.hpp"
using namespace std;

Tic_Tac_Toe_board::Tic_Tac_Toe_board(){
    n_rows = 3;
    n_cols = 5;
    board = new char*[n_rows];

    for (int i = 0; i < n_rows; ++i) {
        board[i] = new char[n_cols];

        for (int j = 0; j < n_cols - i - 1; ++j) {
            board[i][j] = ' ';
        }

        // Initialize each cell with a space
        for (int k = 0; k < 2 * i + 1; ++k) {
            board[i][k + n_cols - i - 1] = ' ';
        }
    }

}

bool Tic_Tac_Toe_board::update_board(int x, int y, char mark){
    if (!(x < 0 || x >= n_rows || y < 0 || y >= n_cols) && (board[x][y] == ' ') && !((x == 0 && y != 2) || (x == 1 && y == 0) || (x == 1 && y == 4))) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    } else {
        return false;
    }
}
void Tic_Tac_Toe_board:: display_board() {
    for (int i = 0; i < n_rows; i++)
    {
        if(i == 0)
            cout << '\n' << setw(18) << "| ";
        else if(i == 1) 
            cout << '\n' << setw(10) << "| ";
        else
            cout << "\n| ";   
        for (int j = 0; j < n_cols; j++)
        {
            if((i == 0 && j != 2) || (i == 1 && j == 0) || (i == 1 && j == 4))
                continue;
            if(board[i][j] != ' ')
                cout << "  " << board[i][j] << "   ";
            else 
                cout << "(" << i << "," << j << ") ";
            cout << "| ";
        }
        cout << '\n';
        if(i == 0)
            cout << setw(25) << "---------";
        else if(i == 1) 
            cout << setw(33) << "-------------------------";
        else 
            cout << "-----------------------------------------";
    }
    
}
bool Tic_Tac_Toe_board::is_winner() {
    if (board[1][1] == board[1][2] && board[1][2] == board[1][3] && board[1][1]!= ' ') {
        return true;
    } else if (board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][1]!= ' ') {
        return true;
    } else if (board[2][1] == board[2][2] && board[2][2] == board[2][3]  && board[2][2]!= ' ') {
        return true;
    } else if (board[2][3] == board[2][4] && board[2][4] == board[2][2] && board[2][3]!= ' ') {
        return true;
    } else if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1]!= ' ') {
        return true;
    } else if (board[0][2] == board[1][3] && board[1][3] == board[2][4]&& board[1][3]!= ' ') {
        return true;
    } else if (board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[0][2]!= ' ') {
        return true;
    }

    return false;
}
bool Tic_Tac_Toe_board::is_draw() {
    return (n_moves == 9 && !is_winner());
}

bool Tic_Tac_Toe_board::game_is_over () {
    return n_moves >= 9;
}
void Tic_Tac_Toe_board::get_move(int& x, int& y) {
        cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
        cin >> x >> y;

}
