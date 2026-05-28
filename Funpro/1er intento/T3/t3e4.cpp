#include <iostream>
#include <cassert>

using namespace std;

int digito(int n, int i)
{
    // assert ((N >= 0)&& (i >= 0));
    for (int ii = 0; ii < i; ++ii)
    {
        n = n / 10;
    }
    return n % 10;
}

void mostrar(int valor)
{
    cout << "resultado: " << valor << endl;
} 


void leer(int& n , int& i)
{
    cout << "introduzca dos numeros, numero y posicion respectivamente: ";
    cin >> n >> i;
    while ((n <= 0)||(i <= 0))
    {
        cout << "error. introduzca un numero: ";
        cin >> n >> i;
    }
}


int main()
{
    int n, i;
    leer(n, i);
    int d = digito(n, i-1);
    mostrar(d);
}









































































































































































































































































