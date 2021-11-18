#include "Node.h"

#include<iostream>
#include<string>

Node::Node(int data){
    value = data;
    height = 0;
}
Node::~Node(){}

int Node::getData() const{
    return value;
}
Node* Node::getLeftChild() const{
    return left;
}
Node* Node::getRightChild() const{
    return right;
}
int Node::getHeight(){
    int leftNum = 0;
    int rightNum = 0;

    if(left != NULL){
        leftNum = left->getHeight();
    }
    if(right != NULL){
        rightNum = right->getHeight();
    }

    int retInt;
    if(leftNum > rightNum){
        retInt = leftNum + 1;
        return retInt;
    }
    else{
        retInt = rightNum + 1;
        return retInt;
    }
}
int Node::balance(){
    int leftNum;
    int rightNum;

    if(left != NULL){
        leftNum = left->getHeight();
    }
    else{
        leftNum = 0;
    }

    if(right != NULL){
        rightNum = right->getHeight();
    }
    else{
        rightNum = 0;
    }

    int retInt;
    retInt = rightNum - leftNum;
    return retInt;
}