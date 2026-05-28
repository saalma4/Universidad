#include <iostream>

using namespace std;

const int N = 5;
typedef int Cuadrado[N][N];

bool esMagico(const Cuadrado &c) {
    bool vistos[N * N + 1];
    for (int k = 0; k <= N * N; k++)
        vistos[k] = false;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int val = c[i][j];
            if (val < 1 || val > N * N) return false;
            if (vistos[val]) return false;
            vistos[val] = true;
        }
    }

    int sumaObjetivo = 0;
    for (int j = 0; j < N; j++)
        sumaObjetivo += c[0][j];

    for (int i = 1; i < N; i++) {
        int suma = 0;
        for (int j = 0; j < N; j++)
            suma += c[i][j];
        if (suma != sumaObjetivo) return false;
    }

    for (int j = 0; j < N; j++) {
        int suma = 0;
        for (int i = 0; i < N; i++)
            suma += c[i][j];
        if (suma != sumaObjetivo) return false;
    }

    int sumaDP = 0;
    for (int i = 0; i < N; i++)
        sumaDP += c[i][i];
    if (sumaDP != sumaObjetivo) return false;

    int sumaDS = 0;
    for (int i = 0; i < N; i++)
        sumaDS += c[i][N - 1 - i];
    if (sumaDS != sumaObjetivo) return false;

    return true;
}

int main() {
    Cuadrado mat;

    cout << "Introduzca " << N << " filas de " << N << " numeros:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> mat[i][j];
        }
    }

    cout << "El cuadrado:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

    if (esMagico(mat)) {
        cout << "sí es mágico" << endl;
    } else {
        cout << "no es mágico" << endl;
    }

    return 0;
}