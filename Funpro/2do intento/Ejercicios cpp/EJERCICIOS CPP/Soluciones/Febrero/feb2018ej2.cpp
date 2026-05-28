// Examen febrero 2018, ejercicio 2

#include <iostream>
#include <array>
using namespace std;

const int F=3;
const int C=3;

typedef array<array<int,C>,F> matrix;

void writeMatrix(matrix& a)
{
	cout<<"Escribe la matriz "<<F<<"x"<<C<<endl;
	for (int f=0;f<F;f++)
	{
		for (int c=0;c<C;c++)
		{
			do
			{
				cin>>a[f][c];
			} while (a[f][c]<0);
		}
	}
}

void addValue(int& a,int& b,int limit)
{
	a=b+1;
	if (a==limit)
	{
		a=b;
	}
}

void quitValue(int& a,int& b,int limit)
{
	a=b-1;
	if (a==-1)
	{
		a=b;
	}
}

void checkNum(const matrix& a)
{
	cout<<"Las cimas de la matriz son:\n";
	int cima;
	int posF1,posC1,posF2,posC2;
	for (int f=0;f<F;f++)
	{
		for (int c=0;c<C;c++)
		{
			addValue(posF1,f,F);
			addValue(posC1,c,C);
			quitValue(posF2,f,F);
			quitValue(posC2,c,C);
			if((a[f][c]>=a[posF1][c])&&(a[f][c]>=a[posF2][c])&&(a[f][c]>=a[f][posC1])&&(a[f][c]>=a[f][posC2]))
			{
				cout<<"Fila "<<f<<" columna "<<c<<" valor "<<a[f][c]<<endl;
			}
		}
	}
}

int main() {
	matrix a;
	writeMatrix(a);
	checkNum(a);
	return 0;
}
