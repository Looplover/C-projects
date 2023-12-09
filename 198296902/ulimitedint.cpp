/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include <iostream>
#include "ulimitedint.h"
UnlimitedInt* abs(UnlimitedInt* i){
    UnlimitedInt* absl = new UnlimitedInt(i->get_array(),i->get_size(),1,i->get_size());
    return absl;
}   
UnlimitedInt* slice(UnlimitedInt* i1,int i){
    int* newt = new int[i+1];
    for(int j = 0; j < i+1; j++){
        newt[j] = i1->get_array()[j];
    }
    UnlimitedInt* ans = new UnlimitedInt(newt,i+1,i1->get_sign(),i+1);
    return ans;
}
bool large(UnlimitedInt* j1, UnlimitedInt* j2){
        if(j1->get_size()>j2->get_size()){
            return true;
        }
        else if(j1->get_size()<j2->get_size()){
            return false;
        }
        else{
            for(int i = 0; i < j1->get_size();i++){
                if(j1->get_array()[i] > j2->get_array()[i]){
                    return true;
                }
                else if(j2->get_array()[i] > j1->get_array()[i]){
                    return false;
                }
            }
        return false;
    }}

UnlimitedInt::UnlimitedInt(){
    this->size = 0;
    this->capacity = 50;
    this->unlimited_int = new int[capacity];
    this->sign = 0;
}

UnlimitedInt::UnlimitedInt(int* unlimited_int,int cap, int sgn, int sz){
    this->unlimited_int = unlimited_int;
    this->capacity = cap;
    this->sign = sgn;
    this->size= sz;
}

UnlimitedInt::UnlimitedInt(string s){
    if(s[0]=='-'){
        sign = -1;
        size = s.size()-1;
        capacity = size;
        unlimited_int = new int[capacity];
        for(int i = 1;i < size+1;i++){
            unlimited_int[i-1] = s[i]-'0';
        }
    }
    else if(s[0]=='0'){
        sign = 0;
        unlimited_int = new int[1];
        unlimited_int[0] = 0;
        size = 1;
        capacity = 1;
    }
    else{
        sign = 1;
        size = s.size();
        capacity = size;
        unlimited_int = new int[capacity];
        for(int i = 0;i < size;i++){
            unlimited_int[i] = s[i]-'0';
        }
    }
} // Create from            string 
UnlimitedInt::UnlimitedInt(int i){
    string s = std::to_string(i);
    if(s[0]=='-'){
        this->sign = -1;
        this->size = s.size()-1;
        this->capacity = size;
        this->unlimited_int = new int[capacity];
        for(int i = 1;i < size+1;i++){
            this->unlimited_int[i-1] = s[i]-'0';
        }
    }
    else if(s[0]=='0'){
        this->sign = 0;
        this->unlimited_int= new int[1];
        this->unlimited_int[0] = 0;
        this->size = 1;
        this->capacity = 1;
    }
    else{
        this->sign = 1;
        this->size = s.size();
        this->capacity = size;
        this->unlimited_int = new int[capacity];
        for(int i = 0;i < size;i++){
            this->unlimited_int[i] = s[i]-'0';
        }
    }
} // Create from int

UnlimitedInt::~UnlimitedInt(){
    delete this->unlimited_int;
}

// Return the size of the unlimited int
int UnlimitedInt::get_size(){
    return this->size;
}

// Return the unlimited_int array
int* UnlimitedInt::get_array(){
    return this->unlimited_int;
}

// Get sign
int UnlimitedInt::get_sign(){
    return this->sign;
}

// Implement these integer operations as they are defined for integers in mathematics
// (Since there are no size restrictions)
UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* i11 = new UnlimitedInt(i1->get_array(),i1->get_size(),1,i1->get_size());
    UnlimitedInt* i22 = new UnlimitedInt(i2->get_array(),i2->get_size(),1,i2->get_size());
    if((!large(i11,i22) && !large(i22,i11))&& i1->get_sign()*i2->get_sign()<0){
        UnlimitedInt* ansh = new UnlimitedInt("0");
        return ansh;
    }
    if(i11->get_array()[0] == 0){
        return i22;
    }
    if(i22->get_array()[0] == 0){
        return i11;
    }
    int carry = 0;
    int len1 = i11->get_size();
    int len2 = i22->get_size();
    int digits = max(len1,len2)+1;
    if(i1->get_sign()*i2->get_sign()>=0){
    int* anar = new int[digits];
    if(digits-1==len1){
        int* small= new int[digits-1];
        for(int i = len2-1;i>=0;i--){
            small[len1-len2+i] = i22->unlimited_int[i];
        }
        for(int i = len1-len2-1;i>=0;i--){
            small[i] = 0;
        }
        for(int i = digits-1;i>=1;i--){
            int sum = i11->get_array()[i-1]+small[i-1]+carry;
            anar[i] = sum%10;
            carry = sum/10;
        }
        if(carry != 0){
            anar[0]=carry;
        }
    }
    else if(digits-1==len2){
        int* small= new int[digits-1];
        for(int i = len1-1;i>=0;i--){
            small[len2-len1+i] = i11->unlimited_int[i];
        }
        for(int i = len2-len1-1;i>=0;i--){
            small[i] = 0;
        }
        for(int i = digits-1;i>=1;i--){
            int sum = i22->get_array()[i-1]+small[i-1]+carry;
            anar[i] = sum%10;
            carry = sum/10;
        }
        if(carry != 0){
            anar[0]=carry;
        }
    }
    UnlimitedInt* ans = new UnlimitedInt();
    ans->capacity = digits;
    if(carry != 0){
        ans->size = digits;
    }
    else{
        ans->size = digits - 1;
        for(int j = 1; j < digits; j++){
            anar[j-1] = anar[j];
        }
    }
    ans->unlimited_int = anar;
    ans->sign = i1->get_sign();
    return ans;
    }
    else{
        carry = 0;
        int* sanar = new int[digits-1];
        if(digits-1==len1 || large(i11,i22)){
        int* small= new int[digits-1];
        for(int i = len2-1;i>=0;i--){
                small[len1-len2+i] = i22->unlimited_int[i];
        }
        for(int i = len1-len2-1;i>=0;i--){
            small[i] = 0;
        }
        for(int i = digits-2;i>=0;i--){
            int sum = i11->get_array()[i]-small[i]+carry;
            if(sum < 0){
            carry = -1;
            sanar[i] = sum+10;
            }
            else{
                sanar[i] = sum;
                carry = 0;
            }
        }
    }
    else if(digits-1==len2 || large(i22,i11)){
        int* small= new int[digits-1];
        for(int i = len1-1;i>=0;i--){
                small[len2-len1+i] = i11->unlimited_int[i];
        }
        for(int i = len2-len1-1;i>=0;i--){
            small[i] = 0;
        }
        for(int i = digits-2;i>=0;i--){
            int sum = i22->get_array()[i]-small[i]+carry;
            if(sum < 0){
            carry = -1;
            sanar[i] = sum+10;
            }
            else{
                carry = 0;
                sanar[i] = sum;
            }
        }
    }
    int k = 0;
    while(sanar[k] == 0){
        k++;
    }
    int* panar = new int[digits-k];
    int i = 0;
    int temp = k;
    while(i < digits-temp){
        panar[i] = sanar[k];
        i++;
        k++;
    }
    int sgn;
    if(large(i11,i22)){
        sgn = i1->get_sign();
    }
    else{
        sgn = i2->get_sign();
    }
    UnlimitedInt* ans = new UnlimitedInt(panar,digits-temp,sgn,digits-temp-1);
    return ans;
    }
}
UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* i11 = new UnlimitedInt(i1->get_array(),i1->get_size(),i1->get_sign(),i1->get_size());
    UnlimitedInt* nop = new UnlimitedInt(i2->get_array(),i2->capacity,(-1)*i2->get_sign(),i2->get_size());
    return add(i11,nop);
}
UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* i22 = new UnlimitedInt(i2->get_array(),i2->get_size(),1,i2->get_size());
    UnlimitedInt* i11 = new UnlimitedInt(i1->get_array(),i1->get_size(),1,i1->get_size());
    if(i11->get_array()[0] == 0 || i22->get_array()[0] == 0){
        UnlimitedInt* ansh = new UnlimitedInt("0");
        return ansh;
    }
    UnlimitedInt* sum = new UnlimitedInt("0");
    for(int i = i11->get_size() - 1; i >= 0 ;i--){
        UnlimitedInt* sum1 = new UnlimitedInt("0");
        for(int j = 0; j < i11->get_array()[i];j++){
            sum1 = add(sum1,i22);
        }
        int* newt = new int[i11->get_size()-1-i+sum1->get_size()];
        for(int l = 0; l < i11->get_size() - 1 - i + sum1->get_size();l++){
            if(l < sum1->get_size()){
                newt[l] = sum1->get_array()[l];
            }
            else{
                newt[l] = 0;
            }
        }
        sum1->unlimited_int = newt;
        sum1->size = i11->get_size()-1-i+sum1->get_size();
        sum = add(sum,sum1);
    }
    sum->sign = (i1->get_sign())*(i2->get_sign());
    return sum;
}
UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* i22 = new UnlimitedInt(i2->get_array(),i2->get_size(),1,i2->get_size());
    UnlimitedInt* i11 = new UnlimitedInt(i1->get_array(),i1->get_size(),1,i1->get_size());
    if(large(i22,i11)){
        if((i1->get_sign())*(i2->get_sign()) >= 0){
            UnlimitedInt* ans = new UnlimitedInt("0");
            return ans;
        }
        else{
            UnlimitedInt* ans = new UnlimitedInt("-1");
            return ans; 
        }
    }
    int* quo = new int[i11->get_size()];
    UnlimitedInt* rem = new UnlimitedInt("0");
    for(int i = 0; i < i11->get_size(); i++){
        int car = 0;
            int* remtem = new int[rem->get_size()+1];
            for(int k = 0; k < rem->get_size();k++){
                remtem[k]=rem->get_array()[k];
            }
            remtem[rem->get_size()] = i11->get_array()[i];
            int k = 0;
            while(remtem[k] == 0 && k < rem->get_size()){
                k++;
            }
            int lmp = k;
            int sz = rem->get_size();
            int* remtem2 = new int[sz-lmp+1];
            int l = 0;
            while(l < sz-lmp+1 && k < sz+1){
                remtem2[l] = remtem[k];
                l++;
                k++;
            }
            rem = new UnlimitedInt(remtem2,sz-lmp+1,1,sz-lmp+1);
            for(int j = 9; j>=0; j--){
                UnlimitedInt* tempo = new UnlimitedInt(j);
                UnlimitedInt* prod = mul(tempo,i22);
                if(!large(prod,rem)){
                    car = j;
                    break;
                }
            }
        quo[i] = car;
        UnlimitedInt* temp = new UnlimitedInt(car);
        UnlimitedInt* pro = mul(temp,i22);
        UnlimitedInt* diff = sub(rem,pro);
        rem = diff;
    }
    int m = i11->get_size();
    int k = 0;
    while(quo[k] == 0){
        k++;
    }
    int* panar = new int[m-k];
    int i = 0;
    int lmp = k;
    while(i < m-lmp && k < m){
        panar[i] = quo[k];
        i++;
        k++;
    }
    if((i1->get_sign())*(i2->get_sign())>0){
        UnlimitedInt* fans = new UnlimitedInt(panar,m-lmp,1,m-lmp);
        return fans;
    }
    else{
        UnlimitedInt* fans = new UnlimitedInt(panar,i11->get_size(),-1,m-lmp);
        UnlimitedInt* prodo = mul(abs(fans),abs(i2));
        if(!large(prodo,i11) && !large(i11,prodo)){
            return fans;
        }
        else{
            UnlimitedInt* min = new UnlimitedInt("1");
            UnlimitedInt* diffr = sub(fans,min);
            return diffr;
        }
    }
}
UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    if(large(i2,i1)){
            return sub(abs(i2),i1);
    }
    int* quo = new int[i1->get_size()];
    UnlimitedInt* rem = new UnlimitedInt("0");
    for(int i = 0; i < i1->get_size(); i++){
        int car = 0;
            int* remtem = new int[rem->get_size()+1];
            for(int k = 0; k < rem->get_size();k++){
                remtem[k]=rem->get_array()[k];
            }
            remtem[rem->get_size()] = i1->get_array()[i];
            int k = 0;
            while(remtem[k] == 0 && k < rem->get_size()){
                k++;
            }
            int lmp = k;
            int sz = rem->get_size();
            int* remtem2 = new int[sz-lmp+1];
            int l = 0;
            while(l < sz-lmp+1 && k < sz+1){
                remtem2[l] = remtem[k];
                l++;
                k++;
            }
            rem = new UnlimitedInt(remtem2,sz-lmp+1,1,sz-lmp+1);
            for(int j = 9; j>=0; j--){
                UnlimitedInt* tempo = new UnlimitedInt(j);
                UnlimitedInt* prod = mul(tempo,abs(i2));
                if(!large(prod,rem)){
                    car = j;
                    break;
                }
            }
        quo[i] = car;
        UnlimitedInt* temp = new UnlimitedInt(car);
        UnlimitedInt* pro = mul(temp,abs(i2));
        UnlimitedInt* diff = sub(rem,pro);
        rem = diff;
    }
    return rem;
}

// Conversion Functions 
string UnlimitedInt::to_string(){
    string ans;
    if(sign != -1){
        ans = "";
    }
    else{
        ans = "-";
    }
    for(int i = 0; i < size; i++){
        ans += (char)(unlimited_int[i]+'0');
    }
    return ans;
}

// int main(void){
//     UnlimitedInt * i1 = new UnlimitedInt("1");
//     UnlimitedInt * i2 = new UnlimitedInt("51");
//     UnlimitedInt * op = new UnlimitedInt();
//     UnlimitedInt* sum = op->mul(i1,i2);
//     cout<<i1->to_string()<<endl;
//     cout<<i2->to_string()<<endl;
//     cout<<sum->to_string()<<endl;
// }