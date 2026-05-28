#include <iostream>
#include <string>
using namespace std;

void leer(string &cadena)
{
    cout << "Introduzca el texto en minúsculas hasta (fin): ";
    cin >> cadena;
    while (cadena != "fin"){}

}
string procesar_palabra(){}
void mostrar_resultado(string &cadena)
{

}
int main(){
    string cadena;
    leer(cadena);
    string cadena_nueva = procesar_palabra(cadena);
    mostrar_resultado(cadena_nueva);
    
}