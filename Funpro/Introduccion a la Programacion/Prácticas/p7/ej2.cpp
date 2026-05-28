#include <iostream>

using namespace std;

const int N = 4;

int main() {
    int matriz[N][N];
    bool esSimetrica = true;

    cout << "Introduzca por filas una matriz " << N << "x" << N << ":" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> matriz[i][j];
        }
    }

    for (int i = 0; i < N && esSimetrica; i++) {
        for (int j = i + 1; j < N; j++) {
            if (matriz[i][j] != matriz[j][i]) {
                esSimetrica = false;
            }
        }
    }

    if (esSimetrica) {
        cout << "SI es simétrica" << endl;
    } else {
        cout << "NO es simétrica" << endl;
    }

    return 0;
}