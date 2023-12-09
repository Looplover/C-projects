/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

void Uht(SymNode* root)
{
    if (root != NULL) {

        int k = 0;
        if (root->left != NULL){
            k = max(k, root->left->height + 1);
        }
 
        if (root->right != NULL){
            k = max(k, root->right->height + 1);
        }
        root->height = k;
    }
}

SymNode::SymNode(){
    height = -1;
    par = NULL;
    left = NULL;
    right = NULL;
    address = -1;
}

SymNode::SymNode(string k){
    key = k;
    height = 0;
    par = NULL;
    left = NULL;
    right = NULL;
    address = -1;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* temp = left;
    left=temp->right;
    if(temp->right != NULL){
        temp->right->par = this;
    }
    temp->right = this;
    temp->par = par;
    par = temp;
    if(temp->par != NULL && key < temp->par->key){
        temp->par->left = temp;
    }
    else{
        if(temp->par != NULL){
            temp->par->right = temp;
        }
    }
    Uht(temp->left);
    Uht(temp->right);
    Uht(temp);
    Uht(temp->par);
    return temp;
}

SymNode* SymNode::RightRightRotation(){
    SymNode* temp = right;
    right=temp->left;
    if(temp->left != NULL){
        temp->left->par = this;
    }
    temp->left = this;
    temp->par = par;
    par = temp;
    if(temp->par != NULL && key > temp->par->key){
        temp->par->right = temp;
    }
    else{
        if(temp->par != NULL){
            temp->par->left = temp;
        }
    }
    Uht(temp->left);
    Uht(temp->right);
    Uht(temp);
    Uht(temp->par);
    return temp;
}


SymNode* SymNode::LeftRightRotation(){
    left = left->RightRightRotation();
    return this->LeftLeftRotation();
}

SymNode* SymNode::RightLeftRotation(){
    right = right->LeftLeftRotation();
    return this->RightRightRotation();
}

SymNode::~SymNode(){
    if(left != NULL){
        delete left;
    }
    if(right != NULL){
        delete right;
    }
    left = NULL;
    right = NULL;
}