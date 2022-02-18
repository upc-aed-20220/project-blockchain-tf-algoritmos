#include "double.h"
#include "Usuario.h"

struct Bloque
{
    Node<Bloque>* node;
    string key;
    string prev_key;
    int index;
    DoubleList<Transaccion>* transacciones;
    int limiteTransacciones;

    Bloque() {
        // key = hashFunction(key);
        prev_key = "00000000000";
        limiteTransacciones = 5;
        transacciones = nullptr;
        node = nullptr;
        transacciones = new DoubleList<Transaccion>();
    }

    int getNumeroTransacciones() { return this->transacciones->size(); }
    string returnKey() { return this->key; }
     
    void insertarTransaccion(Transaccion transaccion) {
        //if (getNumeroTransacciones() >= this->limiteTransacciones)
        //    return;
         this->transacciones->push_back(transaccion);
        // TODO: Debo de insertar un puntero al arreglo o lista de transacciones del usuario que realizo la transaccion
        // TODO: se debe actualizar la key cada vez que se inserte una transaccion
        return;
    }

    string mostrarTransacciones() {
        if (this->transacciones == nullptr) {
            return "Esto es nulo :)";
        }
        string output = "";
        DoubleList<Transaccion>::Iterator it = transacciones->begin();
        for (it; it != transacciones->end(); ++it) {
            output.append((*it).getString());
            output.append("\n");
        }
        /*transacciones;
        for (auto it : *transacciones) {
            output = output + it.getString() + "\n";
        }*/
        return output;
    }

    string generarKey() {
        string temp_string;
        temp_string = "000";
       
        temp_string = temp_string + (char)transacciones->back().getEmisor()[0];
        temp_string = temp_string + to_string((transacciones->back().getEmisor()[0] * 1)% 100) ;

        temp_string = temp_string + (char)transacciones->back().getReceptor()[0];
        temp_string = temp_string + to_string((transacciones->back().getReceptor()[0] * 1)% 100) ;

        float temp_monto = transacciones->back().getMonto();
        string string_monto = to_string(temp_monto);
        temp_string = temp_string + string_monto[0] + string_monto[1];

        string nuevaKey;
        nuevaKey.resize(11);

        int num;
        for (int i = 0; i < 11; i++) {
            //num = (temp_string[i] + prev_key[i])/2;
            num = temp_string[i] + prev_key[i];
            if (i % 2 == 0)
                num = 48 + num % 10;
            else
                num = 65 + num % 25;
            nuevaKey[i] = char(num);

           
        }

        return nuevaKey;
        //this->key = temp_string;;
    }

    void setPrevKey(string _prevkey = "00000000000") {
        this->prev_key = _prevkey;
    }

    void setIndex(int _index) {
        this->index = _index;
    }

    int getIndex() { return this->index + 1; }

    string getKey() { return this->key; }
};
