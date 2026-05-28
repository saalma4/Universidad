#include <iostream>
#include <cmath>
using namespace std;

int sumaDivisores(int num) {
    int suma = 0;

    for (int i = 1; i <= num/2; i++) {
        if (num % i == 0) {
            suma += i;
        }
    }

    return suma;
}

bool esPerfecto(int num) {
    return num == sumaDivisores(num);
}

int main() {
    int numero, mayor = 0;

    cout << "Introduzca una secuencia de enteros positivos acabada en 0: ";

    cin >> numero;

    while (numero != 0) {
        if (numero > mayor && esPerfecto(numero)) {
            mayor = numero;
        }
        cin >> numero;
    }

    if (mayor == 0) {
        cout << "No hay ningun numero perfecto en la secuencia\n";
    } else {
        cout << "El mayor numero perfecto de la secuencia es: " << mayor << endl;
    }


    return 0;
}
