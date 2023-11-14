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
class Instruction {
public:
    virtual void doSomething(Memory&, Register&, int, int, int&) {}
};
 
class LoadInstruction : public Instruction {
public:
    void doSomething(Memory& memory, Register& registe, int regNum, int address, int& idx) {
        string data = memory.getMemory(address);
        registe.setRegister(regNum, data);
    }
};
 
 
class LoadInstruction1 : public Instruction {
public:
    void doSomething(Memory& memory, Register& registe, int regNum, int address, int& idx) {
        string s = ToHexa(address);
        while(s.size() < 2)
            s = '0' + s;
        registe.setRegister(regNum, s);
    }
};
 
class StoreInstruction : public Instruction {
public:
    void doSomething(Memory &memory, Register& registe, int regNum, int address, int& idx) {
        string data = registe.getRegister(regNum);
        memory.setMemory(address, data);
    }
};
 
class StoreInstruction1 : public Instruction {
public:
    void doSomething(Memory &memory, Register& registe, int regNum, int address, int& idx) {
        string data = registe.getRegister(regNum);
        cout << "Register[" << regNum << "]:  " <<  data << '\n';
    }
};
 
class MoveInstruction : public Instruction {
public:
    void doSomething(Memory &memory, Register& registe, int regNum, int address, int& idx) {
            string RS = ToHexa(address);
            while(RS.size() < 2)
                RS = '0' + RS;
 
            int R = ToInteger(RS.substr(0, 1));
            int S = ToInteger(RS.substr(1, 1));
            string data = registe.getRegister(R);
            registe.setRegister(S, data);
        }
    }
;
 
class AddInstruction : public Instruction {
private:
    string performTwoComplementAddition(int& dataS,int& dataT){
        string result = ToHexa(dataS + dataT);
        return result;
    }
public:
    void doSomething(Memory &memory, Register& registe, int regR, int address, int& idx) {
            string ST = ToHexa(address);
            while(ST.size() < 2)
                ST = '0' + ST;
 
            int regS = ToInteger(ST.substr(0, 1));
            int regT = ToInteger(ST.substr(1, 1));
 
            int dataS =  ToInteger(registe.getRegister(regS));
            int dataT = ToInteger(registe.getRegister(regT));
 
            string result = performTwoComplementAddition(dataS, dataT);
            registe.setRegister(regR, result);
        }
    };
 
 
class JumpInstruction : public Instruction {
public:
    void doSomething(Memory &memory, Register& registe, int regR, int address, int& idx) {
        string dataR = registe.getRegister(regR);
        int i = 0;
        string dataZero = registe.getRegister(i);
 
        if (dataR == dataZero)
            idx = address;
 
    }
};
class HaltInstruction : public Instruction {
public:
    void doSomething(Memory &memory, Register& registe, int regR, int address, int& idx) {
        exit(-1);
        cout << "Halting program execution." << endl;
    }
};
 
 
