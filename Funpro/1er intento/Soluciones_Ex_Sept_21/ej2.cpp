/*
 * ej2.cpp
 *
 *  Created on: 03/09/2021
 *      Author: tolo
 */

#include <iostream>
#include <array>
using namespace std;

const int MAX = 20;

typedef array<int,MAX> TArray;

struct TDatos {
	TArray montones;
	int numMont;
};

void leer(TDatos& datos) {
	cout << "Introduzca el numero de montones: ";
	cin >> datos.numMont;
	cout << "Introduzca el numero de cartas de cada monton: ";
	for (int i = 0; i < datos.numMont; i++) {
		cin >> datos.montones[i];
	}
}

void escribir(const TDatos& datos) {
	for (int i = 0; i < datos.numMont; i++) {
		cout << datos.montones[i] << " ";
	}
	cout << "\n";
}

void desplazarIzq(TDatos& datos, int pos) {
	for (int i = pos; i < datos.numMont -1; i++) {
		datos.montones[i] = datos.montones[i+1];
	}
	datos.numMont--;
}

void reorganizar(TDatos& datos) {
	int nuevoMonton = 0;
	int cont = 0;

	while (cont < datos.numMont) {
		datos.montones[cont]--;
		nuevoMonton++;
		if (datos.montones[cont] == 0) {
			desplazarIzq(datos,cont);
		} else {
			cont++;
		}
	}
	datos.montones[datos.numMont] = nuevoMonton;
	datos.numMont++;
}

bool terminado(const TDatos& datos) {
	int cont = 0;

	while (cont < datos.numMont && datos.montones[cont] == cont+1) {
		cont++;
	}

	return cont >= datos.numMont;
}


int main() {
	TDatos datos;

	leer(datos);
	escribir(datos);
	while (!terminado(datos)) {
		reorganizar(datos);
		escribir(datos);
	}

	return 0;
}
