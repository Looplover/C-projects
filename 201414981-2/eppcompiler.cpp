/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include <iostream>
#include "eppcompiler.h"

//Write your code below this line

vector<string> helcomm(vector<string>& comm,SymbolTable* symtable,ExprTreeNode* evl){
    if(evl == NULL){
        return comm;
    }
    if(evl->type == "ADD" && evl->id != "o"){
        helcomm(comm,symtable,evl->right);
        helcomm(comm,symtable,evl->left);
        comm.push_back("ADD");
        return comm; 
    }
    else if(evl->type == "SUB"){
        helcomm(comm,symtable,evl->right);
        helcomm(comm,symtable,evl->left);
        comm.push_back("SUB");
        return comm; 
    }
    else if(evl->type == "DIV"){
        helcomm(comm,symtable,evl->right);
        helcomm(comm,symtable,evl->left);
        comm.push_back("DIV");
        return comm; 
    }
    else if(evl->type == "MUL"){
        helcomm(comm,symtable,evl->right);
        helcomm(comm,symtable,evl->left);
        comm.push_back("MUL");
        return comm; 
    }
    else if(evl->type == "VAR"){
        int addr = symtable->search(evl->id);
        string adds = std::to_string(addr);
        string ans = "PUSH mem["+adds+"]";
        comm.push_back(ans);
        return comm;
    }
    else if(evl->type == "VAL"){
        string ans = "PUSH "+std::to_string(evl->num);
        comm.push_back(ans);
        return comm;
    }
    else{
        helcomm(comm,symtable,evl->right);
        if(evl->left->type == "RET"){
            comm.push_back("RET = POP");
            return comm;
        }
        else{
            int addr = symtable->search(evl->left->id);
            string ans = "mem["+std::to_string(addr)+"] = POP";
            comm.push_back(ans);
            return comm;
        }
    }
}

EPPCompiler::EPPCompiler(){
    // Parser* temp = new Parser();
    // targ = *temp;
    // MinHeap* temp2 = new MinHeap();
    // least_mem_loc = *temp2;
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    // Parser* temp = new Parser();
    // targ = *temp;
    // MinHeap* temp2 = new MinHeap();
    // least_mem_loc = *temp2;
    output_file = out_file;
    memory_size = mem_limit;
    for(int i = 1; i <= mem_limit;i++){
        mem_loc.push_back(mem_limit-i);
    }
}

void EPPCompiler::compile(vector<vector<string>> code){
    vector<string> v;
    for(int k = 0;k < code.size();k++){
        targ.parse(code[k]);
        
        if(code[k][1] == ":="){
            if(code[k][0] != "ret" && code[k][0] != "del"){
                targ.symtable->assign_address(code[k][0],mem_loc.back());
                mem_loc.pop_back();
            }
            else if(code[k][0]=="del"){
                mem_loc.push_back(targ.last_deleted);
            }
        }
        vector<string> tempr = generate_targ_commands();
        for(string i : tempr){
            v.push_back(i);
        }
    }
    write_to_file(v);
}

vector<string> EPPCompiler::generate_targ_commands(){
    ExprTreeNode* evl = targ.expr_trees.back();
    vector<string> comm;
    if(evl->left->type == "DEL"){
            int addr = targ.last_deleted;
            string ans = "DEL = mem["+std::to_string(addr)+"]";
            comm.push_back(ans);
            return comm;
        }
    return helcomm(comm,targ.symtable,evl);
}

void EPPCompiler::write_to_file(vector<string> commands){
    ofstream file(output_file);
    for(int i = 0; i < commands.size();i++){
        file<<commands[i]<<endl;
    }
    file.close();
}

EPPCompiler::~EPPCompiler(){
//   delete &targ;
//   delete &least_mem_loc;
}

// int main()
// {
//     // std::cout << "A" << std::endl;
//     EPPCompiler x = EPPCompiler("t4.txt", 4);
//     // std::cout << "A" << std::endl;
//     // vector<string> v1 = {"x", ":=", "3"};
//     // vector<string> v2 = {"y", ":=", "5"};
//     // vector<string> v6 = {"z", ":=", "7"};
//     // vector<string> v3 = {"del", ":=", "x"};
//     // vector<string> v4 = {"del", ":=", "y"};
//     // vector<string> v5 = {"w", ":=", "(", "5", "+", "(", "z", "/", "2", ")", ")"};
//     // vector<string> v7 = {"ret", ":=", "w"};
//     // std::cout << "B" << std::endl;
//     // vector<vector<string> > v = {v1, v2, v6, v3, v4, v5, v7};
//     // x.compile(v);
//     // cout<<"compiled"<<endl;
//     vector<string> v1 = {"x", ":=", "3"};
//     vector<string> v2 = {"y", ":=", "2"};
//     vector<string> v6 = {"z", ":=", "(", "x", "-", "y", ")"};
//     vector<string> v3 = {"ret", ":=", "z"};
//     vector<vector<string>> v = {v1, v2, v6, v3};
//     x.compile(v);
//     cout<<"compiled"<<endl;
// }
