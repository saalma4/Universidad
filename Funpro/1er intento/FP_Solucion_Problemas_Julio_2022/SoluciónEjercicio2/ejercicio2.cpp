/*
 * ejercicio2.cpp
 *
 *  Created on: 18/07/2022
 *      Alumno:
 *      Titulación:
 *      Grupo:
 *      PC usado:
 */

#include <iostream>
#include <string>
#include <array>

using namespace std;

const int MAX_PAL_DIST = 20;

typedef array<string,MAX_PAL_DIST> TPalabras;

struct TDatos {
	TPalabras pal;
	int nPal;
};

// comprueba si la palabra pal esta almacenada ya en la estructura datos
bool esta(const string& pal, const TDatos& datos) {
	int i = 0;

	while ((i < datos.nPal) && (pal != datos.pal[i])) {
		i++;
	}

	return i < datos.nPal;
}

// devuelve la suma de los caracteres ASCII que conforman la cadena s
int sumaASCII(const string& s) {
    int suma = 0;

    for (int i = 0; i < int(s.size()); i++) {
        suma += int(s[i]);
    }

    return suma;
}

/*
 * comprueba si la suma de los caracteres de la palabra pal en ASCII suman el mismo
 * valor que la suma de los caracteres del patron
 */
bool coincideSumaASCII(const string& patron, const string& pal) {
    return sumaASCII(patron) == sumaASCII(pal);
}

// muestra por pantalla las palabras almacenadas en la estructura datos
void escribir(const TDatos& datos) {
	cout << "Las palabras que cumplen la condicion son:\n\n";
	for (int i = 0; i < datos.nPal; i++) {
		cout << datos.pal[i] << " ";
	}
}

int main()
{
	TDatos datos;
	string patron,pal;

	cout << "Introduzca el patron: ";

    cin >> patron;

	cout << "Introduzca el texto (FIN para terminar):\n";

	datos.nPal = 0;

	cin >> pal;

	while (pal != "FIN") {
		if ((coincideSumaASCII(patron,pal)) && (!esta(pal,datos))) {
			datos.pal[datos.nPal] = pal;
			datos.nPal++;
		}
		cin >> pal;
	}

	escribir(datos);

    return 0;
}
