#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "introduzca un valor: ";
    cin >> n;
    double numerador = 2;
    double denominador = 3;
    double fraccion = 0;
    double producto = 1;
    for (int i = 0; i < n; i++) {
        fraccion = numerador / denominador;
        producto = producto * fraccion;
        cout << "numerador: " << numerador << " denom: " << denominador << " fraccion: " << fraccion << " producto: " << producto << endl;
        if (i % 2 != 0) {
            denominador += 2;
        } else {
            numerador += 2;
        }
    }
    double res = 4 * producto;
    cout << "resultado: " << res << endl;
}