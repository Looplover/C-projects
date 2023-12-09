/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

void Updateheight(SymNode* root)
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

SymNode* Balance(SymNode* root){
    if(root == NULL){
        return root;
    }
    int fht = -1;
    int sht = -1;
 
    if (root->left != NULL)
        fht = root->left->height;
    if (root->right != NULL)
        sht = root->right->height;
    if (abs(fht - sht) == 2) {
        if (fht < sht) {
            int rht1 = -1;
            int rht2 = -1;
            if (root->right->right != NULL)
                rht2 = root->right->right->height;
 
            if (root->right->left != NULL)
                rht1 = root->right->left->height;
 
            if (rht1 > rht2) {
                root = root->RightLeftRotation();
                Updateheight(root);
                return root;
            }
            else {
                root = root->RightRightRotation();
                Updateheight(root);
                return root;
            }
        }
        else {
            int lht1 = -1;
            int lht2 = -1;
            if (root->left->right != NULL)
                lht2 = root->left->right->height;
 
            if (root->left->left != NULL)
                lht1 = root->left->left->height;
 
            if (lht1 >= lht2) {
                root = root->LeftLeftRotation();
                Updateheight(root);
                return root;
            }
            else {
                root = root->LeftRightRotation();
                Updateheight(root);
                return root;
            }
        }
    }
    return root;
}

SymNode* Helmove(SymNode* root,string k){
    if (root != NULL) {
        if (root->key == k) {
            if (root->right == NULL && root->left != NULL) {
                if (root->par != NULL) {
                    if (root->par->key < root->key){
                        root->par->right = root->left;
                    }
                    else{
                        root->par->left = root->left;
                    }
                    Updateheight(root->par);
                }
                root->left->par = root->par;
                root->left = Balance(root->left);
                Updateheight(root->left);
                return root->left;
            }
            else if (root->left == NULL && root->right != NULL) {
                if (root->par != NULL) {
                    if (root->par->key < root->key){
                        root->par->right = root->right;
                    }
                    else{
                        root->par->left = root->right;
                    }
                    Updateheight(root->par);
                }
                root->right->par = root->par;
                root->right = Balance(root->right);
                Updateheight(root->right);
                return root->right;
            }
            else if (root->left == NULL && root->right == NULL) {
                if (root->par->key < root->key) {
                    root->par->right = NULL;
                }
                else {
                    root->par->left = NULL;
                }
                delete root;
                root = NULL;
                return NULL;
            }
            else {
                SymNode* tmpnode = root;
                tmpnode = tmpnode->right;
                while (tmpnode->left != NULL) {
                    tmpnode = tmpnode->left;
                }
                string val = tmpnode->key;
                int idx = tmpnode->address;
                root->right = Helmove(root->right, tmpnode->key);
                root->key = val;
                root->address = idx;
                root = Balance(root);
                Updateheight(root);
                return root;
            }
        }
        else if (root->key < k) {
            root->right = Helmove(root->right, k);
            root = Balance(root);
        }
        else if (root->key > k) {
            root->left = Helmove(root->left, k);
            root = Balance(root);
        }
        if (root != NULL) {
            Updateheight(root);
        }
    }
    Updateheight(root);
    return root;
}

SymNode* Helsert(SymNode* root,SymNode* parent,string k)
{
    if (root == NULL) {
        SymNode* tempo = new SymNode();
        tempo->height = 0;
        tempo->left = NULL;
        tempo->right = NULL;
        tempo->par = parent;
        tempo->key = k;
        return tempo;
    }
    else if (root->key > k) {
        root->left = Helsert(root->left,root, k);
        int fht = -1;
        int sht = -1;
        if (root->left != NULL){
            fht = root->left->height;
        }
        if (root->right != NULL){
            sht = root->right->height;
        }
        if (abs(fht - sht) == 2) {
            if (root->left != NULL && k < root->left->key) {
                root = root->LeftLeftRotation();
                Updateheight(root);
                return root;
            }
            else {
                root = root->LeftRightRotation();
                Updateheight(root);
                return root;
            }
        }
    }
    else if (root->key < k) {
        root->right = Helsert(root->right,root, k);
        int fht = -1;
        int sht = -1;
 
        if (root->left != NULL){
            fht = root->left->height;
        }
        if (root->right != NULL){
            sht = root->right->height;
        }
        if (abs(fht - sht) == 2){
            if (root->right != NULL && k < root->right->key) {
                root = root->RightLeftRotation();
                Updateheight(root);
                return root;
            }
            else {
                root = root->RightRightRotation();
                Updateheight(root);
                return root;
            }
        }
    }
    Updateheight(root);
    return root;
}

SymbolTable::SymbolTable(){
    size = 0;
    root = NULL;
}

void SymbolTable::insert(string k){
    if (root == NULL) {
        root = new SymNode(k);
    }
    else{
        root = Helsert(root,NULL,k);
    }
    size++;
}

void SymbolTable::remove(string k){
    if(search(k) == -2){
        return;
    }
    if(root == NULL){
        return;
    }
    if(root->key == k && root->left == NULL && root->right == NULL){
        size--;
        delete root;
        root = NULL;
        return;
    }
    if(search(k) != -2){
        size--;
    }
    root = Helmove(root,k);  
}

int SymbolTable::search(string k){
    SymNode* curr = get_root();
    while(curr != NULL){
        if(k > curr->key){    
            curr = curr->right;
        }
        else if(k < curr->key){
            curr = curr->left;
        }
        else{
            return curr->address;
        }
    }
    return -2;
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* curr = get_root();
    while(curr != NULL){
        if(k > curr->key){    
            curr = curr->right;
        }
        else if(k < curr->key){
            curr = curr->left;
        }
        else{
            curr->address = idx;
            return;
        }
    }
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    if(root != NULL){
        delete root;
    }
    root = NULL;
}