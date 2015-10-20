#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_

#include <iostream>

template <class T>
class Node
{
public:
    Node(const T & theData = T(), int h = 1)
    : data(theData), height(h)
    {
        next = new Node*[h];
        
        for(int i=0; i<h; i++)
        {
            next[i] = NULL;
        }
    }
    
    ~Node()
    {
        delete[] next;
    }

    T data;
    int height;
    Node **next;
};


template <class T>
class SkipList
{
public:
    SkipList();
    ~SkipList();
    
    bool find(const T & x) const;
    void insert(const T & x);
    void remove(const T & x);
    bool isEmpty() const;
    void makeEmpty();
    void printList();
    
    Node<T> *head;
    static const int maxHeight = 5;
    
    int randomLevel();
    double getRandomNumber();
};

#endif
