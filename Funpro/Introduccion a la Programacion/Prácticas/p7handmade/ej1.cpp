#include <array>
#include <iostream>
using namespace std;

int const N = 4;
int const M = 5;

// N FILAS X M COLUMNAS
typedef array<int, M> Tfila;
typedef array<Tfila, N> TMatrix;

void leerMatriz(TMatrix &mat) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> mat[i][j];
        }
    }
}

void mayor(const TMatrix &m) {
    int mayor = 0;
    int f = 0;
    int c = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (m[i][j] > mayor) {
                mayor = m[i][j];
                f = i;
                c = j;
            }
        }
    }
    cout << "El mayor es: " << mayor << " que aparece en la posicion: [" << f << "][" << c << "]" << endl;
}

int main() {
    TMatrix m = {{}};
    cout << "Introduce una matriz: " << endl;
    leerMatriz(m);
    mayor(m);
}