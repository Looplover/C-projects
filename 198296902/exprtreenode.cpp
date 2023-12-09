/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode(){
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    left = nullptr;
    right = nullptr;
    type = t;
    if(t=="VAL"){
        UnlimitedInt* one = new UnlimitedInt(1);
        val = new UnlimitedRational(v,one);
    }
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    left = new ExprTreeNode();
    right = new ExprTreeNode();
    type = t;
    if(t=="VAL"){
        val = v;
    }
}

ExprTreeNode::~ExprTreeNode(){
    delete val;
    delete evaluated_value;
    delete left;
    delete right;
}