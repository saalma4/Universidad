#include <array>
#include <iostream>
using namespace std;

const int NALUMNOS = 5;
typedef array<double, NALUMNOS> Notas;

void leer_notas(Notas &notas)
{
    for (int i = 0; i < int(notas.size()); ++i)
    {
        cout << "introduce la nota del alumno " << i + 1 << " :";
        cin >> notas[i];
    }
}
double calcular_notamedia(const Notas &notas)
{
    double suma = 0;
    for (int i = 0; i < int(notas.size()); ++i)
    {
        suma += notas[i];
    }
    return suma / double(notas.size());
}
void mostrar_notas(const Notas &notas, double umbral)
{
    for (int i = 0; i < int(notas.size()); ++i)
    {
        if (notas[i] >= umbral)
        {
            cout << "alumno " << i + 1 << " aprueba." << endl;
        }
        else
        {
            cout << "alumno " << i + 1 << " suspende." << endl;
        }
    }
}
int buscar(const Notas& notas, int x)
{

}
int main()
{
    Notas notas;
    leer_notas(notas);
    calcular_notamedia(notas);
    double m = calcular_notamedia(notas);
    mostrar_notas(notas, m);
}
