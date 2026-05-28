#include <iostream>
using namespace std;

int main() {
    int consumoKw;
    double total;

    cout << "Introduce el consumo en Kw: ";
    cin >> consumoKw;

    if (consumoKw <= 100) {
        total = 1 + consumoKw * 0.50;
    }
    else if (consumoKw <= 250) {
        total = 1 + 100 * 0.50 + (consumoKw - 100) * 0.35;
    }
    else {
        total = 1 + 100 * 0.50 + 150 * 0.35 + (consumoKw - 250) * 0.25;
    }

    cout << "El importe total a pagar es: " << total << " €" << endl;
}