#include <iostream>

using namespace std;

void leerMostrar(int& a)
{
    cout << "Introduzca una secuencia de numeros terminada en cero: ";
do 
{
    cin >> a;
    mostrar(a);
}
while (a != 0);
}
bool esZigzag(int a)
{
    bool zigzag = true;
    for(int i = 0; i ; ++i);
}

void mostrar(int a)
{
    if(esZigzag(a))
    {
        cout << "La secuencia introducida SI es en zigzag" << endl;
    }
    else 
    {
        cout << " La secuencia introducida NO es en zigzag" << endl;
    }
}
int main()
{
    int n;
    leerMostrar(n);
} 