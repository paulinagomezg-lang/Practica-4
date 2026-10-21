#ifndef ENRUTADOR_H
#define ENRUTADOR_H
#include <string>
#include <map>
using namespace std;

class Enrutador {
private:
    string Nombre; //Identidicador del enrutador
    map<string, int> Vecinos; //Vecino directo ->el costo del enlace
    map<string, int> TablaCostos; //Destino -> El costo mas corto conocido
    map<string, string> Siguiente_Salto; //Destino -> EL vecino que se viene a enrutar

public:
    Enrutador();
    Enrutador(const string &NombreEnrutador);

    //Manejo de los vecinos directos
    void AgregarVecino(const string &Destino, int Costo);
    void Eliminar_Vecino(const string &Destino);
    bool TieneVecino(const string &Destino) const;
    int CostoVecino(const string &Destino) const;
    const map<string, int>& getVecinos() const;

    //Llena, actualiza la red tras recalcular caminos de la tabla

    void Actualizar_Tabla_Costos(const map<string, int> &Nueva_Tabla);
    void Actualizar_Siguiente_Salto(const map<string, string> &NuevoSaltos);
    int getCosto(const string &Destino) const;
    string getSiguiente_Salto(const string &Destino) const;
    string getNombre() const;
    bool Conoce_Destino(const string &Destino) const;
    void ImprimirTabla() const;

};

#endif // ENRUTADOR_H
