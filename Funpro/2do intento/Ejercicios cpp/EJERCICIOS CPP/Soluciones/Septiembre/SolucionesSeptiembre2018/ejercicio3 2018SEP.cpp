#include <iostream>
#include <array>
using namespace std;
const unsigned TAM = 5;

typedef array<array<char,TAM>,TAM> TMatrix;

void write (TMatrix& a)
{
	for (int i=0;i<TAM;i++)
	{
		for (int j=0;j<TAM;j++)
		{
			do
			{
				cin>>a[i][j];
			} while (a[i][j] != 'x' && a[i][j] != 'o');
		}
	}
}

void read (TMatrix& a)
{
	for (int i=0;i<TAM;i++)
	{
		for (int j=0;j<TAM;j++)
		{
			cout<<a[i][j];
		}
		cout<<endl;
	}
}

void copy (const TMatrix& ant,TMatrix& act)
{
	for (int i=0;i<TAM;i++)
	{
		for (int j=0;j<TAM;j++)
		{
			act[i][j]=ant[i][j];
		}
	}
}

void adjust (int& pos,int& coord)
{
	if (pos<0 || pos>=TAM)
	{
		pos=coord;
	}
}

void ciclo (TMatrix& a,TMatrix& b)
{
	int posXmin,
		posXmax,
		posYmin,
		posYmax;
		
	for (int i=0;i<TAM;i++)
	{
		for (int j=0;j<TAM;j++)
		{
			posXmin = i-1;
			adjust (posXmin,i);
			posXmax = i+1;
			adjust (posXmax,i);
			posYmin = j-1;
			adjust (posYmin,j);
			posYmax = j+1;
			adjust (posYmax,j);
			
			cout<<posXmin<<i<<posXmax<<endl;
			cout<<posYmin<<j<<posYmax<<endl;
			
			if (a[i][j]=='o')
			{
				int cont=0;
				for (int x=posXmin;x<posXmax+1;x++)
				{
					for (int y=posYmin;y<posYmax+1;y++)
					{
						if (a[x][y]=='x')
						{
							cont++;
						}
					}
				}
				cout<<"cont x"<<cont<<endl;
				if (cont==3)
				{
					b[i][j]='x';
				}
			}
			if (a[i][j]=='x')
			{
				int cont=0;
				for (int x=posXmin;x<posXmax+1;x++)
				{
					for (int y=posYmin;y<posYmax+1;y++)
					{
						if (a[x][y]=='x')
						{
							cont++;
						}
					}
				}
				cont=cont-1;
				cout<<"cont x"<<cont<<endl;
				if (cont==2 || cont==3)
				{
					b[i][j]='x';
				}
				else
				{
					b[i][j]='o';
				}
			}
		}
	}
}

int main() 
{
	unsigned gen;
	TMatrix a,b;
	
	cout<<"Introduzca numero de generaciones: ";
	cin>>gen;
	
	cout<<"Introduzca generacion inicial: "<<endl;
	write(a);
	
	cout<<"Generacion 1 (inicial): "<<endl;
	read(a);
	
	copy(a,b);
	
	if (gen>=2)
	{
		for (int i=2;i<=gen;i++)
		{
			
			cout<<"Generacion "<<i<<endl;
			ciclo(a,b);
			read(b);
			copy(b,a);
		}
	}
	
	
	return 0;
}

