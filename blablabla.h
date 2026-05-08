#ifndef BLABLABLA_H
#define BLABLABLA_H
#include<string>
#include<iostream>
using namespace std;

//Account structure
struct Account {
    int accNum;
    string name;
    double balance;
    Account* next;

};
//Transaction structure
    struct transaction {
        double transAmount;
        string transType;
        int fromAcc;
        int toAcc;
    };

//Transaction finding using Stack structure
struct StackNode {
    transaction data;
    StackNode *next;
};
//Search for account Binary Search Tree structure
struct BSTNode {
    int accNum;
    double balance;
    string name;
    BSTNode* left;
    BSTNode* right;
    Account* accPtr;

    BSTNode(Account *a) {
        accNum = a->accNum;
        accPtr = a;
        left = nullptr;
        right = nullptr;
    }
};

extern Account* head;
extern StackNode* top;
extern BSTNode* root;

void addNew(int accNum, string name, double balance);
void deleteAcc(int accNo);
Account* searchAcc(int accNo);

bool deposit(int accNum,double amount);
void pushTransaction(transaction t);
void undo();
void displayHistory();

BSTNode* insertBST(BSTNode* node,Account* newAcc);
void inOrderBST(BSTNode* node);
BSTNode* deleteBST(BSTNode* root, int accNo);
BSTNode* minValueNode(BSTNode* node);



#endif