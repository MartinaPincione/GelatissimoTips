#ifndef TRANSACTION_H
#define TRANSACTION_H
using namespace std;

float tipOptions(){
    cout << "Please select tip percentage: " << endl;
    cout << "(A) 15%" << endl;
    cout << "(B)     20%" << endl;
    cout << "(C)         25%" << endl;
    cout << "(D)             No Tip" << endl;
    char command; cin >> command;
    if (command == 'A') return .15;
    else if (command == 'B') return .2;
    else if (command == 'C') return .25;
    else {
        return 0;
    }
}

float produceTip(float subtotal){
    float tip = tipOptions();
    return subtotal * tip;
}

#endif