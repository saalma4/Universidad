#include <iostream>
#include <array>

using namespace std;

const int F = 2;
const int C = 3;

typedef array<int,C> TFila;

typedef array<TFila, F> TMatrizM;

typedef array<TFila, 2*F> TMatrizT;


// lee por teclado los valores de la matriz inicial m
void leer(TMatrizM& m) {
    cout << "Introduzca la matriz M (" << F << "x" << C << "):\n";
    for (int f = 0; f < F; f++) {
        for (int c = 0; c < C; c++) {
            cin >> m[f][c];
        }
    }
}

// calcula la media de los numeros almacenados en la matriz m
int media(const TMatrizM& m) {
    int suma = 0;

    for (int f = 0; f < F; f++) {
        for (int c = 0; c < C; c++) {
            suma += m[f][c];
        }
    }

    return suma/(F*C);
}

// copia las filas de m en las filas pares de t
void copiarFilasParesDeT(const TMatrizM& m, TMatrizT& t) {
    for (int f= 0; f < F; f++) {
        t[f*2] = m[f];
    }
}

// comprueba si una celda es valida, es decir, no estamos fuera de los limites de la matriz
bool celdaValida(int f, int c) {
    return f >= 0 && f < 2*F && c >= 0 && c < C;
}

// calcula la media de los vecinos de la celda (f,c) de la matriz t
int mediaVecinos(int f, int c, const TMatrizT& t, int mediaM) {
    int suma = 0, vecinos = 0;

    for (int fil = f-1; fil <= f+1; fil++) {
        for (int col = c-1; col <= c+1; col++) {
            if (celdaValida(fil,col) && !(fil == f && col == c)) {
                vecinos++;
                if (t[fil][col] == 0) {
                    suma += mediaM;
                } else {
                    suma += t[fil][col];
                }
            }
        }
    }

    return suma / vecinos;
}

// calcula los valores de la fila impar f de la matriz t
void calcularFilaImparDeT(int f, TMatrizT& t, int mediaM) {
    for (int c = 0; c < C; c++) {
        t[f][c] = mediaVecinos(f,c,t,mediaM);
    }
}

// calcula los valores de las filas impares de t
void calcularFilasImparesDeT(TMatrizT& t, int mediaM) {
    for (int f = 1; f < 2*F; f = f + 2) {
        calcularFilaImparDeT(f,t,mediaM);
    }

}

// construye la matriz final t a partir de la matriz inicial m
void construirMatrizT(const TMatrizM& m, TMatrizT& t) {
    int mediaM = media(m);

    copiarFilasParesDeT(m,t);

    calcularFilasImparesDeT(t,mediaM);
}

// muestra por pantalla el contenido de la matriz final t
void escribir(const TMatrizT& t) {
    cout << "La matriz T (" << 2*F << "x" << C << ") es la siguiente:\n";
    for (int f = 0; f < 2*F; f++) {
        for (int c = 0; c < C; c++) {
            cout << t[f][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    TMatrizM m;
    TMatrizT t = {{}}; // t se inicializa toda a 0

    leer(m);
    construirMatrizT(m,t);
    escribir(t);

    return 0;
}
