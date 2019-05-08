//
// Created by samue on 4/29/2019.
//

#include "Set.h"

#define TemplateClass template<class T>

TemplateClass Set<T>::Set() {
    this->root = NULL;
    this->size = 0;
}

TemplateClass Set<T>::~Set() {
    this->clear(this->root);
}

TemplateClass void Set<T>::clear(Node<T>* curNode) {
    if (curNode == NULL) return;
    this->clear(curNode->p_left);
    this->clear(curNode->p_right);
    delete curNode;
}

TemplateClass void Set<T>::find(T key, Node<T>* parent, Node<T>* loc) {
    if (loc == NULL) {
        parent = NULL;
        loc = NULL;
        return;
    }
    while (loc->getData() != key) {
        if (key < loc->getData()) {
            recurse(key, loc, loc->p_left);
        }
        else {
            recurse(key, loc, loc->p_right);
        }
    }
    return;
}

TemplateClass void Set<T>::contains(T key) {
    Node<T>* parent = NULL;
    Node<T>* loc = this->root;
    this->find(key, NULL, loc);
    if (loc == NULL) {
        return false;
    }
    else {
        return true;
    }
}

TemplateClass void Set<T>::insert(Node<T>* curNode, T val) {
    if (this->root == NULL) {
        Node<T>* insertme = new Node<T>;
        insertme->data = val;
        this->root = insertme;
        return;
    }
    while (curNode != NULL) {
        if (val == curNode->getData()) return;
        else if (val > curNode->getData()) {
            insert(curNode->right, insertNode);
        }
        else if (val < curNode->getDat()) {
            insert(curNode->left, insertNode);
        }
    }
    Node<T>* insertme = new Node<T>;
    insertme->data = val;
    curNode = insertme;
    return;
}

TemplateClass void Set<T>::remove(T key) {

}