/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::ExprTreeNode(string t,int v){
    left = nullptr;
    right = nullptr;
    type = t;
    if(t == "VAL"){
        num = v;
    }

}

ExprTreeNode::~ExprTreeNode(){
    if (left != NULL)
    delete left;
    if (right != NULL)
    delete right;
    left = NULL;
    right = NULL;
}

