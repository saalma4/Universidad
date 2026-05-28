#include <iostream>
#include <array>
#include <string>

using namespace std;
const int TAM_CAR = 5,
		  MAX_PAL_DIST = 50,
		  ABC = 26;
		  
typedef array<bool,ABC> TLetters;
typedef array<string,MAX_PAL_DIST> TPal;

struct TFrase
{
	TPal pal;
	int nPal;
};

void start (TLetters& p)
{
	for (int i=0;i<ABC;i++)
	{
		p[i]=false;
	}
}

int countBool (TLetters& a)
{
	int cont=0;
	for (int i=0;i<ABC;i++)
	{
		if (a[i])
		{
			cont++;
		}
	}
	return cont;
}

bool check (string& pattern, TLetters& c)
{
	int lQuant = 0;
	start(c);
	for (int i=0;i<pattern.size();i++)
	{
		lQuant++;
		for (int j=0;j<ABC;j++)
		{
			if (char(pattern[i])==char(j+'A'))
			{
				c[j]=true;
			}
		}
	}
	int lEqual = countBool(c);
	return (lQuant == TAM_CAR && lEqual == TAM_CAR);
}

bool checkBool (string& a,const TLetters& ch)
{
	int cont=0;
	for (int i=0;i<a.size();i++)
	{
		for (int j=0;j<ABC;j++)
		{
			if (char(a[i])==char(j+'A'))
			{
				if (ch[j])
				{
					cont++;
				}
			}
		}
	}
	return (cont>0);
}

void restartPattern (TLetters& c,string& pattern)
{
	for (int i=0;i<pattern.size();i++)
	{
		for (int j=0;j<ABC;j++)
		{
			if (char(pattern[i])==char(j+'A'))
			{
				c[j]=true;
			}
		}
	}
}

int countWords (string& a,TLetters& c)
{
	int cont = 0;
	for (int i=0;i<a.size();i++)
	{
		for (int j=0;j<ABC;j++)
		{
			if (char(a[i])==j+'A')
			{
				if(c[j])
				{
					cont++;
					c[j]=false;
				}
			}
		}
	}
	return cont;
}

void write (TFrase& a,TLetters& list,string& pat)
{
	for (int i=0;i<a.nPal;i++)
	{
		restartPattern(list,pat);
		cout<<a.pal[i]<<" "<<countWords(a.pal[i],list)<<endl;
	}
}

bool esta(const TFrase& a,const string b)
{
	bool res=false;
	for (int i=0;i<a.nPal;i++)
	{
		if (a.pal[i]==b)
		{
			res=true;
		}
	}
	return res;
}

int main() 
{
	string patron,
		   alfa;
	TLetters p;
	TFrase str;
		str.nPal=0;
		
	start(p);
	
	do
	{
		cout<<"Introduzca un patron (long = "<<TAM_CAR<<", sin letras repetidas):";
		cin>>patron;
	} while (!check(patron,p));
	
	cout<<"Introduce un texto (FIN para terminar): ";
	
	cin>>alfa;
	
	while(alfa != "FIN")
	{
		if (checkBool(alfa,p) && !esta(str,alfa))
		{
			str.pal[str.nPal]=alfa;
			str.nPal++;
		}
		cin>>alfa;
	}
	
	write(str,p,patron);
	
	return 0;
}
