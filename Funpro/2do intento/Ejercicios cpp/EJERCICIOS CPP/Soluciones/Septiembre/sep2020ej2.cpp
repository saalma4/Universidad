// Examen septiembre 2020
// Ejercicio 2

#include <iostream>
#include <array>

using namespace std;
const int N=5;
typedef array<array<int,N>,N> TMatriz;

bool checkRightFunctionality()
{
	bool res=true;
	if (N<2)
	{
		res=false;
	}
	return res;
}

void start(TMatriz& a)
{
	cout<<"introduce los numeros enteros para una matriz cuadrada de "<<N<<"x"<<N<<":\n";
	for (int i=0;i<N;i++)
	{
		for (int j=0;j<N;j++)
		{
			cin>>a[i][j];
		}
	}
}

void selectIndex(int& fil,int& col)
{
	cout<<"Introduce los indices de la fila y columna: \n";
	do
	{
		cin>>fil>>col;
	} while((fil>=N)||(fil<0)||(col>=N)||(col<0));
}

void addValue(int x,int& r,int p)
{
	if (x>=p)
	{
		r=1;
	}
}

void newMatrix(const TMatriz& a,TMatriz& b,int& fil,int& col)
{
	int F=0,C=0;
	selectIndex(fil,col);
	for (int i=0;i<=N-1;i++)
	{
		addValue(i,F,fil);
		for (int j=0;j<=N-1;j++)
		{
			addValue(j,C,col);
			b[i][j]=a[i+F][j+C];
		}
		C=0;
	}
	F=0;
}

void writeNewMatrix(const TMatriz& b)
{
	cout<<"La nueva matriz es: \n";
	for (int i=0;i<N-1;i++)
	{
		for (int j=0;j<N-1;j++)
		{
			cout<<b[i][j]<<" ";
		}
		cout<<endl;
	}
}

int main() 
{
	TMatriz m1,m2;
	int fil,col,F,C;
	bool res = checkRightFunctionality();
	if(res)
	{
		start(m1);
		newMatrix(m1,m2,fil,col);
		writeNewMatrix(m2);
	}
	else
	{
		cout<<"El valor de la variable N debe ser mayor o igual que 2"<<endl;
	}
	return 0;
}
