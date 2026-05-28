#include <iostream>
#include <array>
using namespace std;

const int MAXELEMENTS = 100;
typedef array<int, MAXELEMENTS> Elementos;
struct Lista
{
    int nelms = 0;
    Elementos elm;
};

//facil
void eliminar(Lista& v, int x)
{
    int pos = buscar(v, x);
    if (0 <= pos && pos < v.nelms)
    {
        v.elm[pos] = v.elm[v.nelms -1];
        --v.nelms;
    }    
}
//dificil
void eliminar(Lista& v, int x)
{
    int pos = buscar(v, x);
    if (0 <= pos && pos < v.nelms)
    {
        for(int i=pos + 1; )
    }
}

