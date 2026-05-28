#include <iostream>
#include <array>
#include <string>
using namespace std;

const int MAX = 10;

struct TPersona {
    string nombre;
    double gastos;
};

typedef array<TPersona,MAX> TArray;

struct TDatos {
    TArray personas;
    int numPersonas;
};

int posicion(const string& nombre, const TDatos& datos) {
    int i = 0;

    while (i < datos.numPersonas && nombre != datos.personas[i].nombre) {
        i++;
    }

    return i;
}

void almacenar(const TPersona& persona,TDatos& datos) {
    int pos = posicion(persona.nombre,datos);
    if (pos < datos.numPersonas) {
        datos.personas[pos].gastos += persona.gastos;
    } else {
        /* el enunciado dice que no habra mas de MAX personas distintas
         * y por eso no comprobamos si se llena el array
        */
        datos.personas[datos.numPersonas] = persona;
        datos.numPersonas++;
    }
}

void leer(TDatos& datos) {
    TPersona persona;

    datos.numPersonas = 0;

    cout << "Introduzca nombres y gastos (FIN para terminar)\n";
    cout << "Nombre: ";
    cin >> persona.nombre;
    while (persona.nombre != "FIN") {
        cout << "Gastos: ";
        cin >> persona.gastos;
        almacenar(persona,datos);
        cout << "Nombre: ";
        cin >> persona.nombre;
    }
}

void mostrar(const TDatos& datos) {
    cout << endl;
    for (int i = 0; i < datos.numPersonas; i++) {
        cout << datos.personas[i].nombre
             << " ha gastado en comun "
             << datos.personas[i].gastos
             << endl;
    }
}

double calcularMedia(const TDatos& datos) {
    double suma = 0;

    for (int i = 0; i < datos.numPersonas; i++) {
        suma += datos.personas[i].gastos;
    }

    return (datos.numPersonas > 0) ? (suma / datos.numPersonas) : 0;
}

void calcularYMostrarPagosRecibos(const TDatos& datos, double media) {
    double diferencia;

    cout << endl;
    for (int i = 0; i < datos.numPersonas; i++) {
        diferencia = datos.personas[i].gastos - media;
        if (diferencia == 0) {
            cout << datos.personas[i].nombre << " esta a la par\n";
        } else if (diferencia > 0) {
            cout << datos.personas[i].nombre << " debe recibir "
                 << diferencia << endl;
        } else {
            cout << datos.personas[i].nombre << " debe pagar "
                 << -diferencia << endl;
        }
    }
}

bool gastosAjustados(const TDatos& datos, double media) {
    int i = 0;

    while (i < datos.numPersonas
           && (media - 0.01 <= datos.personas[i].gastos)
                && (datos.personas[i].gastos <= media + 0.01)) {
        i++;
    }

    return i >= datos.numPersonas;
}

// posPersPagarMas sera la posicion de la persona con menos gastos
// posPersRecibirMas sera la posicion de la persona con mas gastos
void encontrarPosiciones(const TDatos& datos,
                         int& posPersPagarMas, int& posPersRecibirMas) {
    posPersPagarMas = 0;
    posPersRecibirMas = 0;

    for (int i = 1; i < datos.numPersonas; i++) {
		if (datos.personas[i].gastos > datos.personas[posPersRecibirMas].gastos) {
			posPersRecibirMas = i;
		} else if (datos.personas[i].gastos < datos.personas[posPersPagarMas].gastos) {
			posPersPagarMas = i;
		}
	}
}

void ajustarCuentasYMostrarPagos(TDatos& datos, double media) {
    int posPersonaPagarMas, posPersonaRecibirMas;
    double cantidadPagar,cantidadRecibir,transferencia;


    cout << endl;
    while (!gastosAjustados(datos,media)) {
        encontrarPosiciones(datos,posPersonaPagarMas,posPersonaRecibirMas);
        cantidadPagar = media - datos.personas[posPersonaPagarMas].gastos;
        cantidadRecibir = datos.personas[posPersonaRecibirMas].gastos - media;
        if (cantidadPagar < cantidadRecibir) {
            transferencia = cantidadPagar;
        } else {
            transferencia = cantidadRecibir;
        }
        cout << datos.personas[posPersonaPagarMas].nombre
             << " paga " << transferencia << " a "
             << datos.personas[posPersonaRecibirMas].nombre << endl;
        datos.personas[posPersonaPagarMas].gastos += transferencia;
        datos.personas[posPersonaRecibirMas].gastos -= transferencia;
    }
}

int main() {
    TDatos datos;
    double media;

    leer(datos);
    mostrar(datos);
    media = calcularMedia(datos);
    cout << "\nLa media de gastos en comun es " << media << endl;
    calcularYMostrarPagosRecibos(datos,media);
    ajustarCuentasYMostrarPagos(datos,media);

    return 0;
}
