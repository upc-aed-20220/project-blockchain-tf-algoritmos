#ifndef DOUBLY_H
#define DOUBLY_H
#include "node.h"

template <class T>
class DoubleList
{
private:
    Node<T> *head;
    Node<T> *tail;
    int nodes;

public:
    DoubleList() : head(nullptr), tail(nullptr), nodes(0) {}

    ~DoubleList()
    {
        while (this->nodes > 0)
        {
            this->pop_back();
        }
    }

    T front()
    {
        if (is_empty())
            throw("No se puede acceder al inicio: No hay elementos");
        return this->head->data;
    }

    Node<T> *front1()
    {
        if (is_empty())
            throw("No se puede acceder al inicio: No hay elementos");
        return this->head;
    }

    T back()
    {
        if (is_empty())
            throw("No se puede acceder al final: No hay elementos");
        return this->tail->data;
    }

    Node<T> *back1()
    {
        if (is_empty())
            throw("No se puede acceder al final: No hay elementos");
        return this->tail;
    }

    void push_front(T data)
    {
        Node<T> *newNode = new Node<T>(data);
        newNode->next = this->head;
        if (!is_empty())
            this->head->prev = newNode;
        else
            this->tail = newNode;
        this->head = newNode;
        this->nodes++;
    }

    void push_back(T data)
    {
        Node<T> *newNode = new Node<T>(data);
        if (this->is_empty())
        {
            this->head = this->tail = newNode;
            this->nodes++;
            return;
        }
        else
        {
            this->tail->next = newNode;
            newNode->prev = tail;
            this->tail = newNode;
            this->nodes++;
        }
    }

    T pop_front()
    {
        if (is_empty())
            throw("No hay elementos");
        T temp = this->head->data;
        if (this->head->next == nullptr)
        {
            delete this->head;
            this->head = this->tail = nullptr;
        }
        else
        {
            this->head = this->head->next;
            delete this->head->prev;
            this->head->prev = nullptr;
        }
        this->nodes--;
        return temp;
    }

    T pop_back()
    {
        if (is_empty())
            throw("No hay elementos");
        T temp = this->tail->data;
        if (this->tail->prev == nullptr)
        {
            delete this->tail;
            this->tail = this->head = nullptr;
        }
        else
        {
            this->tail = this->tail->prev;
            delete this->tail->next;
            this->tail->next = nullptr;
        }
        this->nodes--;
        return temp;
    }

    bool insert(T data, int pos)
    {
        if (pos >= this->size() || pos < 0)
            return false;
        if (pos == 0)
            this->push_front(data);
        else
        {
            Node<T> *nuevo = new Node<T>(data);
            Node<T> *temp = this->head;
            int i = 0;
            while (i++ < pos - 1)
                temp = temp->next;
            nuevo->next = temp->next;
            nuevo->prev = temp;
            temp->next->prev = nuevo;
            temp->next = nuevo;
            ++this->nodes;
        }
        return true;
    }

    bool remove(int pos)
    {
        int size = this->size();
        if (this->is_empty())
            return false;
        Node<T> *temp = this->head;
        if (back1() == _find(pos))
        {
            pop_back();
            return true;
        }
        else if (front1() == _find(pos))
        {
            pop_front();
            return true;
        }
        if (size > 1)
        {
            while (temp && temp->next != _find(pos))
            {
                temp = temp->next;
            }
            Node<T> *temp2 = temp->next;
            temp2->next->prev = temp;
            temp->next = temp2->next;
            temp2->next = nullptr;
            delete temp2;
            this->nodes--;
        }
        return true;
    }

    Node<T> *_find(int index)
    {
        if (index > this->size())
            return nullptr;
        Node<T> *current = this->head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current;
    }

    T &operator[](int pos)
    {
        Node<T> *temp = this->head;
        for (int i = 0; i < pos; i++)
            temp = temp->next;
        return temp->data;
        throw("no implementado");
    }

    class Iterator
    {
        Node<T> *v;
        int pos;

    public:
        Iterator(Node<T> *v, int pos)
        {
            this->v = v;
            this->pos = pos;
        }

        void operator++()
        {
            v = v->next;
            pos++;
        }
        void operator--()
        {
            v = v->prev;
            pos--;
        }

        T operator*() { return v->data; }

        bool operator!=(Iterator i) { return pos != i.pos; }
    };

    Iterator begin() { return Iterator(this->head, 0); }
    Iterator end() { return Iterator(nullptr, this->nodes); }
    Iterator rbegin() { return Iterator(this->tail, this->nodes - 1); }
    Iterator rend() { return Iterator(nullptr, -1); }

    bool is_empty() { return this->head == nullptr && this->tail == nullptr; }

    int size() { return this->nodes; }
};
#endif
