
#include <iostream>
#include <stdexcept>

using namespace std;

#include "stack_b.h"

Stack_B::Stack_B(){
    stk = new(nothrow) int[1024];
    if(stk==NULL){
        throw runtime_error("Out of Memory");
    }
    size = 0;
    capacity = 1024;
}

Stack_B::~Stack_B(){
    delete [] stk;
}

void Stack_B::push(int data){
    if (size==capacity){
        int* temp = stk;
        stk = new(nothrow) int[2*capacity];
        if(stk==NULL){
        throw runtime_error("Out of Memory");
        return;
    }
        for(int i = 0;i<size;i++){
            stk[i]=temp[i];
        }
        stk[size]=data;
        size++;
        capacity *= 2;
        delete [] temp;
    }
    else{
        stk[size]=data;
        size++;
    }
}

int Stack_B::pop(){
    if(size == 0){
        throw runtime_error("Empty Stack");
    }
    else{
        int ans = stk[size-1];
        if(size<=capacity/4 && size>1024){
            int* temp = stk;
            stk = new(nothrow) int[capacity/4];
            if(stk==NULL){
            throw runtime_error("Out of Memory");
            return -1;
         }
            for(int i = 0;i<size-1;i++){
                stk[i] = temp[i];
            }
            size--;
            delete [] temp;
        }
        else{
            size--;
        }
        return ans;
    }
    return -1;
}

int Stack_B::get_element_from_bottom(int idx){
    if (idx<0 || idx >= size){
        throw runtime_error("Index out of range");
        return -1;
    }
    else{
        return stk[idx];
    }
    return -1;
}

int Stack_B::get_element_from_top(int idx){
    if (idx<0 || idx >= size){
        throw runtime_error("Index out of range");
        return -1;
    }
    else{
        return stk[size-1-idx];
    }
    return -1;
}

void Stack_B::print_stack(bool top_or_bottom){
    if(!(top_or_bottom)){
        for(int i = 0; i < size; i++){
            cout<<stk[i]<<endl;
        }
    }
    else{
        for(int i = size-1;i >= 0; i--){
            cout<<stk[i]<<endl;
        }
    }
}

int Stack_B::add(){
    if(size<2){
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

int Stack_B::subtract(){
    if(size<2){
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

int Stack_B::multiply(){
    if(size<2){
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

int Stack_B::divide(){
    if(size<2){
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

int* Stack_B::get_stack(){
    return stk;
}

int Stack_B::get_size(){
    return size;
}