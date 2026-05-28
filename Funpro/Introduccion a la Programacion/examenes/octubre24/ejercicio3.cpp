#include <iostream>
using namespace std;

int main() {
    int k;
    do {
        cout << "introduzca un entero positivo: ";
        cin >> k;
    } while (k <= 0);

    int consecutivos = 0;
    int n;
    cout << "introduzca una secuencia de enteros terminada en 0: ";
    do {
        cin >> n;
        int cnt = 0;
        int numActual = n;
        while (numActual != 0) {
            numActual = numActual / 10;
            cnt++;
        }
        if (n != 0) {
            if (cnt % 2 == 0) {
                consecutivos++;
            } else {
                consecutivos = 0;
            }
        }
        cout << "n: " << n << " consecutivos: " << consecutivos << endl;
    } while (n != 0 && consecutivos != k);
    if (consecutivos == k) {
        cout << "resultado: si";
    } else {
        cout << "resultado: no";
    }
}