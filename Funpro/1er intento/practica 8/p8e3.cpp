#include <iostream>
#include <string>
using namespace std;

void leer(string& palabra){
    cout << "Introduzca el texto en mínusculas hasta (fin) con el anagrama a comprobar al principio. ";
    cin >> palabra;
    while (palabra != "fin"){

    }
}
int procesar_palabra(int& a){
    
}
void mostrar(string& cadena, int cantidad){
    cout << "En este texto hay " << cantidad << "anagramas como " << cadena << endl;
}
int main(){
    string cadena;
    int a;
    leer(cadena);
    int cant = procesar_palabra(a);
    mostrar(cadena, cant);
}