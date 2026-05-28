#include <iostream>
#include <array>
#include <string>

using namespace std;

const int MAX_PAL_DIST = 15;

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

// comprueba si la palabra pal tiene sus caracteres ordenados alfabeticamente
bool caracteresOrdenados(const string& pal) {
    int i = 0;

    while (i < int(pal.size())-1 && pal [i] <= pal[i+1]) {
        i++;
    }

    return i >= int(pal.size())-1;
}

// muestra por pantalla las palabras almacenadas en la estructura datos
void escribir(const TDatos& datos) {
	cout << "Las palabras cuyos caracteres estan ordenados son:\n";
	for (int i = 0; i < datos.nPal; i++) {
		cout << datos.pal[i] << " ";
	}
}

int main()
{
	TDatos datos;
	string pal;

	cout << "Introduzca el texto (FIN para terminar):\n";

	datos.nPal = 0;

	cin >> pal;

	while (pal != "FIN") {
		if ((caracteresOrdenados(pal)) && (!esta(pal,datos))) {
			datos.pal[datos.nPal] = pal;
			datos.nPal++;
		}
		cin >> pal;
	}

	escribir(datos);

    return 0;
}
