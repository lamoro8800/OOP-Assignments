#include <bits/stdc++.h>
#include "VoleMachine.cpp"
using namespace std;

int main(){
    Machine m1;
    int op;
    char continue1;
    do{
        cout << "\n\nEnter one of these options or 0 to exit\n";
        //1- enter a new instruction
        cout << "1- enter a new instruction\n";
        //2- load from file
        cout << "2- load from file\n";
        //3- run the instructions
        cout << "3- run the instructions\n";
        //4- display the memory
        cout << "4- display the memory\n";
        //5- display the register
        cout << "5- display the register\n";

        cin >> op;//get an option
        if(op == 1)
            m1.getNewIstrauction();
        else if(op == 2)
            m1.loadFromFile();
        else if(op == 3)
            m1.runInstructions();
        else if(op == 4)
            m1.displayMemory(), cout << "\n\n";
        else if(op == 5)
            m1.displayRegister(), cout << "\n\n";
        else if(op == 0)
            return 0;
        else
            cout << "Invalid option\n";

        cout << "Do you want to continue(y/n)?";
        cin >> continue1;
    }while(continue1 == 'y' || continue1 == 'Y');
}
