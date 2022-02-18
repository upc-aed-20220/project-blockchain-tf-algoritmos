#include "HashTable.h"
class BlockChain {
    private:
        DoubleList<Usuario>* usuarios;
    //BSTree<Bloque<Transaccion>*>* porNombre;
    //BSTree<Bloque<Transaccion>*>* porNonce; // rango inicial : 20-100 , puede salir repetidos, cada 5 o 10 repetidos aumentar el rango de 20 a 120
    //BSTree<bloque<Transaccion>*>* por;
        HashTable* hashTable;

    public:
    BlockChain() {
        hashTable = new HashTable();
        usuarios = new DoubleList<Usuario>();
    }

    string setBlockinHashTable(Bloque bloque) {
        return hashTable->set(bloque);
    }

    Bloque recalcularHash(Bloque bloque) {
        return hashTable->recalcularHash(bloque);
    }

    int getHashSize() {
        return hashTable->getSize();
    }

    bool verificarExistenciaBloque(string key) {
        return hashTable->keyExists(key);
    }

    void mostrarTodasLasTransacciones() {
        hashTable->mostrarTransacciones();
    }

    void mostrarTodosLosUsuarios() {
        int i = 1;
        for (auto usuario : (*usuarios)) {
            cout << "\tUsuario: " << i << ":\t" << usuario.getNombre() << endl;
            i++;
        }
        cout << endl;
    }

    Bloque retornarBloque(string key)
    {
        return hashTable->retornarBloque(key);
    }

    string ingresarUsuario(Usuario user){
        string temp_string = "";
        for (auto usuario : (*usuarios)) {
            if (user.getNombre() == usuario.getNombre()) {
                temp_string = "\nEl usuario ya existe";
                return temp_string;
            }
        }
        usuarios->push_back(user);
        temp_string = "\nUsuario ingresado correctamente";
        return temp_string;
    }

    //bool registroUsuario(string datos, string alias, string contra, int dinero) {
    //    Usuario* nuevoU = buscarUsuario(usuarios, alias);
    //    if (nuevoU != nullptr) {
    //        cout << "\nUsuario ya registrado, ingrese un nuevo alias ";
    //        return false;
    //    }
    //    nuevoU = new Usuario(datos, alias, contra, dinero);
    //    usuarios.push_back(nuevoU);
    //    return true;
    //}

    bool revisarUsuarioExistente(string nombre) {
        for (auto usuario : (*usuarios)){
            if (nombre == usuario.getNombre()) {
                return true;
            }
        }
        return false;
    }

    void ingresarTransaccionUsuario(Transaccion trans) {
        buscaUsuario(trans.getEmisor()).ingresarTransaccionEmitida(trans);
        buscaUsuario(trans.getReceptor()).ingresarTransaccionRecibida(trans);
    }

    Usuario buscaUsuario(string nombre) {
        for (auto usuario : (*usuarios))
            if (nombre == usuario.getNombre())
                return usuario;
    }

    void filtradoUsuarios(int opc) {
        string nombre;
        char character;
            switch (opc) {
            case 1:
                cout << "\nIngrese nombre a buscar:";
                cin >> nombre;
                for (auto usuario : (*usuarios)) {
                    primeraPalabra(nombre, usuario);
                }break;
            case 2:
                cout << "\nIngrese primera letra:";
                cin >> character;
                for (auto usuario : (*usuarios)) {
                    iniciaPalabra(character, usuario);
                }
                break;
            case 3:
                cout << "\nIngrese ultima letra:";
                cin >> character;
                for (auto usuario : (*usuarios)) {
                    ultimaPalabra(character, usuario);
                }
                break;
            case 4:
                cout << "\nIngrese letra/s contenidas en:";
                cin >> nombre;
                for (auto usuario : (*usuarios)) {
                    mediasPalabras(nombre, usuario);
                }
                break;
            case 5:
                cout << "\nIngrese letra/s no contenidas en:";
                cin >> nombre;
                for (auto usuario : (*usuarios)) {
                    noMediasPalabras(nombre, usuario);
                }
                break;
                default:
                break;
            }
            cout << endl;
        }
    

    void primeraPalabra(string palabra, Usuario usuario) {

        string nombre = usuario.getNombre();
        if (nombre == palabra) {
            cout << usuario;
        }
    }
    void iniciaPalabra(char letraInicial, Usuario usuario) {
        string nombre = usuario.getNombre();
        if (toupper(nombre[0]) == toupper(letraInicial)) {
            cout << usuario;
        }
    }
    void ultimaPalabra(char letraFinal, Usuario usuario) {
        string nombre = usuario.getNombre();
        if (nombre[nombre.length() - 1] == letraFinal) {
            cout << usuario;
        }
    }
    void mediasPalabras(string letrasMedias, Usuario usuario) {
        string nombre = usuario.getNombre();
        if (nombre.rfind(letrasMedias) != string::npos) {
            cout << usuario;
        }
    }
    void noMediasPalabras(string noLetrasMedias, Usuario usuario) {
        string nombre = usuario.getNombre();
        if (nombre.rfind(noLetrasMedias) == string::npos) {
            cout << usuario;
        }
    }

};
