#include <bits/stdc++.h>
using namespace std;


class BigReal{
private:
    char sign;
    bool is_fraction;
    string integer, fraction;
public:
    //constractors
    BigReal (double);
    BigReal (const BigReal&);
    BigReal (string);
    //this function to set a bigreal number
    void set_num(string);
    //addition
    BigReal operator+(const BigReal&);
    //subtraction
    BigReal operator-(const BigReal&);
    // >
    bool operator> (const BigReal&);
    // <
    bool operator< (const BigReal&);
    // ==
    bool operator== (const BigReal&);

    // << 
    friend ostream& operator<< (ostream&, BigReal&);
    // ostream operator<<(const BigReal&);
    //this funcion to calc the size of a bigreal number 
    int size();
    //this funcion to get the sign of a bigreal number 
    char ssign();

};











//this function to check if the entered number is a valid one or not
bool is_valid(string s){//022.11
    //check that there is just one decimal point or there is no
    if(count(s.begin(), s.end(), '.') > 1)
        return 0;
    
    //check that each char in the string is a digit or decimal point
    for (int i = 1; i < s.length(); i++)
        if(!((s[i] >= '0' && s[i] <= '9') || s[i] == '.'))
            return 0;
    
    return 1;
}

void BigReal::set_num(string real){
    //initialization of variables
    integer = '0';
    fraction = '0';

    if(is_valid(real)){
        //1- sign operations
        if(real[0] == '+' || real[0] == '-')
            sign = real[0], real[0] = '0';
        else 
            sign = '+';//1.2
        

        //2- integer part operations
        integer = real.substr(0, real.find('.'));
    
        integer.erase(0, integer.find_first_not_of('0'));
        //3- fraction part operations
        //a- first chack if it is fraction number or not
        if(real.find('.') != string::npos)
            is_fraction = 1;
        else 
            is_fraction = 0;
        //if it has a fraction part continue with opratins
        if(is_fraction)
            fraction = real.substr(real.find('.')+1, real.size() - integer.size());
        else
            fraction = '0';
    
    }else{
        cout << "Invalid BigReal number\n";
    }
}


//The constractor
BigReal::BigReal(string real){
    set_num(real);
}

//double constractor
BigReal::BigReal(double other){
    //to_string function is a function that convert the number to string
    string tmp = to_string(other);
    //if the number has no sign add + to it
    if(other >= 0)
        tmp = '+' + tmp;
    //this fuction to set a bigreal number
    set_num(tmp);
}

//this constractor to make one bigreal equals another 
BigReal::BigReal(const BigReal& other){
    integer = other.integer;
    fraction = other.fraction;
    sign = other.sign;
    is_fraction = other.is_fraction;
}




//addition operator overloading // plus overload
BigReal BigReal::operator+(const BigReal& other){
    //initialization of variables
    if(integer.size() == 0) 
        integer = '0';
    if(fraction.size() == 0) 
        fraction = '0';

    BigReal tmp("+.");
    tmp.fraction.clear();
    tmp.integer.clear();
    //1- two bigreals have the same sign
    if(sign == other.sign){
        tmp.sign = sign;
        //fraction addition 
        if(fraction.size() >= other.fraction.size())/*if the two numbers are 0.123456 and 0.12 the tmp.fraction will be 3456*/
            tmp.fraction = fraction.substr(other.fraction.size(), fraction.size()-other.fraction.size());
        else 
            tmp.fraction = other.fraction.substr(fraction.size(), other.fraction.size()-fraction.size());
        //tmp.fraction will be 6543
        reverse(tmp.fraction.begin(), tmp.fraction.end());

        int carry = 0;
        for (int i = min(fraction.size(), other.fraction.size())-1; i >= 0; i--)
        {
            tmp.fraction.push_back(fraction[i]+other.fraction[i]-'0'+carry);
            if(tmp.fraction.back() > '9'){
                tmp.fraction.back() -= 10;
                carry = 1;
            }else
                carry = 0;
        }
        reverse(tmp.fraction.begin(), tmp.fraction.end());
        

        for (int i = 0; i < max(integer.size(), other.integer.size()); i++)
        {
            char c = carry;
            if(i < integer.size())
                c += integer[integer.size() - i - 1];
            if(i < other.integer.size())
                c += other.integer[other.integer.size() - i - 1];
            if(i < integer.size() && i < other.integer.size())
                c -= '0';

            if(c > '9'){
                c -= 10;
                carry = 1;
            }else 
                carry = 0;

            tmp.integer.push_back(c);
        }
        if(carry)
            tmp.integer.push_back(carry+'0');

        reverse(tmp.integer.begin(), tmp.integer.end());
    
    //2- two bigreals have a different sign
    }else{//12.1 - 2.1
        BigReal greatest("+."), smallest("+.");
        greatest.integer.clear();
        greatest.fraction.clear();
        smallest.integer.clear();
        smallest.fraction.clear();

        greatest.integer = integer;
        greatest.fraction = fraction;
        greatest.sign = sign;
        smallest = other;
        
        smallest.sign = sign;

        tmp = greatest - smallest;

    }
    
    return tmp;
}

//this function for comparing two strings
bool cmp(string s, string t, bool is_int){
    if(is_int && s.length() == t.length())
        return s > t;//123.45
    if(is_int)//       123.100000001
        return s.length() > t.length();
    return s > t;
}


//subtraction operator overloading // - overload
BigReal BigReal::operator-(const BigReal& other){
    BigReal tmp("+.");
    tmp.fraction.clear();
    tmp.integer.clear();

    BigReal greatest("+."), smallest("+.");
    greatest.integer.clear();
    greatest.fraction.clear();
    smallest.integer.clear();
    smallest.fraction.clear();

    //1.2 - 5.1
    if(sign != other.sign){
        greatest.integer = integer;
        greatest.fraction = fraction;
        greatest.sign = sign;
        smallest = other;

        smallest.sign = sign;
        tmp = greatest + smallest;
    }else{
        //get the greater bigreal sign and determine the greatest and smallest bigreal number
        if(cmp(integer, other.integer, 1)){
            tmp.sign = sign;
            greatest.integer = integer;
            greatest.fraction = fraction;
            greatest.sign = sign;
            smallest = other;
        }
        else if(integer == other.integer){
            if(cmp(fraction, other.fraction, 0)){
                tmp.sign = sign;
                greatest.integer = integer;
                greatest.fraction = fraction;
                greatest.sign = sign;
                smallest = other;
            }else{//tmp.sign = ('+' + '-' - other.sign)
                tmp.sign = ('+' + '-' - other.sign);
                smallest.integer = integer;//11 - +5464
                smallest.fraction = fraction;
                smallest.sign = sign;
                greatest = other;
            }
        }else{
            tmp.sign = ('+' + '-' - other.sign);
            smallest.integer = integer;
            smallest.fraction = fraction;
            smallest.sign = sign;
            greatest = other;
        }


        //fraction part operations
        int carry = 0;
        for (int i = max(greatest.fraction.size(), smallest.fraction.size())-1; i >= 0; i--)
        {
            char c = carry + '0';
            if(i < greatest.fraction.size())
                c += greatest.fraction[i];
            else        
                c += '0';
            if(i < smallest.fraction.size())
                c -= smallest.fraction[i];
            else 
                c -= '0';
            if(c < '0'){
                c += 10;
                carry = -1;
            }else 
                carry = 0;

            tmp.fraction.push_back(c);
        }
        reverse(tmp.fraction.begin(), tmp.fraction.end());

        //integer part operation
        for (int i = 0; i < max(greatest.integer.size(), smallest.integer.size()); i++)
        {
            char c = carry + '0';
            if(i < greatest.integer.size())
                c += greatest.integer[greatest.integer.size() - i - 1];
            else 
                c += '0';
            if(i < smallest.integer.size())
                c -= smallest.integer[smallest.integer.size() - i - 1];
            else 
                c -= '0';
            
            if(c < '0'){
                c += 10;
                carry = -1;
            }else 
                carry = 0;
            
            tmp.integer.push_back(c);
        }
        reverse(tmp.integer.begin(), tmp.integer.end());
    }

    return tmp;
}


//this funciton to get size of a bigreal number 
int BigReal::size(){
    int ans = integer.size();
    if(is_fraction)//if the number has a fraction add its size to the answer 
        ans += fraction.size() + 1;

    return ans;
}



//this function to get bigreal sign 
char BigReal::ssign(){
    return sign;    
}



// greater than(>) overload
bool BigReal::operator> (const BigReal& other){
    BigReal tmp(0), tmp1(0);
    tmp.integer = integer;
    tmp.fraction = fraction;
    tmp.sign = sign;
    tmp.is_fraction = is_fraction;

    tmp1 = tmp - other;
    // cout << tmp1.sign << " tmp1.sign\n";
    if(tmp1.sign == '+')
        return !(tmp == other); // greater than +,  equal + -,   smaller than -
    else 
        return 0;
}




//smaller than(<) overload
bool BigReal::operator<(const BigReal& other){
    BigReal tmp(0), tmp1(0);
    tmp.integer = integer;
    tmp.fraction = fraction;
    tmp.sign = sign;
    tmp.is_fraction = is_fraction;

    tmp1 = tmp - other;
    // cout << "tmp1: ";
    // tmp1.print();
    // cout << tmp1.sign << " tmp1.sign\n";
    if(tmp1.sign == '-')
        return !(tmp == other);
    else 
        return 0;
}



//equal operator overload
bool BigReal::operator== (const BigReal& other){
    if(other.sign != sign)
        return 0;
    if(other.integer != integer)
        return 0;
    if(other.fraction != fraction)
        return 0;

    return 1;
}


//print operator(<<) overload
ostream& operator<< (ostream& out, BigReal& real){
    out << real.sign << real.integer << '.' << real.fraction;
    return out; 
}
