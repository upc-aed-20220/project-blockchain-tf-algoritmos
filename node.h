#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node() {
        this->next = this->prev = nullptr;
    }

    Node(T value) {
        this->data = value;
        this->next = this->prev = nullptr;
    }

    void killSelf() {
        if (next != nullptr)
            next.killself();
        delete this;
    }
};

#endif
