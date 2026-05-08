#include "blablabla.h"
#include<iostream>
#include<string>
using namespace std;

bool deposit(int accNum,double amount) {
    Account* acc = searchAcc(accNum);
    if (acc != nullptr) {
        acc->balance+=amount;
        return true;
    }else {
        cout<<"Account not found."<<endl;
        return false;
    }
}

//If no input or wrong input the message will show
void undo() {
    if (top==nullptr) {
        cout<<"No transaction to undo.";
        return;

    }
    //Get the previous transaction from top of stack
    transaction last=top->data;

    if (last.transType=="Deposit") {
        Account* acc = searchAcc(last.fromAcc);
        acc->balance-=last.transAmount; //Account point to balance to show Last Transaction amount

    }

    else if (last.transType=="Withdraw"){
        Account*acc =searchAcc(last.fromAcc);
        acc->balance+=last.transAmount;

    }


    else if (last.transType=="Transfer") {

        Account* from = searchAcc(last.fromAcc);
        Account* to = searchAcc(last.toAcc);

        //Undo the transfer process.
    if (from != nullptr && to != nullptr) {

       //Return the money to sender Account
        from->balance+=last.transAmount;

        //Remove the money from receiver Account
        to->balance-=last.transAmount;
    }
        else {
            cout<<"No transaction to transfer."<<endl;
        }

    }

    //Pop the stack
    StackNode* temp=top;
    top=top->next;
    delete temp;
}

//Push the stack
void pushTransaction(transaction t) {
    StackNode* newNode = new StackNode();
    newNode->data=t;
    newNode->next=top;
    top=newNode;
}


//Display History of transaction made
void displayHistory() {
    StackNode* temp = top;

    cout<<"\nTransaction History:"<<endl;
    while (temp!= nullptr) {
        cout<<"\nTransaction Type: "<<temp-> data.transType
        <<"\n Amount: RM"<<temp-> data.transAmount
        <<"\n Account:"<<temp-> data.fromAcc
        <<"\n To Account: "<<temp-> data.toAcc<<endl;
        temp=temp-> next;
    }
}