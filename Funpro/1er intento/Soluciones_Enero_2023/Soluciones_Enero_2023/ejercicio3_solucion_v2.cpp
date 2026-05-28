#include <iostream>
#include <array>

using namespace std;

const int TAM_REGION = 3;
const int TAM = TAM_REGION * TAM_REGION;
typedef array<int,TAM> TFila;
typedef array<TFila,TAM> TMatriz;

// array auxiliar para controlar la aparicion de numeros del 1 al 9
// sirve para filas, columnas y regiones
typedef array<bool,TAM+1> TAparecidos; // la casilla 0 no se usa

bool checkNum(TAparecidos& numAparecidos, int num)
{
    bool valida = true;
	if ((num >= 1 && num <= TAM) && ! numAparecidos[num]) {
		numAparecidos[num] = true;
	} else if (num != 0) {
		valida = false;
	}
    return valida;
}

// comprueba si la fila fi es valida (no tiene numeros repetidos)
bool filaValida(const TMatriz& tablero, int fi)
{
    TAparecidos numAparecidos = {}; // todas las casillas a false
    bool valida = true;
    for (int co = 0; co < int(tablero[fi].size()) && valida; ++co) {
		valida = checkNum(numAparecidos, tablero[fi][co]);
    }
    return valida;
}

// comprueba si todas las filas son validas
bool filasValidas(const TMatriz& tablero)
{
    bool valida = true;
    for (int fi = 0; fi < int(tablero.size()) && valida; ++fi) {
        valida = filaValida(tablero, fi);
    }
    return valida;
}

// comprueba si la columna co es valida (no tiene numeros repetidos)
bool columnaValida(const TMatriz& tablero, int co)
{
    TAparecidos numAparecidos {}; // todas las casillas a false
    bool valida = true;
    for (int fi = 0; fi < int(tablero.size()) && valida; ++fi) {
		valida = checkNum(numAparecidos, tablero[fi][co]);
    }
    return valida;
}

// comprueba si todas las columnas son validas
bool columnasValidas(const TMatriz& tablero)
{
    bool valida = true;
    for (int co = 0; co < int(tablero[0].size()) && valida; ++co) {
        valida = columnaValida(tablero, co);
    }
    return valida;
}

// comprueba si la region cuya casilla superior izquierda [fiSupReg][coIzqReg]
// es valida (no tiene numeros repetidos)
// todos los vecinos existen
bool regionValida(const TMatriz& tablero, int fiSupReg, int coIzqReg)
{
    TAparecidos numAparecidos {}; // todas las casillas a false
    bool valida = true;
    for (int fi = fiSupReg; fi < fiSupReg+TAM_REGION && valida; ++fi) {
        for (int co = coIzqReg; co < coIzqReg+TAM_REGION && valida; ++co) {
			valida = checkNum(numAparecidos, tablero[fi][co]);
        }
    }
    return valida;
}

// comprueba si todas las regiones son validas
// invoca a regionValida para cada region pasandole
// los indices de la fila y columna de la celda central
// de la region
bool regionesValidas(const TMatriz& tablero)
{
    bool valida = true;
    for (int fi = 0; fi < int(tablero.size()) && valida; fi += TAM_REGION) {
		for (int co = 0; co < int(tablero[fi].size()) && valida; co += TAM_REGION) {
			valida = regionValida(tablero, fi, co);
		}
	}
	return valida;
}

// comprueba si la matriz es un tablero valido de sudoku
bool tableroValido(const TMatriz& tablero)
{
    return (filasValidas(tablero)
			&& columnasValidas(tablero)
			&& regionesValidas(tablero));
}

int main()
{
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
