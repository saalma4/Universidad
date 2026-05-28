#include <iostream>
#include <array>
#include <string>
using namespace std;

const int MAX_PAL_DIST = 15;

typedef array<string,MAX_PAL_DIST> TPalabra;

struct TFrase
{
    TPalabra pal;
    int nPal;
};

bool esta (string& alfa,TFrase& str) // Verifica si la palabra escrita nueva está en el struct
{
    bool res = false;
    for (int i=0;i<str.nPal;i++)
    {
        if (str.pal[i]==alfa)
        {
            res = true;
        }
    }
    return res;
}

bool ordered (const string& str) // Verifica si la palabra está ordenada
{
    char nextChar = 'A';
    int i=0;
    bool res = true;
    while (res && i < int(str.size()))
    {
        if (str[i]>=nextChar)
        {
            nextChar = str[i];
            i++;
        }
        else
        {
            res = false;
        }
    }
    return res;
}

int main()
{
    cout<<"JAVIER MOLINA COLMENERO"<<endl;
    cout<<"INGENIERIA DEL SOFTWARE"<<endl;
    cout<<"PC 112"<<endl;

    string alfa;
    TFrase str;
    str.nPal = 0;

    cout<<"Introduzca el texto (FIN para terminar): ";
    cin>>alfa;

    while (alfa != "FIN")
    {
        if (!esta(alfa,str) && str.nPal < MAX_PAL_DIST)
        {
            str.pal[str.nPal] = alfa;
            str.nPal++;
        }
        cin>>alfa;
    }

    cout<<"Las palabras cuyos caracteres estan ordenados son: "<<endl;

    for (int i=0;i<str.nPal;i++)
    {
        if (ordered(str.pal[i]))
        {
            cout<<str.pal[i]<<" ";
        }
    }
    return 0;
}
