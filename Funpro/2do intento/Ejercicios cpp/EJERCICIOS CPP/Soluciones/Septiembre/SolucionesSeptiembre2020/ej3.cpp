#include <iostream>
#include <array>
#include <string>
using namespace std;

const int MAX = 10;

struct TPersona {
    string nombre;
    int resultado;
    double cantidad;
};

typedef array<TPersona,MAX> TArray;

struct TApuestas {
    TArray personas;
    int numPersonas;
};

int posicion(const string& nombre, const TApuestas& apuestas) {
    int i = 0;

    while (i < apuestas.numPersonas && nombre != apuestas.personas[i].nombre) {
        i++;
    }

    return i;
}

void almacenar(const TPersona& persona,TApuestas& apuestas) {
    int pos = posicion(persona.nombre,apuestas);
    if (pos < apuestas.numPersonas) {
        apuestas.personas[pos].cantidad += persona.cantidad;
    } else {
        /* el enunciado dice que no habra mas de MAX personas distintas
         * y por eso no comprobamos si se llena el array
        */
        apuestas.personas[apuestas.numPersonas] = persona;
        apuestas.numPersonas++;
    }
}

void leer(TApuestas& apuestas, int& resultado) {
    TPersona persona;

    apuestas.numPersonas = 0;

    cout << "Introduzca nombres, resultados y cantidades apostadas (FIN para terminar)\n";
    cout << "Nombre: ";
    cin >> persona.nombre;
    while (persona.nombre != "FIN") {
        cout << "Resultado (0 1 2): ";
        cin >> persona.resultado;
        cout << "Cantidad (> 0): ";
        cin >> persona.cantidad;
        almacenar(persona,apuestas);
        cout << "Nombre: ";
        cin >> persona.nombre;
    }

     cout << "Introduzca el resultado final de la apuesta (0 1 2): Resultado (0 1 2): ";
     cin >> resultado;
}

void mostrarPersona(const TPersona& persona) {
cout << persona.nombre << " " << persona.resultado << " " << persona.cantidad;
}

void mostrarApuestas(const TApuestas& apuestas) {
    cout << endl;
    for (int i = 0; i < apuestas.numPersonas; i++) {
        mostrarPersona(apuestas.personas[i]);
        cout << endl;
    }
}

void calcularTotales(const TApuestas& apuestas, int resultado,
                     double& T1, double& T2, double& ratio) {
    T1 = 0;
    T2 = 0;

    for (int i = 0; i < apuestas.numPersonas; i++) {
        T1 += apuestas.personas[i].cantidad;
        if (resultado == apuestas.personas[i].resultado) {
            T2 += apuestas.personas[i].cantidad;
        }
    }

    ratio = T1 / T2;
}

void mostrarTotales(double T1, double T2, double ratio) {
    cout << endl;
    cout << "Total apostado: " << T1 << endl;
    cout << "Total ganador: " << T2 << endl;
    cout << "Ratio: " << ratio << endl;
}

void mostrarReintegros(const TApuestas& apuestas, int resultado, double ratio) {
    cout << endl;
    for (int i = 0; i < apuestas.numPersonas; i++) {
        mostrarPersona(apuestas.personas[i]);
        if (apuestas.personas[i].resultado == resultado) {
            cout << " -> " << apuestas.personas[i].cantidad * ratio;
        } else {
            cout << " -> 0";
        }
        cout << endl;
    }
}

int main() {
    TApuestas apuestas;
    int resultado;
    double T1, T2, ratio;

    leer(apuestas,resultado);
    mostrarApuestas(apuestas);
    calcularTotales(apuestas,resultado,T1,T2,ratio);
    mostrarTotales(T1,T2,ratio);
    mostrarReintegros(apuestas,resultado,ratio);

    return 0;
}
