#include <iostream>
#include <string>

using namespace std;

const int MAX_PAL_DIST = 20;

int main() {
    string palabras[MAX_PAL_DIST];
    int contador = 0;
    string lectura;

    cout << "Introduzca un texto (FIN para terminar):" << endl;

    while (cin >> lectura && lectura != "FIN" && contador < MAX_PAL_DIST) {
        bool repetida = false;
        for (int i = 0; i < contador; i++) {
            if (palabras[i] == lectura) {
                repetida = true;
                break;
            }
        }

        if (!repetida) {
            palabras[contador] = lectura;
            contador++;
        }
    }

    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - i - 1; j++) {
            if (palabras[j].length() > palabras[j + 1].length()) {
                string temp = palabras[j];
                palabras[j] = palabras[j + 1];
                palabras[j + 1] = temp;
            }
        }
    }

    cout << "Las palabras ordenadas de menor a mayor longitud son:" << endl;
    for (int i = 0; i < contador; i++) {
        cout << palabras[i] << " ";
    }
    cout << endl;

    return 0;
}