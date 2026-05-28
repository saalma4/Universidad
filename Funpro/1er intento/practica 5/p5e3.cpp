#include <iostream>

using namespace std;

void leer(int& a, int& b)
{
    cout << "Introduzca un intervalo (dos números): ";
    cin >> a >> b;
    while ((a <= 0) || (b <= 0) || (a > b))
    {
        cout << "Error. Introduzca un intervalo (dos números): ";
        cin >> a >> b;
    }
}

int mcd(int a, int b)
{

    int auxmayor = b;
    int auxmenor = a;
    while (auxmayor > auxmenor)
    {
        int aux = auxmayor - auxmenor;
        
        auxmayor = auxmenor;
        auxmenor = aux;

        if (auxmayor < auxmenor)
        {
            aux = auxmayor;
            auxmayor = auxmenor;
            auxmenor = aux;
            
        }

    }
    return auxmenor;
}
void calcular_coprimos(int a, int b)
{
    for (int i = a; i <= b; ++i)
    {
        for (int j = i + 1; j <= b; ++j)
        {
            if(mcd(i, j) == 1)
            {
                cout << "Coprimos: " << i << ", " << j << endl;
            }
        }
    }

}
int main ()
{
    int n, m;
    leer(n, m);
    calcular_coprimos(n, m);
}