#include <iostream>
#include <array>
#include <string>

using namespace std;

const int MAX_PAL_DIST = 15;

typedef array<string, MAX_PAL_DIST>TPalabras;

struct TDatos {
	TPalabras pal;
	int nPal;
};

// comprueba si el caracter c aparece en pal
bool aparece(char c, const string& pal) {
    int i = 0;

    while (i < int(pal.size()) && c != pal[i]) {
        i++;
    }

    return i < int(pal.size());
}

// comprueba si todas las letras de pal1 estan en pal2
bool letrasContenidas(const string& pal1, const string& pal2) {
    int i = 0;

    while (i < int(pal1.size()) && aparece(pal1[i],pal2)) {
            i++;
    }

    return i >= int(pal1.size());
}



// comprueba si la palabra pal esta almacenada en la estructura datos
bool esta(const string& pal, const TDatos& datos) {
	int i = 0;

	while ((i < datos.nPal) && (pal != datos.pal[i])) {
		i++;
	}

	return i < datos.nPal;
}

// muestra por pantalla datos almacenados en la estructura datos
void escribir(const TDatos& datos) {
	cout << "\nLas palabras que son locogramas de la primera son:\n\n";
	for (int i = 0; i < datos.nPal; i++) {
		cout << datos.pal[i] << endl;
	}
}

int main()
{
	TDatos datos;
	string primera,pal;

	datos.nPal = 0;

	cout << "Introduzca el texto (FIN para terminar):\n\n";

	cin >> primera;

	if (primera != "FIN") {

        cin >> pal;
        while (pal != "FIN") {
            if (primera.size() == pal.size()
                    && letrasContenidas(primera,pal)
                    && letrasContenidas(pal,primera)
                    && !esta(pal,datos)) {
                datos.pal[datos.nPal] = pal;
                datos.nPal++;
            }
            cin >> pal;
        }
	}

	escribir(datos);

    return 0;
}
