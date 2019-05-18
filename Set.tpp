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

TemplateClass void Set<T>::find(T* key, Node<T>** parent, Node<T>** loc) {
    if (*key == this->root->getData()) {
        *loc = this->root;
        *parent = NULL;
        return;
    }
    Node<T>* temploc;
    Node<T>* tempparent;
    if (*key < this->root->getData()) {
        temploc = this->root->p_left;
    }
    else {
        temploc = this->root->p_right;
    }
    tempparent = this->root;
    while (temploc != NULL) {
        if (*key == temploc->getData()) {
            *loc = temploc;
            *parent = tempparent;
            return;
        }
        tempparent = temploc;
        if (*key < temploc->getData()) {
            temploc = temploc->p_left;
        }
        else {
            temploc = temploc->p_right;
        }
    }
    temploc = NULL;
    tempparent = NULL;
    return;
}

TemplateClass bool Set<T>::contains(T* key) {
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

TemplateClass void Set<T>::insert(T* val) {
    Node<T>* curNode = this->root;
//    std::cout << "DISPLAY: " << this->display(this->root) << std::endl;
    if (this->size == 0) {
        this->root = new Node<T>();
        this->root->data = val;
        this->root->p_left = NULL;
        this->root->p_right = NULL;;
        this->size += 1;
        return;
    }
    Node<T>* parent = this->root;
    while (curNode != NULL) {
        if (*val == curNode->getData()) {
            return;
        }
        else if (*val > curNode->getData()) {
            parent = curNode;
            curNode = curNode->p_right;
        }
        else if (*val < curNode->getData()) {
            parent = curNode;
            curNode = curNode->p_left;
        }
    }
    curNode = new Node<T>;
    curNode->data = val;
    curNode->p_left = NULL;
    curNode->p_right = NULL;
    if (*val < parent->getData()) {
        parent->p_left = curNode;
    }
    else {
        parent->p_right = curNode;
    }
    this->size += 1;
    return;
}

TemplateClass void Set<T>::remove(T* item)
{
    Node<T>* parent = NULL;
    Node<T>* location = NULL;
    if (root == NULL) {
        return;
    }
    find(item, &parent, &location);
    if (location == NULL) {
        return;
    }
//    std::cout << location->data << std::endl;
    if (location->p_left == NULL && location->p_right == NULL)
        case_0(parent, location);
    else if (location->p_left == NULL)
        case_1(parent, location);
    else if (location->p_right == NULL)
        case_1(parent, location);
    else
        case_2(parent, location);
    free(location);
    this->size -= 1;
}

/*
 * Case 0
 * the node is simply removed no other updates necessary.
 */
TemplateClass void Set<T>::case_0(Node<T> *prnt, Node<T> *loc) {
    if (loc->getData() == this->root->getData()) {
        this->root = NULL;
    }
    else {
        if (prnt->p_left != NULL && prnt->p_left->getData() == loc->getData()) {
            prnt->p_left = NULL;
        }
        else {
            prnt->p_right = NULL;
        }
    }
}

TemplateClass void Set<T>::case_1(Node<T> *prnt, Node<T> *loc) {
    Node<T> *child;
    if (loc->p_left != NULL)
        child = loc->p_left;
    else
        child = loc->p_right;
    if (loc->getData() == this->root->getData()) {
        this->root = child;
    }
    else {
        if (prnt->p_left != NULL && prnt->p_left->getData() == loc->getData()) {
            prnt->p_left = child;
        }
        else {
            prnt->p_right = child;
        }
    }
}

TemplateClass void Set<T>::case_2(Node<T> *prnt, Node<T> *loc) {
    Node<T>* cur = loc;
    cur = cur->p_right;
    while (cur->p_left) {
        cur = cur->p_left;
    }
    Node<T>* parentcur = loc;
    if (loc->p_right->p_left) {
        parentcur = parentcur->p_right;
        while (parentcur->p_left->p_left) {
            parentcur = parentcur->p_left;
        }
    }
    if (cur->p_right == NULL) {
        if (loc->p_right->p_left) {
            parentcur->p_left = NULL;
        }
        else {
            parentcur->p_right = NULL;
        }
    }
    else {
        if (loc->p_right->p_left) {
            parentcur->p_left = cur->p_right;
        }
        else {
            parentcur->p_right = cur->p_right;
        }
    }
    if (loc->getData() == this->root->getData()) {
        this->root = cur;
    }
    else {
        if (prnt->p_left->getData() == loc->getData()) {
            prnt->p_left = cur;
        }
        else {
            prnt->p_right = cur;
        }
    }
    cur->p_left = loc->p_left;
    cur->p_right = loc->p_right;
    delete loc;
}

TemplateClass std::vector<T*>* Set<T>::subset(Node<T>* curNode, T tail, T head) {
    std::vector<T*>* ret = new std::vector<T*>;
    if (curNode == NULL) return ret;
    if (curNode->getData() < tail || curNode->getData() > head) return ret;
    std::vector<T*>* left = this->subset(curNode->p_left, tail, head);
    ret->insert(ret->end(), left->begin(), left->end());
    if (curNode->getData() > tail && curNode->getData() < head) {
        ret->push_back(curNode->data);
    }
    std::vector<T*>* right = this->subset(curNode->p_right, tail, head);
    ret->insert(ret->end(), right->begin(), right->end());
    return ret;
}

TemplateClass std::string Set<T>::display(Node<T>* curNode) {
    if (curNode == NULL) return "";
    std::string a = "";
    a += display(curNode->p_left);
    a += std::to_string(curNode->getData());
    a += display(curNode->p_right);
    return a;
}