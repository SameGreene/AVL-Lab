#ifndef AVL_H
#define AVL_H

#include "AVLInterface.h"
#include "Node.h"

#include <iostream>
#include <string>

using namespace std;

class AVL: public AVLInterface{
protected:
    Node* root;
public:    
    AVL();
    ~AVL();

    Node* getRootNode() const;
    void rotateLeft();
    void rotateRight();
    int getNodeHeight(Node* currentNode);
    void calcHeight(Node* currentNode);
    bool add(int data);
    bool addHelper(Node*& currentNode, int data);
    bool remove(int data);
    bool removeHelper(Node*& local_root, int data);
    void replace(Node*& old_root, Node*& local_root);
    void clear();
    void clearHelper(Node* currentNode);
};
#endif