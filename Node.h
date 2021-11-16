#ifndef NODE_H
#define NODE_H

#include "NodeInterface.h"

#include <iostream>
#include <string>

using namespace std;

class Node: public NodeInterface{
public:
    Node* left = NULL;
    Node* right = NULL;
    int value;
    int height = 0;
    int balance = 0; //0=balanced, NEG=left-heavy, POS=right-heavy
    
    Node(int data);
    ~Node();

    int getData() const;
    Node* getLeftChild() const;
    Node* getRightChild() const;
    int getHeight();
};
#endif