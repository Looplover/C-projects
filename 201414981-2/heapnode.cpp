/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "heapnode.h"

//Write your code below this line

HeapNode::HeapNode(){
    par =  nullptr;
    left = nullptr;
    right = nullptr;
}

HeapNode::HeapNode(int _val){
    par = nullptr;
    left = nullptr;
    right = nullptr;
    val = _val;
}

HeapNode::~HeapNode(){
    if (left != nullptr)
    delete left;
    if (right != nullptr)
    delete right;
    left = nullptr;
    right = nullptr;
}