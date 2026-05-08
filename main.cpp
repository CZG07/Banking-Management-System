#include <iostream>
#include <string>
#include"blablabla.h"
#include<iomanip>
#include<cstdlib>
#include<limits>
#include<random>
#include<thread>
#include<chrono>
#include<windows.h>
using namespace std;

//Error handling
void clearInput() {
    cin.clear();
    cin.ignore(10000,'\n');
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}
void pauseAndClear() {
    cout<<"Press Enter to return to menu...";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin.get();
    clearScreen();
}
int generateRandomNumber() {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(100000000,999999999);

    int acc;
    do {
        acc=dist(gen);
    }while (searchAcc(acc)!=nullptr);

    return acc;
}

void typeWriter(const string& text, int delay=20) {
    for (char c: text) {
        cout<<c<<flush;
        Sleep(delay);
    }
    cout<<endl;
}

int main() {
    clearScreen();
    
    int choice;
    while (true){
    cout<<"\n--------------------Banking System--------------------"<<endl;
    cout<<"1. Add new account"<<endl;
    cout<<"2. Delete account"<<endl;
    cout<<"3. Search account"<<endl;
    cout<<"4. Deposit"<<endl;
    cout<<"5. Withdraw"<<endl;
    cout<<"6. Transfer"<<endl;
    cout<<"7. Undo transaction"<<endl;
    cout<<"8. Show transaction history"<<endl;
    cout<<"9. Show all account"<<endl;
    cout<<"0. Exit"<<endl;
    cout<<"Enter Choice:";
        if (!(cin>>choice)) {
            cout<<"Error: Invalid number! Please enter digit 0-9."<<endl;
            clearInput();
            pauseAndClear();
            continue;
        }
        if (choice==0)break;
        if (choice<0||choice>9) {
            cout<<"Error:Please enter a number between 0 and 9."<<endl;
            pauseAndClear();
            continue;

        }


    if (choice==1) {

        typeWriter("\nYou are creating a new bank account.");
        string name;
        double bal;
        int acc = generateRandomNumber();
        cout<<"Generated Account Number(9 digits): "<<acc<<endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        typeWriter("Please enter your name and initial deposit amount.");

        cout<<"Enter name:";
        getline(cin,name);

        cout<<"Enter amount: RM";
        if (!(cin>>bal)) {
            cout<<"Error: Invalid amount entered."<<endl;
            clearInput();
            pauseAndClear();
            continue;
        }
        if (bal<=0) {
            cout<<"Error: Amount must be positive."<<endl;
            pauseAndClear();
            continue;
        }

        addNew(acc,name,bal);
        cout<<"Account added!\n";

        pauseAndClear();

    }else if (choice==2) {
        typeWriter("\nDelete an existing account.");
        int acc;
        cout<<"Enter your account number to proceed: ";

        if (!(cin>>acc)||acc<100000000||acc>999999999) {
            typeWriter("Error: Account number must be 9 digit value!");

            clearInput();
            pauseAndClear();
            continue;
        }

        Account* accPtr = searchAcc(acc);
        if (accPtr != nullptr) {
            cout<<"\nAccount Found:"<<endl;
            cout<<"Name: "<<accPtr->name<<endl;
            cout<<"Balance: "<<accPtr->balance<<endl;

            char confirm;
            cout<<"\nDeletion account confirmation:(Y/N)";
            cin>>confirm;

            if (confirm=='Y'||confirm=='y') {
                deleteAcc(acc);
            }else {
                cout<<"Deleted cancelled. No changes made.";
            }
        }else {
              cout<<"Error: Account "<<acc<<" not found"<<endl;
            }
        pauseAndClear();
        }

    else if (choice==3) {
        int acc;
        typeWriter("\nEnter your account number to view information.");
        cout<<"Account number:";
        if (!(cin>>acc)) {
            cout<<"Error: Account number must be 9 digit value!"<<endl;
            clearInput();
            continue;
        }
        typeWriter("Search for account details...");
        Account* result=searchAcc(acc);

        if (result != nullptr) {
            cout<<"Account found:\n"<<endl;
            cout<<"Name: "<<result->name<<endl;
            cout<<"Balance: RM"<<result->balance<<endl;
        }else {
            cout<<"Account not found!\n"<<endl;
        }

        pauseAndClear();

    }else if (choice==4) {
        typeWriter("\nDeposit money into your account.");
        int acc;
        double amount;
        cout<<"Enter account number:";
        if (!(cin>>acc)) {
            cout<<"Error: Account number must be 9 digit value!"<<endl;
            clearInput();
            continue;
        }
        cout<<"Enter deposit amount: RM";
        if (!(cin>>amount)) {
            cout<<"Error: Invalid amount entered."<<endl;
            clearInput();
            continue;
        }
        if (amount<=0) {
            cout<<"Error: Amount must be positive."<<endl;
            pauseAndClear();
            continue;
        }

        if (deposit(acc,amount)){
            transaction t;
            t.transType = "Deposit";
            t.transAmount = amount;
            t.fromAcc = acc;
            t.toAcc = 0;
            pushTransaction(t);
            cout<<"Deposit successful.\n"<<endl;
        }else {
            cout<<"Deposit failed: Invalid account or system error...";
        }

        pauseAndClear();
    }

    else if (choice==5) {
        typeWriter("\nWithdraw money from your account.");
        typeWriter("Ensure sufficient balance before withdrawal.");
        int acc;
        double amount;

        cout<<"Enter account number:";
        if (!(cin>>acc)) {
            cout<<"Error: Invalid input!"<<endl;
            clearInput();
            continue;
        }

        cout<<"Enter amount: RM";
        if (!(cin>>amount)) {
            cout<<"Error: Invalid amount entered!"<<endl;
            clearInput();
            continue;
        }
        if (amount<=0) {
            cout<<"Error: Amount must be positive."<<endl;
            pauseAndClear();
            continue;
        }

        Account* a=searchAcc(acc);
        if (a != nullptr && a->balance >=amount) {
            a->balance-=amount;

            transaction t;
            t.transType = "Withdraw";
            t.transAmount = amount;
            t.fromAcc = acc;
            t.toAcc = 0;

            pushTransaction(t);
            cout<<"Withdraw successful!\n"<<endl;
            pauseAndClear();
        }else {
            cout<<"Invalid account or Insufficient balance\n";
            pauseAndClear();
        }

    }
    else if (choice==6) {
        typeWriter("\nMoney Transfer.");
        typeWriter("\nPlease enter Sender account number,"
                   " Receiver account number and Amount of money.");
        int from ,to;
        double amount;

        cout<<"\nFrom account:";
        if (!(cin>>from)) {
            cout<<"Error: Invalid input value!"<<endl;
            clearInput();
            continue;
        }
        cout<<"To account:";
        if (!(cin>>to)) {
            cout<<"Error: Invalid account number!"<<endl;
            clearInput();

            continue;
        }
        if (from==to) {
            cout<<"Error: Cannot transfer to same account!"<<endl;
            pauseAndClear();
            continue;
        }
        cout<<"Amount: RM";
        if (!(cin>>amount)) {
            cout<<"Error: Invalid amount entered!"<<endl;
            clearInput();

            continue;
        }
        if (amount<=0) {
            cout<<"Error: Amount must be positive."<<endl;
            pauseAndClear();
            continue;
        }


        Account* f= searchAcc(from);
        Account* t= searchAcc(to);

        if (f != nullptr && t !=nullptr && f->balance >= amount) {
            f->balance -= amount;
            t->balance+=amount;

            transaction trf;
            trf.transType = "Transfer";
            trf.transAmount = amount;
            trf.fromAcc = from;
            trf.toAcc = to;

            pushTransaction(trf);
            cout<<"Transfer successful.\n"<<endl;

        }else {
            cout<<"Transfer failed!\n";
        }
        pauseAndClear();
    }
    else if (choice==7) {
        typeWriter("\nTransaction undo");
        char confirm;
        cout<<"Do you want to undo your transaction?(Y/N) :";
        cin>>confirm;

        if (confirm=='Y'||confirm=='y') {
            undo();
            cout<<"Transaction undo successful!\n";
        }else if (confirm=='N'||confirm=='n') {
            cout<<"Transaction undo cancelled!\n";
        }
        pauseAndClear();
    }
    else if (choice==8) {
        typeWriter("\nDisplaying Transaction History...");
        displayHistory();
        pauseAndClear();

    }
    else if (choice==9) {
        typeWriter("\nDisplaying All Accounts...");
        inOrderBST(root);
        pauseAndClear();
    }
}
    return 0;
}