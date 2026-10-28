#include <iostream>
#include <stdexcept>
#include <queue>
#include <vector> //en donde lo vemos
#include <limits>
#include "Red.h"
using namespace std;

Red::Red() {}

bool Red::Existe_un_Enrutador(const string &Nombre) const{
    return Enrutadores.find(Nombre) != Enrutadores.end();
}

void Red::Agregar_un_Enrutador(const string &Nombre){
    if (Existe_un_Enrutador(Nombre)){
        throw invalid_argument("Ya existe un enrutador con ese nombre :(" + Nombre);
    }
    Enrutadores[Nombre] = Enrutador(Nombre);
    Recalcular_Tablas();
}

void Red::Eliminar_el_Enrutador(const string &Nombre){
    if (!Existe_un_Enrutador(Nombre)){ //NO existe el enrutador
        throw out_of_range("No existe el enrutador :? " +Nombre);
    }
    Enrutadores.erase(Nombre);

    //los demas olvidan el enlace hacia el eliminado
    for (auto &par : Enrutadores){
        par.second.Eliminar_Vecino(Nombre);
    }
    Recalcular_Tablas();
}

void Red::Agregar_un_Enlace(const string &A, const string &B, int Costo){
    if (!Existe_un_Enrutador(A) || !Existe_un_Enrutador(B)){
        throw out_of_range("No se puede enlazar ya que alguno NO existe");
    }
    if (A == B){
        throw invalid_argument("Un enrutador no puede enlazarse con si mismo");
    }
    //Enlace bidireccional, consume los mismo costos en ambos sentidos
    Enrutadores[A].AgregarVecino(B, Costo);
    Enrutadores[B].AgregarVecino(A, Costo);
    Recalcular_Tablas();
}

void Red::Eliminar_un_Enlace(const string &A, const string &B){
    if (!Existe_un_Enrutador(A) || !Existe_un_Enrutador(B)){
        throw out_of_range("No se puede eliminar el enlace, puede que alguno no existe");
    }
    if (!Enrutadores[A].TieneVecino(B)){
        throw invalid_argument("No existe un enlace entre " + A + " y " + B);
    }
    Enrutadores[A].Eliminar_Vecino(B);
    Enrutadores[B].Eliminar_Vecino(A);
    Recalcular_Tablas();
}

//Dijkstra desde el "Origen" solo usa informacion de vecinos de cada enrutador.
void Red::Calcular_Tabla(const string &Origen){
    map<string, int> Distancia;
    map<string, string> Anterior;

    //(Distancia, nombre): el menor se extrae primero
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> Cola;//******
    Distancia[Origen] = 0;
    Cola.push(make_pair(0, Origen));

    while (!Cola.empty()){
        pair<int, string> Actual = Cola.top(); //top ,pop,cola**
        Cola.pop();
        int D = Actual.first;
        string Nodo = Actual.second;

        if (D > Distancia[Nodo]) continue;  //entrada vieja de la cola, se ignora
        const map<string, int> &Vecinos = Enrutadores.at(Nodo).getVecinos();
        for (const auto &v : Vecinos){
            int Nueva = D + v.second;
            auto it = Distancia.find(v.first);
            if (it == Distancia.end() || Nueva < it->second){
                Distancia[v.first] = Nueva;
                Anterior[v.first] = Nodo;
                Cola.push(make_pair(Nueva, v.first));
            }
        }
    }
    //Siguiente salto: Retrocedemos por anterior hasta el vecino directo del origen
    map<string, string>Saltos;
    for (const auto &par : Distancia){
        if (par.first == Origen) continue;
        string Nodo = par.first;
        while (Anterior[Nodo] != Origen){
            Nodo = Anterior[Nodo];
        }
        Saltos[par.first] = Nodo;
    }
    Enrutadores[Origen].Actualizar_Tabla_Costos(Distancia);
    Enrutadores[Origen].Actualizar_Siguiente_Salto(Saltos);
}

void Red::Recalcular_Tablas(){
    for (const auto &par : Enrutadores){
        Calcular_Tabla(par.first);
    }
}

list<string> Red::Encontrar_Camino(const string &Origen, const string &Destino) const{
    if (!Existe_un_Enrutador(Origen)){
        throw out_of_range("No existe el enrutador de origen: " + Origen);
    }
    if (!Existe_un_Enrutador(Destino)){
        throw out_of_range("No existe el enrutador de destino: " + Destino);
    }

    list<string> Camino; //Aquí creamos una lista llamada Camino.
    if (Origen == Destino){
        Camino.push_back(Origen); //agrega elemento al final de la lista
        return Camino;
    }
    if (!Enrutadores.at(Origen).Conoce_Destino(Destino)){ //Enrutadores.at(Origen) obtiene el objeto Enrutador correspondiente al origen.
        throw out_of_range("No hay camino entre " + Origen + " y " + Destino);
    }

    string Actual = Origen;
    while (Actual != Destino){
        Camino.push_back(Actual);
        Actual = Enrutadores.at(Actual).getSiguiente_Salto(Destino); //Desde el enrutador donde estoy, dime cuál es el siguiente enrutador que debo tomar para llegar al destino
    }
    Camino.push_back(Destino);//Agregamos el enrutador actual a la lista.
    return Camino;
}

int Red::Costo_Camino(const string &Origen, const string &Destino) const{
    if (!Existe_un_Enrutador(Origen) || !Existe_un_Enrutador(Destino)){
        throw out_of_range("Alguno de los enrutadores no existe");
    }
    return Enrutadores.at(Origen).getCosto(Destino);
}

void Red::Imprimir_Red() const{
    cout<< "RED ACTUAL:" <<endl;
    for (const auto &par : Enrutadores){
        cout<<" "<<par.first<<" -> Vecinos: ";//par.first contiene la clave del mapa, que en este caso es el nombre del enrutador.
        for (const auto &v : par.second.getVecinos()){
            cout<< v.first<<"(" << v.second <<") ";
        }
        cout <<endl;
    }
}

void Red::Imprimir_Tablas() const{
    for (const auto &par : Enrutadores){
        par.second.ImprimirTabla();
    }
}
