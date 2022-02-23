#include "double.h"
#include "Usuario.h"
#include "nodeArbol.h"
#include <time.h>
class Bloque
{

private:
    NodeBT<Bloque *> *node;
    string key;
    string prev_key;
    size_t fechaInsercion;
    DoubleList<Transaccion> *transacciones;
    int limiteTransacciones;

public:
    Bloque()
    {
        prev_key = "00000000000";
        limiteTransacciones = 5;
        transacciones = nullptr;
        fechaInsercion = time(0);
        node = nullptr;
        transacciones = new DoubleList<Transaccion>();
    }

    void setNode(NodeBT<Bloque *> *b) { node = b; }
    NodeBT<Bloque *> *getNode() { return this->node; }

    bool operator<=(Bloque b)
    {
        return this->getFechaInsercion() <= b.getFechaInsercion();
    }
    bool operator>(Bloque b)
    {
        return this->getFechaInsercion() > b.getFechaInsercion();
    }
    bool operator==(Bloque b)
    {
        return this->getFechaInsercion() == b.getFechaInsercion();
    }
    bool operator<(Bloque b)
    {
        return this->getFechaInsercion() < b.getFechaInsercion();
    }

    DoubleList<Transaccion> *getTransacciones() { return this->transacciones; }
    size_t getFechaInsercion() { return this->fechaInsercion; }
    void setKey(string key) { this->key = key; }
    void setPrevKey(string _prevkey = "00000000000") { this->prev_key = _prevkey; }
    int getNumeroTransacciones() { return this->transacciones->size(); }
    string getKey() { return this->key; }
    string getPrevKey() { return this->prev_key; }

    void insertarTransaccion(Transaccion transaccion)
    {
        this->transacciones->push_back(transaccion);
    }

    string mostrarTransacciones()
    {
        if (this->transacciones == nullptr)
        {
            return "No hay bloques con transacciones";
        }
        string output = "";
        DoubleList<Transaccion>::Iterator it = transacciones->begin();
        for (it; it != transacciones->end(); ++it)
        {
            output.append((*it).getString());
        }

        output.append("\n");
        return output;
    }

    string generarKey()
    {
        string temp_string;
        temp_string = "000";

        temp_string = temp_string + (char)transacciones->back().getEmisor()[0];
        temp_string = temp_string + to_string((transacciones->back().getEmisor()[0] * 1) % 100);

        temp_string = temp_string + (char)transacciones->back().getReceptor()[0];
        temp_string = temp_string + to_string((transacciones->back().getReceptor()[0] * 1) % 100);

        float temp_monto = transacciones->back().getMonto();
        string string_monto = to_string(temp_monto);
        temp_string = temp_string + string_monto[0] + string_monto[1];

        string nuevaKey;
        nuevaKey.resize(11);

        int num;
        for (int i = 0; i < 11; i++)
        {
            num = temp_string[i] + prev_key[i];
            if (i % 2 == 0)
                num = 48 + num % 10;
            else
                num = 65 + num % 25;
            nuevaKey[i] = char(num);
        }

        return nuevaKey;
    }
};
