#include <array>
#include <iostream>
using namespace std;

const int MAX_ALUMNOS = 20;
const int N_EVALUACIONES = 3;

typedef array<double, N_EVALUACIONES> Notas;
struct Alumno {
    string nombre;
    Notas notas;
};

typedef array<Alumno, MAX_ALUMNOS> Alumnos;
struct Clase {
    Alumnos alumnos;
    int nAlumn;
};

void leerNotas(Alumno &alumno) {
    for (int i = 0; i < N_EVALUACIONES; i++) {
        cin >> alumno.notas[i];
    }
}

int main() {
    int numAL;
    Clase clase;
    clase.alumnos = {};
    clase.nAlumn = 0;

    do {
        cout << "introduce el numero de alumnos: ";
        cin >> numAL;
    } while (numAL > MAX_ALUMNOS || numAL < 1);

    do {
        Alumno alumno;
        cout << "introduce el nombre y " << N_EVALUACIONES << " notas: ";
        cin >> alumno.nombre;
        leerNotas(alumno);
        clase.alumnos[clase.nAlumn] = alumno;
        numAL--;
        clase.nAlumn++;
    } while (numAL > 0);

    cout << "Alumno        ";
    for (int i = 1; i <= N_EVALUACIONES; i++) {
        cout << "Nota-" << i << "        ";
    }
    cout << endl;
}
