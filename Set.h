//
// Created by samue on 4/29/2019.
//

#ifndef POOL_TABLE_SET_H
#define POOL_TABLE_SET_H

#define TemplateClass template<class T>

TemplateClass class Node {
public:
    T* data;
    Node<T>* p_left, p_right;
    T getData() {
        return this->data;
    }
};

TemplateClass class Set {

public:
    int size;
    Node<T>* root;
    Set();
    ~Set();
    void clear(Node<T>* curNode);
    void find(T key, Node<T>* parent, Node<T>* loc);
    void contains(Node<T>* curNode, T key);
    void insert(node* curNode, node* insertNode);
    void remove(T key);

};

#include "Set.tpp"

#endif //POOL_TABLE_SET_H
