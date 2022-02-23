#include "BlockChain.h"
#include <fstream>
#include <conio.h>
#include <sstream>
using namespace std;

void leerArchivo(BlockChain *myblockchain)
{
    string registro, last_key = "00000000000";
    string emisor, receptor, s_monto, s_dia, s_mes, s_anio;
    float monto;
    int dia = 1, mes = 1, anio = 1900;
    fstream archivo("DatasetUsuariosOperaciones.csv");
    archivo.open("DatasetUsuariosOperaciones.csv", ios::in);
    int cont = 0;
    cout << "\n\t--------------\n";
    cout << "\tIngresando Datos...";
    cout << "\n\t--------------\n";
    while (getline(archivo, registro))
    {
        stringstream op(registro);
        getline(op, s_monto, ',');
        getline(op, emisor, ',');
        getline(op, receptor, ',');
        getline(op, s_dia, ',');
        getline(op, s_mes, ',');
        getline(op, s_anio, ',');
        dia = stof(s_dia);
        mes = stof(s_mes);
        anio = stof(s_anio);
        monto = stof(s_monto);

        // Ingresamos a los usuarios a nuestra lista
        myblockchain->ingresarUsuario(new Usuario(emisor));
        myblockchain->ingresarUsuario(new Usuario(receptor));

        // Creamos un nuevo puntero de bloque
        Bloque *temp_bloque = new Bloque();

        if (cont % 5 == 0)
        {
            srand(time(NULL));
            Transaccion temp_trans = Transaccion(emisor, receptor, monto, dia, mes, anio);
            temp_bloque->insertarTransaccion(temp_trans);
            temp_bloque->setPrevKey(last_key);
            _sleep(500);
            last_key = myblockchain->setBlockinHashTable(temp_bloque);
            myblockchain->ingresarTransaccionUsuario(temp_trans);
        }
        else
        {
            delete temp_bloque;
            temp_bloque = nullptr;
            temp_bloque = myblockchain->retornarBloque(last_key);
            Transaccion temp_trans = Transaccion(emisor, receptor, monto, dia, mes, anio);
            temp_bloque->insertarTransaccion(temp_trans);
            temp_bloque = myblockchain->recalcularHash(temp_bloque);
            last_key = temp_bloque->getKey();
            myblockchain->ingresarTransaccionUsuario(temp_trans);
        }
        cont++;
    }
    archivo.close();
}

void menuMostrarBlockchain(BlockChain *myblockchain)
{
    system("clear");
    cout << "BlockChain";
    cout << "\n--------------\n";
    myblockchain->mostrarTodasLasTransacciones();
    system("pause");
}

void menuFiltrar(BlockChain *myblockchain)
{
    int opcion;
    system("clear");
    cout << "Filtrado de Datos de Usuarios";
    cout << "\n--------------\n";
    cout << "\n[1] Igual a";
    cout << "\n[2] Inicia con";
    cout << "\n[3] Finaliza con";
    cout << "\n[4] Esta contenido en";
    cout << "\n[5] No esta contenido en";
    cout << "\n\nIngrese una opcion: \t";
    cin >> opcion;
    myblockchain->filtradoUsuarios(opcion);
    cout << "\n";
}

void menuIngresarUsuario(BlockChain *myblockchain)
{
    int opcion;
    string nombre;
    while (opcion != 2)
    {
        system("clear");
        cout << "Ingresar Usuarios";
        cout << "\n--------------\n";
        cout << "\n[1]\tIngrear un usuario Nuevo";
        cout << "\n[2]\tRegresar";
        cout << "\n\nIngrese una opcion: \t";
        cin >> opcion;
        if (opcion == 1)
        {
            cout << "\nIngrese el nombre del nuevo usuario:\t";
            cin >> nombre;
            Usuario *temp_user = new Usuario(nombre);
            myblockchain->ingresarUsuario(temp_user);
        }
        cout << "\n";
        system("PAUSE");
    }
}

void menuMostrarUsuarios(BlockChain *myblockchain)
{
    system("clear");
    cout << "Usuarios Registrados";
    cout << "\n--------------\n";
    myblockchain->mostrarTodosLosUsuarios();
    system("pause");
}

void menuBusquedaArbol(BlockChain *myblockchain)
{

    int ope = 1, nIntentos = 0;
    string emisor;
    while (ope > 0 && ope < 4)
    {
        system("cls");
        cout << "Menu busqueda en el arbol por criterios";
        cout << "\n--------------\n";
        cout << "\n[1]\tObtener todas las transacciones que si hicieron en un fecha X";
        cout << "\n[2]\tObtener todas las transacciones de un monto X";
        cout << "\n[3]\tObtener todas las transacciones de un emisario X";
        cout << "\n[4]\tsalir\n";
        cout << "\nIngrese una opcion: \t";
        cin >> ope;
        system("cls");
        if (ope == 1)
        {
            int dia, mes, anio;
            cout << "\n\tIngrese la fecha (Dia-Mes-Anio)\n\n";
            cout << "Ingrese el dia\t:";
            cin >> dia;
            cout << "Ingrese el mes\t:";
            cin >> mes;
            cout << "Ingrese el anio\t:";
            cin >> anio;
            cout << "\n\t--------------\n";
            cout << "\nTRANSACCIONES PARA LA FECHA\n";
            cout << "\n\t--------------\n";
            myblockchain->buscarPorFechaArbolTransaccion(dia, mes, anio);
            cout << endl;
        }
        else if (ope == 2)
        {
            int begin, end;
            cout << "\nIngrese el rango de monto: \n";
            cout << "\nIngrese inicio: ";
            cin >> begin;
            cout << "\nIngrese final: ";
            cin >> end;
            if (!(begin <= end))
                continue;
            myblockchain->buscarPorMontoArbolTransaccionMonto(begin, end);
            cout << "\n";
        }
        else if (ope == 3)
        {
            string nombre;
            cout << "\nIngrese el nombre del emisario\n";
            cin >> nombre;
            myblockchain->buscarTransaccionesEmitidasDeUnEmisorX(nombre);
        }
        system("PAUSE");
    }
}

void menuIngresarTransaccion(BlockChain *myblockchain, string usersession)
{
    string temp_key;
    string emisor, receptor;
    double monto;
    int dia = 1, mes = 1, anio = 1900;
    int ope;
    while (ope != 3)
    {
        system("cls");
        cout << "Bienvenid@," << usersession << "\n\n";
        cout << "Ingresar Transacciones";
        cout << "\n--------------\n";
        cout << "\n[1]\tInsertar transaccion en un bloque Nuevo";
        cout << "\n[2]\tInsertar transaccion en un bloque Existente";
        cout << "\n[3]\tRegresar";
        cout << "\n\nIngrese una opcion: \t";
        cin >> ope;

        if (ope == 1)
        {
            cout << "\n\nIngresando Transaccion en un bloque nuevo";
            cout << "\n--------------\n";
            Bloque *temp_bloque = new Bloque();

            cout << "\n Ingresando Transaccion en el bloque:\t\n";
            cout << "\nIngrese el monto de la transaccion:\t";
            cin >> monto;
            cout << "\nAsumiendo el usuario actual como emisor ...\t";
            emisor = usersession;
            cout << "\n\nIngrese el nombre del receptor de la transaccion:\t";
            cin >> receptor;
            cout << "\n\n\tIngrese la fecha\n\n";
            cout << "Ingrese el dia\t:";
            cin >> dia;
            cout << "Ingrese el mes\t:";
            cin >> mes;
            cout << "Ingrese el anio\t:";
            cin >> anio;

            if (myblockchain->revisarUsuarioExistente(receptor))
            {
                Transaccion temp_trans = Transaccion(emisor, receptor, monto, dia, mes, anio);
                temp_bloque->insertarTransaccion(temp_trans);
                myblockchain->setBlockinHashTable(temp_bloque);
                myblockchain->ingresarTransaccionUsuario(temp_trans);
                cout << "\nTransaccion realizada correctamente...\n\n";
            }
            else
                cout << "\nUsuario receptor no registrado, transaccion no ingresada\n\n";
            system("PAUSE");
        }

        if (ope == 2)
        {
            system("clear");
            cout << "Ingresando Transaccion en un bloque existente";
            cout << "\n--------------\n";
            if (myblockchain->getHashSize() < 1)
            {
                cout << "\nNo existen bloques en la blockchain, no es posible ingresar una transaccion";
                system("PAUSE");
            }
            else
            {
                int nIntentos = 0;
                do
                {
                    cout << "\nPorfavor ingrese el Hashcode del bloque a modificar:\t";
                    cin >> temp_key;
                    ++nIntentos;
                } while (!myblockchain->verificarExistenciaBloque(temp_key) && nIntentos < 3);

                if (nIntentos == 3)
                {
                    cout << "\nPorfavor acceda a la opcion Mostrar Blockchain' e identifique la key de su bloque y vuelva a intentarlo";
                }
                else
                {
                    Bloque *temp_bloque = myblockchain->retornarBloque(temp_key);

                    cout << "\n Ingresando Transaccion en el bloque:\t"
                         << "\n\n";
                    cout << "Monto\t\tEmisor\tReceptor\tFecha Transaccion\n";
                    cout << temp_bloque->mostrarTransacciones();
                    cout << "\nIngrese el monto de la transaccion:\t";
                    cin >> monto;
                    cout << "Asumiendo el usuario actual como emisor ...\t";
                    emisor = usersession;
                    cout << "\nIngrese el nombre del receptor de la transaccion:\t";
                    cin >> receptor;
                    cout << "\n\n\tIngrese la fecha\n\n";
                    cout << "Ingrese el dia\t:";
                    cin >> dia;
                    cout << "Ingrese el mes\t:";
                    cin >> mes;
                    cout << "Ingrese el anio\t:";
                    cin >> anio;

                    if (myblockchain->revisarUsuarioExistente(receptor))
                    {
                        Transaccion temp_trans = Transaccion(emisor, receptor, monto, dia, mes, anio);
                        temp_bloque->insertarTransaccion(temp_trans);
                        temp_bloque = myblockchain->recalcularHash(temp_bloque);
                        myblockchain->ingresarTransaccionUsuario(temp_trans);
                        cout << "\nTransaccion realizada correctamente...\n\n";

                        myblockchain->recalcularKeyDesdeBloque(temp_bloque);
                    }
                    else
                        cout << "\nUsuario receptor no registrado, transaccion on ingresada\n\n";
                    system("PAUSE");
                }
            }
        }
        cout << endl;
    }
    return;
}

void menuPrincipal(BlockChain *myblockchain, string usersession)
{
    int ope = 0;
    while (ope != 7)
    {
        system("cls");
        cout << "Bienvenid@," << usersession << "\n\n";
        cout << "Menu principal";
        cout << "\n--------------\n";
        cout << "\n[1]\tIngresar Transacciones";
        cout << "\n[2]\tIngresar Usuario";
        cout << "\n[3]\tMostrar Usuarios Registrados";
        cout << "\n[4]\tMostrar Blockchain";
        cout << "\n[5]\tFiltrar/Buscar";
        cout << "\n[6]\tBusqueda por criterio";
        cout << "\n[7]\tsalir";
        cout << "\n\nIngrese una opcion: \t";
        cin >> ope;
        switch (ope)
        {
        case 1:
            menuIngresarTransaccion(myblockchain, usersession);
            break;
        case 2:
            menuIngresarUsuario(myblockchain);
            break;
        case 3:
            menuMostrarUsuarios(myblockchain);
            break;
        case 4:
            menuMostrarBlockchain(myblockchain);
            break;
        case 5:
            menuFiltrar(myblockchain);
            break;
        case 6:
            menuBusquedaArbol(myblockchain);
            break;
        default:
            break;
        }
    }
}

string authUser(BlockChain *myblockchain)
{
    string usersession;
    do
    {
        system("clear");
        cout << "Autenticacion de Usuario";
        cout << "\n--------------\n";

        cout << "\nPorfavor ingrese su nombre:\t";
        cin >> usersession;
    } while (myblockchain->revisarUsuarioExistente(usersession));

    myblockchain->ingresarUsuario(new Usuario(usersession));
    return usersession;
}

int main()
{
    BlockChain *myblockchain = new BlockChain();
    leerArchivo(myblockchain);
    string usersession = authUser(myblockchain);
    menuPrincipal(myblockchain, usersession);
    system("PAUSE");
    return 0;
}
