#include <iostream>
#include <string>
using namespace std;

void leer(string &patron, string &cadena)
{
    cout << "Introduzca el patrón en minúsculas: ";
    cin << patron,
    cout << "Introduzca el texto en minúsculas hasta (fin): ";
    cin >> cadena;
    while (cadena != "fin"){}

}
int main(){
    string patron, cadena;
    
}