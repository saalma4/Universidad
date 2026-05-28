#include <iostream>
#include <iomanip>
#include <array>
using namespace std;
const int NFILAS = 5;
const int NCOLUMNAS = 7;

typedef array<int, NFILAS> Filas;
typedef array<Filas, NCOLUMNAS> Matriz;

void leer_matriz(Matriz& m)
{
    cout << "Introduzca 5 filas de 7 numeros: " << endl;
    for(int f = 0; f < int(m.size()); ++f)
    {
        for(int c = 0;c < int(m[f].size()); ++c)
        {
            cin >> m[f][c];
        }
    }
}
void mostrar_matriz(const Matriz& m)
{
    for(int f = 0; f < int(m.size()); ++f)
    {
        for(int c = 0; c < int(m[f].size()); ++c)
        {
        cout << setw(3) << m[f][c] << " ";
        }
    cout << endl;
    }
}
void buscar_mayor2d(const Matriz& m, int& mayor, int& fila, int& columna)
{
    fila = 0;
    columna = 0;
    mayor = m[0][0];
    for(int f = 0; f < int(m.size()); ++f)
    {
        for(int c = 0; c < int(m[f].size()); ++c)
        {
            if(m[f][c]>=mayor)
            {
                mayor=m[f][c];
                fila=f;
                columna=c;
            }
        }
    }
    cout << "El numero " << mayor << " es el mayor elemento de la matriz" << endl;
    cout << "Se encuentra en [" << fila << "] [" << columna << "]" << endl;

}
int main()
{
    Matriz m;
    int mayor, fila, columna;
    leer_matriz(m);
    buscar_mayor2d(m, mayor, fila, columna);
    mostrar_matriz(m);
}