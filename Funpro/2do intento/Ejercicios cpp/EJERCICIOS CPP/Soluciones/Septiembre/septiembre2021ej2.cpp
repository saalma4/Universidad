#include <iostream>
#include <array>
using namespace std;
const int MAX=20;
typedef array<int,MAX> TArray;

struct cartas
{
	TArray card;
	int pilenum;
};

void read (cartas& a)
{
	cout<<"Escribe la cantidad de montones:";
	cin>>a.pilenum;
	cout<<"Escribe las cartas de cada monton:";
	for (int i=0;i<a.pilenum;i++)
	{
		cin>>a.card[i];
	}
}

void write(const cartas& a)
{
	for (int i=0;i<a.pilenum;i++)
	{
		cout<<a.card[i]<<" ";
	}
	cout<<endl;
}

void identify(const cartas& a,int& resint)
{
	int totalsum=0,
		x=0;
	resint=0;
	for (int i=0;i<a.pilenum;i++)
	{
		totalsum=totalsum+a.card[i];
	}
	cout<<"suma realizada, suma total de "<<totalsum<<endl;
	for (int j=0;j<=210;j=j+x)
	{
		cout<<x<<" "<<j;
		if (j==totalsum)
		{
			resint=x;
			cout<<" Encontrado";
		}
		cout<<endl;
		x++;
	}
	cout<<"comprobacion realizada"<<endl;
}

void transform1 (cartas& a,int& tot)
{
	for (int x=a.pilenum;x<MAX;x++)
	{
		a.card[x]=0;
	}
	for (int j=0;j<=1+tot-a.pilenum;j++)
	{
		for (int i=0;i<a.pilenum;i++)
		{
			if (a.card[i]!=1)
			{
				a.card[i]--;
				a.card[a.pilenum]++;
			}
		}
		a.pilenum++;
		write(a);
	}
	//cout<<"Transformacion 1 realizada"<<endl;
}

void generateBase (cartas& b,int& tot)
{
	for (int i=0;i<tot;i++)
	{
		b.card[i]=i+1;
	}
}

bool checkEquality (cartas& a,cartas& base)
{
	bool res = true;
	for (int i=0;i<a.pilenum;i++)
	{
		if (a.card[i]!=base.card[i])
		{
			res=false;
		}
	}
	return res;
}

void transform2 (cartas& a,int& tot)
{
	int x=0;
	int i=0;
	bool res;
	cartas cartaB;
	generateBase(cartaB,tot);
	while (!res)
	{
		a.card[i]--;
		a.card[tot-x-1]++;
		if (a.card[tot-x-1]==tot-x)
		{
			x++;
		}
		res = checkEquality(a,cartaB);
		if (a.card[i]==1)
		{
			i++;
		}
		write(a);
		for (int k=0;k<tot;k++)
		{
		//	cout<<"Ejecutando excepcion";
			if ((a.card[k-1]==a.card[k]) && (a.card[k]==k+1))
			{
				a.card[k-1]--;
				a.card[k-2]++;
				//cout<<"Excepcion realizada";
			}
		}
		
	}
}

int main() 
{
	cartas a;
	int resint;
	read(a);
	write(a);
	identify(a,resint);
	cout<<"La suma corresponde a un numero triangular de orden "<<resint<<endl;
	write(a);
	transform1 (a,resint); // comprobado, correcto
	transform2 (a,resint);
	
	return 0;
}

