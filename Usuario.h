#include <iostream>
#include "Transaccion.h"
#include "double.h"
using namespace std;
struct Usuario
{
    string nombre;
    DoubleList<Transaccion> *transaccionesEmitidas;
    DoubleList<Transaccion> *transaccionesRecibidas;

    Usuario(string nombre, bool empty)
    {
        this->nombre = nombre;
        transaccionesEmitidas = new DoubleList<Transaccion>();
        transaccionesRecibidas = new DoubleList<Transaccion>();
    }

    Usuario(string _nombre = "")
    {
        transaccionesEmitidas = new DoubleList<Transaccion>();
        transaccionesRecibidas = new DoubleList<Transaccion>();
        nombre = _nombre;
    }

    string getNombre() { return this->nombre; }
    void ingresarTransaccionEmitida(Transaccion trans) { transaccionesEmitidas->push_back(trans); }
    void ingresarTransaccionRecibida(Transaccion trans) { transaccionesRecibidas->push_back(trans); }
    void mostrarTransaccionesEmitidas()
    {
        for (auto elem : *transaccionesEmitidas)
        {
            cout << elem.getString() << "\n";
        }
    }
};

ostream &operator<<(ostream &os, Usuario usuario)
{
    string Emitidos = "";
    string Recibidos = "";

    DoubleList<Transaccion>::Iterator it = usuario.transaccionesEmitidas->begin();
    for (it; it != usuario.transaccionesEmitidas->end(); ++it)
    {
        Emitidos.append((*it).getString());
        Emitidos.append("\n");
    }

    DoubleList<Transaccion>::Iterator it2 = usuario.transaccionesRecibidas->begin();
    for (it2; it2 != usuario.transaccionesRecibidas->end(); ++it2)
    {
        Recibidos.append((*it2).getString());
        Recibidos.append("\n");
    }

    os << "Usuario: " << usuario.nombre << "\n"
       << "Transacciones Emitidas:\n"
       << Emitidos << "\nTransacciones Recibidas\n"
       << Recibidos<<"\n_________________________\n";
    return os;
}
