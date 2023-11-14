#include <bits/stdc++.h>
using namespace std;
 
 
//Memory class
//attributes: vector <string> m
//functions: constructor, setMemory, clearCell
class Memory {
private:
    vector <string> m;
public:
    Memory();
    void setMemory(int&, string);
    string getMemory(int&);
    void clearCell(int&);
};
 
 
//Register class
//attributes: vector <string> r
//functions: constructor, setRegister, clearCell
class Register {
private:
    vector <string> r;
public:
    Register();
    void setRegister(int&, string);
    string getRegister(int&);
    void clearCell(int&);
};

//Machine class
//attributes: processor, storage, addingAddress, programIndex
//functions: constructor, getNewInstruction, loadFromFile, runInstructions, displayMemory, displayRegister
class Machine{
protected:
    Register processor;
    Memory storage;
    int addingAddress;
    int programIndex;
public:
    Machine();
    void getNewIstrauction();
    void loadFromFile();
    void runInstructions();
    void displayMemory();
    void displayRegister();
};



//this function convert Hexadecimal to Integer
int ToInteger(string s){
    return stoi(s, 0, 16);
}
//this function convert Integer to Hexadecimal
string ToHexa(int n){
    stringstream ss;
    ss << hex << n;
    string tmp;
    ss >> tmp;
    //convert lowercase to uppercase
    for (int i = 0; i < tmp.size(); i++)
        if(tmp[i] >= 'a' && tmp[i] <= 'z')
            tmp[i] -= 32;

    return tmp;
}


//instruction part
