/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include <iostream>
#include "evaluator.h"

    int findp(string op,string* p, int* q){
        int j = 0;
        while(p[j] != op){
            j++;
        }
        if(p[j] == op){
            return q[j];
        }
        else{
            return -1;
        }
    }
    bool isnumb(string s){
        if(s[0] == '-' && isdigit(s[1])){
            return true;
        }
        else if(isdigit(s[0]) ){
            return true;
        }
        return false;
    }

    Evaluator::Evaluator(){
        symtable = new SymbolTable();
    }

    Evaluator::~Evaluator(){
        delete symtable;
    }

    // Read an input vector of tokens (strings)
    // Parse it and convert it to a parse tree
    // Push the root of the tree in the expr_trees
    void Evaluator::parse(vector<string> code){
    vector<ExprTreeNode*> Nd;
    vector<string> Cr;
    string p[5] = { "+","-","/","*",")"};
    int q[5] = {1,1,2,2,0};
    for (int i = 2; i < (int)code.size(); i++)
    {
        if (code[i] == "(") {
            Cr.push_back(code[i]);
        }
        else if(isnumb(code[i])){
            UnlimitedInt* numb = new UnlimitedInt(code[i]);
            UnlimitedInt* one = new UnlimitedInt("1");
            UnlimitedRational* daal = new UnlimitedRational(numb,one);
            ExprTreeNode* temp = new ExprTreeNode("VAL",daal);
            Nd.push_back(temp);
        }
        else if (isalpha(code[i][0]) != 0)
        {
            UnlimitedInt* use = new UnlimitedInt();
            ExprTreeNode* temp = new ExprTreeNode("VAR",use);
            temp->id = code[i];
            Nd.push_back(temp);
        }
        else if (findp(code[i],p,q)>0)
        {
            while (
                (!Cr.empty() && Cr.back() != "(")
                && ((findp(Cr.back(),p,q) >= findp(code[i],p,q))))
            {
                string op = Cr.back();
                Cr.pop_back();
                string typ;
                if(op == "+"){
                    typ = "ADD";
                }
                else if(op == "-"){
                    typ = "SUB";
                }
                else if(op == "/"){
                    typ = "DIV";
                }
                else if(op == "*"){
                    typ = "MUL";
                }
                UnlimitedInt* use = new UnlimitedInt();
                ExprTreeNode* temp = new ExprTreeNode(typ,use);
                ExprTreeNode* temp1 = Nd.back();
                Nd.pop_back();
                ExprTreeNode* temp2 = Nd.back();
                Nd.pop_back();
                temp->left = temp2;
                temp->right = temp1;
                Nd.push_back(temp);
            }
            Cr.push_back(code[i]);
        }
        else if (code[i] == ")") {
            while (!Cr.empty() && Cr.back() != "(")
            {
                string op = Cr.back();
                Cr.pop_back();
                string typ;
                if(op == "+"){
                    typ = "ADD";
                }
                else if(op == "-"){
                    typ = "SUB";
                }
                else if(op == "/"){
                    typ = "DIV";
                }
                else if(op == "*"){
                    typ = "MUL";
                }
                UnlimitedInt* use = new UnlimitedInt();
                ExprTreeNode* temp = new ExprTreeNode(typ,use);
                ExprTreeNode* temp1 = Nd.back();
                Nd.pop_back();
                ExprTreeNode* temp2 = Nd.back();
                Nd.pop_back();
                temp->left = temp2;
                temp->right = temp1;
                Nd.push_back(temp);
            }
            if(!Cr.empty()){
                Cr.pop_back();
            }
        }
    }
    ExprTreeNode* tempo = Nd.back();
    ExprTreeNode* assgn = new ExprTreeNode();
    assgn->type = "ADD";
    assgn->id = "o";
    assgn->right = tempo;
    assgn->left = new ExprTreeNode();
    assgn->left->type = "VAR";
    assgn->left->id = code[0];
    expr_trees.push_back(assgn);
}

    // Evaluate the last element of the expr_trees
    // This function is guaranteed to be called immediately 
    // after a call to parse, and will be only called ONCE
    // for a tree
    // Also populate the symbol tables
    void Evaluator::eval(){
        ExprTreeNode* evl = expr_trees.back();
        UnlimitedRational* op = new UnlimitedRational();
        expr_trees.pop_back();
        if(evl == nullptr){
            return;
        }
        if(evl->type == "ADD" && evl->id != "o"){
            expr_trees.push_back(evl->left);
            expr_trees.push_back(evl->right);
            eval();
            eval();
            evl->evaluated_value = op->add(evl->left->evaluated_value,evl->right->evaluated_value);
            return; 
        }
        else if(evl->type == "SUB"){
            expr_trees.push_back(evl->left);
            expr_trees.push_back(evl->right);
            eval();
            eval();
            evl->evaluated_value = op->sub(evl->left->evaluated_value,evl->right->evaluated_value); 
            return;
        }
        else if(evl->type == "DIV"){
            expr_trees.push_back(evl->left);
            expr_trees.push_back(evl->right);
            eval();
            eval();
            evl->evaluated_value = op->div(evl->left->evaluated_value,evl->right->evaluated_value); 
            return;
        }
        else if(evl->type == "MUL"){
            expr_trees.push_back(evl->left);
            expr_trees.push_back(evl->right);
            eval();
            eval();
            evl->evaluated_value = op->mul(evl->left->evaluated_value,evl->right->evaluated_value);
            return;
        }
        else if(evl->type == "VAR" && evl->id != ""){
            evl->evaluated_value = symtable->search(evl->id);
            return;
        }
        else if(evl->type == "VAL"){
            evl->evaluated_value = evl->val;
            return;
        }
        else{
            expr_trees.push_back(evl->right);
            eval();
            evl->evaluated_value = evl->right->evaluated_value;
            symtable->insert(evl->left->id,evl->right->evaluated_value);
            expr_trees.push_back(evl);
            return;
        }
    }
//c:=(((a+b)*3)-7)

// int main(void){
//     Evaluator* evall = new Evaluator();
//     vector<string> code;
//     code.push_back("pow5");
//     code.push_back(":=");
//     code.push_back("(");
//     code.push_back("(");
//     code.push_back("5");
//     code.push_back("*");
//     code.push_back("42");
//     code.push_back(")");
//     code.push_back("/");
//     code.push_back("(");
//     code.push_back("pow4");
//     code.push_back("*");
//     code.push_back("pow4");
//     code.push_back(")");
//     code.push_back(")");
//     evall->parse(code);
//     ExprTreeNode* root = evall->expr_trees.back();
//     // cout<<root->type<<endl;
//     // cout<<root->left->id<<endl;
//     // cout<<root->right->type<<endl;
//     // cout<<root->right->left->type<<endl;
//     // cout<<root->right->left->left->type<<endl;
//     // cout<<root->right->left->left->left->id<<endl;
//     // cout<<root->right->left->left->right->id<<endl;
//     // cout<<root->right->right->val->get_frac_str()<<endl;
//     // cout<<root->right->left->right->val->get_frac_str()<<endl;
//     UnlimitedInt* l = new UnlimitedInt("2");
//     UnlimitedInt* m = new UnlimitedInt("1");
//     UnlimitedRational* po = new UnlimitedRational(l,m);
//     evall->symtable->insert("pow4",po);
//     evall->eval();
//     cout<<evall->symtable->search("pow5")->get_frac_str()<<endl;

// }