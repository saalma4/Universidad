#include <iostream>

using namespace std;

int main()
{
    char caracter;
    cout << "Introduzca un carácter: ";
    cin >> caracter;
    if (caracter == ('.'))
    {
        cout << "Es punto" << endl;
    }
    else if ((caracter >= ('A')) && (caracter <= ('Z')))
    {
        cout << "Es letra" << endl;
    }
    else if ((caracter >= ('a')) && (caracter <= ('z')))
    {
        cout << "Es letra" << endl;
    }
    else
    {
        cout << "Error" << endl;
    }
}