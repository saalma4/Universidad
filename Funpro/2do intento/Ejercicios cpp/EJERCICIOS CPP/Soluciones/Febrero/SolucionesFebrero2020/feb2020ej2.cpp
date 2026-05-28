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
 

bool checkRow(const matrix& a)
{
	bool resr=true;
	int rValue=0;
	for (int f=0;f<N;f++)
	{
		for (int c=0;c<N;c++)
		{
			if (!checkWrong(a,f,c))
			{
				resr=false;
			}
			rValue=rValue+a[f][c];
		}
		if (rValue!=100)
		{
			resr=false;
		}
		rValue=0;
	}
	return resr;
}

bool checkCol(const matrix& a)
{
	bool resc=true;
	int cValue=0;
	for (int f=0;f<N;f++)
	{
		for (int c=0;c<N;c++)
		{
			if (!checkWrong(a,c,f))
			{
				resc=false;
			}
			cValue=cValue+a[c][f];
		}
		if (cValue!=100)
		{
			resc=false;
		}
		cValue=0;
	}
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
