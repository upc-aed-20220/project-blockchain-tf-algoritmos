#include "BlockChain.h"
#include <fstream>
#include <conio.h>
#include <sstream>
using namespace std;
void menuMostrarBlockchain(BlockChain* myblockchain) {
    system("clear");
    cout << "BlockChain";
    cout << "\n--------------\n";
    myblockchain->mostrarTodasLasTransacciones();
    system("pause");
}

void menuFiltrar(BlockChain* myblockchain){
    int opcion;
    system("clear");
    cout << "Filtrado de Datos";
    cout << "\n--------------\n";
    cout << "\n[1] Igual a";
    cout << "\n[2] Inicia con";
    cout << "\n[3] Finaliza con";
    cout << "\n[4] Esta contenido en";
    cout << "\n[5] No esta contenido en";
    cout << "\n\nIngrese una opcion: \t"; cin >> opcion;
    myblockchain->filtradoUsuarios(opcion);
    cout << endl; system("PAUSE");
}

void menuIngresarUsuario(BlockChain* myblockchain) {
    int opcion;
    string nombre;
    while (opcion != 2) {
        system("clear");
        cout << "Ingresar Usuarios";
        cout << "\n--------------\n";
        cout << "\n[1]\tIngrear un usuario Nuevo";
        cout << "\n[2]\tRegresar";
        cout << "\n\nIngrese una opcion: \t"; cin >> opcion;
        if (opcion == 1) {
            cout << "\nIngrese el nombre del nuevo usuario:\t"; cin >> nombre;
            Usuario temp_user = Usuario(nombre);
            cout << myblockchain->ingresarUsuario(temp_user);
        }
        cout << endl; system("PAUSE");
    }
}

void menuIngresarTransaccion(BlockChain* myblockchain, string usersession) {
    string temp_key;
    string emisor, receptor;
    double monto;
    int ope;
    int index = -1;
    while (ope != 3) {
        system("cls");
        cout << "Bienvenid@," << usersession << "\n\n";
        cout << "Ingresar Transacciones";
        cout << "\n--------------\n";
        cout << "\n[1]\tInsertar transaccion en un bloque Nuevo";
        cout << "\n[2]\tInsertar transaccion en un bloque Existente";
        cout << "\n[3]\tRegresar";
        cout << "\n\nIngrese una opcion: \t"; cin >> ope;

        if (ope == 1) {
            cout << "\n\nIngresando Transaccion en un bloque nuevo";
            cout << "\n--------------\n";
            Bloque temp_bloque;
            index = myblockchain->getHashSize();
            temp_bloque.setIndex(index);

            cout << "\n Ingresando Transaccion en el bloque:\t" << index + 1;
            cout << endl;
            cout << "\nIngrese el monto de la transaccion:\t"; cin >> monto;
            cout << "Asumiendo el usuario actual como emisor ...\t"; emisor = usersession;
            cout << "\nIngrese el nombre del receptor de la transaccion:\t"; cin >> receptor;

            if (myblockchain->revisarUsuarioExistente(receptor)) {
                Transaccion temp_trans = Transaccion(emisor, receptor, monto);
                temp_bloque.insertarTransaccion(temp_trans);
                myblockchain->setBlockinHashTable(temp_bloque); 
                myblockchain->ingresarTransaccionUsuario(temp_trans);
            }
            else cout << "\nUsuario receptor no registrado, transaccion on ingresada";
        }

        if (ope == 2) {
            system("clear");
            cout << "Ingresando Transaccion en un bloque existente";
            cout << "\n--------------\n";
            if (myblockchain->getHashSize() < 1) {
                cout<<"\nNo existen bloques en la blockchain, no es posible ingresar una transaccion";
            }
            else {
                int nIntentos = 0;
                do {
                    cout << "\nPorfavor ingrese el Hashcode del bloque a modificar:\t";
                    cin >> temp_key;
                    ++nIntentos;
                } while (!myblockchain->verificarExistenciaBloque(temp_key) && nIntentos < 3);

                if(nIntentos == 3){
                    cout << "\nPorfavor acceda a la opcion Mostrar Blockchain' e identifique la key de su bloque y vuelva a intentarlo";
                }
                else {
                    Bloque temp_bloque = myblockchain->retornarBloque(temp_key);

                    cout << "\n Ingresando Transaccion en el bloque:\t" << temp_bloque.getIndex();
                    cout << endl;
                    cout << temp_bloque.mostrarTransacciones();
                    cout << "\nIngrese el monto de la transaccion:\t"; cin >> monto;
                    cout << "Asumiendo el usuario actual como emisor ...\t"; emisor = usersession;
                    cout << "\nIngrese el nombre del receptor de la transaccion:\t"; cin >> receptor;

                    // 
                    if (myblockchain->revisarUsuarioExistente(receptor)) {
                        Transaccion temp_trans = Transaccion(emisor, receptor, monto);
                        temp_bloque.insertarTransaccion(temp_trans);
                        //myblockchain->setBlockinHashTable(temp_bloque);
                        myblockchain->recalcularHash(temp_bloque);
                        myblockchain->ingresarTransaccionUsuario(temp_trans);
                    }
                    else cout << "\nUsuario receptor no registrado, transaccion on ingresada";
                }
            }
        }
        cout << endl; 
    }
    return;
}

void menuMostrarUsuarios(BlockChain* myblockchain) {
    system("clear");
    cout << "Usuarios Registrados";
    cout << "\n--------------\n";
    myblockchain->mostrarTodosLosUsuarios();
    system("pause");
}

void menuPrincipal(BlockChain* myblockchain, string usersession){
    int ope = 0;
    while (ope != 6) {
        system("cls");
        cout << "Bienvenid@," << usersession << "\n\n";
        cout << "Menu principal";
        cout << "\n--------------\n";
        cout << "\n[1]\tIngresar Transacciones";
        cout << "\n[2]\tIngresar Usuario";
        cout << "\n[3]\tMostrar Usuarios Registrados";
        cout << "\n[4]\tMostrar Blockchain";
        cout << "\n[5]\tFiltrar/Buscar";
        cout << "\n[6]\tsalir";
        cout << "\n\nIngrese una opcion: \t";
        cin >> ope;
        switch (ope) {
            case 1: menuIngresarTransaccion(myblockchain, usersession); break;
            case 2: menuIngresarUsuario(myblockchain); break;
            case 3: menuMostrarUsuarios(myblockchain); break;
            case 4: menuMostrarBlockchain(myblockchain); break;
            case 5: menuFiltrar(myblockchain); break;
        }
    }
}

/*
void imprimirBloques(){

cout << "\n";
	controller->imprimirBloques();


}


*/

string authUser(BlockChain* myblockchain) {
    string usersession;
    system("clear");
    cout << "Autenticacion de Usuario";
    cout << "\n--------------\n";
    /*
    cout << "\nPorfavor ingrese su nombre:\t";
    cin >> usersession;
    */
    //myblockchain->revisarUsuarioExistente(usersession);
    //
    usersession = "patrick";
    myblockchain->ingresarUsuario(Usuario(usersession));
    //destinatario predeterminado
    myblockchain->ingresarUsuario(Usuario("juan"));
    return usersession;
}

void read(BlockChain* myblockchain)
{
    string registro,last_key = "00000000000";
    string emisor,receptor,s_monto;
    float monto;
    fstream archivo("DatasetUsuariosOperaciones.csv");
    archivo.open("DatasetUsuariosOperaciones.csv", ios::in);
    //getline(archivo, registro);
    int cont = 0;
    while (getline(archivo, registro))
    {
        
        stringstream op(registro);
        getline(op, s_monto, ',');
        getline(op, emisor, ',');
        getline(op, receptor, ',');
        monto = stof(s_monto);
        cout << registro ;

        myblockchain->ingresarUsuario(Usuario(emisor));
        myblockchain->ingresarUsuario(Usuario(receptor));
        Bloque temp_bloque;
        if (cont % 5 == 0) {
           Transaccion temp_trans = Transaccion(emisor, receptor, monto);
           temp_bloque.insertarTransaccion(temp_trans);
           temp_bloque.setPrevKey(last_key);
           last_key = myblockchain->setBlockinHashTable(temp_bloque);
           myblockchain->ingresarTransaccionUsuario(temp_trans);
        }
        else {
            temp_bloque = myblockchain->retornarBloque(last_key); // error no devuelve o no encuentra
            
            Transaccion temp_trans = Transaccion(emisor, receptor, monto);
            temp_bloque.insertarTransaccion(temp_trans);
            //myblockchain->setBlockinHashTable(temp_bloque);
            temp_bloque = myblockchain->recalcularHash(temp_bloque);
            last_key = temp_bloque.key;
            myblockchain->ingresarTransaccionUsuario(temp_trans);
        }
        cout << last_key << endl;
        cont++;
    }
    archivo.close();
}


int main()
{
    BlockChain* myblockchain = new BlockChain();
    string usersession = authUser(myblockchain);
    menuPrincipal(myblockchain, usersession);
    //read(myblockchain);

    system("PAUSE");
    return 0;
}
