/*
 * ej3.cpp
 *
 *  Nombre: Monica Pinto
 */

#include <iostream>
#include <array>

using namespace std;

//Definición de tipos
const int MAX_CAR_PATRON = 5;
const int MAX_PAL_DIST = 20;

typedef array <string, MAX_PAL_DIST> TArray;
struct TPalabras {
    char letra;
	TArray palabras;
	int npal;
};

typedef array <TPalabras,MAX_CAR_PATRON> TColeccion;
struct TDatos {
	TColeccion letras;
	int nlet;
};

void leerPatron(string &patron){
    do{
        cout << "Introduzca un patron (longitud maxima = " << MAX_CAR_PATRON << "): ";
        cin >> patron;
    }while (int(patron.size())<0 || int(patron.size())>MAX_CAR_PATRON);
}

bool estaLetra(const TDatos &datos, const char &letra){
    int i=0;

    while (i<int(datos.nlet) && datos.letras[i].letra != letra){
        i++;
    }
    return (i<int(datos.nlet));
}

void inicializarDatos (TDatos &datos, const string &patron){
    datos.nlet = 0;
    for (int i=0; i<int(patron.size()); i++){
        if (!estaLetra(datos,patron[i])){
            datos.letras[datos.nlet].letra = patron[i];
            datos.letras[datos.nlet].npal=0;
            datos.nlet++;
        }
    }
}

bool contieneLetra(const string &palabra, char letra){
    int i=0;

    while (i<int(palabra.size()) && palabra[i]!= letra){
        i++;
    }
    return (i<int(palabra.size()));
}

bool estaPalabra(const TPalabras &palabras, const string &pal){
    int i=0;

    while (i<int(palabras.npal) && palabras.palabras[i]!= pal){
        i++;
    }
    return (i<int(palabras.npal));
}

void insertar(TPalabras &palabras, const string &pal){
    palabras.palabras[palabras.npal] = pal;
    palabras.npal++;
}

void escribir(const TDatos& datos) {
	for (int i = 0; i < datos.nlet; i++) {
        cout << datos.letras[i].letra << " ";
        for (int j=0; j<datos.letras[i].npal; j++){
            cout << datos.letras[i].palabras[j] << " ";
        }
        cout << endl;
	}
}

int main() {
	string palabra, patron;
	TDatos datos;
	int pos;

	leerPatron(patron);
	inicializarDatos(datos, patron);

	cout << "Introduzca texto (FIN para terminar)\n";
	cin >> palabra;
	while (palabra != "FIN") {
        for (int i=0; i<int(datos.nlet); i++){
            if (contieneLetra(palabra, datos.letras[i].letra) &&
            !estaPalabra(datos.letras[i],palabra)){
                insertar(datos.letras[i],palabra);
            }
        }
		cin >> palabra;
	}

	escribir(datos);

	return 0;
}
