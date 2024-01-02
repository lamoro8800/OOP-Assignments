#include <bits/stdc++.h>
#include "BigReal.h"

using namespace std;

int main(){
    // stirng s;
    // cin >> s;
    // BigReal b0(s);


    BigReal b1("-9.156");
    BigReal b2("-9.156");
    BigReal b3 = b1 + b2;


    cout << "b1 equal: " << b1 << '\n';
    cout << "b2 equal: " << b2 << '\n';
    cout << "b3 equal: " << b3 << '\n';


    if(b1 > b2)
        cout << "b1 is greater than b2\n";
    else if(b1 < b2)
        cout << "b1 is smaller than b2\n";
    else
        cout << "are equals\n";

}
