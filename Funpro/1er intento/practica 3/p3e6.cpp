#include <iostream>

using namespace std;

int main()
{
char c;
int contador = 0;
cout << "Introduzca el texto terminado en un punto: ";
cin.get(c); 
while (c != '.')
{
    cout << int(c) << " ";
    contador++;
    cin.get(c);
}
cout << endl;
cout << "Número de caracteres leídos: " << contador << endl;;
}