// Class definition for XO_App class
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1

#include <iostream>
#include"../include/BoardGame_Classes.hpp"
using namespace std;

int main() {
    int choice, op;
    Player* players[2];
    cout << "\nWelcome to FCAI X-O Game. :)\n";
    cout << "Choose a game to play:\n";
    cout << "1- Tic-Tac-Toe\n";
    cout << "2- Foun in a row\n";
    cout << "3- Five by five\n";
    cin >> op; 
    //1 X O game
    if(op == 1){
        //create the first player from type Player
        players[0] = new Player(1, 'x');
        cout << "Press 1 if you want to play with computer: ";
        int computerChoice;
        cin >> computerChoice;

        if (computerChoice == 1)
            players[1] = new RandomPlayer('o', 3);
        else
            players[1] = new Player(2, 'o');

        TicTacToeGameManager tic_tac_toe_game(new Tic_Tac_Toe_board(), players);
        tic_tac_toe_game.run();

    //2 four in a row game
    }else if(op == 2){
        //create the first player from type Player_FourIAR -> FourIAR is for Four In A Row 
        players[0] = new FourIAR_Player(1, 'x');
        cout << "Press 1 if you want to play with computer: ";
        int computerChoice;
        cin >> computerChoice;

        if (computerChoice == 1)
            players[1] = new FourIAR_RandomPlayer('o', 7);
        else
            players[1] = new FourIAR_Player(2, 'o');

        GameManager fourIAR_game(new FourIAR_board(), players);
        fourIAR_game.run();
    //3 five by five game
    }else if(op == 3){
        //create the first player from type Player
        players[0] = new Player(1, 'x');
        cout << "Press 1 if you want to play with computer: ";
        int computerChoice;
        cin >> computerChoice;

        if (computerChoice == 1)
            players[1] = new RandomPlayer('o', 5);
        else
            players[1] = new Player(2, 'o');

        GameManager fiveBF_game(new FiveBF_board(), players);
        fiveBF_game.run();
    }else if(op == 0)
        return 1;
    else 
        cout << "Invalid choice\n";

    //0 to exit
    // system ("pause");
}


/*
Code Run: g++ FiveBF_board.cpp FourIAR_board.cpp FourIAR_Player.cpp FourIAR_RandomPlayer.cpp GameManager.cpp Main_App.cpp Player.cpp RandomPlayer.cpp Tic_Tac_Toe_board.cpp TicTacToeGameManager.cpp
*/
