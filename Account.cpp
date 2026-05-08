#include<iostream>
#include <string>
#include"blablabla.h"
using namespace std;

//Define global variable
Account* head=nullptr;
StackNode* top=nullptr;
BSTNode* root=nullptr;

//Add new account
void addNew(int accNum, string name, double balance) {
    Account* newAcc = new Account();

    newAcc ->accNum = accNum;
    newAcc ->name=name;
    newAcc ->balance = balance;
    newAcc->next=nullptr;

    //Added to linked list
    if (head==nullptr){
        head=newAcc;
    }else {
        Account* temp =head;
        while (temp -> next!=nullptr) {
            temp=temp->next;
        }
        temp->next=newAcc;
    }
    root=insertBST(root,newAcc);
}

//Delete account
void deleteAcc(int accNo) {
    if (head==nullptr)
        return;

    root = deleteBST(root,accNo);

    if (head -> accNum ==accNo) {
        Account * temp=head;
        head = head->next;
        delete temp;
        cout<<"Account Deleted"<<endl;
        return;
    }else {
        Account* curr=head;
        Account* prev=nullptr;
        while (curr !=nullptr && curr -> accNum !=accNo) {
            prev=curr;
            curr=curr->next;
        }
        if (curr !=nullptr) {
            prev->next = curr->next;
            delete curr;
        }else {
            cout<<"Account Not Found"<<endl;
            return;
        }
    }
}
//Searching for account
Account* searchAcc(int accNo) {
    Account* curr=head;

    while (curr!=nullptr) {
        if (curr->accNum ==accNo) {
            return curr;
        }
        curr = curr-> next;
    }
    return nullptr;
}