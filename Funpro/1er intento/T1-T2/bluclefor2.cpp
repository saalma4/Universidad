#include <iostream>

using namespace std;

int main()
{
    int numero, numdv = 0;
    cout << "introduzca un numero: ";
    cin >> numero;
    for (int i = 2; i < numero; i++)
    {
        if (numero % i == 0)
        {
            numdv++;
        }
    }
    if ((numero > 1) && (numdv == 0))
    {
        cout << "el numero es primo" << endl;
    }
    else
    {
        cout << "el numero es compuesto" << endl;
    }

}