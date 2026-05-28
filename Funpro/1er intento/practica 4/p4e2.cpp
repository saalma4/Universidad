#include <iostream>

using namespace std;

bool esPrimo(int ns)
{
    int contador = 0;
    for(int i = 1; i <= ns; ++i)
    {
        if(ns % i == 0)
        {
            contador++;
        }

    }
    if (contador > 2)
    {
        return false;
    }
    else 
    {
        return true;
    }
}

void mostrar_primo(int n)
{
    int contador = 0;
    for (int i = 2; contador < n; ++i)
    {
        if(esPrimo(i))
        {
            cout << i << " ";
            contador++;
        }
    }
}

void leer (int& n)
{
    cout << "Introduzca un número: ";
    cin >> n;
}

int main()
{
    int n, ns;
    leer(n);
    mostrar_primo(n);
    bool esPrimo(ns);
}