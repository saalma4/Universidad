#include <array>
#include <iostream>
using namespace std;

const int F = 4;
const int C = 3;

typedef array<int, 2> Indices;
typedef array<int, C> TFilas;
typedef array<TFilas, F> TMatriz;

void leerMatriz(TMatriz &m) {
    for (int i = 0; i < F; i++) {
        for (int j = 0; j < C; j++) {
            cin >> m[i][j];
        }
    }
}

void mostrarMatriz(const TMatriz &m) {
    for (int i = 0; i < F; i++) {
        for (int j = 0; j < C; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

int getValor(int i, int j, const TMatriz &m) {
    if (i < 0 || i >= F || j < 0 || j >= C) {
        return 0;
    } else {
        return m[i][j];
    }
}

int sumaVecinos(int i, int j, const TMatriz &m) {
    int suma = 0;
    for (int x = i - 1; x <= i + 1; x++) {
        for (int y = j - 1; y <= j + 1; y++) {
            if (!(x == i && y == j)) {
                suma = suma + getValor(x, y, m);
            }
        }
    }
    return suma;
}
Indices resultado(const TMatriz &m) {
    for (int i = 0; i < F; i++) {
        for (int j = 0; j < C; j++) {
            if (sumaVecinos(i, j, m) == m[i][j]) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

int main() {
    TMatriz m = {{}};
    cout << "introduce matriz " << F << " x " << C << " : " << endl;
    leerMatriz(m);
    cout << "La matriz introducida es: " << endl;
    mostrarMatriz(m);
    Indices res = resultado(m);
    cout << "el primer elemento q cumple es: (" << res[0] << ", " << res[1] << ")";
}