#include<iostream>
#include<random>
#include<iomanip>
#include<algorithm>
#include"../include/BoardGame_Classes.hpp"
using namespace std;

void FourIAR_RandomPlayer::get_move(int& x, int& y){
    x = (int) (rand()/(RAND_MAX + 1.0) * dimension);
}
