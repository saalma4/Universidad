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

int sumaASCII(const string& cad) {
    int suma = 0;

    for (int i = 0; i < int(cad.size()); i++) {
        suma += cad[i];
    }
    return suma;
}

bool esta(const string& pal, const TDatos& datos) {
    int i = 0;

	while ((i < datos.nPal) && (pal > datos.pal[i])) {
		i++;
	}

	return i < datos.nPal && pal == datos.pal[i];
}

int posicion(const string& pal, const TDatos& datos) {
	int i = 0;

	while ((i < datos.nPal) && (pal > datos.pal[i])) {
		i++;
	}

	return i;
}

void abrirHueco(TDatos& datos, int pos) {

    for (int i = datos.nPal; i > pos; i--) {
        datos.pal[i] = datos.pal[i-1];
    }
}


void escribir(const string& primera, const TDatos& datos) {
	cout << "Las palabras que son menores que " << primera << " son:\n";
	for (int i = 0; i < datos.nPal; i++) {
		cout << datos.pal[i] << " ";
	}
	cout << endl;
}

int main()
{
	TDatos datos;
	string pal, primera;
	int pos,sumaASCIIPrimera;

	datos.nPal = 0;

	cout << "Introduzca un texto (FIN para terminar): ";

	cin >> primera;

	if (primera != "FIN") {
        sumaASCIIPrimera = sumaASCII(primera);
        cin >> pal;
        while (pal != "FIN") {
            if (sumaASCII(pal) < sumaASCIIPrimera && !esta(pal,datos)) {
                pos = posicion(pal,datos);
                abrirHueco(datos,pos);
                datos.pal[pos] = pal;
                datos.nPal++;
            }
            cin >> pal;
        }
        escribir(primera,datos);
	}


    return 0;
}
