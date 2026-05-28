#include <iostream>
using namespace std;

int main() {
    const int precio_unidad = 100;
    const int iva = 12;
    const int descuento = 5;
    int unidades, precio_unidades;
    double precio_iva, precio_final;

    cout << "Numero de unidades adquiridas: ";
    cin >> unidades;
    precio_unidades = unidades * precio_unidad;
    precio_iva = precio_unidades + (precio_unidades * 0.12);
    if (precio_iva > 300) {
        cout << "Se aplica el descuento del 5%" << endl;
        precio_final = precio_iva - (precio_iva * 0.05);
    }
    else {
        precio_final = precio_iva;
    }
    cout << "El precio total a pagar es: " << precio_final << endl;
}