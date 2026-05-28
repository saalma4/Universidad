#include <iostream>
#include <array>
#include <string>

using namespace std;

const int MAX_PAL_DIST = 15;

typedef array<string, MAX_PAL_DIST>Palabras;

struct Datos {
	Palabras pal;
	int npal;
};

const int NLETRAS = 'Z' - 'A' + 1;
typedef array<bool, NLETRAS> Letras;


void apariciones(const string& pal, Letras& lt)
{
	lt = {}; // inicializa todos los elementos a false
	for (int i = 0; i < int(pal.size()); ++i) {
		if ('A' <= pal[i] && pal[i] <= 'Z') {
			lt[ pal[i] - 'A' ] = true;
		}
	}
}

// comprueba si la palabras pal1 y pal2 son locogramas
bool son_locogramas(const string& pal1, const string& pal2)
{
	bool ok = (pal1.size() == pal2.size());
	if (ok) {
		Letras lt1, lt2;
		apariciones(pal1, lt1);
		apariciones(pal2, lt2);
		ok = (lt1 == lt2);
	}
	return ok;
}

// comprueba si la palabra pal esta almacenada en la estructura datos
bool esta(const string& pal, const Datos& datos) {
	int i = 0;
	while ((i < datos.npal) && (pal != datos.pal[i])) {
		i++;
	}
	return i < datos.npal;
}

// comprueba si pal es locograma de primera, en cuyo caso la almacena en datos, si no esta ya
void procesar(Datos& datos, const string& primera, const string& pal)
{
	if (!esta(pal, datos)
		&& son_locogramas(primera, pal)) {
		datos.pal[datos.npal] = pal;
		datos.npal++;
	}
}

// lee los datos de entrada, procesando cada palabra leida
void leer_y_procesar_secuencia(Datos& datos)
{
	string primera, pal;

	datos.npal = 0;

	cout << "Introduzca el texto (FIN para terminar):\n\n";

	cin >> primera;
	if (primera != "FIN") {
        cin >> pal;
        while (pal != "FIN") {
			procesar(datos, primera, pal);
            cin >> pal;
        }
	}
}

// muestra por pantalla datos almacenados en la estructura datos
void escribir(const Datos& datos) {
	cout << "\nLas palabras que son locogramas de la primera son:\n\n";
	for (int i = 0; i < datos.npal; i++) {
		cout << datos.pal[i] << endl;
	}
}

int main()
{
	Datos datos;

	leer_y_procesar_secuencia(datos);

	escribir(datos);
}


