
#include <stdexcept>
#include <iostream>

using namespace std;
#include "list.h"
#include "node.h"

List::List(){
    sentinel_head = new(nothrow) Node(true);
    sentinel_tail = new(nothrow) Node(true);
    if(sentinel_head==NULL || sentinel_tail==NULL){
        throw runtime_error("Out of Memory");
        return;
    }
    sentinel_head->next = sentinel_tail;
    sentinel_tail->prev = sentinel_head;
    size = 0;
}

List::~List(){
    int sub = size;
    for(int i = 0;i<sub;i++){
        delete_tail();
    }
    delete sentinel_head;
    delete sentinel_tail;
}

void List::insert(int v){
    Node* temp = new(nothrow) Node(v, sentinel_tail, sentinel_tail->prev);
    if(temp==NULL){
        throw runtime_error("Out of Memory");
        return;
    }
    sentinel_tail->prev->next = temp;
    sentinel_tail->prev = temp;
    size++;
}

int List::delete_tail(){
    Node* tmp = sentinel_tail->prev;
    if(tmp == sentinel_head){
        throw runtime_error("Empty Stack");
        return -1;
    }
    tmp->prev->next = sentinel_tail;
    sentinel_tail->prev = tmp->prev;
    size--;
    int ans = tmp->get_value();
    delete tmp;
    return ans;
}

int List::get_size(){
    return size;
}

Node* List::get_head(){
    return sentinel_head;
}

