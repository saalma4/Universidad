#include <iostream>
using namespace std;

int main() {
    int n1, n2;
    int suma = 0;
    do {
        cout << "introduzca dos numeros enteros positivos: ";
        cin >> n1 >> n2;
    } while (n1 < 0 || n2 < 0);

    if (n1 != 0 && n2 != 0) {
        int cnt = 1;
        while (n1 >= 1) {
            if (n1 % 2 != 0) {
                suma += n2;
            }
            n1 = n1 / 2;
            n2 = n2 * 2;
        }
    }
    cout << "resultado: " << suma << endl;
}