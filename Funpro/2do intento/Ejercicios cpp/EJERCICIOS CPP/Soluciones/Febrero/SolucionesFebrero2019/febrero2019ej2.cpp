#include <iostream>
#include <string>
#include <array>
using namespace std;

const int TAM = 6;
typedef array<char, TAM> TFila;
typedef array<TFila, TAM> TMatriz;

void checkPos (char& a,TMatriz& clave,int& coord1,int& coord2)
{
	for (int i=0;i<TAM;i++)
	{
		for (int j=0;j<TAM;j++)
		{
			if (a == clave[i][j])
			{
				coord1 = i;
				coord2 = j;
			}
		}
	}
}

void cifrar (TMatriz& clave,string& texto,string& cifrado)
{
	int f1=0,
		f2=0,
		c1=0,
		c2=0;
	
	cifrado=texto;

	for (int i=0;i<texto.size()-1;i=i+2)
	{
		checkPos(texto[i],clave,f1,c1);
		checkPos(texto[i+1],clave,f2,c2);
		cifrado[i]=clave[f1][f2];
		cifrado[i+1]=clave[c1][c2];
	}
}

int main() {
    TMatriz clave = {{ {{'p','k','a','f','5','v'}},
                       {{'e','o','9','t','y','0'}},
                       {{'s','3','z','7','d','j'}},
                       {{'r','b','n','u','m','1'}},
                       {{'2','w','4','h','8','g'}},
                       {{'c','x','6','q','i','l'}},
                    }};
    string texto = "holayadios";
    string cifrado;

    cifrar(clave,texto,cifrado);

    cout << "El texto cifrado es: " << cifrado << endl;

    return 0;
}
