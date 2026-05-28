#include <iostream>

using namespace std;

int vabs(int numero)
{
    if (numero < 0)
    {
        numero = -numero;
    }
    return numero;
}

int main()
{
    int num, num2;
    cout << "introduce dos numeros: ";
    cin >> num >> num2;
    cout << "resultado: " << vabs(num) << " " << vabs(num2) << endl;

}
