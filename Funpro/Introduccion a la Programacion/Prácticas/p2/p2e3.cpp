#include <iostream> 
using namespace std;

int main() {
    char c;
    cout << "introduzca una letra o un punto: ";
    cin >> c;
    int codigo = (int)c;
    if ((codigo >= 65 && codigo <= 90) || (codigo >= 97 && codigo <= 122)) {
        cout << "es una letra" << endl;
    }
    else if (codigo == 46) {
        cout << "es un punto" << endl;
    }
    else {
        cout << "error" << endl;
    }
}
