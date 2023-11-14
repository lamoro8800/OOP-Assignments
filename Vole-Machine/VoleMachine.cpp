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
 


// Memory methods implementation
Memory::Memory(){
    m.reserve(256);
}
void Memory::setMemory(int& address, string s){
    m[address] = s;
    address++;
}
string Memory::getMemory(int& i){
    return m[i];
}
void Memory::clearCell(int& address) {
    m[address] = "00";
}



//Register methods implementation
Register::Register(){
    r.resize(16);
}
void Register::setRegister(int& address, string s){
    r[address] = s;
    address++;
}
string Register::getRegister(int& i){
    return r[i];
}
void Register::clearCell(int& address) {
    r[address] = "00";
}



//Machine methods implementation
//Machine constructor
Machine::Machine(){
    //set memory with "00"
    for (int i = 0; i < 256;)
        storage.setMemory(i, "00");

    //set the register with "0";
    for (int i = 0; i < 16;)
        processor.setRegister(i, "00");

    addingAddress = 0;
    programIndex = 0;
}

//this method gets a new instruction as an input
void Machine::getNewIstrauction(){
    string s;
    cout << "Enter the new instrauction: ";
    cin >> s;
    string tmp = s.substr(0, 2);
    storage.setMemory(addingAddress, tmp);
    tmp = s.substr(2, 2);
    storage.setMemory(addingAddress, tmp);

}

//this method gets instructions from file and set it in the memory
void Machine::loadFromFile(){
    string Input;
    cout << "Enter file name: ";
    cin >> Input;
    Input += ".txt";
    //open the file
    ifstream file(Input);
    //checking if it open or not
    if(!file.is_open()){
        cout << "Error: Couldn't open the file " << Input << endl;
        return;
    }

    string tmp, tmp1;
    while (!file.eof())
    {
        file >> tmp;
        //Usually the hexadecimal number is like 0xff, so I want to take "ff" only and set "ff" in the memory.
        if(tmp.size() == 3)
            tmp1.push_back(tmp[2]);
        else
            tmp1 = tmp.substr(2, 2);

        if(tmp1.size() == 2)
            storage.setMemory(addingAddress, tmp1), tmp1.clear();

    }
    file.close();
}


//run instructions funcion
void Machine::runInstructions(){
    int cnt = 0;
    while(addingAddress - programIndex >= 2){//there is at least 1 instruction (2 idexes) between them this is valid otherwise it is invalid
        cnt++;
        string instr;
        instr += storage.getMemory(programIndex);
        programIndex++;
        instr += storage.getMemory(programIndex);
        programIndex++;

        Instruction* ptr;
        //instruction options
        if(instr.front() == '1')
            ptr = new LoadInstruction;
        else if(instr.front() == '2')
            ptr = new LoadInstruction1;
        else if(instr.front() == '3'){
            if (instr.substr(2, 2) == "00") 
                ptr = new StoreInstruction1();
            else 
                ptr = new StoreInstruction();
        }

        else if(instr.front() == '4')
            ptr = new MoveInstruction();
        else if(instr.front() == '5')
            ptr = new AddInstruction();
        else if(instr.front()=='B')
            ptr = new JumpInstruction ;
        if (instr.front() == 'C') 
            ptr = new HaltInstruction();
        else{
            cout << "Invalid instruction!\n\n";
            return;
        }
        int i = ToInteger(instr.substr(1, 1));
        int j = ToInteger(instr.substr(2, 2));
        ptr->doSomething(storage, processor, i, j, programIndex);
    }
    if(!cnt)
        cout << "Invalid instruction\n\n";
}
//this function used to print the Memory on the screen
void Machine::displayMemory(){
    cout << "Memory:\n";
    for (int i = 0; i < 256; i++)
        cout << setw(3) << i << "-  " << storage.getMemory(i) << '\n';
    //setw for set width this is a function to align the output
}
// this function used to print the Register on the screen
void Machine::displayRegister(){
    cout << "Register:\n";
    for (int i = 0; i < 16; i++)
        cout << setw(3) << i << "-  " << processor.getRegister(i) << '\n';

}
