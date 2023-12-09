
#include <iostream>
#include <fstream>
#include "Node.h"
#include "dict.h"
#include "search.h"

using namespace std;

class maxHeap{
public:
    int size = 0;
    vector<pair<Node*,long double>> arr;
    maxHeap(){
        size = 0;
    }
    maxHeap(int sz, vector<pair<Node*,long double>> argon){
        size = sz;
        arr = argon;
    }

    int getParentIndex(int i){
        return (i-1)/2;
    }
    int getLeftChildIndex(int i){
        return 2*i+1;
    }
    int getRightChildIndex(int i){
        return 2*i+2;
    }
    void heapifyDown(int index){
        int leftChild = getLeftChildIndex(index);
        int rightChild = getRightChildIndex(index);
        int min = index;
        if (leftChild >= size){
            return;
        }
        if (arr[min].second>arr[leftChild].second){
            min = leftChild;
        }
        if (rightChild<size){
            if (arr[min].second>arr[rightChild].second){
                min = rightChild;
            }
        }
        if (index!=min){
            auto temp = arr[min];
            arr[min] = arr[index];
            arr[index] = temp;
            heapifyDown(min);
        }
    }
    void buildHeap(){
        int n = size;
        auto heap = arr;
        for (int i = n/2-1;i>=0;i--){
            heapifyDown(i);
        }
    }
    ~maxHeap(){
        for (int i=0;i<size;i++){
            delete arr[i].first;
        }
    }

};

class QNA_tool {

private:

    // You are free to change the implementation of this function
    void query_llm(string filename, Node* root, int k, string API_KEY, string question);

    // You can add attributes/helper functions here
    SearchEngine* search;
    Dict* texts;
    Dict* repo;
    maxHeap* maxheap;

public:

    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    
    QNA_tool(); // Constructor
    ~QNA_tool(); // Destructor

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);
    // This function is similar to the functions in dict and search 
    // The corpus will be provided to you via this function
    // It will be called for each sentence in the corpus

    Node* get_top_k_para(string question, int k);
    // This function takes in a question, preprocess it
    // And returns a list of paragraphs which contain the question
    // In each Node, you must set: book_code, page, paragraph (other parameters won't be checked)

    std::string get_paragraph(int book_code, int page, int paragraph);
    // Given the book_code, page number, and the paragraph number, returns the string paragraph.
    // Searches through the corpus.

    void query(string question, string filename);
    // This function takes in a question and a filename.
    // It should write the final answer to the specified filename.

    /* -----------------------------------------*/
    /* Please do not touch the code above this line */

    // You can add attributes/helper functions here
};