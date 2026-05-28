#include <iostream>
using namespace std;

bool esPrimoRec(int num, int divisor) {
    if (num < 2)
        return false;
    if (divisor == num)
        return true;
    if (num % divisor == 0)
        return false;

    return esPrimoRec(num, divisor + 1);
}

int main() {
    int numero;

    cout << "Introduce un numero natural mayor que 1: ";
    cin >> numero;

    while (numero <= 1) {
        cout << "Debe ser mayor que 1. Introduce otro: ";
        cin >> numero;
    }

    if (esPrimoRec(numero, 2))
        cout << numero << " es primo." << endl;
    else
        cout << numero << " no es primo." << endl;

    return 0;
}
