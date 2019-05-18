//
// Created by samue on 4/29/2019.
//

#ifndef POOL_TABLE_SET_H
#define POOL_TABLE_SET_H

#define TemplateClass template<class T>

#include <vector>
#include <string>

TemplateClass class Node {
public:
    T* data;
    Node<T>* p_left;
    Node<T>* p_right;
    Node<T>() {
        this->data = new T();
        p_left = NULL;
        p_right = NULL;
    }
    T getData() {
        return *(this->data);
    }
};

TemplateClass class Set {

public:
    int size;
    Node<T>* root;
    Set();
    ~Set();
    void clear(Node<T>* curNode);
    void find(T* key, Node<T>** parent, Node<T>** loc);
    bool contains(T* key);
    void insert(T* val);
    void remove(T* key);
    void case_0(Node<T>* prnt, Node<T>* loc);
    void case_1(Node<T>* prnt, Node<T>* loc);
    void case_2(Node<T>* prnt, Node<T>* loc);
    std::vector<T*>* subset(Node<T>* curNode, T tail, T head);
    std::string display(Node<T>* curNode);

};

#include "Set.tpp"

#endif //POOL_TABLE_SET_H