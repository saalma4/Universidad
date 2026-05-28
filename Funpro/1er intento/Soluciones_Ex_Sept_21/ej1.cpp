/*
 * ej1.cpp
 *
 *  Created on: 03/09/2021
 *      Author: tolo
 */

#include <iostream>
#include <array>
using namespace std;

const int MAX = 4;

typedef array<int,MAX> TFila;
typedef array<TFila,MAX> TMatriz;

void rotar1vez(TMatriz& m) {
	TMatriz maux;

	for (int fi = 0; fi < MAX; fi++) {
		for (int co = 0; co < MAX; co++) {
			maux[co][MAX-1-fi] = m[fi][co];
		}
	}

	m = maux;
	/*
	for (int fi = 0; fi < MAX; fi++) {
		for (int co = 0; co < MAX; co++) {
			m[fi][co] = maux[fi][co];
		}
	}
    */
}

void rotar(TMatriz& mat, int n) {

	for (int cont = 1; cont <= n % 4; cont++) {
		rotar1vez(mat);
	}
}

void leer(TMatriz& m) {

	for (int fi = 0; fi < MAX; fi++) {
		for (int co = 0; co < MAX; co++) {
			cin >> m[fi][co];
		}
	}
}

void escribir(const TMatriz& m) {

	for (int fi = 0; fi < MAX; fi++) {
		for (int co = 0; co < MAX; co++) {
			cout <<  m[fi][co] << " ";
		}
		cout << endl;
	}
}


int main() {
	TMatriz mat;
	int n;

	cout << "Introduzca los elementos de la matriz ("
                << MAX << " x " << MAX << ") fila a fila:" << endl;
	leer(mat);

	cout << "\nIntroduzca el numero de rotaciones a realizar: ";
	cin >> n;

	rotar(mat,n);

	cout << "\nLa matriz resultado tras las rotaciones es:\n";
	escribir(mat);

	return 0;
}


