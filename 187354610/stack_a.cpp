
#include <iostream>
#include <stdexcept>
using namespace std;
#include "stack_a.h"

Stack_A::Stack_A(){
    size = 0;
}

void Stack_A::push(int data){
    if (size==1024){
        throw runtime_error("Stack Full");
    }
    else{
        stk[size++]=data;
    }
}

int Stack_A::pop(){
    if(size == 0){
        throw runtime_error("Empty Stack");
    }
    else{
        return stk[--size];
    }
    return -1;
}

int Stack_A::get_element_from_bottom(int idx){
    if (idx<0 || idx >= size){
        throw runtime_error("Index out of range");
    }
    else{
        return stk[idx];
    }
    return -1;
}

int Stack_A::get_element_from_top(int idx){
    if (idx<0 || idx >= size){
        throw runtime_error("Index out of range");
    }
    else{
        return stk[size-1-idx];
    }
    return -1;
}

void Stack_A::print_stack(bool top_or_bottom){
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

int Stack_A::add(){
    if(size<2){
        throw runtime_error("Not Enough Arguments");
    }
    else{
        int top1 = pop();
        int top2 = pop();
        push(top1+top2);
        return top1+top2;
    }
    return -1;
}

int Stack_A::subtract(){
    if(size<2){
        throw runtime_error("Not Enough Arguments");
    }
    else{
        int top1 = pop();
        int top2 = pop();
        push(top2-top1);
        return top2-top1;
    }
    return -1;
}

int Stack_A::multiply(){
    if(size<2){
        throw runtime_error("Not Enough Arguments");
    }
    else{
        int top1 = pop();
        int top2 = pop();
        push(top1*top2);
        return top1*top2;
    }
    return -1;
}

int Stack_A::divide(){
    if(size<2){
        throw runtime_error("Not Enough Arguments");
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

int* Stack_A::get_stack(){
    return stk;
}

int Stack_A::get_size(){
    return size;
}