#include <iostream>

using namespace std;

void guiones (int num)
{
    for (int i = 0; i < (2*num - 1); ++i)
    {
        cout  << "-";
    }
    cout<<endl;
}

void mostrar_espacios(int f, int num)
{
    for (int i = 0; i < (num - f - 1); ++i)
    {
        cout << " ";
    }
}

void mostrar_num_ascendentes(int f)
{
    for (int i = 1; i <= (f+1); ++i)
    {
        cout << i;
    }
}

void mostrar_num_desc(int f)
{
    for (int i = f; i >= 1; --i)
    {
        cout << i;
    }
}


void mostrar_linea(int f, int num)
{
    mostrar_espacios(f, num);
    mostrar_num_ascendentes(f);
    mostrar_num_desc(f);
    cout << endl;
}

void piramide (int num)
{
    for (int f = 0; f < num; ++f)
    {
        mostrar_linea(f, num);
    }
}

void mostrar_piramide(int num)
{
    guiones(num);
    piramide(num);
    guiones(num);
}

void leer (int& num)
{
    cout << "Introduzca el numero de filas (menor de 10): ";
    cin >> num;
    while ((num < 0) || (num >= 10))
    {
        cout << "Error. Introduzca el numero de filas (menor de 10): ";
        cin >> num;
    }
}
int main()
{
    int num;
    leer(num);
    mostrar_piramide(num);
}