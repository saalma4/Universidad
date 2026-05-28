// Ejercicio 3

#include <iostream>
#include <array>

using namespace std;

const int TAM = 9;

typedef unsigned TMatriz[TAM][TAM];
typedef array<int,TAM+1> TFrec;



bool filasValidas (const TMatriz& a)
{
	bool res = true;
	TFrec frec;
	//cout<<"filasValidas ejecutado";
	for (int i=0;i<TAM;i++)
	{
		frec = {};
		for (int j=0;j<TAM;j++)
		{
			for (int x=1;x<TAM+1;x++)
			{
				if (a[i][j]==x)
				{
					frec[x]++;
				}
			}
		}
		for (int x=1;x<TAM+1;x++)
		{
			if (frec[x]>1)
			{
				res=false;
			}
		}
	}
	return res;
}

bool columnasValidas (const TMatriz& a)
{
	bool res = true;
	TFrec frec;
	//cout<<"columnasValidas ejecutado";
	for (int i=0;i<TAM;i++)
	{
		frec = {};
		for (int j=0;j<TAM;j++)
		{
			for (int x=1;x<TAM+1;x++)
			{
				if (a[j][i]==x)
				{
					frec[x]++;
				}
			}
		}
		for (int x=1;x<TAM+1;x++)
		{
			if (frec[x]>1)
			{
				res=false;
			}
		}
	}
	return res;
}

bool regionesValidas (const TMatriz& a)
{
	bool res = true;
	TFrec frec;
	
	int F=0,
		C=0;
	
	int checkCount=1;
	//cout<<"regionesValidas ejecutado";
	while (checkCount<10)
	{
		frec = {};
		//cout<<checkCount<<endl;
		for (int i=F;i<F+3;i++)
		{
			for (int j=C;j<C+3;j++)
			{
				for (int x=1;x<TAM+1;x++)
				{
					if (a[i][j]==x)
					{
						//cout<<"found"<<a[i][j];
						frec[x]++;
					}
				}
				//cout<<endl;
			}
		}
		for (int x=1;x<TAM+1;x++)
		{
			if (frec[x]>1)
			{
				res=false;
			}
		}
		C=C+3;
		if (C>=TAM)
		{
			F=F+3;
			C=0;
		}
		checkCount++;
	}
	return res;
}

bool tableroValido (const TMatriz& a)
{
	return (filasValidas(a) && columnasValidas(a) && regionesValidas(a));
}

int main() {
    TMatriz tablero1 = {{5,3,0,0,7,0,0,0,0},
                        {6,0,0,1,9,5,0,0,0},
                        {0,9,8,0,0,0,0,6,0},
                        {8,0,0,0,6,0,0,0,3},
                        {4,0,0,8,0,3,0,0,1},
                        {7,0,0,0,2,0,0,0,6},
                        {0,6,0,0,0,0,2,8,0},
                        {0,0,0,4,1,9,0,0,5},
                        {0,0,0,0,8,0,0,7,9}
						};

    TMatriz tablero2 = {{5,3,0,0,7,0,0,0,0},
                        {6,0,0,1,9,5,0,0,0},
                        {0,9,8,0,0,0,0,6,0},
                        {8,0,3,0,6,0,0,0,3},
                        {4,0,0,8,0,3,0,0,1},
                        {7,0,0,0,2,0,0,0,6},
                        {0,6,0,0,0,0,2,8,0},
                        {0,0,0,4,1,9,0,0,5},
                        {0,0,0,0,8,0,0,7,9}
                        };

    TMatriz tablero3 = {{5,3,0,0,7,0,0,0,0},
                        {6,0,0,1,9,5,0,0,0},
                        {0,9,8,0,2,0,0,6,0},
                        {8,0,0,0,6,0,0,0,3},
                        {4,0,0,8,0,3,0,0,1},
                        {7,0,0,0,2,0,0,0,6},
                        {0,6,0,0,0,0,2,8,0},
                        {0,0,0,4,1,9,0,0,5},
                        {0,0,0,0,8,0,0,7,9}
                        };

    TMatriz tablero4 = {{5,3,0,0,7,0,6,0,0},
                        {6,0,0,1,9,5,0,0,0},
                        {0,9,8,0,0,0,0,6,0},
                        {8,0,0,0,6,0,0,0,3},
                        {4,0,0,8,0,3,0,0,1},
                        {7,0,0,0,2,0,0,0,6},
                        {0,6,0,0,0,0,2,8,0},
                        {0,0,0,4,1,9,0,0,5},
                        {0,0,0,0,8,0,0,7,9}
                        };

    if (tableroValido(tablero1)) {
        cout << "El tablero1 es un sudoku VALIDO" << endl;
    } else {
        cout << "El tablero1 es un sudoku NO VALIDO" << endl;
    }

    if (tableroValido(tablero2)) {
        cout << "El tablero2 es un sudoku VALIDO" << endl;
    } else {
        cout << "El tablero2 es un sudoku NO VALIDO" << endl;
    }

    if (tableroValido(tablero3)) {
        cout << "El tablero3 es un sudoku VALIDO" << endl;
    } else {
        cout << "El tablero3 es un sudoku NO VALIDO" << endl;
    }

    if (tableroValido(tablero4)) {
        cout << "El tablero4 es un sudoku VALIDO" << endl;
    } else {
        cout << "El tablero4 es un sudoku NO VALIDO" << endl;
    }

    return 0;
}
