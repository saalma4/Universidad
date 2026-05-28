#include <iostream>

using namespace std;

int main()
{
    cout << "introduzca un numero: ";
    int numero;
    cin >> numero;
    int dig1 = numero % 10;
    int dig3 = (numero / 100) % 10;
    bool tres_dig_cap = ((numero > 99) && (numero < 1000)) && (dig1 == dig3);
    cout << tres_dig_cap << endl;
    
}

