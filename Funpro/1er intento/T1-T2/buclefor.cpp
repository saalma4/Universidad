#include <iostream>

using namespace std;

int main()
{
    int numero;
    cout << "escriba un numero: ";
    cin >> numero;
    for (int i = 0; i < numero; i++)
    {
        for (int j = 0; j < numero; j++)
        {
            cout << " *";
        }
        cout << endl;
    }
}