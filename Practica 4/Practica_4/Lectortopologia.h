#ifndef LECTORTOPOLOGIA_H
#define LECTORTOPOLOGIA_H
#include <string>
#include "Red.h"
using namespace std;

class Lectortopologia
{
private:
    Red &Destino; //la red que se va a llenar con lo que diga el archivo
    void Procesar_Linea(const string &Linea, int NumeroLinea);
    static bool Es_entero(const string &Texto, int &Valor);
    static string A_Mayusculas(string Texto);
public:
    Lectortopologia(Red &RedDestino);
    void Cargar(const string &Ruta);


};

#endif // LECTORTOPOLOGIA_H
