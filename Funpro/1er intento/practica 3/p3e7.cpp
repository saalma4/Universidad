#include <iostream>

using namespace std;

int main()
{
    int n;
    double x = 2, y = 1, resultado = 2 * (2 / 1);
    do
    {
        cout << "Introduzca el número de fracciones: ";
        cin >> n;
        if (n <= 0)
        {
            cout << "Error. ";
        }
    } while (n <= 0);
    
    for (int i = 0; i < n; ++i)
    {
        if (i == 0)
        {
            resultado = 2 * (2 / 1);
        }
        else
        {
            if (x > y)
            {
                y += 2;
            }
            else
            {
                x += 2;
            }
            resultado = resultado *(x / y);
        }
        
    }
    cout << "El valor de PI con "<< n << " fracciones es: " << resultado;
}