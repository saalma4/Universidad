#include <iostream>

using namespace std;

int main()
{
    int numero;
    cout << "Introduzca un número entero: ";
    cin >> numero;
    if (numero > 0)
    {
        cout << "El número " << numero << " no es negativo" << endl;
    }
    else if (numero == 0)
    {
        cout << "El número es neutro" << endl;
    }
    else 
    {
        cout << "El número " << numero << " sí es negativo" << endl;
    }
}