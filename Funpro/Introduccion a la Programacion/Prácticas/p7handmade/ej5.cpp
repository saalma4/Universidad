#include "ej4.cpp"
#include <array>
#include <iostream>
using namespace std;

bool esMagico(const TMatriz &c) {
    for (int i = 0; i < M; i++) {
        if (sumarFila(c, i) != 65) {
            return false;
        }
        for (int j = 0; j < M; j++) {
            if (sumarColumna(c, j) != 65 || c[i][j] < 1 || c[i][j] > M * M) {
                return false;
            }
            for (int f = 0; f < M; f++) {
                for (int col = 0; col < M; col++) {
                    if (i != f && j != col) {
                        if (c[i][j] == c[f][col]) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return sumaDiagonalPrincipal(c) == 65 && sumaDiagonalSecundaria(c) == 65;
}

int main() {
    TMatriz m = {{}};
    cout << "introduzca una matriz" << endl;
    leerMatriz(m);
    if (esMagico(m)) {
        cout << "si es magico" << endl;
    } else {
        cout << "no es magico" << endl;
    }
}