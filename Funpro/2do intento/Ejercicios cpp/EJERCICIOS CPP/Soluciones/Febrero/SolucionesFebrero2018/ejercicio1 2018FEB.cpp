// Ejercicio 1

#include <iostream>
#include <array>

using namespace std;

const unsigned TAM = 9;

typedef unsigned TArray[TAM];
typedef array<unsigned,TAM> TFrec;

// funcion que calcula el valor dominante del array a
int valorDominante(const TArray& a)
{
	int res=-1;
	TArray frec = {};
	for (int i=0;i<TAM;i++)
	{
		for (int j=0;j<TAM;j++)
		{
			if (a[i]==j)
			{
				frec[j]++;
			}
		}
	}
	for (int x=0;x<TAM;x++)
	{
		if (frec[x]>TAM/2)
		{
			res=x;
		}
	}
	return res;
}

int main() {
    TArray a1 = {3,4,3,2,3,1,3,3,1},
           a2 = {4,4,3,2,3,1,3,3,1},
           a3 = {1,3,2,1,4,4,4,4,4};

    cout << "El elemento dominante del primer array es: "
         << valorDominante(a1) << endl;
    cout << "El elemento dominante del segundo array es: "
         << valorDominante(a2) << endl;
    cout << "El elemento dominante del tercer array es: "
         << valorDominante(a3) << endl;

    return 0;
}
