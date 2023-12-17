#include <iostream>
#include"../include/BoardGame_Classes.hpp"
using namespace std;

void FourIAR_Player::get_move(int& x, int& y){
    cout << "\nPlease enter which number of column do you want to play (0 to 6): ";
    cin >> x;
}

string FourIAR_Player::to_string(){
    return name;
}
