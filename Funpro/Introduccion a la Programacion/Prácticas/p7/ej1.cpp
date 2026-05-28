#include <iostream>

using namespace std;

const int N = 4;
const int M = 5;

int main() {
    int matriz[N][M];
    int mayor, posFila, posCol;

    cout << "Introduzca por filas una matriz " << N << " x " << M << ":" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> matriz[i][j];
        }
    }

    mayor = matriz[0][0];
    posFila = 0;
    posCol = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (matriz[i][j] > mayor) {
                mayor = matriz[i][j];
                posFila = i;
                posCol = j;
            }
        }
    }

    cout << "El mayor de la matriz es: " << mayor
         << " que aparece en la posicion: [" << posFila << "] [" << posCol << "]" << endl;

    return 0;
}