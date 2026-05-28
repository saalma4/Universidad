#include <iostream>
#include <array>
using namespace std;

const int TAM=10;
typedef array<int,TAM> TNum;

struct TLista
{
	TNum num;
	int cNum;
};

bool esta (int& alfa,TLista& a)
{
	bool res=false;
	for (int i=0;i<a.cNum;i++)
	{
		if (alfa == a.num[i])
		{
			res=true;
		}
	}
	return res;
}

void write (TLista& a)
{
	int alfa;
	a.cNum=0;
	
	cin>>alfa;
	while (alfa != 0)
	{
		if (!esta(alfa,a) && a.cNum<TAM)
		{
			a.num[a.cNum]=alfa;
			a.cNum++;
		}
		cin>>alfa;
	}
}

void read (const TLista& a)
{
	for (int i=0;i<a.cNum;i++)
	{
		cout<<a.num[i]<<" ";
	}
	cout<<endl;
}

void trio(TLista& l1,TLista& l2,TLista& l3)
{
	for (int i=0;i<l1.cNum;i++)
	{
		for (int j=0;j<l2.cNum;j++)
		{
			for (int k=0;k<l3.cNum;k++)
			{
				if ((l1.num[i]+l2.num[j])==l3.num[k])
				cout<<l1.num[i]<<" "<<l2.num[j]<<" "<<l3.num[k]<<endl;
			}
		}
	}
}

int main() 
{
	TLista a1,
		   a2,
		   a3;
	
	cout<<"Introduzca Lista 1: ";
	write(a1);
	
	cout<<"Introduzca Lista 2: ";
	write(a2);
	
	cout<<"Introduzca Lista 3: ";
	write(a3);
	
	cout<<"Lista 1: ";
	read(a1);
	
	cout<<"Lista 2: ";
	read(a2);
	
	cout<<"Lista 3: ";
	read(a3);
	
	cout<<"Los trios de numeros son: "<<endl;
	trio(a1,a2,a3);
	
	return 0;
}
