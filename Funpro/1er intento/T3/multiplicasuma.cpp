#include <iostream>

using namespace std;

void leer(int& num)
{
    cout << "introduzca un numero: ";
    cin >> num;
}
void multiplicar(int& a, int& b)
{
    int resultado;
    if (a > b)
    {
        for (int i= 0; i < b; ++i)
        {
            resultado += a;
        }
    }
    else
    {
        for (int i = 0; i < a; ++i)
        {
            resultado += b;
        }
    }
}
void mostrar(int m)
{
    cout << "resultado: " << m << endl;
}
int main()
{
    int n1, n2;
    leer(n1);
    leer(n2);
    multiplicar(n1, n2);
    mostrar(n1);

}