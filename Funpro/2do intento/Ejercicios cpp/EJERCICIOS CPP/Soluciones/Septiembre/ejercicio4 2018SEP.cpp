#include <iostream>
#include <array>
#include <string>
using namespace std;

const int MAX_PAL_DIST = 50,
		  ABC = 26;

typedef array<string,MAX_PAL_DIST> TPal;
typedef array<bool,ABC> TLetters;

struct TFrase
{
	TPal pal;
	int nPal;
};

void startLetters (TLetters& a)
{
	for (int i=0;i<ABC;i++)
	{
		a[i]=false;
	}
}

void lettersPattern(TLetters& a,string& patron,int& cont)
{
	cont=0;
	for (int i=0;i<int(patron.size());i++)
	{
		for (int j=0;j<ABC;j++)
		{
			if (patron[i]==char(j+'A'))
			{
				if (!a[j])
				{
					a[j]=true;
					cont++;
				}
			}
		}
	}
}

bool esta(string& a,TFrase& str)
{
	bool res=false;
	for (int i=0;i<str.nPal;i++)
	{
		if (a==str.pal[i])
		{
			res=true;
		}
	}
	return res;
}

bool check (TLetters& a,TLetters& x)
{
	bool res = true;
	for (int i=0;i<ABC;i++)
	{
		if (a[i]!=x[i])
		{
			res=false;
		}
	}
	return res;
}

void locograma (string& patron,TFrase& str)
{
	int plength = int(patron.size()),
		cont2=0,
		cont1=0,
		dist;
	string base;
	TLetters a,newer;
	startLetters(a);
	startLetters(newer);
	lettersPattern(a,patron,dist);
	
	for (int i=0;i<str.nPal;i++)
	{
		base = str.pal[i];
//		cout<<base<<" ";
		for (int k=0;k<base.size();k++)
		{
			for (int j=0;j<ABC;j++)
			{
				if (base[k]==char(j+'A'))
				{
					if(newer[j]==false)
					{
						newer[j]=true;
						cont1++;
					}
				}
			}
			cont2++;
		}
//		for(int m=0;m<ABC;m++)
//		{
//			cout<<a[m]<<newer[m]<<" ";
//		}
//		cout<<endl;
//		cout<<cont1<<" "<<dist<<" "<<cont2<<" "<<plength<<" "<<check(a,newer)<<endl;
		if (check(a,newer) && cont2 == plength)
		{
			cout<<str.pal[i]<<" ";
		}
		startLetters(newer);
		cont2=0;
		cont1=0;
	}
	
}

void compare (TFrase& ori,TFrase& str)
{
	for (int i=0;i<ori.nPal;i++)
	{
		if (!esta(ori.pal[i],str))
		{
			str.pal[str.nPal]=ori.pal[i];
			str.nPal++;
		}
	}
}

int main() 
{
	string patron,alfa;
	TFrase ori,
		   str;
	ori.nPal=0;
	str.nPal=0;
	cout<<"Introduzca un texto (FIN para terminar): ";
	
	cin>>patron; 
	
	cin>>alfa;
	while (alfa != "FIN")
	{
		ori.pal[ori.nPal] = alfa;
		ori.nPal++;
		cin>>alfa;
	}
	
	compare(ori,str);
	
	cout<<"Las palabras que son locogramas son: ";
	locograma(patron,str);
	
	return 0;
}

// SACAS LAS COSAS DE TUS CASAS Y LUEGO ME DICES CASAS Y CCSAS SSSAS SIN SENTIDO FIN 
