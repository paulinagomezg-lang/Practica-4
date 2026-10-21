#ifndef RED_H
#define RED_H
#include <string>
#include <map>
#include <list>
#include "Enrutador.h"
using namespace std;

class Red
{
public:
    //Dijkstra desde el "Origen" solo usa informacion de vecinos de cada enrutador.
    void Calcular_Tabla(const string &Origen);
    map<string, Enrutador> Enrutadores; //nombre -> enrutador

public:
    Red();
    bool Existe_un_Enrutador(const string &Nombre) const;
    void Agregar_un_Enrutador(const string &Nombre);
    void Eliminar_el_Enrutador(const string &Nombre);
    void Agregar_un_Enlace(const string &A, const string &B, int Costo);
    void Eliminar_un_Enlace(const string &A, const string &B);
    void Recalcular_Tablas();
    list<string> Encontrar_Camino(const string &Origen, const string &Destino) const;
    int Costo_Camino(const string &Origen, const string &Destino) const;
    void Imprimir_Red() const;
    void Imprimir_Tablas() const;
};

#endif // RED_H
