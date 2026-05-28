#include <iostream>
#include <array>

using namespace std;

const int TAM = 9;

typedef array<int,TAM> TFila;
typedef array<TFila,TAM> TMatriz;

// array auxiliar para controlar la aparicion de numeros del 1 al 9
// sirve para filas, columnas y regiones
typedef array<bool,TAM+1> TArray; // la casilla 0 no se usa

/*
// inicializa a false el array auxiliar numAparecidos
void inicializar(TArray& numAparecidos) {
    for (int i = 1; i < TAM+1; i++) {
        numAparecidos[i] = false;
    }
}
*/

// comprueba si la fila fi es valida (no tiene numeros repetidos)
bool filaValida(const TMatriz& tablero, int fi) {
    TArray numAparecidos;
    bool valida = true;
    int co;

    //inicializar(numAparecidos);
    numAparecidos = {{}}; // todas las casillas a false
    co = 0;
    while (co < TAM && valida) {
        if (tablero[fi][co] == 0) {
            co++;
        } else if ((tablero[fi][co] >= 1 && tablero[fi][co] <= 9) &&
                    !numAparecidos[tablero[fi][co]]) {
            numAparecidos[tablero[fi][co]] = true;
            co++;
        } else {
            valida = false;
        }
    }

    return co >= TAM;
}

// comprueba si todas las filas son validas
bool filasValidas(const TMatriz& tablero) {
    int fi;

    fi = 0;
    while (fi < TAM && filaValida(tablero,fi)) {
        fi++;
    }

    return fi >= TAM;
}

// comprueba si la columna co es valida (no tiene numeros repetidos)
bool columnaValida(const TMatriz& tablero, int co) {
    TArray numAparecidos;
    bool valida = true;
    int fi;

    //inicializar(numAparecidos);
    numAparecidos = {{}}; // todas las casillas a false
    fi = 0;
    while (fi < TAM && valida) {
        if (tablero[fi][co] == 0) {
            fi++;
        } else if ((tablero[fi][co] >= 1 && tablero[fi][co] <= 9) &&
                    !numAparecidos[tablero[fi][co]]) {
            numAparecidos[tablero[fi][co]] = true;
            fi++;
        } else {
            valida = false;
        }
    }

    return fi >= TAM;
}

// comprueba si todas las columnas son validas
bool columnasValidas(const TMatriz& tablero) {
    int co;

    co = 0;
    while (co < TAM && columnaValida(tablero,co)) {
        co++;
    }

    return co >= TAM;
}

// comprueba si la region cuya casilla central es [fiCentroReg][coCentroReg]
// es valida (no tiene numeros repetidos)
bool regionValida(const TMatriz& tablero, int fiCentroReg, int coCentroReg) {
    TArray numAparecidos;
    bool valida = true;
    int fi,co;

    //inicializar(numAparecidos);
    numAparecidos = {{}}; // todas las casillas a false
    fi = fiCentroReg-1;
    while (fi <= fiCentroReg+1 && valida) {
        co = coCentroReg-1;
        while (co <= coCentroReg+1 && valida) {
            if (tablero[fi][co] == 0) {
                co++;
            } else if ((tablero[fi][co] >= 1 && tablero[fi][co] <= 9) &&
                       !numAparecidos[tablero[fi][co]]) {
                numAparecidos[tablero[fi][co]] = true;
                co++;
            } else {
                valida = false;
            }
        }
        fi++;
    }

    return valida;

}

// comprueba si todas las regiones son validas
// invoca a regionValida para cada region pasandole
// los indices de la fila y columna de la celda central
// de la region
bool regionesValidas(const TMatriz& tablero) {
    bool valida = true;
    int fiCentroReg, coCentroReg;

    fiCentroReg = 1;
    while (fiCentroReg < TAM && valida) {
        coCentroReg = 1;
        while (coCentroReg < TAM && valida) {
            valida = regionValida(tablero, fiCentroReg, coCentroReg);
            coCentroReg += 3;
        }
        fiCentroReg += 3;
    }

    return valida;

 /*
    return regionValida(tablero,1,1) && regionValida(tablero,1,4) && regionValida(tablero,1,7) &&
            regionValida(tablero,4,1) && regionValida(tablero,4,4) && regionValida(tablero,4,7) &&
            regionValida(tablero,7,1) && regionValida(tablero,7,4) && regionValida(tablero,7,7);
*/

}

// comprueba si la matriz es un tablero valido de sudoku
bool tableroValido(const TMatriz& tablero) {

    return filasValidas(tablero) && columnasValidas(tablero) && regionesValidas(tablero);

}


int main() {
    TMatriz tablero1 =
                    {{ {{5,3,0,0,7,0,0,0,0}},
                        {{6,0,0,1,9,5,0,0,0}},
                        {{0,9,8,0,0,0,0,6,0}},
                        {{8,0,0,0,6,0,0,0,3}},
                        {{4,0,0,8,0,3,0,0,1}},
                        {{7,0,0,0,2,0,0,0,6}},
                        {{0,6,0,0,0,0,2,8,0}},
                        {{0,0,0,4,1,9,0,0,5}},
                        {{0,0,0,0,8,0,0,7,9}}
                    }};

    TMatriz tablero2 =
                    {{ {{5,3,0,0,7,0,0,0,0}},
                        {{6,0,0,1,9,5,0,0,0}},
                        {{0,9,8,0,0,0,0,6,0}},
                        {{8,0,3,0,6,0,0,0,3}},
                        {{4,0,0,8,0,3,0,0,1}},
                        {{7,0,0,0,2,0,0,0,6}},
                        {{0,6,0,0,0,0,2,8,0}},
                        {{0,0,0,4,1,9,0,0,5}},
                        {{0,0,0,0,8,0,0,7,9}}
                    }};

    TMatriz tablero3 =
                    {{ {{5,3,0,0,7,0,0,0,0}},
                        {{6,0,0,1,9,5,0,0,0}},
                        {{0,9,8,0,2,0,0,6,0}},
                        {{8,0,0,0,6,0,0,0,3}},
                        {{4,0,0,8,0,3,0,0,1}},
                        {{7,0,0,0,2,0,0,0,6}},
                        {{0,6,0,0,0,0,2,8,0}},
                        {{0,0,0,4,1,9,0,0,5}},
                        {{0,0,0,0,8,0,0,7,9}}
                    }};

    TMatriz tablero4 =
                    {{ {{5,3,0,0,7,0,6,0,0}},
                        {{6,0,0,1,9,5,0,0,0}},
                        {{0,9,8,0,0,0,0,6,0}},
                        {{8,0,0,0,6,0,0,0,3}},
                        {{4,0,0,8,0,3,0,0,1}},
                        {{7,0,0,0,2,0,0,0,6}},
                        {{0,6,0,0,0,0,2,8,0}},
                        {{0,0,0,4,1,9,0,0,5}},
                        {{0,0,0,0,8,0,0,7,9}}
                    }};

    if (tableroValido(tablero1)) {
        cout << "El tablero1 es un sudoku VALIDO" << endl;
    } else {
        cout << "El tablero1 es un sudoku NO VALIDO" << endl;
    }

    if (tableroValido(tablero2)) {
        cout << "El tablero2 es un sudoku VALIDO" << endl;
    } else {
        cout << "El tablero2 es un sudoku NO VALIDO" << endl;
    }

    if (tableroValido(tablero3)) {
        cout << "El tablero3 es un sudoku VALIDO" << endl;
    } else {
        cout << "El tablero3 es un sudoku NO VALIDO" << endl;
    }

    if (tableroValido(tablero4)) {
        cout << "El tablero4 es un sudoku VALIDO" << endl;
    } else {
        cout << "El tablero4 es un sudoku NO VALIDO" << endl;
    }

    return 0;
}
