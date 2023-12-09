/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include <iostream>
#include "ulimitedrational.h"

    bool blarge(UnlimitedInt* j1, UnlimitedInt* j2){
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

    UnlimitedRational* reduce(UnlimitedRational* r){
        UnlimitedInt* p0 = r->get_p();
        UnlimitedInt* q0 = r->get_q();
        UnlimitedInt* op;
        if(blarge(q0,p0)){
            UnlimitedInt* temp = p0;
            p0 = q0;
            q0 = temp;
        }
        UnlimitedInt* rem = q0;
        UnlimitedInt* big = p0;
        while(op->mod(big,rem)->get_array()[0] != 0){
            UnlimitedInt* tempo = rem;
            rem = op->mod(big,rem);
            big = tempo;
        }
        UnlimitedRational* ans = new UnlimitedRational(op->div(r->get_p(),rem),op->div(r->get_q(),rem));
        return ans;
    }

    UnlimitedRational::UnlimitedRational(){
        p = new UnlimitedInt();
        q = new UnlimitedInt();
    }

    UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
        p = new UnlimitedInt(num->get_array(),num->get_size(),num->get_sign(),num->get_size());
        q = new UnlimitedInt(den->get_array(),den->get_size(),den->get_sign(),den->get_size());
    }

    UnlimitedRational::~UnlimitedRational(){
        delete p;
        delete q;
    }

    UnlimitedInt* UnlimitedRational::get_p(){
        UnlimitedInt* pn = new UnlimitedInt(p->get_array(),p->get_size(),p->get_sign(),p->get_size());
        return pn;
    }

    UnlimitedInt* UnlimitedRational::get_q(){
        UnlimitedInt* qn = new UnlimitedInt(q->get_array(),q->get_size(),q->get_sign(),q->get_size());
        return qn;
    }

    string UnlimitedRational::get_p_str(){
        string ans = get_p()->to_string();
        return ans;
    } // Return the numerator as a string

    string UnlimitedRational::get_q_str(){
        string ans = get_q()->to_string();
        return ans;
    } // Return the denominator as a string
    
    string UnlimitedRational::get_frac_str(){
        string ans = get_p_str() + '/' + get_q_str();
        return ans;
    } // Return the rational as "p/q"

    // Rational arithmetic operations
    UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2){
        UnlimitedInt* p1 = i1->get_p();
        UnlimitedInt* p2 = i2->get_p();
        UnlimitedInt* q1 = i1->get_q();
        UnlimitedInt* q2 = i2->get_q();
        UnlimitedInt* mul1 = UnlimitedInt::mul(p1,q2);
        UnlimitedInt* mul2 = UnlimitedInt::mul(p2,q1);
        UnlimitedInt* num = UnlimitedInt::add(mul1,mul2);
        UnlimitedInt* den = UnlimitedInt::mul(q1,q2);
        UnlimitedRational* ans = new UnlimitedRational(num,den);
        return reduce(ans);
    }

    UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2){
        UnlimitedInt* p1 = i1->get_p();
        UnlimitedInt* p2 = i2->get_p();
        UnlimitedInt* q1 = i1->get_q();
        UnlimitedInt* q2 = i2->get_q();
        UnlimitedInt* op = new UnlimitedInt();
        UnlimitedRational* ans = new UnlimitedRational(op->sub(op->mul(p1,q2),op->mul(p2,q1)),op->mul(q1,q2));
        return reduce(ans);
    }

    UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2){
        UnlimitedInt* p1 = i1->get_p();
        UnlimitedInt* p2 = i2->get_p();
        UnlimitedInt* q1 = i1->get_q();
        UnlimitedInt* q2 = i2->get_q();
        UnlimitedInt* op;
        UnlimitedRational* ans = new UnlimitedRational(op->mul(p1,p2),op->mul(q1,q2));
        return reduce(ans);
    }

    UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2){
        UnlimitedInt* p1 = i1->get_p();
        UnlimitedInt* p2 = i2->get_p();
        UnlimitedInt* q1 = i1->get_q();
        UnlimitedInt* q2 = i2->get_q();
        UnlimitedInt* op;
        UnlimitedRational* ans = new UnlimitedRational(op->mul(p1,q2),op->mul(q1,p2));
        return reduce(ans);
    }

// int main(void){
//     UnlimitedInt * p1 = new UnlimitedInt("13");
//     UnlimitedInt * q1 = new UnlimitedInt("1");
//     UnlimitedInt * p2 = new UnlimitedInt("2");
//     UnlimitedInt * q2 = new UnlimitedInt("51");
//     UnlimitedRational* r1 = new UnlimitedRational(p1,q1);
//     UnlimitedRational* r2 = new UnlimitedRational(p2,q2);
//     UnlimitedRational * op = new UnlimitedRational();
//     UnlimitedRational* sum = op->add(r1,r2);
//     cout<<r1->get_frac_str()<<endl;
//     cout<<r2->get_frac_str()<<endl;
//     cout<<sum->get_frac_str()<<endl;
// }
