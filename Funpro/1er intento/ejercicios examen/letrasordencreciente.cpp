#include <iostream>
#include <array>
#include <string>
using namespace std;

const int MAX_PAL_DIST = 15;
typedef array<string, MAX_PAL_DIST>Lista;

struct Info{
    Lista elm;
    int nelms;
};

void anyadir (Info& v, const string& palabra){
    if(v.nelms < v.elm.size()){
        v.elm[v.nelms]=palabra;
        v.nelms++;
    }
}

bool orden(const string& palabra){
    bool ok;
    int long = palabra.size();
    int i = 0;
    while (i < long -1 && palabra[i] <= palabra [i+1]){
        
    }
}