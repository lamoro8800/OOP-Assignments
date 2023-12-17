// File name: FourIAR_board.cpp
// Purpose: Four-in-a-row
// Author(s): Ahmed Ashraf
// ID(s): 20230606
// Section: S27
// Date: 13 Dec 2023
#include <bits/stdc++.h>
#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
#include "../include/BoardGame_Classes.hpp"
using namespace std;

// Set the board
FourIAR_board::FourIAR_board () {
   n_rows = 6;
   n_cols = 7;
   board = new char*[n_rows];
   for (int i = 0; i < n_rows; i++) {
      board [i] = new char[n_cols];
      for (int j = 0; j < n_cols; j++)
         board[i][j] = '0';
   }
}

// Return true  if move is valid and put it on board
// within board boundaries in empty cell
// Return false otherwise
bool FourIAR_board::update_board (int x, int y, char mark){
   // Only update if move is valid
   if ((x >= 0 && x <= 6) && (used_squares[x] < 6)) {
      board[5-used_squares[x]][x] = toupper(mark);
      n_moves++;
      used_squares[x]++;
      return true;
   }
   else
      return false;
}

// Display the board and the pieces on it
void FourIAR_board::display_board() {
   for (int i = 0; i < n_rows; i++)
   {
      cout << "\n| ";
      for (int j = 0; j < n_cols; j++)
      {
         if(board[i][j] != '0')
            cout << "  " << board[i][j] << "   ";
         else
            cout << "(" << i << "," << j << ") ";
         cout << "| ";
      }
      cout << "\n---------------------------------------------------------";
   }

}

bool FourIAR_board::checkingIsWinner(int x, int y){
   int freq[256]{};
   for (int i = x; i < min(x+4, 6); i++)
   {
      char c = board[i][y];
      if(c != '0')
         freq[c]++;
   }
   if (freq['X'] == 4 || freq['O'] == 4)
      return 1;
   memset(freq, 0, sizeof(freq));
   for (int i = y; i < min(y+4, 7); i++)
   {
      char c = board[x][i];
      if(c != '0')
         freq[c]++;
   }
   if (freq['X'] == 4 || freq['O'] == 4)
      return 1;
   memset(freq, 0, sizeof(freq));
   int cnt = 0;
   while(x < 6 && y < 7 && cnt != 4){
      if(board[x][y] != '0')
         freq[board[x][y]]++;
      x++;
      y++;
      cnt++;
   }
   return (freq['X'] == 4 || freq['O'] == 4);
}
// Returns true if there is any winner
// either X or O
// Written in a complex way. DO NOT DO LIKE THIS.
bool FourIAR_board::is_winner() {
   for (int i = 0; i < n_rows; i++)
      for (int j = 0; j < n_cols; j++)
         if(checkingIsWinner(i, j))
            return 1;
   return 0;
}

// Return true if 9 moves are done and no winner
bool FourIAR_board::is_draw() {
   return (n_moves == 6*7 && !is_winner());
}

bool FourIAR_board::game_is_over () {
   return n_moves >= 6*7;
}
