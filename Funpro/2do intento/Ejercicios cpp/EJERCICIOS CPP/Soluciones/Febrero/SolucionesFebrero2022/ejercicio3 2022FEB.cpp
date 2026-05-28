#include <iostream>
#include <array>
using namespace std;

const int F = 2,
          C = 3;

typedef array<array<int,C>,F> TMatriz1;
typedef array<array<int,C>,F*2> TMatriz2;

void read (TMatriz1& a) // Lee el imput de la primera matriz
{
    for (int i=0;i<F;i++)
    {
        for (int j=0;j<C;j++)
        {
            do
            {
                cin>>a[i][j];
            }
            while (a[i][j] < 1);
        }
    }
}

void start (const TMatriz1& m,TMatriz2& t) // Inicializa la segunda matriz, copiando la
{                                          // original en las filas pares, y dando valor
    for (int i=0;i<F*2;i++)                // 0 en las filas impares
    {
        for (int j=0;j<C;j++)
        {
            if (i%2 == 0)
            {
                t[i][j] = m[i/2][j];
            }
            else
            {
                t[i][j] = 0;
            }
        }
    }
}

void adjust (int& pos,const int& coord) // Ajusta el valor pos si es mayor que el maximo o menor que 0
{
    if (pos < 0)
    {
        pos = 0;
    }
    if (pos > coord)
    {
        pos = coord;
    }
}

void write (const TMatriz2& a) // Escribe la matriz
{
    for (int i=0;i<F*2;i++)
    {
        for (int j=0;j<C;j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
}

void process (TMatriz2& a) // Realiza el proceso
{
    int posXmax,
        posXmin,
        posYmax,
        posYmin,
        mediatot = 0,
        media = 0,
        cont = 0,
        mediaCheck = 0;

    for (int i=1;i<F*2;i+=2)
    {
        for (int j=0;j<C;j++)
        {
            posXmax = i+2; // Se marcan los limites para buscar a los vecinos
            posXmin = i-1;
            posYmax = j+2;
            posYmin = j-1;
            adjust(posXmax,F*2); // Se ajustan los valores
            adjust(posXmin,F*2);
            adjust(posYmax,C);
            adjust(posYmin,C);

            for (int x=posXmin;x<posXmax;x++)
            {
                for (int y=posYmin;y<posYmax;y++)
                {
                    if (a[x][y] != 0) // Si no vale 0, se apunta para la media
                    {
                        {
                            mediatot = mediatot + a[x][y];
                            cont++;
                        }
                    }
                    if (a[x][y] == 0) // Si vale 0
                    {
                        if (i != x || i != y) // Y no es la misma casilla en la que estamos
                        {
                            mediaCheck++; // Se añade una comprobación más a la media
                        }
                    }
                }
            }
            media = mediatot / cont;

            // EXCEPCIÓN (Sale un error en el cual si estamos en la última fila, se
            // comprobará una vez más de las deseadas)
            if (i == 3)
            {
                mediaCheck--;
            }

            for (int i=0;i<mediaCheck;i++)
            {
                mediatot = mediatot + media;
                media = mediatot / cont;
            }
            cont++;

            // EXCEPCIÓN (Sale un error en el cual si estamos en la última posición, se
            // añade un valor más al contador)
            if (i == F*2-1 && j == C-1)
            {
                cont--;
            }

            a[i][j] = mediatot / cont; // Calculamos el número resultante

            mediatot = 0;
            media = 0;
            cont = 0;
            mediaCheck = 0;
        }
    }
}

int main()
{
    cout<<"JAVIER MOLINA COLMENERO"<<endl;
    cout<<"INGENIERIA DEL SOFTWARE"<<endl;
    cout<<"PC 112"<<endl;

    TMatriz1 m;
    TMatriz2 t;

    cout<<"Introduzca la matriz M ("<<F<<"x"<<C<<") :"<<endl<<endl;

    read(m);

    cout<<endl<<"La matriz T ("<<F*2<<"x"<<C<<") es la siguiente: "<<endl;

    start(m,t);
    cout<<endl;
    process(t);
    write(t);
}
