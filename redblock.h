#include "node.h"
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

class RedBlack {
    node* root;
    int size;
    node* TNULL;

public:
    RedBlack() {
        TNULL = new node;
        TNULL->isRed = false;
        TNULL->right = NULL;
        TNULL->left = NULL;
        root = TNULL;
        size = 0;
    }

    void insert(int num) {
        node* curr = new node;
        curr->parent = NULL;
        curr->elem = num;
        curr->left = TNULL;
        curr->right = TNULL;
        curr->isRed = true;

        node* y = NULL;
        node* x = this->root;

        while (x != TNULL) {
            y = x;
            if (curr->elem < x->elem) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        curr->parent = y;

        if (y == NULL) {
            root = curr;
        }
        else if (curr->elem < y->elem) {
            y->left = curr;
        }
        else {
            y->right = curr;
        }

        if(curr->parent == NULL){
            curr->isRed = false;
        }

        size++;
        insertFix(curr);
    }

    void insertFix(node*& curr) {
        node* parent = NULL;
        node* grandparent = NULL;

        while ((curr != root) && (curr->isRed) && (curr->parent->isRed)) {
            parent = curr->parent;
            grandparent = curr->parent->parent;

            if (parent == grandparent->left) {
                node* uncle = grandparent->right;

                if (uncle != NULL && uncle->isRed) {
                    parent->isRed = false;
                    uncle->isRed = false;
                    grandparent->isRed = true;
                    curr = grandparent;
                }
                else {
                    if (curr == parent->right) {
                        leftRotate(parent);
                        curr = parent;
                        parent = curr->parent;
                    }
                    rightRotate(grandparent);
                    swap(parent->isRed, grandparent->isRed);
                    curr = parent;
                }
            }
            else {
                node* uncle = grandparent->left;

                if ((uncle != NULL) && (uncle->isRed)) {
                    parent->isRed = false;
                    uncle->isRed = false;
                    grandparent->isRed = true;
                    curr = grandparent;
                }
                else {
                    if (curr == parent->left) {
                        rightRotate(parent);
                        curr = parent;
                        parent = curr->parent;
                    }
                    leftRotate(grandparent);
                    swap(parent->isRed, grandparent->isRed);
                    curr = parent;
                }
            }
        }
        root->isRed = false;
    }

    void leftRotate(node*& x) {
        node* y = x->right;
        x->right = y->left;
        if(y->left != NULL){
            y->left->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == NULL){
            this->root = y;
        }
        else if(x == x->parent->left){
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(node*& x) {
        node* y = x->left;
        x->left = y->right;
        if(y->right != NULL){
            y->right->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == NULL){
            this->root = y;
        }
        else if(x == x->parent->right){
            x->parent->right = y;
        }else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void print() {
        cout << "Size: " << size << endl;
        if (size > 0) {
            cout << "Op: p" << endl;
            printHelper(root, "", 'Q');
        }
    }

    void printHelper(node* curr, string pre, char loc) {
        if (curr != TNULL) {
            cout << "Op: " << pre << loc << ": " << curr->elem;
            if (curr->isRed) {
                cout << "(R)" << endl;
            }
            else {
                cout << "(B)" << endl;
            }

            printHelper(curr->left, pre + "    ", 'L');
            printHelper(curr->right, pre + "    ", 'R');
        }
    }
};

