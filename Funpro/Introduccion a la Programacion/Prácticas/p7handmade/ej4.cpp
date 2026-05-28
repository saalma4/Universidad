#include <array>
#include <iostream>
using namespace std;

const int M = 5;
typedef array<int, M> TFilas;
typedef array<TFilas, M> TMatriz;

void leerMatriz(TMatriz &mat) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            cin >> mat[i][j];
        }
    }
}
int sumarFila(const TMatriz &m, int fila) {
    int suma = 0;
    for (int j = 0; j < M; j++) {
        suma = suma + m[fila][j];
    }
    return suma;
}
int sumarColumna(const TMatriz &m, int columna) {
    int suma = 0;
    for (int i = 0; i < M; i++) {
        suma = suma + m[i][columna];
    }
    return suma;
}
int sumaDiagonalPrincipal(const TMatriz &m) {
    int suma = 0;
    for (int i = 0; i < M; i++) {
        suma = suma + m[i][i];
    }
    return suma;
}
int sumaDiagonalSecundaria(const TMatriz &m) {
    int suma = 0;
    for (int i = 0; i < M; i++) {
        suma = suma + m[i][M - 1 - i];
    }
    return suma;
}

// int main() {
//     TMatriz m = {{}};
//     int fila, columna;
//     cout << "introduzca una matriz: ";
//     leerMatriz(m);
//     do {
//         cout << "introduzca fila a sumar: ";
//         cin >> fila;
//     } while (fila < 0 || fila > M - 1);
//     cout << "la suma de la fila " << fila << " es: " << sumarFila(m, fila) << endl;

//     do {
//         cout << "introduzca columna a sumar: ";
//         cin >> columna;
//     } while (columna < 0 || columna > M - 1);
//     cout << "la suma de la columna " << columna << " es: " << sumarColumna(m, columna) << endl;

//     cout << "la suma diagonal principal es: " << sumaDiagonalPrincipal(m) << endl;
//     cout << "la suma diagonal secundaria es: " << sumaDiagonalSecundaria(m) << endl;
// }