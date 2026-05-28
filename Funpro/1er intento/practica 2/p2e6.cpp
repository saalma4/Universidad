#include <iostream>

using namespace std;

const int gastos_fijos = 1;
const double KWH_100 = 0.50;
const double KWH_150 = 0.35;
const double RESTO_KWH = 0.25;

int main()
{
    int consumo;
    double importe, consumo_100, consumo_150, resto_consumo;
    cout << "Introduzca el consumo del contador: " << endl,
    cin >> consumo;
    if (consumo <= 100)
    {
        importe = (consumo * KWH_100) + gastos_fijos;
    }
    else if ((100 < consumo) && (consumo <= 250))
    {
        importe = 50 + ((consumo - 100) * KWH_150) + gastos_fijos;
    }
    else 
    {
       importe = 102.5 + ((consumo - 250) * RESTO_KWH) + 1;
    }
    cout << "Consumo: " << consumo << " Kwh. Importe: " << importe << endl;
}