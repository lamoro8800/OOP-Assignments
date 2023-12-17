#include <iostream>
#include"../include/BoardGame_Classes.hpp"
using namespace std;


TicTacToeGameManager::TicTacToeGameManager(Board* bPtr, Player* playerPtr[2]) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

void TicTacToeGameManager::run() {
    int x, y;
    boardPtr->display_board();

    while (!boardPtr->game_is_over()) {
        for (int i : {0, 1}) {
            players[i]->get_move(x, y);
            while (!boardPtr->update_board(x, y, players[i]->get_symbol()) || (x == 0 && y == 0) ||
            (x == 0 && y == 1) || (x == 0 && y == 3) || (x == 0 && y == 4) ||
            (x == 1 && y == 0) || (x == 1 && y == 4)) {
                // cout << "Invalid choice. Please choose again.\n";
                players[i]->get_move(x, y);
            }
            boardPtr->display_board();
            if (boardPtr->is_winner()) {
                cout << '\n' << players[i]->to_string() << " wins\n";
                return;
            }
            if (boardPtr->is_draw()) {
                cout << "\nDraw!\n";
                return;
            }
        }
    }
}
