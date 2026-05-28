#include <iostream>

using namespace std;

const double IVA = 1.12;
const double DESCUENTO = 0.05;

int main()
{
    int cantidad;
    double precio_unidad, precio_sin_IVA, precio_IVA, precio_total;
    cout << "Introduzca la cantidad de unidades adquiridas: " << endl;
    cin >> cantidad;
    cout << "Introduzca el precio de una unidad: " << endl;
    cin >> precio_unidad;
    if ((cantidad < 0) || (precio_unidad < 0))
    {
        cout << "Error" << endl;
    }
    else
    {
        precio_sin_IVA = cantidad * precio_unidad;
        precio_IVA = precio_sin_IVA * IVA;

        if (precio_IVA < 300)
        {
            precio_total = precio_IVA;
            cout << "El precio total a pagar es: " << precio_total << endl;
        }
        else
        {
            cout << "Se aplica el descuento del 5%" << endl;
            precio_total = precio_IVA - (precio_IVA * DESCUENTO);
            cout << "El precio total a pagar es: " << precio_total << endl;
        }

    }
   
}