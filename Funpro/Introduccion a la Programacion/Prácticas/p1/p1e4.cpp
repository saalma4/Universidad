#include <iostream>
using namespace std;

int main()
{
    char c1, c2, c3, c4;
    cout << "introduce una palabra: ";
    cin >> c1 >> c2 >> c3 >> c4;
    cout << "Introduzca una palabra de cuatro letras: ";
    cin >> c1 >> c2 >> c3 >> c4;
    c1 = char(int(c1) + 1);
    c2 = char(int(c2) + 1);
    c3 = char(int(c3) + 1);
    c4 = char(int(c4) + 1);
    cout << "resultado: ";
    cout << c1 << c2 << c3 << c4;
}