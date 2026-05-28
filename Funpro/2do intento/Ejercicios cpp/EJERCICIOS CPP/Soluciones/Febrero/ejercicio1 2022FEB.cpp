// JAVIER MOLINA COLMENERO
// PC 112

#include <iostream>
#include <array>
using namespace std;

const int TAM = 7;
typedef array<array<int,TAM>,TAM> TMatriz;

void startPascal (TMatriz& a) // todos los valores de la fila 0 y columna 0 son 1
{
    for (int i=0;i<TAM;i++)
    {
        a[i][0]=1;
        a[0][i]=1;
    }
}

void pascal (TMatriz& a) // Realiza el triángulo de Pascal
{
    int i=1,
        j=1,
        pos=TAM-1; // El indice de la columna máxima a analizar

    while (pos > 0)
    {
        if (j < pos)
        {
            a[i][j] = a[i-1][j] + a[i][j-1];
            j++;
        }
        else
        {
            j=1;
            i++;
            pos--;
        }

    }
}

void write (const TMatriz& a) // Escribe la matriz
{
    for (int i=0;i<TAM;i++)
    {
        for (int j=0;j<TAM;j++)
        {
            if (a[i][j] != 0) // En caso de que el número sea un 0, no se escribe
            {
                cout<<a[i][j]<<" ";
                if (a[i][j] < 10)
                {
                    cout<<" ";
                }
            }
        }
        cout<<endl;
    }
}

int main()
{
    cout<<"JAVIER MOLINA COLMENERO"<<endl;
    cout<<"INGENIERIA DEL SOFTWARE"<<endl;
    cout<<"PC 112"<<endl;

    TMatriz a = {{}};

    startPascal(a);
    pascal(a);

    write(a);
    return 0;
}
