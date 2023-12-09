#include <assert.h>
#include <sstream>
#include "qna_tool.h"

using namespace std;

#define FILENAME "mahatma-gandhi-collected-works-volume-1.txt"

bool sep(char i)
{
    //cout << "sep" << endl;
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

textnode *finder(int book_code, int page, int paragraph, int sentence_no, SearchEngine *src)
{
    //cout << "finder" << endl;
    textnode *curr = src->root;
    while (curr != nullptr)
    {
        if (curr->book_code == book_code && curr->page == page && curr->paragraph == paragraph && curr->sentence_no == sentence_no)
        {
            return curr;
        }
        curr = curr->nxt;
    }
    return nullptr;
}

QNA_tool::QNA_tool()
{
    //cout << "constructor" << endl;
    search = new SearchEngine();
    texts = new Dict();
    repo = new Dict();
    maxheap = new maxHeap();
    int cnt=0;
    ifstream file;
        file.open("unigram_freq.csv");
        vector<string> row;
        string line, wrd, temp;
        getline(file, line);
        //cout << "constructor2" << endl;
        while (getline(file, line))
        {
            //cout << "constructor5" << endl;
            row.clear();
            stringstream s(line);
            char del = ',';
            while (getline(s, wrd, del))
            {
                //cout << "constructor6" << endl;
                row.push_back(wrd);
            }
            if (row.size() > 0)
            {
                //cout << "constructor7" << endl;
                if (row[0] != "")
                {
                    // cout << "constructor8" << endl;
                    // cout << "line " << line << endl;
                    // cout << "row" << endl;
                    // for (int i = 0;i<row.size();i++){
                    //     cout << row[i] << endl;
                    // }
                    // cout << row[1] << "row 1" << endl;
                    long long ct = stoll(row[1]);
                    //cout << "constructor9" << endl;
                    repo->master_insert1(row[0],ct);
                    cnt++;
                    //cout << "constructor4" << endl;
                    //break;
                }
            }
        }
        //cout <<cnt << endl;
}

QNA_tool::~QNA_tool()
{
    if (texts != nullptr)
    {
        delete texts;
    }
    if (repo != nullptr)
    {
        delete repo;
    }
    if(search != nullptr){
        delete search;
    }
}

void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    //cout << "insert" << endl;
    texts->insert_sentence(book_code, page, paragraph, sentence_no, sentence);
    search->insert_sentence(book_code, page, paragraph, sentence_no, sentence);
    return;
}

Node *QNA_tool::get_top_k_para(string question, int k)
{
    vector<string> words;
    string alp = "";
    for (char i : question)
    {
        string new_query="";

        if (sep(i))
        {
            if (alp != "")
            {
                words.push_back(alp);
                alp = "";
            }
        }
        else
        {
            int ind=i;
            if (ind>=65 && ind<=90){
                ind+=32;
            }
            char al=ind;
            alp += al;
        }
    }
    if (alp != "")
    {
        words.push_back(alp);
        alp = "";
    }
    textnode *paras = search->root;
    // textnode *books = new textnode(0,0,0,-1,"");
    int bc = 0;
    int pg = 0;
    int par = 0;
    int iter = 0;
    // string flg = "0,0,0";
    Dict *x = new Dict();
    while (paras != nullptr)
    {

        // if (to_string(paras->book_code) + "," + to_string(paras->page) + "," + to_string(paras->paragraph) != flg)
        if ((paras->book_code != bc) || (paras->page != pg) || (paras->paragraph != par))
        {
            long double namp = 0;
            for (auto word : words)
            {
                long double wsc = static_cast<long double>(texts->get_word_count(word) + 1) / static_cast<long double>(repo->get_word_count(word) + 1);
                long long freq = x->get_word_count(word);
                //std::cout<<texts->get_word_count(word)<<" "<<word<<
                //std::endl;
                namp += freq * wsc;
            }
            // std::cout<<namp<<std::endl;
            // std::cout<<bc<<" "<<pg<<" "<<par<<std::endl;
            if(iter < k){
            //cout << iter << " iter less than k" << endl;
            pair<Node *, long double> p;
            Node *tempos = new Node();
            tempos->book_code = bc;
            tempos->page = pg;
            tempos->paragraph = par;
            p.first = tempos;
            p.second = namp;
            maxheap->arr.push_back(p);
            maxheap->size = maxheap->size+1;
            if(iter == k-1){
            //cout << iter << " iter equal to k" << endl;
            maxheap->buildHeap();
        }
            iter++;
        }
        else if(iter>=k){
            //cout << iter << " iter greater to k" << endl;
            if(namp > maxheap->arr[0].second){
                pair<Node *, long double> p;
                Node *tempos = new Node();
                tempos->book_code = bc;
                tempos->page = pg;
                tempos->paragraph = par;
                p.first = tempos;
                p.second = namp;
                maxheap->arr[0] = p;
                iter++;
                maxheap->heapifyDown(0);
            }
            else{
                iter++;
                
            }
            // cout << "Heap" << endl;
            // for (int qe = 0;qe<maxheap->size;qe++){
            //     cout << maxheap->arr[qe].first->book_code << maxheap->arr[qe].second << "end";
            // }
        }
            // textnode *ans = new textnode(paras->book_code, paras->page, paras->paragraph, -1, paras->text);
            bc = paras->book_code;
            pg = paras->page;
            par = paras->paragraph;
            // books->nxt = ans;
            // ans->prev = books;
            delete x;
            x = new Dict();
            x->insert_sentence(paras->book_code, paras->page, paras->paragraph, -1, paras->text);
            paras = paras->nxt;
            // books = books->nxt;
        }
        else
        {
            // books->text += paras->text;
            x->insert_sentence(paras->book_code, paras->page, paras->paragraph, -1, paras->text);
            paras = paras->nxt;
        }
    }
    long double namp = 0;
    for (auto word : words)
    {
        long double wsc = static_cast<long double>(texts->get_word_count(word) + 1) / static_cast<long double>(repo->get_word_count(word) + 1);
        long long freq = x->get_word_count(word);
        namp += freq * wsc;
    }
    if(iter < k){
            //cout << iter << " iter less than k" << endl;
            pair<Node *, long double> p;
            Node *tempos = new Node();
            tempos->book_code = bc;
            tempos->page = pg;
            tempos->paragraph = par;
            p.first = tempos;
            p.second = namp;
            maxheap->arr.push_back(p);
            maxheap->size = maxheap->size+1;
            if(iter == k-1){
            //cout << iter << " iter equal to k" << endl;
            maxheap->buildHeap();
        }
            iter++;
        }
        else if(iter>=k){
            //cout << iter << " iter greater to k" << endl;
            if(namp > maxheap->arr[0].second){
                pair<Node *, long double> p;
                Node *tempos = new Node();
                Node* t=maxheap->arr[0].first;
                tempos->book_code = bc;
                tempos->page = pg;
                tempos->paragraph = par;
                p.first = tempos;
                p.second = namp;
                maxheap->arr[0] = p;
                iter++;
                maxheap->heapifyDown(0);
                delete t;
            }
            else{
                iter++;                
            }
            // cout << "Heap" << endl;
            // for (int qe = 0;qe<maxheap->size;qe++){
            //     cout << maxheap->arr[qe].first->book_code << maxheap->arr[qe].second << "end";
            // }
        }
    // textnode *ans = new textnode(paras->book_code, paras->page, paras->paragraph, -1, paras->text);

    /*int iter = 0;
    while (books->prev!=nullptr)
    {
        string content = books->text;
        long double namp = 0;
        for (auto word : words)
        {
            long double wsc = static_cast<long double>(texts->get_word_count(word) + 1) / static_cast<long double>(repo->get_word_count(word) + 1);
            int freq = search->helsearch(word, content);
            namp += freq * wsc;
        }
        if (iter == k)
        {
            maxheap->buildHeap();
            iter++;
        }
        else if (iter < k)
        {
            pair<Node *, long double> p;
            Node *tempos = new Node();
            tempos->book_code = books->book_code;
            tempos->page = books->page;
            tempos->paragraph = books->paragraph;
            p.first = tempos;
            p.second = namp;
            maxheap->arr.push_back(p);
            maxheap->size++;
            books = books->prev;
            iter++;
        }
        else{
            if (namp > maxheap->arr[0].second)
            {
                pair<Node *, long double> p;
                Node *tempos = new Node();
                tempos->book_code = books->book_code;
                tempos->page = books->page;
                tempos->paragraph = books->paragraph;
                p.first = tempos;
                p.second = namp;
                maxheap->arr[0] = p;
                iter++;
                books=books->prev;
                maxheap->heapifyDown(0);
            }
            else{
                iter++;
                books=books->prev;
            }
        }
    }*/
    /*Node *curr = new Node();
    Node *top_k = curr;
    for (int j = 0; j < k; j++)
    {
        Node *ans = maxheap->arr[0].first;
        auto templ = maxheap->arr[maxheap->size - 1];
        maxheap->arr[maxheap->size - 1] = maxheap->arr[0];
        maxheap->arr[0] = templ;
        maxheap->size--;
        curr->left = ans;
        ans->right = curr;
        curr = curr->left;
        maxheap->heapifyDown(0);
    }
    Node *temp = top_k;
    top_k = top_k->left;
    delete temp;
    top_k->right = nullptr;
    curr->left = nullptr;
    delete maxheap;
    //delete books;
    maxheap = new maxHeap();
    return curr;*/
    Node *top_k = new Node();
    Node *curr = top_k;
    for (int j = 0; j < k; j++)
    {
        Node *ans = maxheap->arr[0].first;
        auto templ = maxheap->arr[maxheap->size - 1];
        maxheap->arr[maxheap->size - 1] = maxheap->arr[0];
        maxheap->arr[0] = templ;
        maxheap->size--;
        curr->left = ans;
        ans->right = curr;
        curr = curr->left;
        //cout << "xyz" << endl;
        maxheap->heapifyDown(0);
    }
    
    //cout << "finished";
    Node * temp = top_k; top_k = top_k->left; delete temp;
    top_k->right = nullptr; curr->left = nullptr;
    delete maxheap;
    //delete books;
    maxheap = new maxHeap();
    Node * temp2 = curr;
    // int abc = 0;
    // while(temp2!=nullptr){
    //     cout << temp2->book_code << "book code" << abc << endl;
    //     abc++;
    //     temp2 = temp2->right;
    // }
    return curr;
    //cout << "get_t_k" << endl;
    /*vector<string> words;
    string alp = "";
    for (char i : question)
    {
        if (sep(i))
        {
            if(alp != ""){
                words.push_back(alp);
                alp = "";
            }
        }
        else
        {
            alp += i;
        }
    }
    textnode* paras = search->root;
    textnode* books = new textnode();
    string flg = "0,0,0";
    while(paras != nullptr){
        if(to_string(paras->book_code)+","+to_string(paras->page)+","+to_string(paras->paragraph) != flg){
            textnode* ans = new textnode(paras->book_code,paras->page,paras->paragraph,-1,paras->text);
            flg = to_string(paras->book_code)+","+to_string(paras->page)+","+to_string(paras->paragraph);
            books->nxt = ans;
            ans->prev = books;
            paras = paras->nxt;
            books = books->nxt;
        }
        else{
            books->text += paras->text;
            paras = paras->nxt;
        }
    }
    int iter = 0;
    while(books->prev!=nullptr){
        //cout << "here" << endl;
        string content = books->text;
        long double namp = 0;
        for(auto word : words){
            long double wsc = static_cast<long double>(texts->get_word_count(word) + 1) / static_cast<long double>(repo->get_word_count(word) + 1);
            // cout<<wsc<<endl;
            int freq = search->helsearch(word,content);
            namp += freq*wsc;
        }
        //cout<<namp<<endl;
        // std::cout << "Book_code: " << books->book_code << " Page: " << books->page << " Paragraph: " << books->paragraph << " Score: "<< namp<< endl;
        
        if(iter < k){
            //cout << iter << " iter less than k" << endl;
            pair<Node *, long double> p;
            Node *tempos = new Node();
            tempos->book_code = books->book_code;
            tempos->page = books->page;
            tempos->paragraph = books->paragraph;
            p.first = tempos;
            p.second = namp;
            maxheap->arr.push_back(p);
            maxheap->size = maxheap->size+1;
            books = books->prev;
            if(iter == k-1){
            //cout << iter << " iter equal to k" << endl;
            maxheap->buildHeap();
        }
            iter++;
        }
        else if(iter>=k){
            //cout << iter << " iter greater to k" << endl;
            if(namp > maxheap->arr[0].second){
                pair<Node *, long double> p;
                Node *tempos = new Node();
                tempos->book_code = books->book_code;
                tempos->page = books->page;
                tempos->paragraph = books->paragraph;
                p.first = tempos;
                p.second = namp;
                maxheap->arr[0] = p;
                iter++;
                books = books->prev;
                maxheap->heapifyDown(0);
            }
            else{
                iter++;
                books = books->prev;
            }
            // cout << "Heap" << endl;
            // for (int qe = 0;qe<maxheap->size;qe++){
            //     cout << maxheap->arr[qe].first->book_code << maxheap->arr[qe].second << "end";
            // }
        }
    }
    for (int i =0;i<k;i++){
        cout << i << endl;
        cout << maxheap->arr[i].first->book_code << " " << maxheap->arr[i].first->paragraph << " " ;
        cout << maxheap->arr[i].second << endl;
    }
    Node *top_k = new Node();
    Node *curr = top_k;
    for (int j = 0; j < k; j++)
    {
        Node *ans = maxheap->arr[0].first;
        auto templ = maxheap->arr[maxheap->size - 1];
        maxheap->arr[maxheap->size - 1] = maxheap->arr[0];
        maxheap->arr[0] = templ;
        maxheap->size--;
        curr->left = ans;
        ans->right = curr;
        curr = curr->left;
        //cout << "xyz" << endl;
        maxheap->heapifyDown(0);
    }
    
    //cout << "finished";
    Node * temp = top_k; top_k = top_k->left; delete temp;
    top_k->right = nullptr; curr->left = nullptr;
    delete maxheap;
    delete books;
    maxheap = new maxHeap();
    Node * temp2 = curr;
    int abc = 0;
    while(temp2!=nullptr){
        cout << temp2->book_code << "book code" << abc << endl;
        abc++;
        temp2 = temp2->right;
    }
    return curr;*/
}

void QNA_tool::query(string question, string filename)
{
    std::cout << "Q: " << question << std::endl;
    std::cout << "A: Studying COL106 :)" << std::endl;
    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph)
{

    std::cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;

    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence))
    {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ','))
        {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos)
            {
                token = token.substr(start, end - start + 1);
            }

            // Check if the element is a number or a string
            if (token[0] == '\'')
            {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            }
            else
            {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if (
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph))
        {
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

void QNA_tool::query_llm(string filename, Node *root, int k, string API_KEY, string question)
{

    // first write the k paragraphs into different files

    Node *traverse = root;
    int num_paragraph = 0;

    while (num_paragraph < k)
    {
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    // write the query to query.txt
    ofstream outfile("query.txt");
    outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the basis of this, ";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();

    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}

// int main(){
//     QNA_tool qna_tool;
//     qna_tool.get_top_k_para("when did gandhi die ?", 5);
//     return 0;
// }