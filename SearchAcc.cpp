#include"blablabla.h"
#include <iostream>
#include<string>
#include<iomanip>
using namespace std;


BSTNode* insertBST(BSTNode* node,Account* newAcc) {
    //If tree is empty, create a new node
    if (node==nullptr) {
        return new BSTNode(newAcc);
    }
    //Else continue going down the BST
    if (newAcc->accNum < node->accNum) {
        node->left = insertBST(node->left, newAcc);
    } else if (newAcc->accNum > node->accNum) {
        node->right = insertBST(node->right, newAcc);
    }
    return node;
}

void inOrderBST(BSTNode* node) {
    //If the node is null, means that reaches empty leaf/child will prevent from crashing the program by trying to access the null data.
    if (node==nullptr)
        return;
    //Go to left subtree
    inOrderBST(node->left);

    cout<<" Account Number: "<<node->accPtr->accNum<<endl;
    cout<<" Name: "<<node->accPtr->name<<endl;
    cout<<" Balance: RM"<<fixed<<setprecision(2)<<node->accPtr->balance<<"\n"<<endl;

    //Go to right subtree
    inOrderBST(node->right);
}
BSTNode* minValueNode(BSTNode* node) {
    BSTNode* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

BSTNode* deleteBST(BSTNode*root,int accNo){
    if (root==nullptr)return nullptr;

    if (accNo<root->accNum)
        root->left=deleteBST(root->left,accNo);
    else if (accNo>root->accNum)
        root->right=deleteBST(root->right,accNo);
else {
    if (root->left == nullptr) {
        BSTNode* temp = root->right;
        delete root;
        return temp;
    }else if (root->right == nullptr) {
        BSTNode* temp = root->left;
        delete root;
        return temp;
    }BSTNode* temp = minValueNode(root->right);
    root->accPtr = temp->accPtr;
    root->accNum = temp->accNum;
    root->right = deleteBST(root->right,temp->accNum);
}
return root;
}
