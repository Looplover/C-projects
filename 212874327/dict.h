// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class TriNode
{
private:
    // private attributes
    char alphabet;
    TriNode **children = new TriNode *[128] {};
    // vector<vector<int>> sentences;
    //  a vector of vectors having info of all sentences that this fragment is a overlap of so you just return these as nodes of linked list directly ;)

public:
    TriNode();
    long long count;
    TriNode(char alpha, long long count, vector<vector<int>> sentences);
    TriNode(char alpha);

    ~TriNode();

    char get_alphabet();
    void cnt_increment();
    long long get_count();

    TriNode **get_children();
};

class Dict
{
private:
    // You can add attributes/helper functions here
    TriNode *root;

public:
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    long long get_word_count(string word);

    void dump_dictionary(string filename);

    void master_insert1(string word, long long ct);

    /* -----------------------------------------*/
};
