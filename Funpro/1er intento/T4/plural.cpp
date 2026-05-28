#include <iostream>
#include <string>
using namespace std;

void plural(string &palabra)
{
    if (palabra[int(palabra.size()) - 1] == 'a' || palabra[int(palabra.size()) - 1] == 'e' || palabra[int(palabra.size()) - 1] == 'i' || palabra[int(palabra.size()) - 1] == 'o' || palabra[int(palabra.size()) - 1] == 'u')
    {
        palabra += "s";
    }
    else if (palabra[int(palabra.size()) - 1] == 'z')
        {
            palabra[int(palabra.size()) - 1] = 'c';
            palabra += "es";
        }
    else 
    {
        palabra += "es";
    }
}

void leer_palabra(string &palabra)
{
    cout << "introduzca una palabra: ";
    cin >> palabra;
    plural(palabra);
}
void mostrar_resultado(string &palabra)
{
    cout << palabra;
}
int main()
{
    string palabra;
    leer_palabra(palabra);
    mostrar_resultado(palabra);
}