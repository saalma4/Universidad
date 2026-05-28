#include <iostream>

using namespace std;

int main()
{
    int n1, n2, cociente = 0;
    cout << "Introduzca dos numeros: ";
    cin >> n1 >> n2;
    while ((n1 <  0) || (n2 <= 0))
    {
        cout << "Error, introduzca de nuevo los numeros: ";
        cin >> n1 >> n2;
    }
    while (n1 >= n2)
    {
        n1 -= n2;
        ++cociente;

    }
    cout << "resto: " << n1 << " cociente: " << cociente << endl;
}

