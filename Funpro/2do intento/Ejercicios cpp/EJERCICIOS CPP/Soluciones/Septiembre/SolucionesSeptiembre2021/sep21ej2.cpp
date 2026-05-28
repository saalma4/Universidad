#include <iostream>
#include <array>
using namespace std;

const int MAX = 20;

typedef array<int,MAX> TArray;

struct TCards
{
    TArray num;
    int quant;
};

int limite()
{
    int a=0;
    for (int i=0;i<=20;i++)
    {
        a=a+i;
    }
    return a;
}

int detectTriaNum (TCards& a)
{
    int sumatotal = 0;
    int pilasend = 0;
    for (int i=0;i<a.quant;i++)
    {
        sumatotal=sumatotal+a.num[i];
    }

    int limit = limite(),
        sum=0,
        cont=1;

    while (sum <= limit && sum != sumatotal)
    {
        sum=sum+cont;

        if (sum == sumatotal)
        {
            pilasend = cont;
        }
        cont++;
    }
    return pilasend;
}

void write (const TCards& a)
{
	for (int i=0;i<a.quant;i++)
	{
		cout<<a.num[i]<<" ";
	}
}

void phaseone (TCards& a)
{
	a.quant++;
	a.num[a.quant-1]=a.quant-1;
	for (int i=0;i<a.quant-1;i++)
	{
		a.num[i]--;
	}
	write(a);
	cout<<endl;
}

bool check (TCards& a)
{
	bool res = true;
	for (int i=0;i<a.quant;i++)
	{
		if (a.num[i]!=i+1)
		{
			res=false;
		}
	}
	return res;
}

void phasetwo (TCards& a)
{
	int nextobj = a.quant-1;
	while (!check(a))
	{
		for (int i=0;i<a.quant;i++)
		{
			if (a.num[nextobj] == nextobj+1)
				{
					nextobj--;
				}
			if (a.num[i] != i+1 && a.num[i] != 1)
			{
				
				a.num[i]--;
				a.num[nextobj]++;
			}
			
		}
		write(a);
				cout<<endl;
	}
}

int main()
{
    TCards cards;
    int montones;

    cout<<"Introduzca la cantidad de montones: ";
    cin>>montones;

    cards.quant = montones;
    cout<<"Escribe los montones: "<<endl;

    for (int i=0;i<cards.quant;i++)
    {
        cin>>cards.num[i];
    } 
    
    int pilasfinales = detectTriaNum (cards);
    
    for (int i=cards.quant;i<pilasfinales;i++)
    {
    	phaseone(cards);
	}

	phasetwo(cards);
	
	return 0;
}
