#include <string>
#include <queue>
#include <stack>
#include <cmath>
#include <functional>
#include "nodeArbol.h"

using namespace std;

template <class T>
class Arbol
{
    NodeBT<T> *root;
    function<void(T)> show;   
    function<bool(T, T)> comp; 
    function<bool(T, T)> equals;
    function<T(void)> defaultValue;

public:
    Arbol(function<bool(T, T)> comp, function<void(T)> show, function<bool(T, T)> equals, function<T(void)> defaultValue) : root(nullptr), comp(comp), show(show), equals(equals), defaultValue(defaultValue) {}

    void propagar(NodeBT<T>* node, NodeBT<T>* parent, string returnKey, HashTable* hashTable)
    {
        if (node == nullptr)
        {
            return;
        }

        recalcularBloque(node, parent, returnKey, hashTable);

        propagar(node->left, node, returnKey, hashTable);
        propagar(node->right, node, returnKey, hashTable);
    }
    void recalcularBloque(NodeBT<T>* node, NodeBT<T>* parent, string returnKey, HashTable* hashTable)
    {
        if (node->data->getKey() == returnKey)
        {
            return;
        }
        hashTable->removerBloque(node->data);
        node->data->setPrevKey(parent->data->getKey());
        hashTable->setBlockinHashTable(node->data);
    }

    NodeBT<T> *insert(T value, NodeBT<T> *&node)
    {
        return _insert(this->root, value, node);
    }

    NodeBT<T>* insert2(T value, NodeBT<T>*& node)
    {
        return _insert2(this->root, value, node);
    }

    bool find(T value) { return _find(this->root, value); }
    T findValue(T value) { return _findValue(this->root, value); };
    void findByCriteria(function<bool(T)> criteria) { _findByCriteria(this->root, criteria); }
    void findyRange(function<int(T)> isInRange) { _findByRange(root, isInRange); }
    void displayInOrder() { displayInOrder(this->root); }
    void displayPreOrder() { _displayPreOrder(this->root); }
    void clear() { clear(this->root); }

    int height()
    {
        return height(this->root);
    }

    ~Arbol()
    {
        clear();
        delete this;
    }

private:

    NodeBT<T>* _insert2(NodeBT<T>*& node, T value, NodeBT<T>*& parent)
    {
        if (node == nullptr) {
            node = new NodeBT<T>(value);
            return node;
        }
        else if (value <= node->data) {
            parent = node;
            NodeBT<T>* temp = _insert2(node->left, value, parent);
            return temp;
        }
        else if (value > node->data) {
            parent = node;
            NodeBT<T>* temp = _insert2(node->right, value, parent);
            return temp;
        }
    }

    NodeBT<T> *_insert(NodeBT<T> *&node, T value, NodeBT<T> *&parent)
    {
        if (node == nullptr)
        {
            node = new NodeBT<T>(value);
            return node;
        }
        if (equals(value, node->data))
        {
            node->values->push_back(value);
            return node;
        }
        if (comp(value, node->data))
        {
            parent = node;
            NodeBT<T> *temp = _insert(node->left, value, parent);
            updateHeight(node);
            balanceSubTree(node);
            return temp;
        }
        else
        {
            parent = node;
            NodeBT<T> *temp = _insert(node->right, value, parent);
            updateHeight(node);
            balanceSubTree(node);
            return temp;
        }
    }

    void updateHeight(NodeBT<T> *node)
    {
        node->height = maximo(height(node->left), height(node->right)) + 1;
    }

    int maximo(int a, int b)
    {
        return (a > b) ? a : b;
    }

    void balanceSubTree(NodeBT<T> *&node)
    {
        int criteria = height(node->left) - height(node->right);
        NodeBT<T> *leftChild = node->left;
        NodeBT<T> *rightChild = node->right;
        if (criteria > 1)
        {
            if (!leftChild->left)
            {
                leftRotation(node->left);
                rightRotation(node);
            }
            else
                rightRotation(node);
        }
        else if (criteria < -1)
        {
            if (!rightChild->right)
            {
                rightRotation(node->right);
                leftRotation(node);
            }
            else
                leftRotation(node);
        }
        leftChild = rightChild = nullptr;
    }

    int height(NodeBT<T> *node)
    {
        return (node) ? node->height : -1;
    }

    void rightRotation(NodeBT<T> *&node)
    {
        NodeBT<T> *leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        updateHeight(node);
        updateHeight(leftChild);
        node = leftChild;
    }

    void leftRotation(NodeBT<T> *&node)
    {
        NodeBT<T> *rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        updateHeight(node);
        updateHeight(rightChild);
        node = rightChild;
    }

    bool _find(NodeBT<T> *node, T value)
    {
        if (node == nullptr)
            return false;
        if (equals(value, node->data))
        {
            for (auto elem : *node->values)
                show(elem);
            return true;
        }
        if (comp(value, node->data))
            return _find(node->left, value);
        else
            return _find(node->right, value);
    }
    T _findValue(NodeBT<T> *node, T value)
    {
        if (!node)
            return defaultValue();
        if (equals(value, node->data))
            return node->data;
        if (comp(value, node->data))
            return _findValue(node->left, value);
        else
            return _findValue(node->right, value);
    }

    void _findByCriteria(NodeBT<T> *node, function<bool(T)> criteria)
    {
        if (!node)
            return;
        if (criteria(node->data))
            show(node->data);
        _findByCriteria(node->left, criteria);
        _findByCriteria(node->right, criteria);
    }
    void _findByRange(NodeBT<T> *node, function<int(T)> isInRange)
    {
        if (!node)
            return;

        switch (isInRange(node->data))
        {
        case 0:
            for (auto elem : *node->values)
                show(elem);
            _findByRange(node->left, isInRange);
            _findByRange(node->right, isInRange);
            break;
        case 1:
            for (auto elem : *node->values)
                show(elem);
            _findByRange(node->left, isInRange);
            break;
        case 2:
            for (auto elem : *node->values)
                show(elem);
            _findByRange(node->right, isInRange);
            break;
        case 3:
            _findByRange(node->right, isInRange);
            break;
        case 4:
            _findByRange(node->left, isInRange);
            break;
        }
    }

    void displayInOrder(NodeBT<T> *node)
    {
        if (node != nullptr)
        {
            displayInOrder(node->left);
            for (auto elem : *node->values)
                show(elem);
            displayInOrder(node->right);
        }
        return;
    }
    void _displayPreOrder(NodeBT<T> *node)
    {
        if (node != nullptr)
        {
            for (auto elem : *node->values)
                show(elem);
            _displayPreOrder(node->left);
            _displayPreOrder(node->right);
        }
        return;
    }
    void clear(NodeBT<T> *&node)
    {
        node->KillSelf();
        node = nullptr;
        return;
    }
};
