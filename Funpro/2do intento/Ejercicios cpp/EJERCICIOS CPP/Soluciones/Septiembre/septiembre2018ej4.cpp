#include <iostream>
#include <array>
#include <string>

using namespace std;
const int MAX_PAL_DIST = 50;
const int ABC = 26;

typedef array<bool,ABC> TLetters;
typedef array<string,MAX_PAL_DIST> TPal;

struct TFrase
{
	TPal pal;
	int nPal;
};

void start(TLetters& a)
{
	for (int i=0;i<ABC;i++)
	{
		a[i]=false;
	}
}

void patterno (const string& a,TLetters& list,int& cont)
{
	//cout<<"Subprograma patterno ejecutado"<<endl;
	cont = 0;
	for (int i=0;i<a.size();i++)
	{
		for (int j=0;j<ABC;j++)
		{
			if (char(a[i])==char(j+'A'))
			{
				if (!list[j])
				{
					cont++;
				}
				list[j]=true;
			}
		}
	}
}

bool esta (const string& a,const TFrase& sta)
{
	bool res=false;
	for (int i=0;i<sta.nPal;i++)
	{
		if (a==sta.pal[i])
		{
			res=true;
		}
	}
	return res;
}

bool locograma (const string& a,const TLetters& list,const int& contador,const int& tot)
{
	//cout<<"Subprograma locograma ejecutado"<<endl;
	int counter=0;
	TLetters listA;
	start(listA);
	for (int i=0;i<a.size();i++)
	{
		for (int j=0;j<ABC;j++)
		{
			if (char(a[i])==char(j+'A'))
			{
				listA[j]=true;
			}
		}
	}
	
	return (list == listA && tot == a.size());
}

int main() 
{
	string alfa,pattern;
	TFrase starter,res;
	starter.nPal=0;
	res.nPal=0;
	int contador=0;
	TLetters boo;
	
	start(boo);
	
	cout<<"Escribe un texto (FIN para terminar): ";
	cin>>pattern;
	
	patterno(pattern,boo,contador);
	int totalLetras = pattern.size();
	
	cin>>alfa;
	
	while (alfa!="FIN")
	{
		starter.pal[starter.nPal]=alfa;
		starter.nPal++;		
		cin>>alfa;
	}
	
	for (int i=0;i<starter.nPal;i++)
	{
		if (locograma(starter.pal[i],boo,contador,totalLetras)&&!esta(starter.pal[i],res))
		{
			res.pal[res.nPal]=starter.pal[i];
			res.nPal++;
		}
	}
	
	for (int i=0;i<res.nPal;i++)
	{
		cout<<res.pal[i]<<" ";
	}
	return 0;
}

// SACAS LAS COSAS DE TUS CASAS Y LUEGO ME DICES CASAS Y CCSAS SSSAS SIN SENTIDO FIN

