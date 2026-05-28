#include <iostream>
#include <array>
#include <string>
using namespace std;

const int LETTERS = 26,
		  MAX_PAL_DIST = 10;
typedef array<bool,LETTERS> TLetters;
typedef array<string,MAX_PAL_DIST> TLista;

struct TFrase
{
	TLista pal;
	int nPal;
};

void start(TLetters& res)
{
	for (int i=0;i<LETTERS;i++)
	{
		res[i]=false;			
	}
}

void patronLetras (const string& pattern, TLetters& res)
{
	//cout<<"Proceso patronLetras ejecutado"<<endl;
	for (int i=0;i<LETTERS;i++)
	{
		for (int j=0;j<pattern.size();j++)
		{
			if (char(pattern[j])==char(i+'A'))
			{
				res[i]=true;			
			}
		}
	}
}

int buscarPalabra (const TLetters& res, const string& str)
{
	int cont=0;
	//cout<<"Proceso buscarPalabra ejecutado"<<endl;
	for (int i=0;i<str.size();i++)
	{
		for (int j=0;j<LETTERS;j++)
		{
			if (res[j] && (str[i]==char(j+'A')))
			{
				//cout<<"ver";
				cont++;	
			}
		}
	}
	return cont;
}

void write (const TFrase& a)
{
	for (int i=0;i<a.nPal;i++)
	{
		cout<<a.pal[i]<<" ";
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

int main() 
{
	string pattern,pal;
	TLetters list;
	TFrase str,sta;
	str.nPal=0;
	sta.nPal=0;
	int cont,
		x;
	
	start(list);
	
	cout<<"Introduzca el patron: ";
	cin>>pattern;
	
	cout<<"Introduzca el valor de x: ";
	cin>>x;
	
	patronLetras(pattern,list);
	
	cout<<"Introduzca el texto (FIN PARA TERMINAR): "<<endl;
	
	cin>>pal;
	while (pal != "FIN")
	{
		if (sta.nPal<MAX_PAL_DIST)
		{
			cont=buscarPalabra(list,pal);
			if (cont>=x && !esta(pal,sta))
			{
				sta.pal[sta.nPal]=pal;
				sta.nPal++;
				str.nPal++;
			}
			str.pal[str.nPal] = pal;
		}
		cin>>pal;
	}
	
	write(sta);
	
	return 0;
}

/*
ERRORES:

No puede poner más de 10 caracteres // Hecho
Las palabras se repiten // Hecho

*/

