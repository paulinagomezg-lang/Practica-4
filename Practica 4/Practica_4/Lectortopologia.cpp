#include "Lectortopologia.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <stdexcept>

using namespace std;

Lectortopologia::Lectortopologia(Red &RedDestino):Destino(RedDestino) {}

string Lectortopologia::A_Mayusculas(string Texto){
    for (size_t i=0; i<Texto.size(); i++){
        Texto[i]=(char)toupper((unsigned char)Texto[i]);
    }
    return Texto;
}

//true si un texto es completamente numeros enteros
bool Lectortopologia::Es_entero(const string &Texto, int &Valor){
    istringstream Flujo(Texto);
    char Resto;
    return (Flujo >> Valor) && !(Flujo >>Resto);
}

void Lectortopologia::Cargar(const string &Ruta){
    ifstream Archivo(Ruta.c_str());
    if (!Archivo.is_open()){
        throw runtime_error("Nose pudo abrir el archivo: " + Ruta);
    }
    string Linea;
    int NumeroLinea = 0;
    while (getline(Archivo, Linea)){
        NumeroLinea++;
        Procesar_Linea(Linea, NumeroLinea);
    }
}

void Lectortopologia::Procesar_Linea(const string &Linea, int NumeroLinea){
    //Los separadores que utilizamos se vuelven espacios
    string Limpia = Linea;
    for (size_t i= 0; i < Limpia.size(); i++){
        if (Limpia[i] == ',' || Limpia[i] == ';' ||Limpia[i] == '\r' || Limpia[i] == '\t'){
            Limpia[i] = ' ';
        }
    }
    //se parte la linea en palabras
    vector<string>Palabras;
    istringstream Flujo(Limpia);
    string Palabra;
    while (Flujo >> Palabra) Palabras.push_back(Palabra);
    if(Palabras.empty() || Palabras[0][0] == '#') return; //Linea vacia o comentario
    string Tipo = A_Mayusculas(Palabras[0]);
    string A, B;
    int Costo = 0;
    bool EsEnlace = false;

    if (Tipo == "ENRUTADOR" && Palabras.size() == 2){
        A = Palabras[1];
    }
    else if (Tipo == "ENLACE" && Palabras.size() == 4 && Es_entero(Palabras[3], Costo)){
        A = Palabras[1];
        B = Palabras[2];
        EsEnlace= true;
    }
    else if (Palabras.size() == 3 && Es_entero(Palabras[2], Costo)){
        A = Palabras[0];
        B = Palabras[1];
        EsEnlace = true;
    }
    else if (Palabras.size() == 1){
        A = Palabras[0];
    }
    else{
        ostringstream Mensaje;
        Mensaje << "Linea" << NumeroLinea << " con formato invalido: " << Linea;
        throw runtime_error(Mensaje.str());
    }
    if (!Destino.Existe_un_Enrutador(A)) Destino.Agregar_un_Enrutador(A);
    if (EsEnlace){
        if (!Destino.Existe_un_Enrutador(B)) Destino.Agregar_un_Enrutador(B);
        Destino.Agregar_un_Enlace(A, B, Costo);
    }
}
