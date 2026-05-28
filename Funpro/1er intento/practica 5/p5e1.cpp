#include <iostream>

using namespace std;

void leer(double& a)
{
    cout << "Introduzca el valor de X [0..1]: ";
    cin >> a;
    while ((a < 0) || (a > 1))
    {
        cout << "Error. Introduzca el valor de X [0..1]: ";
        cin >> a;
    }
}

double xelevadoa(double a, int g)
{
    double resultado = a;
    for (int u = 1; u < g; ++u)
    {
        resultado *= a;
    }
    return resultado;
}
int factorial(int a)
{
    int resultado = a;
    for (int i = 1; i < a; ++i)
    {
        resultado = resultado * i;
    }
    return resultado;
}
double calcular_serie(double a)
{
    int fraccion = 1;
    double resultado = 1, sumando;
    do
    {
        sumando = xelevadoa(a, fraccion) / factorial(fraccion);
        resultado += sumando;
        fraccion++;

    } while (sumando > 0.0001);
   return resultado;
}
void mostrar_serie(double a)
{
    double resultado = calcular_serie(a);
    cout << "Serie: " << resultado;

}

int main()
{
    double x;
    leer(x);
    mostrar_serie(x);
}