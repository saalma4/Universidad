#include <array>
#include <iostream>
using namespace std;

const int MAX_PAL_DIST = 20;
typedef array<string, 20> TPalabras;

struct TDatos {
    TPalabras palabras;
    int npal;
};

bool esta(const string &palabra, const TDatos &datos) {
    for (int i = 0; i < datos.npal; i++) {
        if (datos.palabras[i] == palabra) {
            return true;
        }
    }
    return false;
}

int posicionPalabra(const string &palabra, TDatos &datos) {
    int i = 0;
    while ((i < datos.npal) && (palabra.size() >= datos.palabras[i].size())) {
        i++;
    }
    return i;
}

void hacerHueco(TDatos &datos, int pos) {
    for (int i = datos.npal; i > pos; i--) {
        datos.palabras[i] = datos.palabras[i - 1];
    }
}
void escribir(const TDatos &datos) {
    for (int i = 0; i < datos.npal; i++) {
        cout << datos.palabras[i] << " ";
    }
    cout << endl;
}

int main() {
    TDatos datos;
    datos.npal = 0;
    int pos;
    string palabra;
    cout << "introduce una serie de palabras: ";
    cin >> palabra;
    while (palabra != "FIN") {
        if (!esta(palabra, datos)) {
            pos = posicionPalabra(palabra, datos);
            hacerHueco(datos, pos);
            datos.palabras[pos] = palabra;
            datos.npal++;
        }
        cin >> palabra;
    }
    cout << "las palabras ordenadas son : ";
    escribir(datos);
    cout << endl;
}