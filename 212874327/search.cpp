// Do NOT add any other includes
#include "search.h"

textnode::textnode(int bookcode, int pag, int para, int sent, string tex)
{
    book_code = bookcode;
    page = pag;
    paragraph = para;
    sentence_no = sent;
    text = tex;
    nxt = nullptr;
    prev = nullptr;
}

SearchEngine::SearchEngine()
{
}

SearchEngine::~SearchEngine()
{
    while (root != nullptr)
    {
        textnode *x = root->nxt;
        delete root;
        root = x;
    }
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    string text = "";
    for (char i : sentence)
    {
        int val = i;
        if (val >= 65 && val <= 90)
        {
            val += 32;
        }
        char charac = val;
        text = text + charac;
    }
    textnode *t = new textnode(book_code, page, paragraph, sentence_no, text);
    if (root)
    {
        t->prev = tail;
        tail->nxt = t;
        tail = t;
    }
    else
    {
        root = t;
        tail = t;
    }

    /*for (auto i : text)
    {
        std::cout << i;
    }
    std::cout << std::endl;*/
}
bool separator2(char i)
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
long long pow(int num, int exp)
{
    long long ans = 1;
    long long LARGE_PRIME = 199999;
    for (int i = 0; i < exp; i++)
    {
        ans *= num;
        ans %= LARGE_PRIME;
    }
    return ans;
}

int hash_val(vector<char> pattern)
{
    long long LARGE_PRIME = 199999;
    long long size = pattern.size();
    long long val = pattern[0];
    long long sum = val;
    for (long i = 1; i < size; i++)
    {
        /*val = pattern[i];
        sum += val;
        sum %= LARGE_PRIME;
        sum *= 256;
        sum %= LARGE_PRIME;*/
        val = pattern[i];
        sum = (sum * 512) % LARGE_PRIME;
        sum = (sum + val) % LARGE_PRIME;
        // sum += val;
    }
    return sum;
}

int update_hash(int init_hash, char char_rem, char char_add, int length)
{
    long long LARGE_PRIME = 199999;
    long long rem = char_rem;
    long long add = char_add;
    // long long ans = ((((init_hash + LARGE_PRIME - (rem * pow(256, length - 1))) % LARGE_PRIME) * 256) + add) % LARGE_PRIME;
    long long ans = (((((init_hash + LARGE_PRIME - ((rem * pow(512, length - 1)) % LARGE_PRIME)) % LARGE_PRIME) * 512) % LARGE_PRIME) + add) % LARGE_PRIME;
    // long long ans = init_hash + add - rem;
    return ans;
}

int SearchEngine::helsearch(string pattern, string corpa){
    vector<char> patvec;
    int n_matches = 0;
    for (char i : pattern)
    {
        int val = i;
        if (val >= 65 && val <= 90)
        {
            val += 32;
        }
        char charac = val;
        patvec.push_back(charac);
        // cout << charac << endl;
    }
    int hash_val_pattern = hash_val(patvec);
    int length = pattern.size();
        // cout << curr->text.size() << endl;
        // cout << length << endl;
    if (corpa.size() >= length)
    {
        int k = 0;
        vector<char> codevec;
        for (int j = 0; j < length; j++)
        {
            codevec.push_back(corpa[j]);
        }
        int hash_value = hash_val(codevec);
        while (k + length < corpa.size() + 1)
        {
            // std::cout << curr->text[k] << std::endl;
            if (k > 0)
            {
                hash_value = update_hash(hash_value, corpa[k - 1], corpa[k + length - 1], length);
                // cout << "abc" << endl;
            }
            if (hash_val_pattern == hash_value)
            {
                int flag = 1;
                for (int j = k; j < k + length; j++)
                {
                    if (patvec[j - k] != corpa[j])
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag)
                {
                    if (k == 0)
                    {
                        if (k + length == corpa.size())
                        {
                            n_matches++;
                        }
                        else
                        {
                            if (separator2(corpa[k + length]))
                            {
                                n_matches++;
                            }
                        }
                    }
                    else
                    {
                        if (separator2(corpa[k - 1]))
                        {
                            if (k + length == corpa.size())
                            {
                                n_matches++;
                            }
                            else
                            {
                                if (separator2(corpa[k + length]))
                                {
                                    n_matches++;
                                }
                            }
                        }
                    }
                }
            
            }
            k++;
        }
    }
    return n_matches;
}

Node *SearchEngine::search(string pattern, int &n_matches)
{
    Node *result = nullptr;
    Node *end = nullptr;
    vector<char> patvec;
    n_matches = 0;
    for (char i : pattern)
    {
        int val = i;
        if (val >= 65 && val <= 90)
        {
            val += 32;
        }
        char charac = val;
        patvec.push_back(charac);
        // cout << charac << endl;
    }
    /*for (char i : pattern)
    {
        //std::cout << i;
        int val = i;
        if (val >= 65 && val <= 90)
        {
            val += 32;
        }
        char charac = val;
        pt=pt+charac;
    }*/
    int hash_val_pattern = hash_val(patvec);
    int length = pattern.size();
    textnode *curr = root;
    // while (curr != nullptr)
    // {
    //     cout << curr->text << endl;
    //     curr = curr->nxt;
    // }
    while (curr != nullptr)
    {
        // cout << curr->text.size() << endl;
        // cout << length << endl;
        if (curr->text.size() >= length)
        {
            int k = 0;
            vector<char> codevec;
            for (int j = 0; j < length; j++)
            {
                codevec.push_back(curr->text[j]);
            }
            int hash_value = hash_val(codevec);
            while (k + length < curr->text.size() + 1)
            {
                // std::cout << curr->text[k] << std::endl;
                if (k > 0)
                {
                    hash_value = update_hash(hash_value, curr->text[k - 1], curr->text[k + length - 1], length);
                    // cout << "abc" << endl;
                }
                if (hash_val_pattern == hash_value)
                {
                    int flag = 1;
                    // cout << "abc" << endl;
                    for (int j = k; j < k + length; j++)
                    {
                        if (patvec[j - k] != curr->text[j])
                        {
                            flag = 0;
                            break;
                        }
                    }
                    // cout << "abc" << endl;
                    if (flag)
                    {
                        if (result != nullptr)
                        {
                            // cout << curr->book_code << curr->page << curr->paragraph << curr->sentence_no << k << " " << curr->text[k] << endl;
                            Node *x = new Node(curr->book_code, curr->page, curr->paragraph, curr->sentence_no, k);
                            /*result->left = root->left;
                            result->right = root;
                            root->left = result;
                            root = result;
                            n_matches++;*/
                            // x->right = result->right;
                            // x->left = result;
                            // result->right = x;
                            // result=x;
                            // x->right = result;
                            // result->left = x;

                            // result = x;
                            n_matches++;
                            x->left = end;
                            end->right = x;
                            end = x;
                            /*x->left = result;
                            result->right = x;
                            result = x;
                            n_matches++;*/
                        }
                        else
                        {
                            // cout << curr->book_code << curr->page << curr->paragraph << curr->sentence_no << k << " " << curr->text[k] << endl;
                            result = new Node(curr->book_code, curr->page, curr->paragraph, curr->sentence_no, k);
                            n_matches++;
                            end = result;
                        }
                    }
                }
                k++;
            }
        }
        curr = curr->nxt;
    }
    return result;
}
/*
int main()
{
    vector<char> pattern = {'i', ' ', 'a', 'm', ' ', 's', 'a', 'd'};
    vector<char> pattern1 = {' ', 'a', 'm', ' ', 's', 'a', 'd', 's'};
    cout << hash_val(pattern) << endl;
    cout << hash_val(pattern1) << endl;
    cout << update_hash(hash_val(pattern), 'i', 's', 8) << endl;
    SearchEngine s;
    s.insert_sentence(0, 0, 0, 0, "My name@?><;: is Akshat.");
    s.insert_sentence(1, 0, 0, 0, "My~\\ name _=-+)(is Ram.");
    s.insert_sentence(2, 0, 0, 0, "My name is !@#$%^&*Rahul.");
    s.insert_sentence(3, 0, 0, 0, "My name is,/\'\" Rohan.");
    s.insert_sentence(1, 350, 0, 1, "VOL.1: 1884 30 NOVEMBER, 1896 351");
    int y = 0;
    vector<char> pattern1 = {'3', '0', ' ', 'N', 'O', 'V', 'E', 'M', 'B', 'E', 'R', ',', ' ', '1', '8', '9', '6'};
    Node *x = s.search("1", y);
    cout << hash_val(pattern1) << endl;
    std::cout << y << std::endl;
    while (x != nullptr)
    {
        std::cout << x->book_code << std::endl;
        x = x->right;
    }
}*/
