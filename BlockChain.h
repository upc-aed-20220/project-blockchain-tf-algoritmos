#include "HashTable.h"
#include "Arbol.h"
class BlockChain
{
private:
    Arbol<Usuario *> *usuarios;
    Arbol<Bloque *> *arbolFecha;
    Arbol<Transaccion> *arbolTransacciones;
    Arbol<Transaccion> *arbolTransaccionesMonto;
    HashTable *hashTable;

public:
    BlockChain()
    {
        hashTable = new HashTable();
        auto showU = [](Usuario *user) -> void
        { cout << *user << "\n"; };
        auto compU = [](Usuario *a, Usuario *b) -> bool
        { return a->getNombre() < b->getNombre(); };
        auto equalsU = [](Usuario *a, Usuario *b) -> bool
        { return a->getNombre() == b->getNombre(); };
        auto dfU = []() -> Usuario *
        { return nullptr; };
        usuarios = new Arbol<Usuario *>(compU, showU, equalsU, dfU);

        auto showB = [](Bloque *b) -> void
        { cout << b->mostrarTransacciones() << " "; };
        auto compB = [](Bloque *a, Bloque *b) -> bool
        { return *a < *b; };
        auto equalsB = [](Bloque *a, Bloque *b) -> bool
        { return *a == *b; };
        auto dfB = []() -> Bloque *
        { return nullptr; };
        arbolFecha = new Arbol<Bloque *>(compB, showB, equalsB, dfB);

        auto showT = [](Transaccion b) -> void
        { cout << b.show() << "\n"; };
        auto compT = [](Transaccion a, Transaccion b) -> bool
        { return a < b; };
        auto equalsT = [](Transaccion a, Transaccion b) -> bool
        { return a == b; };
        auto dfT = []() -> Transaccion
        { return Transaccion(); };
        arbolTransacciones = new Arbol<Transaccion>(compT, showT, equalsT, dfT);

        auto showTM = [](Transaccion b) -> void
        { cout << b.show() << "\n"; };
        auto compTM = [](Transaccion a, Transaccion b) -> bool
        { return a.getMonto() < b.getMonto(); };
        auto equalsTM = [](Transaccion a, Transaccion b) -> bool
        { return a.getMonto() == b.getMonto(); };
        auto dfTM = []() -> Transaccion
        { return Transaccion(); };
        arbolTransaccionesMonto = new Arbol<Transaccion>(compTM, showTM, equalsTM, dfTM);
    }

    HashTable *getHashTable() { return this->hashTable; } 

    int getHashSize() { return hashTable->getSize(); }

    void recalcularKeyDesdeBloque(Bloque *bloque)
    {
        NodeBT<Bloque *> *parent = nullptr;
        NodeBT<Bloque *> *node = bloque->getNode();
        arbolFecha->propagar(node, parent, node->data->getKey(), hashTable);
    }

    void buscarPorFechaArbolTransaccion(int dia, int mes, int anio)
    {
        Transaccion t = Transaccion(dia, mes, anio);
        arbolTransacciones->find(t);
    }
    void buscarPorMontoArbolTransaccionMonto(int begin, int end)
    {
        auto isInRange = [begin, end](Transaccion t) -> int
        {
            return (t.getMonto() > begin && t.getMonto() < end) ? 0 : (t.getMonto() == end) ? 1
                                                                  : (t.getMonto() == begin) ? 2
                                                                  : (t.getMonto() < begin)  ? 3
                                                                  : (t.getMonto() > end)    ? 4
                                                                                            : -1;
        };
        arbolTransaccionesMonto->findyRange(isInRange);
    }
    void buscarTransaccionesEmitidasDeUnEmisorX(string nombre)
    {
        Usuario *user = buscaUsuario(nombre);
        if (!user)
        {
            cout << "\nEmisor No Encontrado\n";
            return;
        }
        user->mostrarTransaccionesEmitidas();
        user = nullptr;
    }

    void insertarBloqueEnArbol(Bloque *bloque)
    {
        NodeBT<Bloque *> *parent = nullptr;
        NodeBT<Bloque *> *node = arbolFecha->insert2(bloque, parent);

        bloque->setNode(node);
        parent ? bloque->setPrevKey(parent->data->getKey()) : bloque->setPrevKey("00000000000");
    }

    void insertarTransaccionEnArbol(Transaccion transaccion)
    {
        NodeBT<Transaccion> *p = nullptr;
        arbolTransacciones->insert(transaccion, p);
        arbolTransaccionesMonto->insert(transaccion, p);
        p = nullptr;
    }

    void ingresarTransaccionUsuario(Transaccion trans)
    {
        insertarTransaccionEnArbol(trans);
        Usuario *aux = buscaUsuario(trans.getEmisor());
        aux->ingresarTransaccionEmitida(trans);
        Usuario *aux2 = buscaUsuario(trans.getReceptor());
        aux2->ingresarTransaccionRecibida(trans);
    }

    string setBlockinHashTable(Bloque *bloque)
    {
        insertarBloqueEnArbol(bloque);
        string key = hashTable->setBlockinHashTable(bloque);
        return key;
    }

    void ingresarUsuario(Usuario *user)
    {
        string temp_string = "";
        if (usuarios->findValue(user))
        {
            cout << "\nUsuario Existente\n";
        }
        else
        {
            NodeBT<Usuario *> *p = nullptr;
            usuarios->insert(user, p);
            p = nullptr;
            cout << "\n Usuario ingresado correctamente\n";
        }
    }

    Bloque *recalcularHash(Bloque *bloque) { return hashTable->recalcularHash(bloque); }

    Bloque *retornarBloque(string key) { return hashTable->retornarBloque(key); }

    Usuario *buscaUsuario(string nombre)
    {
        Usuario aux = Usuario(nombre, true);
        return usuarios->findValue(&aux);
    }

    bool verificarExistenciaBloque(string key) { return hashTable->keyExists(key); }

    bool revisarUsuarioExistente(string nombre)
    {
        Usuario aux(nombre, true);
        return usuarios->findValue(&aux) != nullptr;
    }

    void mostrarTodasLasTransacciones() { hashTable->mostrarTransacciones(); }

    void mostrarTodosLosUsuarios()
    {
        usuarios->displayPreOrder();
    }

    void filtradoUsuarios(int opc)
    {
        string nombre;
        char character;
        switch (opc)
        {
        case 1:
            cout << "\nIngrese nombre a buscar:";
            cin >> nombre;
            cout << "\n";
            usuarios->findByCriteria([&, this](Usuario *user) -> bool
                                     { return primeraPalabra(nombre, user); });
            break;
        case 2:
            cout << "\nIngrese primera letra:";
            cin >> character;
            cout << "\n";
            usuarios->findByCriteria([&, this](Usuario *user) -> bool
                                     { return iniciaPalabra(character, user); });
            break;
        case 3:
            cout << "\nIngrese ultima letra:";
            cin >> character;
            cout << "\n";
            usuarios->findByCriteria([&, this](Usuario *user) -> bool
                                     { return ultimaPalabra(character, user); });
            break;
        case 4:
            cout << "\nIngrese letra/s contenidas en:";
            cin >> nombre;
            cout << "\n";
            usuarios->findByCriteria([&, this](Usuario *user) -> bool
                                     { return mediasPalabras(nombre, user); });
            break;
        case 5:
            cout << "\nIngrese letra/s no contenidas en:";
            cin >> nombre;
            cout << "\n";
            usuarios->findByCriteria([&, this](Usuario *user) -> bool
                                     { return noMediasPalabras(nombre, user); });
            break;
        }
        cout << "\n";
        system("pause");
    }

    bool primeraPalabra(string palabra, Usuario *usuario)
    {
        string nombre = usuario->getNombre();
        if (nombre == palabra)
        {
            return true;
        }
        else
            return false;
    }
    bool iniciaPalabra(char letraInicial, Usuario *usuario)
    {
        string nombre = usuario->getNombre();
        if (toupper(nombre[0]) == toupper(letraInicial))
        {
            return true;
        }
        else
            return false;
    }
    bool ultimaPalabra(char letraFinal, Usuario *usuario)
    {
        string nombre = usuario->getNombre();
        if (nombre[nombre.length() - 1] == letraFinal)
        {
            return true;
        }
        else
            return false;
    }
    bool mediasPalabras(string letrasMedias, Usuario *usuario)
    {
        string nombre = usuario->getNombre();
        if (nombre.rfind(letrasMedias) != string::npos)
        {
            return true;
        }
        else
            return false;
    }
    bool noMediasPalabras(string noLetrasMedias, Usuario *usuario)
    {
        string nombre = usuario->getNombre();
        if (nombre.rfind(noLetrasMedias) == string::npos)
        {
            return true;
        }
        else
            return false;
    }
};
