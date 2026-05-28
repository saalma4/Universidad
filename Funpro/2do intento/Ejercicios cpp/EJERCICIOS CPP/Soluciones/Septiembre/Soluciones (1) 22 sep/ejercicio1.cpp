#include <iostream>
#include <array>

using namespace std;

const int TAM = 7;

typedef array<int,TAM> TFila;
typedef array<TFila, TAM> TMatriz;


// inicializa a 1 la primera fila y la primera columna
void inicializar(TMatriz& m) {

    for (int cont = 0; cont < TAM; cont++) {
        m[0][cont] = 1;
        m[cont][0] = 1;
    }
}

// construye la matriz con el triangulo de Pascal
void construir(TMatriz& m) {

    inicializar(m);
    for (int f = 1; f < TAM-1; f++) {
        for (int c = 1; c < TAM-f; c++) {
            m[f][c] = m[f][c-1]+m[f-1][c];
        }
    }
}

// muestra por pantalla el triangulo de Pascal contenido en la matriz
void escribir(const TMatriz& m) {

    for (int f = 0; f < TAM; f++) {
        for (int c = 0; c < TAM-f; c++) {
                cout << m[f][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
	TMatriz pascal = {{}}; // toda la matriz rellena de 0

	construir(pascal);
	escribir(pascal);

	return 0;
}

