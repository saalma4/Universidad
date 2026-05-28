#include <iostream>

using namespace std;

const double POR_TEORIA = 0.7;
const double POR_PRACTICA = 0.3;

int main()
{
    double nota_teoria, nota_practica, nota_final;
    cout << "introduzca la nota de la teoria: ";
    cin >> nota_teoria;
    cout << "introduzca la nota de la practica: ";
    cin >> nota_practica;
    nota_final = (nota_teoria * POR_TEORIA) + (nota_practica * POR_PRACTICA);
    cout << "la calificacion es: " << nota_final << endl;
}