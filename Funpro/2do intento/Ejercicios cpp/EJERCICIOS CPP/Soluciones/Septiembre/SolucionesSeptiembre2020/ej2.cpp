#include <iostream>
#include <array>
using namespace std;

const int N = 4;

typedef array<int,N> TFila;
typedef array<TFila,N> TMatriz;

void leerMatriz(TMatriz& m) {
    cout << "Introduce los numeros enteros para una matriz cuadrada de " << N << "x" << N << ":" << endl;
    for (int fi = 0; fi < N; fi++) {
        for (int co = 0; co < N; co++) {
            cin >> m[fi][co];
        }
    }
}

void leerIndices(int& fil, int& col) {
    do {
        cout << "Introduce los indices de la fila y columna:\n";
        cin >> fil >> col;
    } while (fil < 0 || fil >= N || col < 0 || col >= N);
}

void rellenarFila(TFila& filaM2, const TFila& filaM1, int col) {
    int cm2 = 0;

    for (int cm1 = 0; cm1 < N; cm1++) {
        if (cm1 != col) {
            filaM2[cm2] = filaM1[cm1];
            cm2++;
        }
    }

}

void construirMatriz(TMatriz& m2, const TMatriz& m1, int fil, int col) {
    int fm2 = 0;

    for (int fm1 = 0; fm1 < N; fm1++) {
        if (fm1 != fil) {
            rellenarFila(m2[fm2],m1[fm1],col);
            fm2++;
        }
    }
}

void mostrarMatriz(const TMatriz& m) {
    cout << "La matriz construida " << N-1 << "x" << N-1 << " es:" << endl;
    for (int fi = 0; fi < N-1; fi++) {
        for (int co = 0; co < N-1; co++) {
            cout << m[fi][co] << " ";
        }
        cout << endl;
    }
}


int main() {
    TMatriz m1,m2;
    int fil,col;

    leerMatriz(m1);
    leerIndices(fil,col);
    construirMatriz(m2,m1,fil,col);
    mostrarMatriz(m2);


    return 0;
}
