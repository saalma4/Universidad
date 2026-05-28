#include <iostream>

using namespace std;

void leer(int &a)
{
    cout << "Introduzca un número: ";
    cin >> a;
    while ((a < 0) || (a == 0))
    {
        cout << "Error. Introduzca un número: ";
        cin >> a;
    }
}

void funFibon(int &x, int &y)
{
    int aux = y;
    y = x + y;
    x = aux;
}
int calcularNesimo(int a)
{
    int resultado = 0, x = 0, y = 1;
    for (int i = 1; i < a; ++i)
    {
        funFibon(x, y);
    }
    return y;
}
void mostrarNesimo(int r, int n)
{
    cout << "fibonacci (" << n << ") : " << r << endl;
}

int main()
{
    int n;
    leer(n);
    int resultado = calcularNesimo(n);
    mostrarNesimo(resultado, n);
}
