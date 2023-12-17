// File name: FiveBF_board.cpp
// Purpose: 5 x 5 Tic Tac Toe
// Author(s): Alaa Eldin Hassan Ahmed
// ID(s): 20230615
// Section: S27
// Date: 14 Dec 2023
#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
#include "../include/BoardGame_Classes.hpp"
using namespace std;

FiveBF_board::FiveBF_board ()
{
    n_rows = n_cols = 5;
    board = new char*[n_rows];
    for (int i = 0; i < n_rows; i++)
    {
        board [i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = 0;
    }
}
bool FiveBF_board::update_board (int x, int y, char mark)
{
    // Only update if move is valid
    if (!(x < 0 || x >= 5 || y < 0 || y >= 5) && (board[x][y] == 0))
    {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    else
        return false;
}

// Display the board and the pieces on it
void FiveBF_board::display_board()
{
    for (int i = 0; i < n_rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < n_cols; j++)
        {
            if(board[i][j] != 0)
                cout << "  " << board[i][j] << "   ";
            else
                cout << "(" << i << "," << j << ") ";
            cout << "| ";
        }
        cout << "\n-----------------------------------------"<<endl;
    }
}
bool FiveBF_board::is_winner()
{
    if(n_moves==24)
    {
        char u='X';
        for(int z=0; z<2; z++)
        {
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j <5; j++)
                {
                    // Check rows
                    if ( j + 2 < 5&&board[i][j] == u && board[i][j + 1] == u && board[i][j + 2] == u)
                    {
                        player[z]++;
                    }
                    //Check columns
                    if ( j + 2 < 5&&board[j][i] == u && board[j + 1][i] == u && board[j + 2][i] == u)
                    {
                        player[z]++;
                    }
                    //Check the main diagonal
                    if ( i + 2 < 5 && j + 2 < 5&&board[i][j]==u && board[i+1][j+1]==u&& board[i+2][j+2]==u )
                    {
                        player[z]++;
                    }

                    //Check the anti diagonal
                    if(i + 2 < 5 && j - 2 >=0 &&board[i][j]==u && board[i+1][j-1]==u&&board[i+2][j-2]==u)
                    {
                        player[z]++;
                    }
                }
            }
            u = 'O';
        }
        if( player[0]>player[1])
        {
            cout<<"X is winner"<<endl;
        }
        else if (player[0]<player[1])
        {
            cout<<"O is winner"<<endl;
        }
    }
    return false;
}

bool FiveBF_board::is_draw()
{
    if(n_moves==24)
    {
        return (player[0]==player[1]);
    }
    return false;
}

bool FiveBF_board::game_is_over ()
{
    return n_moves >= 24;
}
