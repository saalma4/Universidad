#include <iostream>
using namespace std;

int main() {
    int num;
    cout << "introduzca un numero y te dire si es positivo o negativo: ";
    cin >> num;
    if (num < 0) {
        cout << "el numero " << num << " es negativo";
    }
    else if (num > 0) {
        cout << "el numero " << num << " es positivo";
    }
    else {
        cout << "el numero es 0!!";
    }
}