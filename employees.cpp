#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <unistd.h>
#include <list>
#include "transaction.h"

#define SMALL_BUSINESS 30
#define MEDIUM_BUSINESS 50
#define LARGE_BUSINESS 100

using namespace std;

class Employee{
private:
    double taxableTip;
    //clock_t taxableTime; //time is currently represented in ticks    
protected:  //makes the following accessible to classes that inherit from this class
    int taxableTime;
public:
    bool active;
    int employeeID;
    string name;
    Employee(){
        name = "EMPTY SPOT";
        employeeID = 0;
        active = false;
        taxableTime = 0.0;
        taxableTip = 0.0;
    }

    Employee(string Name, int EmployeeID ){ 
        name = Name;
        employeeID = EmployeeID;
        active = false;
        taxableTime = 0.0;
        taxableTip = 0.00;
    }

    void GetInfo(){
        cout << "Employee ID: " << employeeID << endl;
        cout << "Name: " << name << endl;
        cout << "Active: ";
        if (active == 0){
            cout << "false" << endl;
        }
        else{
            cout << "true" << endl;
        }
        cout << "Taxable Time: " << taxableTime << " seconds" << endl;
        cout << "Taxable Tips: $" << taxableTip << endl;
    }

    void AddTips(float amnt){
        taxableTip+= amnt;
    }

    void checkAnalytics(){
        if (taxableTime > 30){
            cout << name << " has reached overtime pay at " << taxableTime << " ticks." << endl;
        }
        else{
            cout << name << " has not yet reached overtime pay at " << taxableTime << " ticks." << endl;
        }
    }
    virtual void clockIn() = 0; // virtual function: if there is an implementation of this in a derived class, execute the derived implementation
    virtual void clockOut() = 0;

};


class salesAssociate: public Employee { //employees inherits Person class
public:
    salesAssociate(string Name, int EmployeeID): Employee(Name, EmployeeID){}

    void clockIn(){
        taxableTime = clock();
        cout << name << " has clocked in for a shift as sales associate at Gelatissimo." << endl;
    }
    void clockOut(){
        taxableTime = clock() - taxableTime;
        cout << name << " has clocked out with a time of: " << taxableTime << endl;
    }

};

class manager: public Employee { //employees inherits Person class
public:
    manager(string Name, int EmployeeID): Employee(Name, EmployeeID){}

    void clockIn(){
        taxableTime = clock();
        cout << name << " has clocked in for a shift as a manager at Gelatissimo." << endl;
    }
    void clockOut(){
        taxableTime = clock() - taxableTime;
        cout << name << " has clocked out with a time of: " << taxableTime << endl;
    }

};

ostream& operator<<(ostream& COUT, Employee& employ){           //operator overloading 
    COUT << "Employee : " << employ.name << endl;
    return COUT;
}



Employee* addAccount(){
    string n;
    int id;
    char role;
    cout << "Please enter your name: ";  cin >> n;
    cout << "\n";
    cout << "Please enter a four digit ID: "; cin >> id;
    cout << "Are you a manager (M) or a sales associate (S): "; cin >> role;
    if (role == 'S') return new salesAssociate(n, id);
    else if (role == 'M') return new manager(n, id);
    else{
        cout << "The command you have entered is not valid. Please try again." << endl;
        return addAccount();
    }
}


void printMenu(){
    cout << "Please choose an action: " << endl;
    cout << "(A) Add employee account" << endl;
    cout << "(I) Clock-In" << endl;
    cout << "(O) Clock-Out" << endl;
    cout << "(D) Distribute tips" << endl;
    cout << "(V) View Analytics" << endl;
    cout << "(T) Terminate program" << endl;
}

/* COVERT TICKS TO HRS 
int clocktoMins(){

}
*/


int main(){

    int businessSize, curSize = 0;
    cout << "Please enter the size of your business to build your employee program: ";  cin >> businessSize;
    if (businessSize <= SMALL_BUSINESS) businessSize = SMALL_BUSINESS;
    else if (businessSize <= MEDIUM_BUSINESS) businessSize = MEDIUM_BUSINESS;
    else if (businessSize <= LARGE_BUSINESS) businessSize = LARGE_BUSINESS;
    else{
        cout << "Your business is too large for this small scale program." << endl; 
        cout << "Program terminating." << endl;
        return 0;
    }
    Employee* gelatissimo[businessSize];    

    while(1){
        int id; char command;
        printMenu(); cin >> command;
        if (command == 'I'){
            cout << "Please input your employee ID: "; cin >> id;
            for (int i =0; i< curSize; i++){
                if (gelatissimo[i]->employeeID == id) gelatissimo[i]->clockIn();
            }
        }
        else if (command == 'O'){
            cout << "Please input your employee ID: "; cin >> id;
            for (int i =0; i< curSize; i++){
                if (gelatissimo[i]->employeeID == id) gelatissimo[i]->clockOut();
            }
        }
        else if (command == 'V'){
            cout << "Please input your employee ID: "; cin >> id;
            for (int i = 0; i< curSize; i++){
                if (gelatissimo[i]->employeeID == id) gelatissimo[i]->checkAnalytics();
            }
        }
        else if (command == 'A'){
            gelatissimo[curSize] = addAccount();
            curSize++;
        }
        else if (command == 'D'){
            float subtotal, tipAmnt;
            int employCnt = 0;
            Employee* employees[curSize];
            cout << "Enter the subtotal for which you would like to process tip information: "; cin >> subtotal;
            tipAmnt = produceTip(subtotal);
            for (int i =0; i< curSize; i++){
                if (gelatissimo[i]->active == true){
                    employees[employCnt++] = gelatissimo[i];
                }
            float distributeTip = tipAmnt / employCnt;
            for (int i = 0; i < employCnt ; i++){
                employees[i]->AddTips(distributeTip);
            }
            }
        }
        else if (command == 'T') break;
    }
    cout << "Program terminating." << endl;
    return 0;
}


/*
    salesAssociate salesAssoc1("Baddie", 1234);
    manager manager1("Shorty", 5678);

                                     // polymorphism
    Employee* emply1 = &salesAssoc1; // creating pointers to use the most derived version of a method
    Employee* emply2 = &manager1;
    Employee* emply3 = new manager("Bawdy", 9100); //virtual function
    Employee* emply4 = new salesAssociate("Nicholas", 1213);

    Employee* employees[4] = {emply1, emply2, emply3, NULL};

    cout << salesAssoc1;             // also works with : operator << (cout, manager1);
    */
