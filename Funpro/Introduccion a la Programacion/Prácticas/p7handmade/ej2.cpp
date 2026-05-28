#include <array>
#include <iostream>
using namespace std;

int const N = 4;

typedef array<int, N> Tfila;
typedef array<Tfila, N> TMatrix;

void leerMatriz(TMatrix &mat) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> mat[i][j];
        }
    }
}

bool esSimetrica(const TMatrix &m) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (m[i][j] != m[j][i]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    TMatrix m = {{}};
    cout << "Introduce una matriz: " << endl;
    leerMatriz(m);
    if (esSimetrica(m)) {
        cout << "SI";
    } else {
        cout << "NO";
    }
    cout << " es simetrica" << endl;
}