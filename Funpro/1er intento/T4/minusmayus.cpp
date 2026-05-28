#include <iostream>
#include <string>
using namespace std;

void minus_mayus(string& palabra)
{
    for (int i = 0; i < int(palabra.size()); ++i)
    {
        int distancia = palabra[i] - 'a';
        palabra[i] = distancia + 'A';

    }
}
void leer_palabra(string& palabra)
{
    cout << "introduzca una palabra: ";
    cin >> palabra;
    minus_mayus(palabra);
}
void mostrar_resultado(string& palabra)
{
    cout << palabra;
}
int main()
{
    string palabra;
    leer_palabra(palabra);
    mostrar_resultado(palabra);

}