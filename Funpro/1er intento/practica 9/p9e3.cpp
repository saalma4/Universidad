#include <iostream>
#include <array>
using namespace std;

const int NFILAS = 7;
const int NCOLUMNAS = 12;

typedef array <int, NFILAS> Fila;
typedef array <Fila, NCOLUMNAS> Matriz;

void leer_matriz(Matriz& m)
{
    cout << "Introduzca la imagen de  " << m.size() << " x " << m[0].size() << " caracteres: ";
    for (int f = 0; f < m.size(); ++f)
    {
        for (int c = 0; c < m[f].size(); ++c)
        {
            cin >> m[f][c];
        }
    }

}
int main(){
    
}