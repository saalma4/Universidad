#include <iostream>

using namespace std;

int main()
{
    int numero1, total = 0;
    cout << "Introduzca una secuencia de numeros terminada en 0: ";
    cin >> numero1;
    while (numero1 != 0) 
    {
        total += numero1;
        cin >> numero1;
    }
    cout << "resultado: " << total;
}