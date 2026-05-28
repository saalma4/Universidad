#include <iostream>

using namespace std;

const char SIMBOLO = 'x';
const char SIMBOLO2 = 'o';

int main()
{   
    double n;
    int fila = 1;
    do
    {
        cout << "Introduzca un número: ";
        cin >> n;
    } while (n <= 0);
    for (int fila = 0; fila < n; ++fila)
    {
        if (fila % 2 ==0)
        {
        for (int columna = 0; columna < n; ++columna)
        {
            if (columna % 2 == 0)
            {
                cout << SIMBOLO;
            }
            else
            {
                cout << SIMBOLO2;
            }
        
        } 
        }
        else
        {
        for (int columna = 0; columna < n; ++columna)
        {
            if (columna % 2 == 0)
            {
                cout << SIMBOLO2;
            }
            else
            {
                cout << SIMBOLO;
            }
        
        } 
        }

     cout << endl;
    }
     
}