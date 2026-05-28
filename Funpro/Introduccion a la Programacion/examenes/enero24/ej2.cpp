#include <array>
#include <iostream>
using namespace std;

const int TAM = 5;

typedef array<int, TAM> Tfilas;
typedef array<Tfilas, TAM> Tmatriz;

double mediaDiagonal(const Tmatriz &m) {
    double suma = 0;
    for (int i = 0; i < TAM; i++) {
        suma += m[i][i];
    }
    return suma / TAM;
}

double mediaColumna(const Tmatriz &m, int col) {
    double suma = 0;
    for (int i = 0; i < TAM; i++) {
        suma += m[i][col];
    }
    return suma / TAM;
}

int indiceColumnaValida(const Tmatriz &m) {
    double mediaDiag = mediaDiagonal(m);
    for (int j = 0; j < TAM; j++) {
        if (mediaColumna(m, j) >= mediaDiag) {
            return j;
        }
    }
    return -1;
}

void leerMatriz(Tmatriz &m) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            cin >> m[i][j];
        }
    }
}
void mostrarMatriz(const Tmatriz &m) {
    cout << "Matriz: " << endl;
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    Tmatriz m = {{}};
    cout << "introduce " << TAM << " x " << TAM << " numeros: " << endl;
    leerMatriz(m);
    mostrarMatriz(m);
    cout << "Media diagonal: " << mediaDiagonal(m) << endl;
    if (indiceColumnaValida(m) == -1) {
        cout << "La columna no ha sido encontrada";
    } else {
        cout << "El indice de la columna es: " << indiceColumnaValida(m);
    }
}