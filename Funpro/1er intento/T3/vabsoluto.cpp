#include <iostream>

using namespace std;

int vabs(int numero)
{
    int x = numero;
    if (numero < 0)
    {
        x = -x;
    }
    return x;
}

int main()
{
    int num;
    cout << "introduce un numero: ";
    cin >> num;
    int a = vabs(num);
    cout << "resultado: " << a << endl;

}
