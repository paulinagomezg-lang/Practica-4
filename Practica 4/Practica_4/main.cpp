#include <iostream>
#include <stdexcept>
#include "Red.h"
using namespace std;

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

int main(){
    try {
        Red R;
        R.Agregar_un_Enrutador("A");
        R.Agregar_un_Enrutador("B");
        R.Agregar_un_Enrutador("C");
        R.Agregar_un_Enrutador("D");

        // Topologia de la Figura 1 del PDF
        R.Agregar_un_Enlace("A", "B", 4);
        R.Agregar_un_Enlace("A", "C", 10);
        R.Agregar_un_Enlace("A", "D", 5);
        R.Agregar_un_Enlace("B", "C", 3);
        R.Agregar_un_Enlace("B", "D", 1);
        R.Agregar_un_Enlace("D", "C", 2);

        R.Imprimir_Red();
        cout << endl;
        R.Imprimir_Tablas();
        cout << endl;

        Mostrar_Camino(R, "A", "C");
        Mostrar_Camino(R, "A", "D");
        Mostrar_Camino(R, "C", "A");

        cout << "\n--- Elimino los enlaces A-B y A-D: A queda solo con C (costo 10) ---" << endl;
        R.Eliminar_un_Enlace("A", "B");
        R.Eliminar_un_Enlace("A", "D");
        Mostrar_Camino(R, "A", "B");

        cout << "\n--- Agrego enrutador E sin enlaces ---" << endl;
        R.Agregar_un_Enrutador("E");
        try {
            Mostrar_Camino(R, "A", "E");
        } catch (const exception &e){
            cout << "Error esperado: " << e.what() << endl;
        }

        cout << "\n--- Elimino el enrutador C ---" << endl;
        R.Eliminar_el_Enrutador("C");
        R.Imprimir_Red();
        try {
            Mostrar_Camino(R, "A", "B");
        } catch (const exception &e){
            cout << "Error esperado: " << e.what() << endl;
        }
        Mostrar_Camino(R, "B", "D");

        cout << "\n--- Errores controlados ---" << endl;
        try { R.Agregar_un_Enrutador("A"); } catch (const exception &e){ cout << e.what() << endl; }
        try { R.Agregar_un_Enlace("A", "Z", 3); } catch (const exception &e){ cout << e.what() << endl; }
        try { R.Agregar_un_Enlace("A", "A", 3); } catch (const exception &e){ cout << e.what() << endl; }
        try { R.Agregar_un_Enlace("A", "B", -2); } catch (const exception &e){ cout << e.what() << endl; }
    } catch (const exception &e){
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}
