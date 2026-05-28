#include <array>
#include <iostream>
using namespace std;

const int MAX_NUM_DIST = 15;

typedef array<int, MAX_NUM_DIST> Lista;
struct Resultado {
    Lista lista;
    int nelem;
};

int sumaDigitos(int num) {
    int suma = 0;
    while (num > 0) {
        suma += num % 10;
        num = num / 10;
    }
    return suma;
}

bool esta(const Resultado &res, int num) {
    for (int i = 0; i < res.nelem; i++) {
        if (res.lista[i] == num) {
            return true;
        }
    }
    return false;
}

void anyadirAlResultado(Resultado &res, int num) {
    res.lista[res.nelem] = num;
    res.nelem++;
}

int main() {
    Resultado res;
    res.lista = {};
    res.nelem = 0;
    int patron;
    int num;

    do {
        cout << "introduce el numero patron: ";
        cin >> patron;
    } while (patron <= 0);

    int ndigitosPatron = sumaDigitos(patron);
    cout << "introduce una coleccion de numeros enteros (0 para terminar): ";
    cin >> num;
    while (num != 0) {
        if (ndigitosPatron == sumaDigitos(num)) {
            if (!esta(res, num)) {
                anyadirAlResultado(res, num);
            }
        }
        cin >> num;
    }

    cout << "resultado: ";
    for (int i = 0; i < res.nelem; i++) {
        cout << res.lista[i] << " ";
    }
}
