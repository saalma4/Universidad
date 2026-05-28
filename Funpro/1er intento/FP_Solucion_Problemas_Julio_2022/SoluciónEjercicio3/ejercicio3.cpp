/*
 * ejercicio3.cpp
 *
 *  Created on: 18/07/2022
 *      Alumno:
 *      Titulación:
 *      Grupo:
 *      PC usado:
 */

#include <iostream>
#include <array>

using namespace std;

const int N = 4;
const int M = 3;

typedef array<int,M> TFila;
typedef array<TFila, N> TImagen;


// lee por teclado los valores de la matriz inicial a
void leer(TImagen& a) {
    cout << "Introduzca la matriz(" << N << "x" << M << "):\n";
    for (int f = 0; f < N; f++) {
        for (int c = 0; c < M; c++) {
            cin >> a[f][c];
        }
    }
}

// comprueba si una celda es valida, es decir, no estamos fuera de los limites de la matriz
bool celdaValida(int f, int c) {
    return f >= 0 && f < N && c >= 0 && c < M;
}

/*
 *  calcula la media de los vecinos de la celda (f,c) de la matriz a. Para la
 * media se incluye el propio valor de la celda (f,c)
 */
int media(int f, int c, const TImagen& a) {
    int suma = 0, vecinos = 0;

    for (int fil = f-1; fil <= f+1; fil++) {
        for (int col = c-1; col <= c+1; col++) {
            if (celdaValida(fil,col)) {
                vecinos++;
                suma += a[fil][col];
            }
        }
    }

    return suma / vecinos;
}


/*
 *  construye la matriz final b a partir de la matriz inicial a
 *  mediante operacion de suavizado
 */
void suavizado(const TImagen& a, TImagen& b) {
    for (int f = 0; f < N; f++) {
        for (int c = 0; c < M; c++) {
            b[f][c] = media(f,c,a);
        }
    }
}

// muestra por pantalla el contenido de la matriz final b
void escribir(const TImagen& b) {
    cout << "La matriz tras la operacion de suavizado es la siguiente:\n";
    for (int f = 0; f < N; f++) {
        for (int c = 0; c < M; c++) {
            cout << b[f][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    TImagen a,b;

    leer(a);
    suavizado(a,b);
    escribir(b);

    return 0;
}
