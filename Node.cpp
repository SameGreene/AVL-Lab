#include "Node.h"

#include<iostream>
#include<string>

Node::Node(int data){
    value = data;
    height = 1;
    balance = 0;
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
    return height;
}
