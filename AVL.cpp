#include "AVL.h"

#include <iostream>
#include <string>

AVL::AVL(){
    root = NULL;
}
AVL::~AVL(){}

Node* AVL::getRootNode() const{
    return root;
}
void AVL::rotateLeft(Node* tempRoot){
    Node* temp;
    temp = tempRoot->right;
    tempRoot->right = temp->left;
    temp->left = tempRoot;
    root = temp;
    return;
}
void AVL::rotateRight(Node* tempRoot){
    Node* temp;
    temp = tempRoot->left;
    tempRoot->left = temp->right;
    temp->right = tempRoot;
    tempRoot = temp;
    return;
}
int AVL::getNodeHeight(Node* currentNode){
    if(currentNode == NULL){
        return 0;
    }
    else{
        return currentNode->getHeight();
    }
}
void AVL::checkBalance(Node* currentNode){
    Node* tempLeft;
    tempLeft = currentNode->left;
    Node* tempRight;
    tempRight = currentNode->right;

    int leftBal;
    int rightBal;

    if(tempLeft != NULL){
        checkBalance(tempLeft);
    }
    if(tempRight != NULL){
        checkBalance(tempRight);
    }
    currentNode->balance = tempRight->height - tempLeft->height;

    if(currentNode->balance < 0){
        //left-heavy
        rotateRight(currentNode);
    }
    else if(currentNode->balance >0){
        //right-heavy
        rotateLeft(currentNode);
    }
    return;
}
void AVL::calcHeight(Node* currentNode){
    int max = 0;
    
    if(currentNode == NULL){
        return;
    }

    if(getNodeHeight(currentNode->getLeftChild()) > max){
        max = getNodeHeight(currentNode->getLeftChild());
    }
    if(getNodeHeight(currentNode->getRightChild()) > max){
        max = getNodeHeight(currentNode->getRightChild());
    }

    currentNode->height = max + 1;
}
bool AVL::add(int data){
    bool retBool = addHelper(root, data);
    checkBalance(root);
    return retBool;
}
bool AVL::addHelper(Node*& currentNode, int data){
    if(currentNode == NULL){
        currentNode = new Node(data);
        currentNode->left = NULL;
        currentNode->right = NULL;
        currentNode->value = data;
        return 1;
    }
    else if(data == currentNode->getData()){
        return 0;
    }
    else if(data < currentNode->getData()){
        bool retBool = addHelper(currentNode->left, data);
        calcHeight(currentNode);
        return retBool;
    }
    else if(data > currentNode->getData()){
        bool retBool = addHelper(currentNode->right, data);
        calcHeight(currentNode);
        return retBool;
    }
    else{
        return 0;
    }
}
bool AVL::remove(int data){
    bool retBool = removeHelper(root, data);
    checkBalance(root);
    return retBool;
}
bool AVL::removeHelper(Node*& local_root, int data){
    if(local_root == NULL){
        return 0;
    }
    else{
        if(data < local_root->value){
            return removeHelper(local_root->left, data);
        }
        else if(data > local_root->value){
            return removeHelper(local_root->right, data);
        }
        else{
            Node* old_root = local_root;

            if(local_root->left == NULL){
                local_root = local_root->right;
                delete old_root;
            }
            else if(local_root->right == NULL){
                local_root = local_root->left;
                delete old_root;
            }
            else{
                replace(old_root, local_root->left);
            }

            return 1;
        }
    }
}
void AVL::replace(Node*& old_root, Node*& local_root){
    if(local_root->right != NULL){
        replace(old_root, local_root->right);
    }
    else{
        old_root->value = local_root->value;
        removeHelper(old_root->left, local_root->value);
    }
}
void AVL::clear(){
    clearHelper(this->root);
    this->root = NULL;
}
void AVL::clearHelper(Node* currentNode){
    if(currentNode != NULL){
        clearHelper(currentNode->left);
        clearHelper(currentNode->right);
        delete currentNode;
    }
}