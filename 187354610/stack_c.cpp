
#include <iostream>
#include <stdexcept>

using namespace std;

#include "stack_c.h"
#include "list.h"

Stack_C::Stack_C(){
    stk = new(nothrow) List();
    if(stk == NULL){
        throw runtime_error("Out of Memory");
    }
}

Stack_C::~Stack_C(){
    delete stk;
}

void Stack_C::push(int data){
    stk->insert(data);
}

int Stack_C::pop(){
    return stk->delete_tail();
}

int Stack_C::get_element_from_bottom(int idx){
    if (idx<0 || idx >= stk->get_size()){
        throw runtime_error("Index out of range");
        return -1;
    }
    else{
        Node* star = stk->get_head();
        for(int i = 0; i <= idx; i++){
            star = star->next;
        }
        if (!(star->is_sentinel_node())){
            return star->get_value();
        }
    }
    return -1;
}

int Stack_C::get_element_from_top(int idx){
    if (idx<0 || idx >= stk->get_size()){
        throw runtime_error("Index out of range");
        return -1;
    }
    else{
        int ind = stk->get_size() - 1 - idx;
        Node* star = stk->get_head();
        for(int i = 0; i <= ind; i++){
            star = star->next;
        }
        if (!(star->is_sentinel_node())){
            return star->get_value();
        }
    }
    return -1;
}

void Stack_C::print_stack(bool top_or_bottom){
    if(!(top_or_bottom)){
        Node* star = stk->get_head();
        for(int i = 0; i < stk->get_size(); i++){
            star = star->next;
            cout<<star->get_value()<<endl;
        }
    }
    else{
        Node* star = stk->get_head();
        for(int i = 0;i <= stk->get_size(); i++){
            star = star->next;
        }
        for(int i = 0; i < stk->get_size(); i++){
            star = star->prev;
            cout<<star->get_value()<<endl;
        }
    }
}

int Stack_C::add(){
    if(stk->get_size()<2){
        throw runtime_error("Not Enough Arguments");
        return -1;
    }
    else{
        int top1 = pop();
        int top2 = pop();
        push(top1+top2);
        return top1+top2;
    }
    return -1;
}

int Stack_C::subtract(){
    if(stk->get_size()<2){
        throw runtime_error("Not Enough Arguments");
        return -1;
    }
    else{
        int top1 = pop();
        int top2 = pop();
        push(top2-top1);
        return top2-top1;
    }
    return -1;
}

int Stack_C::multiply(){
    if(stk->get_size()<2){
        throw runtime_error("Not Enough Arguments");
        return -1;
    }
    else{
        int top1 = pop();
        int top2 = pop();
        push(top1*top2);
        return top1*top2;
    }
    return -1;
}

int Stack_C::divide(){
    if(stk->get_size()<2){
        throw runtime_error("Not Enough Arguments");
        return -1;
    }
    else{
        int top1 = pop();
        int top2 = pop();
        if(top1){
            if(top1*top2 >= 0){
                push(top2/top1);
                return top2/top1;
            }
            else {
                if(top2%top1 == 0){
                    push(top2/top1);
                    return top2/top1;
                }
                else{
                    push((top2/top1) - 1);
                    return (top2/top1) - 1;
                }
            }
        }
        else{
            throw runtime_error("Divide by Zero Error");
        }
    }
    return -1;
}

List* Stack_C::get_stack(){
    return stk;
}

int Stack_C::get_size(){
    return stk->get_size();
}