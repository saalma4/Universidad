#include <iostream>

using namespace std;

const char SIMBOLO = '*';
const char ESPACIO = ' ';

int main()
{
    int num;
    cout << "introdzca un numero: ";
    cin >> num;
    for (int fila =  0; fila < num; fila++)
    {
        for (int colum = 0; colum < num; colum++)
        {
            if ((fila == 0) || (colum == num - 1) || (fila == colum))
            {
                cout << SIMBOLO;
            }
            else
            {
                cout << ESPACIO;
            }

        }
        cout << endl;
    }
}