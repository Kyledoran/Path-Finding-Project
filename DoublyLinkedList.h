#include <iostream>


#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

template <typename T>
struct Node;

template <typename T>
class DoublyLinkedList {

private:



public:
    int n;
    Node<T>* head;
    Node<T>* tail;
    DoublyLinkedList();
    void insertFront(T t);
    void insertBack(T t);
    void remove(T t);
    bool contains(T t);
    void print();
    int sumData();
    struct iterator{
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;

        iterator(T* ptr)  {
            iter = ptr;
        }
        T& operator*() const {
            return *iter;
        }
        T* operator->(){
            return iter;
        }
        iterator& operator++() {
            iter++;
            return *this;
        }
        friend bool operator== (const iterator& a, const iterator& b)
        {
            return a.iter == b.iter;
        };
        friend bool operator!= (const iterator& a, const iterator& b) {
            return a.iter != b.iter;
        };


    private:
        T* iter;
    };
    iterator begin() {
        return iterator(&arr[0]);
    }
    iterator end()   {
        return iterator(&arr[current]);
    }

};

// Initialize the list with dummy head and tail nodes
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    n = 0;
    head = new Node<T>(NULL, nullptr, nullptr);
    tail = new Node<T>(NULL, nullptr, nullptr);
    head->next = tail;
    tail->prev = head;
}

// Increment the count of items and
// add at the front of the list
template <typename T>
void DoublyLinkedList<T>::insertFront(T t) {
    Node<T>* node = new Node<T>(t, head, head->next);
    head->next->prev = node;
    head->next = node;
    n++;
}
template<typename T>
void DoublyLinkedList<T>::insertBack(T t) {
    Node<T>* node = new Node<T>(t, tail->prev, tail);
    tail->prev->next = node;
    tail->prev = node;
    n++;

}

// Search through the list and remove the specified item
template <typename T>
void DoublyLinkedList<T>::remove(T t) {
    for (Node<T>* node = head->next; node != tail; node = node->next) {
        if (node->data == t) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            n--;
            break;
        }
    }
}

// Determine whether or not the list already has a certain element
template <typename T>
bool DoublyLinkedList<T>::contains(T t) {
    for (Node<T>* node = head->next; node != tail; node = node->next) {
        if (node->data == t) {
            return true;
        }
    }
    return false;
}

// print out every node
template <typename T>
void DoublyLinkedList<T>::print() {
    for (Node<T>* node = head->next; node != tail; node = node->next) {
        std::cout << node->data << std::endl;
    }
}
template <typename T>
int DoublyLinkedList<T>::sumData(){
    int sum =0;
    for (Node<T>* node = head->next; node != tail; node = node->next) {
        sum+= node->data;
    }
    return sum;
}
// Define a Node struct to keep track of a single data element and the preceding and following nodes
template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    Node(T data, Node* prev, Node* next) : data(data), prev(prev), next(next) {}
    Node(T data) : data(data) {}

};


#endif /* DoublyLinkedList_h */