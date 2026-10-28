#include <iostream>
#include <stdexcept>
#include "Enrutador.h"
#include <string>
#include <map>
using namespace std;

Enrutador::Enrutador() : Nombre(""){}

Enrutador::Enrutador(const string &NombreEnrutador) : Nombre(NombreEnrutador){
    //Un eruptador siempre conoce el camino asi mismo con un costo de 0
    TablaCostos[Nombre] = 0;
}

string Enrutador::getNombre() const{
    return Nombre;
}

void Enrutador::AgregarVecino(const string &Destino, int Costo){
    if (Costo < 0){
        throw invalid_argument("El costo de un enlace no puede ser negativo :( ");
    }
    Vecinos[Destino] = Costo; // si de casualidad ya existia el costo se actualiza
}

void Enrutador::Eliminar_Vecino(const string &Destino){
    Vecinos.erase(Destino);
}

bool Enrutador::TieneVecino(const string &Destino) const{
    return Vecinos.find(Destino) != Vecinos.end();
}

int Enrutador::CostoVecino(const string &Destino) const{
    auto it = Vecinos.find(Destino);
    if (it == Vecinos.end()){
        throw out_of_range("El enrutador no tiene un enlace directo hacia el: "+ Destino);
    }
    return it -> second;
}

const map<string, int>& Enrutador::getVecinos() const{
    return Vecinos;
}

void Enrutador::Actualizar_Tabla_Costos(const map<string, int> &Nueva_Tabla){
    TablaCostos = Nueva_Tabla;
}

void Enrutador::Actualizar_Siguiente_Salto(const map<string, string> &NuevoSaltos){
    Siguiente_Salto = NuevoSaltos;
}

int Enrutador::getCosto(const string &Destino) const{
    auto it = TablaCostos.find(Destino);
    if (it == TablaCostos.end()){
        throw out_of_range("No se conoce la ruta hacia: "+ Destino);
    }
    return it->second;
}

string Enrutador::getSiguiente_Salto(const string &Destino) const{
    auto it = Siguiente_Salto.find(Destino);//mire esta variable y asignela it
    if (it == Siguiente_Salto.end()){
        throw out_of_range("No hay siguiente salto conocido al camino:" + Destino);
    }
    return it->second; //segunda parte de esas dos cosas
}

bool Enrutador::Conoce_Destino(const string &Destino) const{
    return TablaCostos.find(Destino) != TablaCostos.end();
}

void Enrutador::ImprimirTabla() const{
    cout <<"TABLA DE COSTOS "<< Nombre<<" : "<<endl;
    for (const auto &par : TablaCostos){ //par es una direccion de memoria de lo que hay en el mapa(tipo de dato)
        cout <<" -> " <<par.first<<" : Costo "<<par.second;
        if (Siguiente_Salto.find(par.first) != Siguiente_Salto.end() && par.first != Nombre){
            cout<< " (Via "<<Siguiente_Salto.at(par.first)<< ")"; //dame valor de esta clave o sino dame un error
        }
        cout << endl;
    }
}