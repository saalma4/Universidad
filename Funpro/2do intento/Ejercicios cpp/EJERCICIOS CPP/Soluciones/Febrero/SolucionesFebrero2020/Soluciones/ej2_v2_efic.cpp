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

// comprueba que los valores de la fila sean validos y sumen 100
bool filaValida(const TFila& fila,int valorSuma) {
    int co, suma;
    bool valoresValidos = true;

    suma = 0;
    co = 0;
    while (co < N && valoresValidos) {
        if (fila[co] < 0 || fila[co] >= 100) {
            valoresValidos = false;
        } else {
            suma += fila[co];
            co++;
        }
    }

    return valoresValidos && suma == valorSuma;
}


bool filasValidas(const TMatriz& m,int valorSuma) {
    bool correcta = true;
    int fi;

    fi = 0;
    while (fi < N && correcta) {
        correcta = filaValida(m[fi],valorSuma);
        fi++;
    }
    return correcta;
}

bool esDEN(const TMatriz& m) {
    return filasValidas(m,100) && sumaColumnasValida(m,100);
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
