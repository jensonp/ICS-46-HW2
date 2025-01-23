#include "../src/unordered_list.h"
#include "Timer.h"
#include <iostream>
#include <fstream>
using namespace std;

UnorderedArrayList::UnorderedArrayList(int cap)
    : UnorderedList("UnorderedArrayList"), capacity(cap), size(0), buf(new string[cap]) {}
UnorderedArrayList::~UnorderedArrayList(){ delete [] buf; }

int UnorderedArrayList::find_index(const string& word){
    for(int i=0; i<size; ++i)
        if (buf[i] == word) { return i; }
    return -1;
}
bool UnorderedArrayList::is_empty() { return size == 0; }
bool UnorderedArrayList::is_full() { return size >= capacity; }
void UnorderedArrayList::double_cap(){
    int double_cap = 2*capacity;
    string* double_buf = new string[double_cap];
    for(int i=0; i<size; ++i){ double_buf[i] = buf[i]; }
    delete [] buf;
    buf = double_buf;
    capacity = double_cap;
}

void UnorderedArrayList::insert(const string& word){
    if(is_full()) double_cap(); // array is full -> doubling capacity
    buf[size++] = word;
}
bool UnorderedArrayList::find(const string& word){ return find_index(word) >= 0; }
void UnorderedArrayList::remove(const string& word){ 
    int index = find_index(word);
    if(index >= 0) buf[index] = buf[--size]; // swap the parameter string and last string in the array
}
void UnorderedArrayList::print(ostream& out){ for(int i=0; i<size; ++i) out << buf[i] << "\n"; }

UnorderedLinkedList::UnorderedLinkedList()
    : UnorderedList("UnorderedLinkedList"), head(nullptr) {}

UnorderedLinkedList::~UnorderedLinkedList() { ListNode::delete_list(head); }

void ListNode::print(ostream& out, ListNode* L){
    for(; L != nullptr; L=L->next) out << L->data << "\n"; 
}
ListNode* ListNode::find(const string& word, ListNode* L){
    for(; L != nullptr; L=L->next){
        if(L->data == word) return L;
    }
    return nullptr;
}
void ListNode::delete_list(ListNode* L){
    while(L){
        ListNode* temp = L;
        L = L->next;
        delete temp;
    }
}
void ListNode::remove(const string& word, ListNode* &L){
    ListNode* p = nullptr;
    ListNode* c = L;
    for(; c != nullptr; p=c, c=c->next){
        if(c->data == word){
            if(p==nullptr) L=c->next; // head removal
            else p->next=c->next; // above head removal
            delete c; 
            return;
        }
    }
}

bool UnorderedLinkedList::is_empty(){ return head==nullptr; }
bool UnorderedLinkedList::is_full(){ return false; }
void UnorderedLinkedList::print(ostream& out){ ListNode::print(out, head); }

void UnorderedLinkedList::insert(const string& word){ head = new ListNode(word, head); }
bool UnorderedLinkedList::find(const string& word){ return ListNode::find(word, head); }
void UnorderedLinkedList::remove(const string& word){ ListNode::remove(word, head); }

ostream& operator<<(ostream& out, UnorderedList& L){ L.print(out); return out; }

void error(string word, string msg)
{
    cerr << "Error Word: " << word << "\n"
         << "Error Message: " << msg << "\n"; 
    exit(EXIT_FAILURE);
}
void insert_all_words(int K, string file_name, UnorderedList& L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    if (!in) { error(file_name, "File Open Error: insert"); }
    int limit = K * NWORDS / 10;
    t.start();
    for(string word; (in >> word) && limit > 0; --limit) { L.insert(word); }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}
void find_all_words(int K, string file_name, UnorderedList& L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    if (!in) { error(file_name, "File Open Error: find"); }
    int limit = K * NWORDS / 10;
    t.start();
    for(string word; (in >> word) && limit > 0; --limit) { L.find(word); }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}
void remove_all_words(int K, string file_name, UnorderedList& L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    if (!in) { error(file_name, "File Open Error: remove"); }
    int limit = K * NWORDS / 10;
    t.start();
    for(string word; (in >> word) && limit > 0; --limit) { L.remove(word); }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}
void measure_UnorderedList_methods(string file_name, UnorderedList& L){
    cout << L.name << endl;
    for(int K = 1; K <= 10; ++K) {
        cout << "\tK = " << K << endl;
        insert_all_words(K, file_name, L);
        find_all_words(K, file_name, L);
        remove_all_words(K, file_name, L);
        if(!L.is_empty()) error(L.name, "is not empty");
    }
}

void measure_lists(string input_file){
    UnorderedArrayList UAL;
    UnorderedLinkedList ULL;
    measure_UnorderedList_methods(input_file, UAL);
    measure_UnorderedList_methods(input_file, ULL);
}
