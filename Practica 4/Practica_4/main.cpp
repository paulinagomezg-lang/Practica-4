#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include "Red.h"
#include "LectorTopologia.h"
using namespace std;

// Lee un entero sin que el programa se caiga si el usuario escribe letras
int Leer_Entero(const string &Mensaje){
    while (true){
        cout << Mensaje;
        string Texto;
        if (!getline(cin, Texto)) return 0;   // se acabo la entrada: sale del menu
        istringstream Flujo(Texto);
        int Valor;
        char Resto;
        if ((Flujo >> Valor) && !(Flujo >> Resto)) return Valor;
        cout << "Ingrese un numero entero valido." << endl;
    }
}

string Leer_Texto(const string &Mensaje){
    cout << Mensaje;
    string Texto;
    getline(cin, Texto);
    return Texto;   // si se acabo la entrada queda vacio
}

void Mostrar_Camino(const Red &R, const string &Origen, const string &Destino){
    list<string> Camino = R.Encontrar_Camino(Origen, Destino);
    cout << "Camino " << Origen << " -> " << Destino << ": ";
    bool Primero = true;
    for (const string &Nodo : Camino){
        if (!Primero) cout << " -> ";
        cout << Nodo;
        Primero = false;
    }
    cout << "   (costo " << R.Costo_Camino(Origen, Destino) << ")" << endl;
}

void Mostrar_Menu(){
    cout << " SIMULADOR DE RED DE ENRUTADORES ;3" << endl;
    cout << "1. Cargar la red desde un archivo .txt" << endl;
    cout << "2. Agregar un enrutador" << endl;
    cout << "3. Eliminar un enrutador" << endl;
    cout << "4. Agregar un enlace" << endl;
    cout << "5. Eliminar un enlace" << endl;
    cout << "6. Camino y costo entre dos enrutadores" << endl;
    cout << "7. Imprimir la red" << endl;
    cout << "8. Imprimir las tablas de costos" << endl;
    cout << "0. Salir" << endl;
}

int main(int argc, char *argv[]){
    Red R;
    Lectortopologia Lector(R);

    // Si se pasa el archivo como argumento, se carga de una vez
    if (argc > 1){
        try {
            Lector.Cargar(argv[1]);
            cout << "Red cargada desde " << argv[1] << endl;
        } catch (const exception &e){
            cout << "Error: " << e.what() << endl;
        }
    }

    int Opcion = -1;
    while (Opcion != 0 && cin){
        Mostrar_Menu();
        Opcion = Leer_Entero("Opcion: ");
        try {
            if (Opcion == 1){
                Lector.Cargar(Leer_Texto("Ruta del archivo: "));
                cout << "Red cargada." << endl;
            } else if (Opcion == 2){
                R.Agregar_un_Enrutador(Leer_Texto("Nombre del enrutador: "));
            } else if (Opcion == 3){
                R.Eliminar_el_Enrutador(Leer_Texto("Nombre del enrutador a eliminar: "));
            } else if (Opcion == 4){
                string A = Leer_Texto("Enrutador A: ");
                string B = Leer_Texto("Enrutador B: ");
                int Costo = Leer_Entero("Costo del enlace: ");
                R.Agregar_un_Enlace(A, B, Costo);
            } else if (Opcion == 5){
                string A = Leer_Texto("Enrutador A: ");
                string B = Leer_Texto("Enrutador B: ");
                R.Eliminar_un_Enlace(A, B);
            } else if (Opcion == 6){
                string Origen = Leer_Texto("Origen: ");
                string Destino = Leer_Texto("Destino: ");
                Mostrar_Camino(R, Origen, Destino);
            } else if (Opcion == 7){
                R.Imprimir_Red();
            } else if (Opcion == 8){
                R.Imprimir_Tablas();
            } else if (Opcion != 0){
                cout << "Opcion no valida." << endl;
            }
        } catch (const exception &e){
            cout << "Error: " << e.what() << endl;
        }
    }
    cout << "Hasta luego." << endl;
    return 0;
}