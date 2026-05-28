#include <iostream>
using namespace std;

void decimalAbinario(int n) {
    if (n < 2) {
        cout << n;
    } else {
        decimalAbinario(n / 2);
        cout << n % 2;
    }
}

int main() {
    int n;
    cout << "Introduce un numero natural: ";
    cin >> n;

    while (n < 0) {
        cout << "Debe ser un numero natural (>=0). Introduce otro: ";
        cin >> n;
    }

    cout << "El numero " << n << " en binario es: ";
    decimalAbinario(n);
    cout << endl;

    return 0;
}
