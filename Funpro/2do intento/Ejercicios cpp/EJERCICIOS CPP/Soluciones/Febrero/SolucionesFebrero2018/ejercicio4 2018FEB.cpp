// Ejercicio 4

#include <iostream>
#include <array>
#include <string>

using namespace std;

const int MAX_CAR_PATRON = 5;
const int MAX_PAL_DIST = 50;
const int ABC = 26;

typedef array<char,ABC> TPattern;
typedef array<string,MAX_PAL_DIST> TPal;

struct TPatron
{
	TPattern let;
	int nLet;
};

struct TFrase
{
	TPal pal;
	int nPal;
};

bool encounter (char& a,string& b)
{
	bool res = false;
	for (int i = 0;i<b.size();i++)
	{
		if (a==b[i])
		{
			res=true;
		}
	}
	return res;
}

bool already (string& a,TFrase& b)
{
	bool res=false;
	for (int j=0;j<b.nPal;j++)
	{
		if (a==b.pal[j])
		{
			res=true;
		}
	}
	return res;
}

bool detect (string& alfa,TPatron& c)
{
	bool res=false;
	for (int i=0;i<alfa.size();i++)
	{
		for (int j=0;j<c.nLet;j++)
		{
			if (char(alfa[i])==c.let[j])
			{
				res=true;
			}
		}
	}
	return res;
}

bool esta (char x,TPatron& c)
{
	bool res=false;
		for (int j=0;j<ABC;j++)
		{
			if (char(x)==char(j+'A'))
			{
				for (int v=0;v<c.nLet;v++)
				{
					if (x==c.let[v])
					{
						res=true;
					}
				}
			}
		}
	return res;
}

void pattern (TPatron& a,string& pal)
{
	for (int i=0;i<pal.size();i++)
	{
		if (!esta(pal[i],a))
		{
			a.let[a.nLet]=pal[i];
			a.nLet++;
		}
	}
}

int main() 
{
	string patron,pal;
	TPatron a;
	TFrase str;
	a.nLet=0;
	str.nPal=0;
	do
	{
		cout<<"Introduzca un patron (longitud maxima = "<<MAX_CAR_PATRON<<"): ";
		cin>>patron;
	} while (patron.size()>MAX_CAR_PATRON);
	
	pattern(a,patron);
	
	cout<<"Introduzca un texto (FIN para terminar): ";
	
	cin>>pal;
	
	while (pal != "FIN")
	{
		if (!already(pal,str))
		{
			str.pal[str.nPal] = pal;
			str.nPal++;
		}
		cin>>pal;
	}
	
	cout<<"Palabras que comparten letra con las letras del patron: "<<endl<<endl;
	
	for (int i=0;i<a.nLet;i++)
	{
		cout<<a.let[i]<<" ";
		for (int j=0;j<str.nPal;j++)
		{
			if (encounter(a.let[i],str.pal[j]))
			{
				cout<<str.pal[j]<<" ";
			}
		}
		cout<<endl;
	}
	
	return 0;
}

