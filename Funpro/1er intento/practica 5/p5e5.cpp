#include <iostream>

using namespace std;

void leer(int &a)
{
    cout << "Introduce el número de filas: ";
    cin >> a;
    do
    {
        cout << "Error. Introduce el número de filas: ";
        cin >> a;

    } while ((a < 0) && (a > 10));
}
void incremento_circular(int &a, int max)
{
}
int calcular_figura(int a)
{
    for (int filas = 0; filas < a; ++filas)
    {
        int max;
        for (int colum = 0; colum < a; ++colum)
        {
            incremento_circular(a, max);
        }
    }
}
void mostrar_figura(int a)
{
}
int main()
{
    int n;
    leer(n);
    calcular_figura(n);
    mostrar_figura(n);
}