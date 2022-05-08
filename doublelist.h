//
// Created by kamila on 13.11.2021.
//

#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct DoubleNode {
// the default access mode and default inheritance mode are public
    T value;
    DoubleNode *next, *prev;
    // konstruktor domyslny (niepotrzebny)
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(const T& item, DoubleNode *nptr=nullptr, DoubleNode *pptr=nullptr)
            : value(item), next(nptr), prev(pptr) {} // konstruktor
    ~DoubleNode() {} // destruktor
};


template <typename T>
class DoubleList {
    DoubleNode<T> *head, *tail;
public:
    DoubleList() : head(nullptr), tail(nullptr) {}
    ~DoubleList(){
        for (DoubleNode<T> *node; !empty(); ) {
            node = head->next; // zapamietujemy
            delete head;
            head = node; // kopiowanie wskaznika
        }
    } // tu trzeba wyczyscic wezly
    DoubleList(const DoubleList& other){

        DoubleNode<T> *current = other.head;
        head = tail = nullptr;
        while(current != nullptr)
        {
            DoubleNode<T> *tmp = new DoubleNode<T>();
            tmp->prev = nullptr;
            tmp->next = nullptr;
            tmp->value = current->value;

            if(empty())
                head = tail = tmp;
            else
            {
                tail->next = tmp;
                tmp->prev = tail;
                tail = tail->next;
            }

            current = current->next;
        }
    }
    // copy constructor
    // usage:   DoubleList<int> list2(list1);
    DoubleList(DoubleList&& other); // move constructor NIEOBOWIAZKOWE
    // usage:   DoubleList<int> list2(std::move(list1));
    DoubleList& operator=(const DoubleList& other)
    {
        if(this == &other)
            return *this;

        DoubleList<T> temp(other);
        std::swap(temp.head, head);
        std::swap(temp.tail, tail);

        return *this;
    }
    // copy assignment operator, return *this
    // usage:   list2 = list1;
    DoubleList& operator=(DoubleList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE
    bool empty() const { return head == nullptr; }
    int size() const; // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1)
    void push_front(T&& item); // O(1) NIEOBOWIAZKOWE
    void push_back(const T& item); // O(1)
    void push_back(T&& item); // O(1) NIEOBOWIAZKOWE
    T& front() const { return head->value; } // zwraca poczatek, nie usuwa
    T& back() const { return tail->value; } // zwraca koniec, nie usuwa
    void pop_front(); // usuwa poczatek O(1)
    void pop_back(); // usuwa koniec O(n)
    void clear(); // czyszczenie listy z elementow O(n)
    void display(); // O(n)
    void display_reversed(); // O(n)
    // Operacje z indeksami. NIEOBOWIAZKOWE
    T& operator[](int pos); // podstawienie L[pos]=item
    const T& operator[](int pos) const; // odczyt L[pos]
    void erase(int pos);
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(int pos, const T& item); // inserts item before pos,
    void insert(int pos, T&& item); // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

template <typename T>
void DoubleList<T>::push_front(const T& item) {
    if (!empty()) {
        head = new DoubleNode<T>(item, head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}

template <typename T>
void DoubleList<T>::push_front(T&& item) {
    if (!empty()) {
        head = new DoubleNode<T>(std::move(item), head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(std::move(item));
    }
}

template <typename T>
int DoubleList<T>::size() const {
    if(empty())
    {
        return 0;
    }
    if(head == tail)
        return 1;
    else{
        DoubleNode<T> *current = head;
        int i = 0;

        while (current != nullptr)
        {
            current = current->next;
            i++;
        }
        return i;
    }

}
template <typename T>
void DoubleList<T>::push_back(const T& item) {
    if (!empty()) {
        DoubleNode<T> *temp = tail;
        tail->next = new DoubleNode<T>(item);
        tail = tail->next;
        tail->prev = temp;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}
template <typename T>
void DoubleList<T>::display() {
    DoubleNode<T> *node = head;
    while (node != nullptr){
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << std::endl;
}
template <typename T>
void DoubleList<T>::pop_front() {
    assert(!empty());
    DoubleNode<T> *node = head; // zapamietujemy
    if (head == tail) { // jeden wezel na liscie
        head = tail = nullptr;
    } else { // wiecej niz jeden wezel na liscie

        head = head->next;
        head->prev = nullptr;
    }
    delete node;
}
template <typename T>
void DoubleList<T>::pop_back() {
    assert(!empty());
    DoubleNode<T> *node = tail; // zapamietujemy
    if (head == tail) { // jeden wezel na liscie
        head = tail = nullptr;
    } else { // wiecej niz jeden wezel na liscie
        // Szukamy poprzednika ogona.
        DoubleNode<T> *before=head;
        while (before->next != tail) {
            before = before->next;
        }
        tail = before;
        tail->next = nullptr;
    }
    delete node;
}
template <typename T>
void DoubleList<T>::clear() {
    assert(!empty());
    if(head == tail)
    {
        head = tail = nullptr;
    }
    else
    {
        DoubleNode<T> *current = head;
        DoubleNode<T> *tmp = nullptr;

        while (current != nullptr) {
            tmp = current->next;
            delete current;
            current = tmp;
        }

    }
    head = nullptr;
    tail = nullptr;
}
template <typename T>
void DoubleList<T>::display_reversed() {
    if(empty())
    {
        return;
    }
    else if(head == tail)
        std::cout<<head<<std::endl;

    else {
        DoubleNode<T> *temp = tail;

        do {
            std::cout << temp->value << " ";
            temp = temp->prev;
        } while (temp != nullptr);
        std::cout << std::endl;
    }
}

#endif

// EOF