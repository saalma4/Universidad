#include <iostream>
#include <array>
using namespace std;

const int TAM = 7;
typedef array <int, TAM> Fila;
typedef array <Fila, TAM> Meitrix;

void leer (Meitrix& m){
    for(int f = 0; f < int(m.size()); f++){
        m[f][0]=1;
        m[0][f]=1;
    }
}
void construir (Meitrix& m){
    for (int f = 1; f < TAM-1 ;f++){
        for(int c = 1;c < TAM-f; c++){
            m[f][c]=m[f][c-1]+m[f-1][c];
        }
    }
}
void mostrar (const Meitrix& m){
    cout << "Resultado: " << endl;
    for(int f=0;f<int(m.size());f++){
        for(int c=0;c<int(m[f].size());c++){
            cout<<m[f][c]<<" ";
        }cout<<endl;
    }
}
int main(){
    Meitrix m={{}};
    leer(m);
    construir(m);
    mostrar(m);
}
