/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your expression below this line

int pow(int p){
    int ans = 1;
    for(int k = 0; k < p; k++){
        ans *= 10;
    }
    return ans;
}

int tonum(string s){
    if(s[0]=='-'){
        int sign = -1;
        int size = s.size()-1;
        int sum = 0;
        for(int i = 1;i < size+1;i++){
            sum += (s[i]-'0')*(pow((size-i)));
        }
        return sign*sum;
    }
    else if(s[0]=='0'){
        return 0;
    }
    else{
        int size = s.size();
        int sum = 0;
        for(int i = 0;i < size;i++){
            sum += (s[i]-'0')*(pow((size-i-1)));
        }
        return sum;
    }
}

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

Parser::Parser(){
    symtable = new SymbolTable();
}

void Parser::parse(vector<string> expression){
    vector<ExprTreeNode*> Nd;
    vector<string> Cr;
    string p[5] = { "+","-","/","*",")"};
    int q[5] = {1,1,2,2,0};
    for (int i = 2; i < (int)expression.size(); i++)
    {
        if (expression[i] == "(") {
            Cr.push_back(expression[i]);
        }
        else if(isnumb(expression[i])){
            int numb = tonum(expression[i]);
            ExprTreeNode* temp = new ExprTreeNode("VAL",numb);
            Nd.push_back(temp);
        }
        else if (isalpha(expression[i][0]) != 0)
        {
            int use;
            ExprTreeNode* temp = new ExprTreeNode("VAR",use);
            temp->id = expression[i];
            Nd.push_back(temp);
        }
        else if (findp(expression[i],p,q)>0)
        {
            while (
                (!Cr.empty() && Cr.back() != "(")
                && ((findp(Cr.back(),p,q) >= findp(expression[i],p,q))))
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
                int use;
                ExprTreeNode* temp = new ExprTreeNode(typ,use);
                ExprTreeNode* temp1 = Nd.back();
                Nd.pop_back();
                ExprTreeNode* temp2 = Nd.back();
                Nd.pop_back();
                temp->left = temp2;
                temp->right = temp1;
                Nd.push_back(temp);
            }
            Cr.push_back(expression[i]);
        }
        else if (expression[i] == ")") {
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
                int use;
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
    if(expression[0]=="ret"){
        assgn->left->type = "RET";
    }
    else if(expression[0]=="del"){
        assgn->left->type = "DEL";
        last_deleted = symtable->search(assgn->right->id);
        symtable->remove(assgn->right->id);
    }
    else{
        assgn->left->type = "VAR";
        assgn->left->id = expression[0];
        symtable->insert(expression[0]);
    }
    expr_trees.push_back(assgn);
}

Parser::~Parser(){
    if (symtable != NULL)
  delete symtable;
  symtable = NULL;
}