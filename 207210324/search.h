// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;
class textnode
{
public:
    string text;
    textnode *nxt;
    textnode *prev;

    int book_code;
    int page;
    int paragraph;
    int sentence_no;

    textnode(int book_code, int page, int para, int sent, string text);
};

class SearchEngine
{
private:
    // You can add attributes/helper functions here

public:
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    textnode *root = nullptr;
    textnode *tail = nullptr;
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node *search(string pattern, int &n_matches);

    /* -----------------------------------------*/
};
