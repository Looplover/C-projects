/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include <iostream>
#include "symtable.h"


SymbolTable::SymbolTable(){
    size = 0;
    root = nullptr;
}

SymbolTable::~SymbolTable(){
    delete root;
}
// Insert a key value pair in the symbol table
void SymbolTable::insert(string k, UnlimitedRational* v){
    SymEntry* ent = new SymEntry(k,v);
    if(size == 0){
        root = ent;
        size++;
        return;
    }
    SymEntry* curr = get_root();
    while(true){
        if(k > curr->key){
            if(curr->right == nullptr){
                curr->right = ent;
                size++;
                break;
            }
            else{
                curr = curr->right;
            }
        }
        else{
            if(curr->left == nullptr){
                curr->left = ent;
                size++;
                break;
            }
            else{
                curr = curr->left;
            }
        }
    }

}

// Remove a key (and value) in the symbol table
void SymbolTable::remove(string k){
    SymEntry* curr = root;
    while(true){
        if(curr->key == k){
            if(curr->left == nullptr && curr->right == nullptr){
                delete curr;
                size--;
                return;
            }
            else{
                if(root->left != nullptr){
                    SymEntry* temp = curr->left;
                    while(temp->right != nullptr){
                        temp = temp->right;
                    }
                    curr->key = temp->key;
                    curr->val = temp->val;
                    delete temp;
                    size--;
                    return;
                }
                else{
                    SymEntry* temp = curr->right;
                    while(temp->left != nullptr){
                        temp = temp->left;
                    }
                    curr->key = temp->key;
                    curr->val = temp->val;
                    delete temp;
                    size--;
                    return;
                }
            }
        }
        else if(curr->key > k){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        } 
    }
}

// Find the val corresponding to the key in the symbol table
UnlimitedRational* SymbolTable::search(string k){
    SymEntry* curr = get_root();
    while(true){
        if(k > curr->key){    
            curr = curr->right;
        }
        else if(k < curr->key){
            curr = curr->left;
        }
        else{
            return curr->val;
        }
    }
}

// Get size
int SymbolTable::get_size(){
    return size;
}

// Get root 
SymEntry* SymbolTable::get_root(){
    return root;
}