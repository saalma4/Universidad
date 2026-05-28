#include <iostream>

using namespace std;

int main()
{
    int nmodelos, preciomodelo;
    double media, ptotal;
    cout << "Introduzca número de modelos de coche: ";
    cin >> nmodelos;
    for (int i =1; i <= nmodelos; i++)
    {
        cout << "Precio modelo " << i << ": ";
        cin >> preciomodelo;
        ptotal += preciomodelo;
    }
    media = ptotal / nmodelos;
    cout << "El valor medio de los 4 modelos de coche asciende a: " << media << "€" << endl;

}