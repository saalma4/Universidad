#include <iostream>

using namespace std;

const char SIMBOLO = 'x';

int main()
{   
    int n;
    int fila = 1;
    do
    {
        cout << "Introduzca un número: ";
        cin >> n;
    } while (n <= 0);
    for (int fila = 0; fila < n; ++fila)
    {
        cout << SIMBOLO;
    }
    cout << endl;
    
}