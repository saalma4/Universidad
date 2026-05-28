#include <array>
#include <iostream>
using namespace std;

int const MAX = 50;
typedef array<int, MAX> TArray;
struct TEstaturas {
    int cantAlturas;
    TArray altura;
};

void leerCantidad(TEstaturas &estaturas) {
    do {
        cout << "Cuantas estaturas va a introducir (maximo 50): ";
        cin >> estaturas.cantAlturas;
    } while (estaturas.cantAlturas < 1 || estaturas.cantAlturas > MAX);
}
void leerAlturas(TEstaturas &estaturas) {
    for (int i = 0; i < estaturas.cantAlturas; i++) {
        cin >> estaturas.altura[i];
    }
}
double sumaTodosElementos(const TEstaturas &estaturas) {
    double suma = 0;
    for (int i = 0; i < estaturas.cantAlturas; i++) {
        suma = suma + estaturas.altura[i];
    }
    return suma;
}
double media(const TEstaturas &estaturas) {
    double res = sumaTodosElementos(estaturas) / estaturas.cantAlturas;
    return res;
}

int masAltos(const TEstaturas &estaturas) {
    double mediaFinal = media(estaturas);
    int cnt = 0;
    for (int i = 0; i < estaturas.cantAlturas; i++) {
        if (estaturas.altura[i] > mediaFinal) {
            cnt++;
        }
    }
    return cnt;
}
int masBajos(const TEstaturas &estaturas) {
    double mediaFinal = media(estaturas);
    int cnt = 0;
    for (int i = 0; i < estaturas.cantAlturas; i++) {
        if (estaturas.altura[i] < mediaFinal) {
            cnt++;
        }
    }
    return cnt;
}
int main() {
    TEstaturas estaturas;
    leerCantidad(estaturas);
    cout << "intruduzca las " << estaturas.cantAlturas << " estaturas: ";
    leerAlturas(estaturas);
    cout << "La media es: " << media(estaturas) << endl;
    cout << "mas altos: " << masAltos(estaturas) << endl;
    cout << "mas bajos: " << masBajos(estaturas) << endl;
}
