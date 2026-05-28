// Ejercicio 2

#include <iostream>
#include <array>

using namespace std;

const int F = 3,
		  C = 3;
		  
typedef array<array<int,C>,F> TMatrix;

void read (TMatrix& a)
{
	for (int i=0;i<F;i++)
	{
		for (int j=0;j<C;j++)
		{
			cin>>a[i][j];
		}
	}
}

void recalibrate (int& pos,int& index)
{
	if (pos<0 || pos>2)
	{
		pos = index;
	}
}

void buscarCima (TMatrix& a)
{
	int posFU,
		posFD,
		posCU,
		posCD;
		
	for (int i=0;i<F;i++)
	{
		for (int j=0;j<C;j++)
		{
			posFU = i-1;
			posFD = i+1;
			posCU = j-1;
			posCD = j+1;
			
			recalibrate(posFU,i);
			recalibrate(posFD,i);
			recalibrate(posCU,j);
			recalibrate(posCD,j);
			
			if (a[i][j]>=a[posFU][j] && a[i][j]>=a[posFD][j] && a[i][j]>=a[i][posCU] && a[i][j]>=a[i][posCD])
			{
				cout<<"Fila "<<i<<" columna "<<j<<" valor "<<a[i][j]<<endl;
			}
		}
	}
}

int main() 
{
	TMatrix a;
	
	cout<<"Introduce la matriz: "<<endl;
	read(a);
	
	buscarCima(a);
	
	return 0;
}

