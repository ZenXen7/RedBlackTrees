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
	
	void insertFix(node* z) {
    while (z->parent != NULL && z->parent->isRed) {
        if (z->parent == z->parent->parent->left) {
            node* y = z->parent->parent->right;
            if (y->isRed) {
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    if (z->parent != NULL) {
                        z->parent->isRed = false;
                    }
                    leftRotate(z);
                }
                z->parent->parent->isRed = true;
                rightRotate(z->parent->parent);
            }
        }
        else {
            node* y = z->parent->parent->left;
            if (y->isRed) {
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->isRed = false;
                z->parent->parent->isRed = true;
                leftRotate(z->parent->parent);
            }
            
            if(z == root){
                break;
            }
        }
    }
    root->isRed = false;
}


    void leftRotate(node*& x) {
        node* y = x->right;
        x->right = y->left;
        if(y->left != TNULL){
        	y->left->parent = x;
		}
		y->parent = x->parent;
		if(x->parent = NULL){
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
       if(y->right != TNULL){
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
        print("", 'Q', root);
    }

    void print(string pre, char loc, node* n) {
        if (n != TNULL) {
            cout << pre << loc << ": " << n->elem;
            if (n->isRed) {
                cout << "(R)" << endl;
            }
            else {
                cout << "(B)" << endl;
            }

            print(pre + "	", 'L', n->left);
            print(pre + "	", 'R', n->right);
        }
    }
};

