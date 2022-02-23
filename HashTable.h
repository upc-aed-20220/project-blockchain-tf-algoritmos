#include "Bloque.h"

const int maxColision = 3;
const float maxFillFactor = 0.5;

class HashTable
{
private:
    DoubleList<Bloque *> *array;
    int capacity;
    int size;
    string lastKeyGen;

public:
    HashTable()
    {
        this->capacity = 10;
        this->array = new DoubleList<Bloque *>[capacity];
        this->size = 0;
    }

    void setCapacity(int c) { this->capacity = c; }
    int getCapacity() { return this->capacity; }
    int getSize() { return this->size; }

    // guardado de datos linea 18 main.cpp
    DoubleList<Bloque *> *getArray() { return this->array; }

    string setBlockinHashTable(Bloque *bloque)
    {
        string key = bloque->generarKey();
        bloque->setKey(key);

        double factor = this->fillFactor();
        if (factor >= maxFillFactor)
        {
            rehashing();
        }

        size_t hashcode = getHashCode(key);
        int index = hashcode % this->capacity;

        this->array[index].push_back(bloque);
        size++;
        return key;
    }

    Bloque *recalcularHash(Bloque *block)
    {
        NodeBT<Bloque *> *a = block->getNode();
        Bloque *temp = new Bloque(*block);
        remove(block->getKey());
        string key = temp->generarKey();
        temp->setKey(key);
        a->data = temp;
        size_t hashcode = getHashCode(key);
        int index = hashcode % this->capacity;
        this->array[index].push_back(temp);
        size++;
        return temp;
    }

    void removerBloque(Bloque *block)
    {
        remove(block->getKey());
    }

    void remove(string key)
    {
        size_t hashcode = getHashCode(key);
        int index = hashcode % capacity;
        int posKey = -1;
        bool seEncontro = false;
        for (auto it = this->array[index].begin(); !seEncontro && it != this->array[index].end(); ++it)
        {
            ++posKey;
            if ((*it)->getKey() == key)
            {
                seEncontro = true;
            }
        }
        this->array[index].remove(posKey);
        this->size--;
    }

    size_t getHashCode(string key, string key_prev = "")
    {
        size_t hash = 0;
        for (int i = 0; i < key.length(); ++i)
            hash = hash + (key[i] * 1) * i;
        return hash;
    }

    bool keyExists(string key)
    {
        size_t hashcode = getHashCode(key);
        int index = hashcode % capacity;
        for (auto it = array[index].begin(); it != array[index].end(); ++it)
        {
            if ((*it)->getKey() == key)
            {
                return true;
            }
        }
        return false;
    }

    void mostrarTransacciones()
    {
        for (int i = 0; i < capacity; ++i)
            for (auto bloque : this->array[i])
            {
                cout << "--------------------------------------\n";
                cout << "\nBloque ->";
                cout << "\tKey: " << bloque->getKey() << "\tPrevKey: " << bloque->getPrevKey();
                cout << "\nTransacciones:\n";
                cout << "----------------\n";
                cout << "Monto\t\tEmisor\tReceptor\tFecha Transaccion\n";
                cout << bloque->mostrarTransacciones() << endl;
            }
    }

    Bloque *operator[](int index) { return array->_find(index)->data; }

    auto begin(int i)
    {
        return this->array[i].begin();
    }
    auto end(int i)
    {
        return this->array[i].end();
    }
    int bucket_size(int index)
    {
        return this->array[index].size();
    }
    float bucket_count() { return this->size; }

    Bloque *retornarBloque(string key)
    {
        size_t hashcode = getHashCode(key);
        int index = hashcode % capacity;
        Bloque *temp = searchInList(index, key);
        return temp;
    }

    Bloque *searchInList(int index, string key)
    {
        int tamanio = array[index].size();
        tamanio;
        for (auto it = array[index].begin(); it != array[index].end(); ++it)
        {
            if ((*it)->getKey() == key)
            {
                return *it;
            }
        }
        return nullptr;
    }

private:
    float fillFactor()
    {
        return size / (capacity * maxColision);
    }

    void rehashing()
    {
        DoubleList<Bloque *> *array2 = new DoubleList<Bloque *>[this->capacity * 2];

        // for (int i = 0; i < this->capacity; ++i)
        //{
        //
        //     for (auto iter = this->array[i].begin(); iter != this->array[i].end(); ++iter)
        //     {
        //         if (!iter->isEmpty())
        //         {
        //             size_t hashcode = getHashCode((*iter).key);
        //             int index = hashcode % (this->capacity * 2);
        //             array2[index].push_back(Bloque((*iter).key, (*iter).value));
        //         }
        //     }
        // }

        setCapacity(this->capacity * 2);
        delete[] array;
        array = array2;
    }
};
