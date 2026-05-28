#include <iostream>
#include <array>
using namespace std;

const int TAM=4;

typedef array<array<int,TAM>,TAM> TMatriz;

void readMatrix (TMatriz& a)
{
	cout<<"Escribe la matriz"<<endl;
	for (int i=0;i<TAM;i++)
	{
		for (int j=0;j<TAM;j++)
		{
			cin>>a[i][j];
		}
	}
}

void duplicate (TMatriz& a, TMatriz& b)
{
	for (int i=0;i<TAM;i++)
	{
		for (int j=0;j<TAM;j++)
		{
			a[i][j]=b[i][j];
		}
	}
}

void rotateMatrix (TMatriz& a, TMatriz& b)
{
	for (int i=0;i<TAM;i++)
	{
		for (int j=0;j<TAM;j++)
		{
			b[j][TAM-1-i]=a[i][j];
		}
	}
	duplicate(a,b);
}

void writeMatrix (TMatriz& a)
{
	for (int i=0;i<TAM;i++)
	{
		for (int j=0;j<TAM;j++)
		{
			cout<<a[i][j]<<" ";
			if (a[i][j]<10)
			{
				cout<<" ";
			}
		}
		cout<<endl;
	}
}

int main() {
	TMatriz a,r;
	int rot;
	readMatrix(a);
	
	cout<<"Escribe el numero de rotaciones";
	do
	{
		cin>>rot;
	} while (rot<0);
	
	cout<<"La matriz después de "<<rot<<" rotaciones es:"<<endl;
	for (int c=0;c<rot;c++)
	{
		rotateMatrix (a,r);
	}
	writeMatrix(r);
	
	return 0;
}

/*
00 = 03   10 = 02    20 = 01    30 = 00
01 = 13   11 = 12    21 = 11    31 = 10
02 = 23   12 = 22    22 = 21    32 = 20
03 = 33   13 = 32    23 = 31    33 = 30

1 6 7 9 2 5 15 16 8 7 1 4 3 12 11 10
*/
