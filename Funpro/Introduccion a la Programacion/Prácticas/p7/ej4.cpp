#include <iostream>

using namespace std;

const int M = 4;

typedef int Matriz[M][M];

int sumaFila(const Matriz m, int fil) {
    int suma = 0;
    for (int j = 0; j < M; j++) {
        suma += m[fil][j];
    }
    return suma;
}

int sumaColumna(const Matriz m, int col) {
    int suma = 0;
    for (int i = 0; i < M; i++) {
        suma += m[i][col];
    }
    return suma;
}

int sumaDiagonalPrincipal(const Matriz m) {
    int suma = 0;
    for (int i = 0; i < M; i++) {
        suma += m[i][i];
    }
    return suma;
}

int sumaDiagonalSecundaria(const Matriz m) {
    int suma = 0;
    for (int i = 0; i < M; i++) {
        suma += m[i][M - 1 - i];
    }
    return suma;
}

int main() {
    Matriz m;
    int filaUser, colUser;

    cout << "Introduzca una matriz de enteros de " << M << "x" << M << " (por filas):" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            cin >> m[i][j];
        }
    }

    do {
        cout << "Introduzca la fila a sumar (entre 0 y " << M - 1 << "): ";
        cin >> filaUser;
    } while (filaUser < 0 || filaUser >= M);
    cout << "La suma de la fila " << filaUser << " es: " << sumaFila(m, filaUser) << endl;

    do {
        cout << "Introduzca la columna a sumar (entre 0 y " << M - 1 << "): ";
        cin >> colUser;
    } while (colUser < 0 || colUser >= M);
    cout << "La suma de la columna " << colUser << " es: " << sumaColumna(m, colUser) << endl;

    cout << "La suma de la diagonal principal es: " << sumaDiagonalPrincipal(m) << endl;
    cout << "La suma de la diagonal inversa es: " << sumaDiagonalSecundaria(m) << endl;

    return 0;
}