#include <iostream>

using namespace std;


void mostrar (long v)
{

}

long fact (int x)
{
    long f = 1;
    for (int i = 2; i <= x; i++)
    {
        f = f *= i;
    }
}

void mostrar (long v)
{
    cout << "resultado: " << v << endl;
}

long combinatorio (int m, int n)
{
    return fact(m) / (fact(n) * fact(m - n));
}

void leer (int& m, int& n)
{
    cout << "introduce m y n";
    cin >> m >> n;
    while ((m<n) || (n<0))
    {
        cout << "error. introduce m y n";
        cin >> m >> n;
    }
}

int main()
{
    int m;
    int n;
    leer (m,n);
    long c = combinatorio(m,n);
    mostrar(c);
}