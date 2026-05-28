#include <iostream>
using namespace std;

int main() {
    int n1, n2, n3;
    cout << "introduzca 3 numeros y te dire cual es el mayor estricto, si es que lo hay.. ";
    cin >> n1 >> n2 >> n3;
    if (n1 > n2 && n1 > n3) {
        cout << "el mayor estricto es " << n1 << endl;
    }
    else if (n2 > n1 && n2 > n3) {
        cout << "el mayor estricto es " << n2 << endl;
    }
    else if (n3 > n1 && n3 > n2) {
        cout << "el mayor estricto es " << n3 << endl;
    }
    else {
        cout << "no hay mayor estricto." << endl;
    }

}