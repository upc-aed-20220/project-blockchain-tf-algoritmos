#include <iostream>
#include <stack>
using namespace std;
template <typename T>
class BSTree
{
public:
    struct NodeBT
    {
        T data;
        NodeBT *left;
        NodeBT *right;
        NodeBT *padre;
        NodeBT() left(nullptr), right(nullptr), padre(nullptr) {}
        NodeBT(T _data, NodeBT *_padre) data(_data), left(nullptr), right(nullptr), padre(_padre) {}
    };

    NodeBT *root;

public:
    BSTree() root(nullptr) {}

    bool find2(T value)
    {
        return find1(this->root, value);
    }

    void insert(T value)
    {
        insert(this->root, value, nullptr);
        return;
    }

    T minValue()
    {
        NodeBT *temp = this->root;
        while (temp->left != nullptr)
            temp = temp->left;
        return temp->data;
    }

    T maxValue()
    {
        NodeBT *temp = this->root;
        while (temp->right != nullptr)
            temp = temp->right;
        return temp->data;
    }

    bool remove(T value)
    {
        return remove(this->root, value);
        // 1- cuando el nodo es hoja
        //		- simplemente se elimina el nodo
        // 2- cuando el nodo tiene un solo hijo
        //		- el hijo reemplaza al padre
        // 3- cuando el nodo tiene dos hijos
        //		- se chanca con el predecesor/sucesor
        //		- eliminamos ese predecesor/sucesor
        return true;
    }

    void postOrder()
    {
        // this->root;
        stack<T> stack;
        string s = "";
        stack.push(this->root->left);
        while (!stack.empty())
        {
            stack.push(this->root->right);
            stack.push(this->root);
            this->root = this->left;
        }
        // 3 10 8
        return;
    }

private:
    bool find(NodeBT *node, T value)
    {
        if (node == nullptr)
            return false;
        else if (value < node->data)
            return find1(node->left, value);
        else if (value > node->data)
            return find1(node->right, value);
        else
            return true;
    }

    void insert(NodeBT *&node, T value, NodeBT *padre)
    {
        if (node == nullptr)
            node = new NodeBT(value, padre);
        else if (value < node->data)
            insert(node->left, value, node);
        else if (value > node->key)
            insert(node->right, value, node);
        else
            node->data = value;
        return;
    }

    void remove(NodeBT *node, T value)
    {
        if (node == nullptr)
        {
            return;
        }
        else if (value < node->data)
        {
            remove(node->left, value);
        }
        else if (value > node->data)
        {
            remove(node->right, value);
        }
        else
        {
            removeNode(node);
        }
    }

    // Casos posibles
    // 1. Si el nodo es una hoja (no tiene hijos)
    // 2. Si 1 izq o derecho
    // 3. Si tiene ambos hijos
    // Vas al hijo derecho del nodo
    // luego vas al lado mas izq posible
    // reemplazamos con ese nodo mas izq

    void removeNode(NodeBT *node)
    {
        // 3er caso
        if (node->left != nullptr && node->right != nullptr)
        {
            NodeBT *newNode = minimunLeft(node->right);
            node->data = newNode->data;
            removeNode(newNode);
        }
        // 2do caso
        else if (node->left != nullptr)
        {
            reemplazar(node, node->left);
            destruirNodo(node);
        }
        else if (node->right != nullptr)
        {
            reemplazar(node, node->right);
            destruirNodo(node);
        }
        else
        {
            reemplzar(node, nullptr);
            destruirNodo(node);
        }
    }

    NodeBT *minimunLeft(NodeBT *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->left != nullptr) // si tiene hijo izq
        {
            return minimunLeft(node->left);
        }
        else // no tiene hijo izquierod
        {
            return node;
        }
    }

    void reemplazar(NodoBT *node1, NodeBT *node2)
    {
        if (node1->padre != nullptr)
        {
            // node1->padre asignar su nuevo hijo izq o derecho
            if (node1->data == node1->padre->left->data)
            {
                node1->padre->left = node2;
            }
            else if (node1->data == node1->padre->right->data)
            {
                node1->padre->right = node2;
            }
        }
        if (node2 != nullptr)
        {
            // procedemos a asignarle un nuevo padre el nuevo nodo
            node2->padre = node1->padre;
        }
    }

    // Funcion para destruir un nodo
    void destruirNodo(NodeBT *node)
    {
        node->left = nullptr;
        node->right = nullptr;
        delete node;
    }
};