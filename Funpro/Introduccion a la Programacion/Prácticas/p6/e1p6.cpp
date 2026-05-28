#include <array>
#include <iostream>
using namespace std;

int const TAM = 10;

typedef array<int, TAM> TArray;

void leer(TArray &a) {
    for (int &x : a) {
        cin >> x;
    }
}

int mayor(const TArray &a) {
    int mayor = 0;
    for (int x : a) {
        if (x > mayor) {
            mayor = x;
        }
    }
    return mayor;
}

int main() {
    cout << "introduce 10 numeros: ";
    TArray a;
    leer(a);

    cout << "el mayor del array es: " << mayor(a) << endl;
}
