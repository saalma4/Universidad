#include <iostream>
#include <string>
using namespace std;

void leer (string &cadena)
{
    do
    {
        cout << "Introduzca un texto en minusculas hasta (fin): ";
        cin >> cadena;
    } while (cadena != 'fin');
}
int main(){
    string cadena;
    leer(cadena);
    
}