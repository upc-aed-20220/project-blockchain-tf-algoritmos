#pragma once
#include <deque>

template <typename T>
struct NodeBT
{
    T data;
    int height;
    NodeBT *left;
    NodeBT *right;
    std::deque<T> *values;
    NodeBT() : left(nullptr), right(nullptr), height(0)
    {
        values = new std::deque<T>;
    }
    NodeBT(T value) : data(value), left(nullptr), right(nullptr), height(0)
    {
        values = new std::deque<T>;
        values->push_back(value);
    }
    ~NodeBT()
    {
        if (values->empty() == false)
            values->clear();
        delete values;
    }
    void killSelf()
    {
        if (left != nullptr)
            left->killSelf();
        if (right != nullptr)
            right->killSelf();
        delete this;
    }
};
