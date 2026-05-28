#include <iostream>

using namespace std;

int main()
{
    int numero1;
    cout << "Introduzca una secuencia de numeros terminada en 0: ";
    cin >> numero1;
    while (numero1 != 0) 
    {
       if (numero1 % 2 == 0)
       {
        cout << numero1 << " ";
       }
        cin >> numero1;
    }

}