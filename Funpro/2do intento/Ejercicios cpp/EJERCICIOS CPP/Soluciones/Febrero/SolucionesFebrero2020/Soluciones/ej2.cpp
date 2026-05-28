#include <iostream>
#include <array>
using namespace std;

const int N = 3;

typedef array<int,N> TFila;
typedef array<TFila,N> TMatriz;

void leer(TMatriz& m) {
    cout << "Introduce los numeros enteros para una matriz cuadrada de " << N << "x" << N << ":" << endl;
    for (int fi = 0; fi < N; fi++) {
        for (int co = 0; co < N; co++) {
            cin >> m[fi][co];
        }
    }
}

void mostrar(const TMatriz& m) {
    cout << "La matriz introducida es:\n";
    for (int fi = 0; fi < N; fi++) {
        for (int co = 0; co < N; co++) {
            cout << m[fi][co] << " ";
        }
        cout << endl;
    }
}

int sumaColumna(const TMatriz& m, int co) {
    int suma = 0;

    for (int fi = 0; fi < N; fi++) {
        suma += m[fi][co];
    }
    return suma;
}

bool sumaColumnasValida(const TMatriz& m,int valorSuma) {
    int co = 0;

    while (co < N && sumaColumna(m,co) == valorSuma) {
        co++;
    }
    return co >= N;
}

int sumaFila(const TFila& fila) {
    int suma = 0;

    for (int co = 0; co < N; co++) {
        suma += fila[co];
    }
    return suma;
}

bool sumaFilasValida(const TMatriz& m,int valorSuma) {
    int fi = 0;

    while (fi < N && sumaFila(m[fi]) == valorSuma) {
        fi++;
    }
    return fi >= N;
}


bool valoresMatrizValidos(const TMatriz& m) {
    bool validos = true;
    int fi,co;

    fi = 0;
    while (fi < N && validos) {
        co = 0;
        while (co < N && validos) {
            if (m[fi][co] < 0 || m[fi][co] >= 100) {
                validos = false;
            }
            co++;
        }
        fi++;
    }
    return validos;
}

bool esDEN(const TMatriz& m) {
    return valoresMatrizValidos(m) && sumaFilasValida(m,100) && sumaColumnasValida(m,100);
}

int main() {
    TMatriz matriz;

    leer(matriz);
    mostrar(matriz);
    if (esDEN(matriz)) {
        cout << "La matriz introducida SI es doblemente estocastica normalizada\n";
    } else {
        cout << "La matriz introducida NO es doblemente estocastica normalizada\n";
    }

    return 0;
}
