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
void AVL::rotateLeft(Node*& tempRoot){
    Node* temp;
    temp = tempRoot->right;
    tempRoot->right = temp->left;
    temp->left = tempRoot;
    tempRoot = temp;
}
void AVL::rotateRight(Node*& tempRoot){
    Node* temp;
    temp = tempRoot->left;
    tempRoot->left = temp->right;
    temp->right = tempRoot;
    tempRoot = temp;
}
void AVL::balanceLeft(Node*& currentNode){
    if(currentNode == NULL){
        return;
    }

    if(currentNode->right->balance() <= -1){
        rotateRight(currentNode->right);
    }
    rotateLeft(currentNode);
}
void AVL::balanceRight(Node*& currentNode){
    if(currentNode == NULL){
        return;
    }

    if(currentNode->left->balance() >= 1){
        rotateLeft(currentNode->left);
    }
    rotateRight(currentNode);
}
int AVL::getNodeHeight(Node* currentNode){
    if(currentNode == NULL){
        return 0;
    }
    else{
        return currentNode->getHeight();
    }
}
bool AVL::add(int data){
    bool retBool = addHelper(root, data);
    return retBool;
}
bool AVL::addHelper(Node*& currentNode, int data){
    if(currentNode == NULL){
        currentNode = new Node(data);
        currentNode->left = NULL;
        currentNode->right = NULL;
        currentNode->height = 0;
        return 1;
    }
    else if(data == currentNode->getData()){
        return 0;
    }
    else if(data > currentNode->getData()){
        bool retBool = addHelper(currentNode->right, data);
        if(retBool == 1){
            if(currentNode->balance() > 1){
                balanceLeft(currentNode);
            }
            else if(currentNode->balance() < -1){
                balanceRight(currentNode);
            }
        }
        return retBool;
    }
    else if(data < currentNode->getData()){
        bool retBool = addHelper(currentNode->left, data);
        if(retBool == 1){
            if(currentNode->balance() > 1){
                balanceLeft(currentNode);
            }
            else if(currentNode->balance() < -1){
                balanceRight(currentNode);
            }
        }
        return retBool;
    }
    
    if(currentNode->balance() > 1){
        balanceLeft(currentNode);
    }
    else if(currentNode->balance() < -1){
        balanceRight(currentNode);
    }

    return 0;
}
bool AVL::remove(int data){
    bool retBool = removeHelper(root, data);
    balanceRemove(root);
    return retBool;
}
bool AVL::removeHelper(Node*& local_root, int data){
    if(local_root == NULL){
        return 0;
    }
    
    Node* tempNode = local_root;
    Node* tempLeft = local_root->left;

    if(data < local_root->value){
        return removeHelper(local_root->left, data);
    }
    if(data > local_root->value){
        return removeHelper(local_root->right, data);
    }

    if(local_root->left == NULL && local_root->right == NULL){
        delete local_root;
        local_root = NULL;
        return 1;
    }
    if(local_root->left == NULL || local_root->right == NULL){
        tempLeft = local_root->left;

        if(tempLeft == NULL){
            tempLeft = local_root->right;
        }

        delete local_root;
        local_root = tempLeft;
        return 1;
    }
    while(tempLeft->right != NULL){
        tempNode = tempLeft;
        tempLeft = tempLeft->right;
    }
    if(local_root->value != tempNode->value){
        tempNode->right = tempLeft->left;
    }
    else{
        tempNode->left = tempLeft->left;
    }

    local_root->value = tempLeft->value;
    delete tempLeft;
    return 1;
}
void AVL::balanceRemove(Node*& currentNode){
    if(currentNode == NULL){
        return;
    }

    if(currentNode->balance() > 1){
        balanceLeft(currentNode);
    }
    if(currentNode->balance() < -1){
        balanceRight(currentNode);
    }

    balanceRemove(currentNode->left);
    balanceRemove(currentNode->right);
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