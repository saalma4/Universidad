#include <iomanip>
#include <iostream>

using namespace std;

const int N = 5;

int main() {
    int cuadrado[N][N];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cuadrado[i][j] = 0;

    int fila = 0;
    int col = N / 2;

    for (int k = 1; k <= N * N; k++) {
        cuadrado[fila][col] = k;

        int sigFila = fila - 1;
        int sigCol = col - 1;

        if (sigFila < 0) sigFila = N - 1;
        if (sigCol < 0) sigCol = N - 1;

        if (cuadrado[sigFila][sigCol] != 0) {
            fila = fila + 1;
            if (fila >= N) fila = 0;
        } else {
            fila = sigFila;
            col = sigCol;
        }
    }

    cout << "El cuadrado magico para N=" << N << " es:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(3) << cuadrado[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}