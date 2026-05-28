/*
 * ej3.cpp
 *
 *  Created on: 03/09/2021
 *      Author: tolo
 */


#include <iostream>
#include <string>
#include <array>
using namespace std;

const int MAX_PAL_DIST = 10;

typedef array<string,MAX_PAL_DIST> TPalabras;

struct TDatos {
	TPalabras pal;
	int nPal;
};

int buscar(char c, const string& pal) {
	int ind = 0;

	while ((ind < int(pal.size())) && (pal[ind] != c)) {
		ind++;
	}

	return ind;
}

bool palabraValida(const string& pal, const string& patron, int x) {
	int ind,contCarComun,pos;
	string palaux;

	palaux = pal;
	contCarComun = 0;
	ind = 0;

	while ((contCarComun < x) && (ind < int(patron.size()))) {
		pos = buscar(patron[ind],palaux);
		if (pos < int(palaux.size())) {
			palaux[pos] = ' ';
			contCarComun++;
		}
		ind++;
	}

	return contCarComun >= x;
}


bool esta(const string& pal, const TDatos& datos) {
	int i = 0;

	while ((i < datos.nPal) && (pal != datos.pal[i])) {
		i++;
	}

	return i < datos.nPal;
}



void escribir(const TDatos& datos) {

	for (int i = 0; i < datos.nPal; i++) {
		cout << datos.pal[i] << " ";
	}
	cout << endl;
}

int main()
{
	TDatos datos;
	string pal, patron;
	int x;

	cout << "Introduzca el patron: ";

	cin >> patron;

	cout << "Introduzca el valor de x: ";

	cin >> x;

	cout << "Introduzca el texto (FIN para terminar):\n";

	datos.nPal = 0;

	cin >> pal;

	while (pal != "FIN") {
		if ((palabraValida(pal,patron,x)) && (!esta(pal,datos))) {
			datos.pal[datos.nPal] = pal;
			datos.nPal++;
		}
		cin >> pal;
	}

	cout << "\nLas palabras que contienen al menos " << x
            << " caracteres en comun con " << patron << " son:\n\n";
	escribir(datos);

    return 0;
}


