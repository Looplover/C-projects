// Do NOT add any other includes
#include "dict.h"

Dict::Dict()
{
    root = new TriNode();
}

Dict::~Dict()
{
    delete root;
}

bool separator(char i)
{
    // if (i == '.' || i == ',' || i == '-' || i == ':' || i == '!' || i == '(' || i == ')' || i == '?' || i == ';' || i == '@' || i == '[' || i == ']' || i == '\'' || i == '\"' || i == ' '|| i=='˙'||)
    string s = ".,-:!\"\'()?—[]˙;@ ";
    if (s.find(i) != std::string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void master_insert(string word, TriNode *root)
{
    int ind;
    TriNode *curr = root;
    for (int i = 0; i < word.size(); i++)
    {
        ind = word[i];
        if (curr->get_children()[ind] == nullptr)
        {
            curr->get_children()[ind] = new TriNode(word[i]);
        }
        curr = curr->get_children()[ind];
        if (i == word.size() - 1)
        {
            curr->cnt_increment();
        }
    }
}
void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    string word = "";
    char character;
    for (char i : sentence)
    {
        character = i;
        if (separator(i))
        {
            if (word != "")
            {
                master_insert(word, root);
            }
            word = "";
        }
        else
        {
            int ascii = i;
            if (ascii >= 65 && ascii <= 90)
            {
                ascii += 32;
            }
            char alphabet = ascii;
            character = alphabet;
            word = word + alphabet;
        }
    }
    // if (word != "")
    if (!separator(character))
    {
        master_insert(word, root);
    }
}

int Dict::get_word_count(string word)
{
    int ind;
    TriNode *curr = root;
    int i = 0;
    for (i; i < word.size(); i++)
    {
        ind = word[i];
        if (curr->get_children()[ind] == nullptr)
        {
            break;
        }
        curr = curr->get_children()[ind];
        if (i == word.size() - 1 && curr != nullptr)
        {
            return curr->get_count();
        }
    }
    return 0;
}

/*int Dict::get_word_count(string word)
{
    int ind = word[0];
    TriNode *curr;
    if (root->get_children()[ind] != NULL)
    {
        curr = root->get_children()[ind];
    }
    else
    {
        return -1;
    }
    for (int i = 0; i < word.size(); i++)
    {
        if (curr->get_alphabet() != word[i])
        {
            break;
        }
        if (i < word.size() - 1)
        {
            ind = word[i + 1];
            if (curr->get_children()[ind] != NULL)
            {
                curr = curr->get_children()[ind];
            }
            else
            {
                break;
            }
        }
        else
        {
            if (curr->get_alphabet() == word[i])
            {
                return curr->get_count();
            }
        }
    }
    return -1;
}*/

void recursion(TriNode *root, string suffix, string filename)
{
    string suffix_prime = suffix;
    if (root->get_alphabet() != ' ')
    {
        suffix_prime = suffix_prime + (root->get_alphabet());
    }
    if (root->get_count() >= 1)
    {
        ofstream file(filename, ios::out | ios::app);
        file << suffix_prime;
        file << ", ";
        file << std::to_string(root->get_count()) << endl;
        file.close();
    }
    for (int i = 0; i < 128; i++)
    {
        if (root->get_children()[i])
        {
            // string suffix_prime = suffix + (root->get_alphabet());

            recursion(root->get_children()[i], suffix_prime, filename);
        }
    }
}

void Dict::dump_dictionary(string filename)
{
    recursion(root, "", filename);
}

TriNode::TriNode()
{
    count = 0;
    alphabet = ' ';
}

TriNode::TriNode(char character)
{
    count = 0;
    alphabet = character;
}

TriNode::~TriNode()
{
    for (int i = 0; i < 128; i++)
    {
        delete children[i];
    }
    delete[] children;
    // delete &sentences;
}

char TriNode::get_alphabet()
{
    return alphabet;
}

int TriNode::get_count()
{
    return count;
}

TriNode **TriNode::get_children()
{
    return children;
}

void TriNode::cnt_increment()
{
    if (count == -1)
    {
        count = 1;
    }
    else
    {
        count++;
    }
}
/*
int main()
{
    Dict d;
    d.insert_sentence(0, 0, 0, 0, "I am happy");
    d.insert_sentence(0, 0, 0, 0, "I Am sad");
    d.insert_sentence(0, 0, 0, 0, "It is cold today");
    d.insert_sentence(0, 0, 0, 0, "The cats are fighting");
    d.insert_sentence(0, 0, 0, 0, "akshat@511");
    d.insert_sentence(0, 0, 0, 0, "akshat ,shrenik");
    d.insert_sentence(0, 0, 0, 0, "abcd:pqrs");
    d.insert_sentence(0, 0, 0, 0, "abrw,shd ");
    d.dump_dictionary("test.txt");
    return 0;
}
*/