#include <iostream>
using namespace std;

bool esPrimo(int& num)
{
	bool res = true;
	if (num==1)
	{
		res=false;
	}
	if (num>=2)
	{
		for (int i = 2; i < num-1 ;i++)
		{
			if (num%i==0)
			{
				res=false;
		 }
		}
	}
	return res;
}

int main() {
	int num,
		mayor=0;
	cout<<"Introduzca una secuencia de enteros positivos acabada en 0: ";
	cin>>num;
	while (num!=0)
	{
		if (num>mayor && esPrimo(num))
		{
			mayor=num;
		}
		cin>>num;
	}
	if (mayor==0)
	{
		cout<<"No hay ningun primo en la secuencia";
	}
	else
	{
		cout<<"El mayor primo es "<<mayor;
	}
	return 0;
}

