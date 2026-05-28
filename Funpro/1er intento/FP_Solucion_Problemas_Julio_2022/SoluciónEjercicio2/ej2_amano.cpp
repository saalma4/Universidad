#include <iostream>
#include <array>
#include <string>
using namespace std;

const int MAX_PAL_DIST = 15;
const string FIN = "FIN";

typedef array<string, MAX_PAL_DIST> Tarray;
struct Tpalabras{
    Tarray palabras;
    int numPalabras;
};

int sumaASCII(const string& palabra){
    int suma = 0;
    for(int i = 0; i < palabra.size(); ++i){
        suma += int(palabra[i]);
    }
    return suma;
}
bool esta(const Tpalabras& pal, const string& palabra){
    int i = 0;
    while((i < pal.numPalabras) && (pal.palabras[i] != palabra)){
        ++i;
    }
    return (i < pal.numPalabras);
}
void escribir (const Tpalabras& pal){
    cout << "Las palabras que cumplen la condicion son: " << endl;
    for (int i = 0; i < pal.numPalabras; ++i){
        cout << pal.palabras[i] << " ";
    }
}
int main (){
    Tpalabras palabras;
    string patron, palabra;

    cout << "Introduzca el patron: " << endl;
    cin >> patron;

    cout << "Introduzca el texto terminado en FIN: " << endl;
    palabras.numPalabras = 0;
    cin >> palabra;
    while (palabra != FIN){
        if((sumaASCII(patron) == sumaASCII(palabra)) && !esta(palabras, palabra)){
            palabras.palabras[palabras.numPalabras] = palabra;
            palabras.numPalabras++;
        }
        cin >> palabra;
    }
    
    escribir(palabras);

    return 0;
}