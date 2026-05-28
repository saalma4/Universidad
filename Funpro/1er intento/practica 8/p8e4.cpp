#include <iostream>
#include <array>
#include <string>
using namespace std;
const int NMAX_ALUMNOS = 20;
const int N_EVALUACIONES = 3;

typedef array<double, NMAX_ALUMNOS> Nalumnos;
struct Alumnos
{
    Nalumnos nalumnos;
    string nombre;
};

void leer_notas(Nalumnos nalumnos, Alumnos alumnos)
{
    cout << "Introduce el numero de alumnos de la clase (maximo 20): ";
    cin >> nalumnos;
    for (int i = 0; i < int(nalumnos.size()); ++i)
    {
        cout << "introduce la nota del alumno " << i + 1 << " :";
        cin >> nalumnos[i];
    }
}   
void mostrar_notas(const Nalumnos &nalumnos, double umbral)
{
    for (int i = 0; i < int(nalumnos.size()); ++i)
    {
        if (notas[i] >= umbral)
        {
            cout << "alumno " << i + 1 << " aprobado" << endl;
        }
        else
        {
            cout << "alumno " << i + 1 << " suspenso" << endl;
        }
    }
}
int main(){
    Nalumnos alumnos;
    leer_notas(alumnos);
    mostrar_notas(alumnos);
}