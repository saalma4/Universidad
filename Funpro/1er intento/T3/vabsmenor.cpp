#include <iostream>

using namespace std;

void ordenanumero(int a, int b)
{
    if (a > b)
    {
        cout << a << " " << b << endl;
    }
    else
    {
        cout << b << " " << a << endl;
    }
}

int main()
{
    int n1, n2;
    cout << "introduzca dos valores: ";
    cin >> n1 >> n2;
    ordenanumero(n1, n2);
}
