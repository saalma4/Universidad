#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

const int MAX_ALUMNOS = 20;
const int N_EVALUACIONES = 3;

int main() {
    string nombres[MAX_ALUMNOS];
    double notas[MAX_ALUMNOS][N_EVALUACIONES];
    double mediaEvaluacion[N_EVALUACIONES] = {0.0, 0.0, 0.0};
    int n_alumnos;

    do {
        cout << "Introduce el numero de alumnos (max " << MAX_ALUMNOS << "): ";
        cin >> n_alumnos;
    } while (n_alumnos < 1 || n_alumnos > MAX_ALUMNOS);

    for (int i = 0; i < n_alumnos; i++) {
        cout << "Introduce el nombre del alumno " << i + 1 << ": ";
        cin >> nombres[i];
        cout << "Introduce las 3 notas de " << nombres[i] << ": ";
        for (int j = 0; j < N_EVALUACIONES; j++) {
            cin >> notas[i][j];
            mediaEvaluacion[j] += notas[i][j];
        }
    }

    for (int j = 0; j < N_EVALUACIONES; j++) {
        mediaEvaluacion[j] /= n_alumnos;
    }

    cout << endl;
    cout << left << setw(15) << "Alumno"
         << setw(15) << "Nota-1"
         << setw(15) << "Nota-2"
         << setw(15) << "Nota-3" << endl;

    cout << string(60, '-') << endl;

    for (int i = 0; i < n_alumnos; i++) {
        cout << left << setw(15) << nombres[i];
        for (int j = 0; j < N_EVALUACIONES; j++) {
            if (notas[i][j] >= mediaEvaluacion[j]) {
                cout << left << setw(15) << "Aprobado";
            } else {
                cout << left << setw(15) << "Suspenso";
            }
        }
        cout << endl;
    }

    return 0;
}