#include <iostream>
#include <cmath>
using namespace std;

bool esPrimo(int num) {
    bool res = false;
    int divisor, tope;

    if (num >= 2) {
        tope = sqrt(num);
        divisor = 2;
        while ((divisor <= tope) && (num % divisor != 0)){
            divisor++;
        }
        res = divisor > tope;
    }

    return res;
}

int main() {
    int numero, mayor = 0;

    cout << "Introduzca una secuencia de enteros positivos acabada en 0: ";

    cin >> numero;

    while (numero != 0) {
        if (numero > mayor && esPrimo(numero)) {
            mayor = numero;
        }
        cin >> numero;
    }

    if (mayor == 0) {
        cout << "No hay ningun primo en la secuencia\n";
    } else {
        cout << "El mayor primo de la secuencia es: " << mayor << endl;
    }


    return 0;
}
