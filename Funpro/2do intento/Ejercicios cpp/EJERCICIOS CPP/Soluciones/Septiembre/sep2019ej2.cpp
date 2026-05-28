#include <iostream>
#include <string>
#include <array>
using namespace std;

const int FILAS=7;
const int COLUMNAS=12;
typedef array<char, COLUMNAS> TFila;
typedef array<TFila, FILAS> TMatriz;

int diametro(const TMatriz& imagen)
{
	int mayor = 0;
	int alfa = 0,
		cont = 0,
		valorinicial,
		valorfinal;
	for (int i=0;i<FILAS;i++)
	{
		for (int j=0;j<COLUMNAS;j++)
		{
			if (imagen[i][j]=='*')
			{
				cont++;
				switch (cont)
				{
					case 1: valorinicial = j;
					break;
					case 2: valorfinal = j;
					break;
				}
			}
		}
		if (cont == 2)
		{
			alfa = valorfinal-valorinicial-1;
		}
		if (alfa>mayor)
		{
			mayor = alfa;
		}
		cont=0;
	}
	return mayor;
}

int main() {

    TMatriz imagen1 = {{{{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}},
                        {{' ',' ','*','*',' ',' ',' ',' ',' ',' ',' ',' '}},
                        {{' ','*',' ',' ','*',' ',' ',' ',' ',' ',' ',' '}},
                        {{'*',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' '}},
                        {{'*',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' '}},
                        {{' ','*',' ',' ','*',' ',' ',' ',' ',' ',' ',' '}},
                        {{' ',' ','*','*',' ',' ',' ',' ',' ',' ',' ',' '}},
                    }};
    TMatriz imagen2 = {{{{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}},
                        {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}},
                        {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}},
                        {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}},
                        {{' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' '}},
                        {{' ',' ',' ',' ',' ',' ',' ',' ','*',' ','*',' '}},
                        {{' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' '}},
                    }};


    cout << "Diametro circunferencia1: " << diametro(imagen1)<< endl;

    cout << "Diametro circunferencia2: " << diametro(imagen2)<< endl;


    return 0;
}
