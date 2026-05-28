#include <array>
#include <iostream>
using namespace std;

const int MAX_LONG_DIST = 15;

struct Elemento {
    int longitud;
    int nrepeticiones;
};

typedef array<Elemento, MAX_LONG_DIST> listaElementos;

struct Resultado {
    listaElementos elementos;
    int nelem;
};

int numeroDeDigitos(int num) {
    int cnt = 0;
    while (num != 0) {
        num = num / 10;
        cnt++;
    }
    return cnt;
}

bool actualizarSiExiste(Resultado &res, const Elemento &el) {
    for (int i = 0; i < res.nelem; i++) {
        if (res.elementos[i].longitud == el.longitud) {
            res.elementos[i].nrepeticiones++;
            return true;
        }
    }
    return false;
}

void addAlResultado(Resultado &res, const Elemento &el) {
    res.elementos[res.nelem] = el;
    res.elementos[res.nelem].nrepeticiones++;
    res.nelem++;
}

int main() {
    Resultado estructuraFinal;
    estructuraFinal.elementos = {};
    estructuraFinal.nelem = 0;
    int num;

    cout << "Introduce una coleccion de numeros enteros (0 para terminar): ";
    do {
        cin >> num;
        if (num != 0) {
            Elemento el;
            el.longitud = numeroDeDigitos(num);
            el.nrepeticiones = 0;
            bool actualizado = actualizarSiExiste(estructuraFinal, el);
            if (!actualizado) addAlResultado(estructuraFinal, el);
        }
    } while (num != 0);

    cout << "L    V" << endl;
    for (int i = 0; i < estructuraFinal.nelem; i++) {
        cout << estructuraFinal.elementos[i].longitud << "    " << estructuraFinal.elementos[i].nrepeticiones << endl;
    }
}