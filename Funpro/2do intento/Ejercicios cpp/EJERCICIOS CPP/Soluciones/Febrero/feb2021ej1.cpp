#include <iostream>
#include <array>
using namespace std;
const int M=5; // Columnas
const int N=4; // Filas

typedef array<array<int,M>,N> TMatrix;

void start(TMatrix& a,int& x)
{
	cout<<"Escribe la matriz "<<x<<":"<<endl;
	for(int i=0;i<N;i++)
	{
		for (int j=0;j<M;j++)
		{
			cin>>a[i][j];
		}
	}
	x++;
}

bool sonEspejo (TMatrix& a,TMatrix& b)
{
	bool res = true;
	int i=0,
		j=0;

	do
	{
		cout<<"Proceso ejecutado"<<endl;
		while(j<=M/2+1)
		{
			if (a[i][j]!=b[i][M-j])
			{
				res = false;
			}
			j++;
		}
		j=0;
		i++;
	} while (res || i<N);
	return res;
}

int main() {
	int x=1;
	TMatrix a,b;
	start(a,x);
	start(b,x);
	if (sonEspejo(a,b))
	{
		cout<<"Las dos matrices son espejo."<<endl;
	}
	else
	{
		cout<<"Las dos matrices NO son espejo."<<endl;
	}
	
	return 0;
}
// 1 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
