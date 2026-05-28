#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "introduzca un entero: ";
    cin >> n;
    int cnt = 0;
    while (n != 0) {
        n = n / 10;
        cout << n << endl;
        cnt++;
    }
    if (cnt % 2 == 0) {
        cout << "Ese entero SI es clave" << endl;
    } else {
        cout << "Ese entero NO es clave" << endl;
    }
}