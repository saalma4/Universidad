#include <iostream>
#include <array>
using namespace std;
const int N = 3;
typedef array<array<int,N>,N> matrix;

void writeMatrix(matrix& a)
{
	cout<<"Introduce los numeros enteros para una matriz cuadrada de "<<N<<"x"<<N<<endl;
	for (int f=0;f<N;f++)
	{
		for (int c=0;c<N;c++)
		{
			cin>>a[f][c];
		}
	}
}

bool checkWrong(const matrix& a,int& f,int& c)
{
	bool res = true;
	if (a[f][c]<0||a[f][c]>=100)
	{
		res=false;
	}
	return res;
}

bool resx(const matrix& a,int& fix1,int& fix2)
{
	bool resm;
	int v=0;
	for (int fix1=0;fix1<N;fix1++)
	{
		for (int fix2=0;fix2<N;fix2++)
		{
			if (!checkWrong(a,fix1,fix2))
			{
				resm=false;
			}
			v=v+a[fix1][fix2];
		}
		if (v!=100)
		{
			resm=false;
		}
		v=0;
	}
	return resm;
}

bool checkRow(const matrix& a)
{
	bool resr=true;
	int i;
	int j;
	resr = resx(a,i,j);
	return resr;
}

bool checkCol(const matrix& a)
{
	bool resc=true;
	int i;
	int j;
	resc = resx(a,j,i);
	return resc;
}

void finalCheck(const matrix& a)
{
	bool resr=checkRow(a);
	bool resc=checkCol(a);
	if (resr && resc)
	{
		cout<<"La matriz introducida SI es doblemente estocastica normalizada";
	}
	else
	{
		cout<<"La matriz introducida NO es doblemente estocastica normalizada";
	}
}

int main() {
	matrix m1;
	writeMatrix(m1);
	finalCheck(m1);
	return 0;
}
