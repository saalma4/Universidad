#include <array>
#include <iostream>
using namespace std;

const int SIZE = 5;
typedef array<double, SIZE> Vector;

void leer(Vector &v)
{
    cout << "Introduzca 5 números: ";
    for (int i = 0; i < int(v.size()); ++i)
    {
        cin >> v[i];
    }
}
double buscar_mayor(const Vector &v)
{
    double mayor = v[0];
    for  (int i = 0; i < int(v.size()); ++i)
    {
        if (v[i] > mayor)
        {
        mayor = v[i];
        }
    }
    return mayor;
}
void mostrar_mayor(double &x)
{
    cout << "El mayor elemento de la lista es " << x <<  endl;
}
void mostrar_lista(const Vector &v)
{
    cout << "Lista: ";
    for (int i = 0; i < int(v.size()); ++i)
    {
        cout << v[i] << " ";
    }

}
int main()
{
    Vector lista;
    leer(lista);
    double mayor = buscar_mayor(lista);
    mostrar_mayor(mayor);
    mostrar_lista(lista);

}
