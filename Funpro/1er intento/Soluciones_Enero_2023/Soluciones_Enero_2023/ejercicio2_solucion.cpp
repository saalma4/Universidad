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

// comprueba si el caracter c aparece en pal
bool aparece(char c, const string& pal) {
    int i = 0;

    while (i < int(pal.size()) && (c != pal[i])) {
        i++;
    }

    return i < int(pal.size());
}

// comprueba si todas las letras de pal1 estan en pal2
bool letrasContenidas(const string& pal1, const string& pal2) {
    int i = 0;

    while (i < int(pal1.size()) && aparece(pal1[i], pal2)) {
            i++;
    }

    return i >= int(pal1.size());
}

// comprueba si la palabra pal esta almacenada en la estructura datos
bool esta(const string& pal, const Datos& datos) {
	int i = 0;

	while ((i < datos.npal) && (pal != datos.pal[i])) {
		i++;
	}
	return i < datos.npal;
}

// comprueba si la palabras pal1 y pal2 son locogramas
bool son_locogramas(const string& pal1, const string& pal2)
{
	return (pal1.size() == pal2.size()
			&& letrasContenidas(pal1, pal2)
			&& letrasContenidas(pal2, pal1));
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
