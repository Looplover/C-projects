/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"


SymEntry::SymEntry(){
    left = nullptr;
    right = nullptr;
}

SymEntry::SymEntry(string k, UnlimitedRational* v){
    left = nullptr;
    right = nullptr;
    key = k;
    val = v;
}

SymEntry::~SymEntry(){
    delete left;
    delete right;
    delete val;
}