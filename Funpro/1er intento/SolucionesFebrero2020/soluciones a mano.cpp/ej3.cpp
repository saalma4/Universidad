#include <iostream>
#include <string>
#include <array>
using namespace std;

const string FIN = "FIN";
const int MAX_PERSONAS = 10;

struct Persona {
    string nombre;
    double gastos = 0;
};
typedef array<Persona, MAX_PERSONAS> ListaPersonas;
struct Datos {
    int numelem = 0;
    ListaPersonas elem;
};

