/*
 * ejercicio1.cpp
 *
 *  Created on: 18/07/2022
 *      Alumno:
 *      Titulación:
 *      Grupo:
 *      PC usado:
 */

#include <iostream>
#include <array>

using namespace std;

const int TAM = 10;

typedef array<int,TAM> TArray;


/*
 *  devuelve la longitud de la mayor sub-sucesión ordenada de los números
 *  almacenados en el array pasado como parámetro
 */
int mayorLongitud(const TArray& a) {
    int mayor = 0;
    int longitud = 1; // comenzamos en indice 1

    for (int i = 1; i < int(a.size()); i++) {
        if (a[i-1] > a[i]) {
            if (longitud > mayor) {
                mayor = longitud;
            }
            longitud = 0;
        }
        longitud++;
    }

    // hay que comprobar si la ultima sub-sucesion es la de mayor longitud
    if (longitud > mayor) {
        mayor  = longitud;
    }

    return mayor;
}


void leer(TArray& a) {

    cout << "Introduzca " << TAM << " numeros enteros: ";
    for (int i = 0; i < TAM; i++) {
        cin >> a[i];
    }

}

int main() {
	TArray a;


	// leemos la colección de números y los almacenamos en el array
	leer(a);

	// probamos nuestra función mayorLongitud
    cout << "La longitud de la mayor sub-sucesion es: " << mayorLongitud(a) << endl;


	return 0;
}

