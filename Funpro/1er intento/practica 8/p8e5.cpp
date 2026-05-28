#include <iostream>
#include <string>
using namespace std;

void leer(string &operador, string &cadena1, string &cadena2)
{
    do
    {
        cout << "Introduzca la operacion a realizar (+,-,*) (& para terminar): ";
        cin >> operador;
    } while (operador != '&');
    cout << "Introduzca op1: ";
    cin >> cadena;
    cout >> "Introduzca op2; ";
    cin >> cadena;
}
string resultado(string& palabra)
{

}

int main(){
    string operador, palabra1, palabra2;
    leer(operador, palabra1, palabra2);
}