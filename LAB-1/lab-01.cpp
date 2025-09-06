#include <iostream>
#include <string>
#include "stopwatch.hpp"
using namespace std;

// =============================
// Part A: Resizable Array
// =============================
class ResizableArray {
    friend class ArrayStack;
private:
    int* data;
    int capacity;
    int size;

    void resize(int newCapacity){
        int* newdata = new int[newCapacity];
        for(int i = 0; i < size; i++){
            newdata[i] = data[i];
        }
        delete[] data;
        data = newdata;
        capacity = newCapacity;
    };

public:
    ResizableArray(){
        data = new int[2];
        size = 0;
        capacity = 2;
    };

    // Copy constructor
    ResizableArray(const ResizableArray& other){
        capacity = other.capacity;
        size = other.size;
        data = new int[capacity];
        for(int i = 0; i < size; i++) data[i] = other.data[i];
    }

    // Assignment operator
    ResizableArray& operator=(const ResizableArray& other){
        if(this == &other) return *this;
        delete[] data;
        capacity = other.capacity;
        size = other.size;
        data = new int[capacity];
        for(int i = 0; i < size; i++) data[i] = other.data[i];
        return *this;
    }

    ~ResizableArray(){
        delete[] data;
    };

    void push_back(int value){
        if(size == capacity){
            resize(capacity*2);
        }
        data[size] = value;
        size++;
    };

    void pop_back(){
        if(size > 0) size--;
        if(size == capacity/4 && capacity > 3) resize(capacity/2);
    };

    int get(int index) const{
        return data[index];
    };

    int siz() const{
        return size;
    };

    bool empty() const{
        return size == 0;
    };
};

// =============================
// Part B: Linked List
// =============================
class LinkedList {
    friend class LinkedListStack;
private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int siz;

public:
    LinkedList(){
        head  = tail =  nullptr;
        siz = 0;
    };

    // Copy constructor
    LinkedList(const LinkedList& other){
        head = tail = nullptr;
        siz = 0;
        Node* curr = other.head;
        while(curr){
            insertAtTail(curr->data);
            curr = curr->next;
        }
    }

    // Assignment operator
    LinkedList& operator=(const LinkedList& other){
        if(this == &other) return *this;
        while(head) deleteHead();
        Node* curr = other.head;
        while(curr){
            insertAtTail(curr->data);
            curr = curr->next;
        }
        return *this;
    }

    ~LinkedList(){
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    };

    void insertAtHead(int value){
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        if (tail == nullptr) tail = newNode;
        siz++;
    };

    void insertAtTail(int value){
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        siz++;
    };

    void deleteHead(){
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        siz--;
    };

    bool empty() const{
        return head == nullptr;
    };

    int size() const{
        return siz;
    };
};

// =============================
// Part C: Stack Implementations
// =============================

// --- Stack using ResizableArray ---
class ArrayStack {
private:
    ResizableArray arr;

public:
    ArrayStack() {}

    ArrayStack(const ArrayStack& other) : arr(other.arr) {}
    ArrayStack& operator=(const ArrayStack& other){
        arr = other.arr;
        return *this;
    }

    void push(int value){ arr.push_back(value); };
    void pop(){ arr.pop_back(); };
    int top() const{ return arr.get(arr.siz()-1); };
    bool empty() const{ return arr.empty(); };
};

// --- Stack using LinkedList ---
class LinkedListStack {
private:
    LinkedList list;

public:
    LinkedListStack() {}

    LinkedListStack(const LinkedListStack& other) : list(other.list) {}
    LinkedListStack& operator=(const LinkedListStack& other){
        list = other.list;
        return *this;
    }

    void push(int value){ list.insertAtHead(value); };
    void pop(){ list.deleteHead(); };
    int top() const{ return list.head->data; };
    bool empty() const{ return list.empty(); };
};

// =============================
// Part D: Text Buffer
// =============================

class TextBufferArray {
private:
    ArrayStack left;
    ArrayStack right;

public:
    void insert(char c){ left.push(c); };
    void remove(){ if (!left.empty()) left.pop(); };
    void moveLeft(){ if (!left.empty()){ right.push(left.top()); left.pop(); } };
    void moveRight(){ if (!right.empty()){ left.push(right.top()); right.pop(); } };

    string getText(){
        ArrayStack leftCopy = left;
        ArrayStack rightCopy = right;
        string result = "";
        while(!leftCopy.empty()){ rightCopy.push(leftCopy.top()); leftCopy.pop(); }
        while(!rightCopy.empty()){ result += rightCopy.top(); rightCopy.pop(); }
        return result;
    }
};

class TextBufferList {
private:
    LinkedListStack left;
    LinkedListStack right;

public:
    void insert(char c){ left.push(c); };
    void remove(){ if (!left.empty()) left.pop(); };
    void moveLeft(){ if (!left.empty()){ right.push(left.top()); left.pop(); } };
    void moveRight(){ if (!right.empty()){ left.push(right.top()); right.pop(); } };

    string getText(){
        LinkedListStack leftCopy = left;
        LinkedListStack rightCopy = right;
        string result = "";
        while(!leftCopy.empty()){ rightCopy.push(leftCopy.top()); leftCopy.pop(); }
        while(!rightCopy.empty()){ result += rightCopy.top(); rightCopy.pop(); }
        return result;
    }
};

// =============================
// Driver Program
// =============================
int main() {
    Stopwatch timer;
    
    int n = 0;
    long double arrayTimer = 0;
    long double listTimer = 0;
    int runs = 100; 

    while( n++ < runs ){
    cout << "Testing TextBuffer with ArrayStack...\n";
    timer.reset();
    TextBufferArray buf1;
    string text = "datastructures";
    for (char c : text) buf1.insert(c);

    buf1.moveLeft(); buf1.moveLeft(); buf1.moveLeft(); buf1.moveLeft(); buf1.moveLeft();
    buf1.insert('X');
    cout << "After inserting X: " << buf1.getText() << endl;

    buf1.remove(); buf1.remove(); buf1.remove();
    cout << "After deleting 3 chars: " << buf1.getText() << endl;

    buf1.moveRight(); buf1.moveRight();
    buf1.insert('Y');
    cout << "After inserting Y: " << buf1.getText() << endl;

    double Arraytime = timer.elapsedTime();
    arrayTimer += Arraytime;

    cout << "\nTesting TextBuffer with LinkedListStack...\n";
    timer.reset();
    TextBufferList buf2;
    for (char c : text) buf2.insert(c);

    buf2.moveLeft(); buf2.moveLeft(); buf2.moveLeft(); buf2.moveLeft(); buf2.moveLeft();
    buf2.insert('X');
    cout << "After inserting X: " << buf2.getText() << endl;

    buf2.remove(); buf2.remove(); buf2.remove();
    cout << "After deleting 3 chars: " << buf2.getText() << endl;

    buf2.moveRight(); buf2.moveRight();
    buf2.insert('Y');
    cout << "After inserting Y: " << buf2.getText() << endl;

    double ListTime = timer.elapsedTime();
    listTimer += ListTime;
    }
    
    long double avgArray = arrayTimer / runs;
    long double avgList = listTimer / runs;

    cout << "\n=============================\n";
    cout << "Average Time (Array Buffer): " << avgArray << " seconds\n";
    cout << "Average Time (List Buffer): " << avgList << " seconds\n";
    cout << "Difference (Array - List): " << (avgArray - avgList) << " seconds\n";
    return 0;
}
