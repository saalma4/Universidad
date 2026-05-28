#include <iostream>
#include <array>
using namespace std;

const int NFILAS = 3;
const int NCOLUMNAS = 5;

typedef array <int, NFILAS> Fila;
typedef array <Fila, NCOLUMNAS> Matriz;

void leer_matriz(Matriz& m)
{
    cout << "Introduzca " << m.size() << " x: " << m[0].size() << " numeros: ";
    for (int f = 0; f < m.size(); ++f)
    {
        for (int c = 0; c < m[f].size(); ++c)
        {
            cin >> m[f][c];
        }
    }

}
int sumar_fla(Fila& fila)
{
    int suma = 0;
    for (int c = 0; c < int(fila.size()); ++c)
    {
        suma += fila[c];
    }
    return suma;
}
int sumar_columnas(Matriz& m, int c)
{
    int suma = 0;
    for (int f = 0; f < int (m[f].size()); ++f)
    {
        suma += m[f][c];
    }
    return suma;
}
void escribir_fila(const Fila& fila)
{
    for (int c = 0; c < int(fila.size()); ++c)
    {
        cout << fila[c] << " ";
        
    }
}
void escribir_matriz_formato(const Matriz& m)
{
    
}

