#include <iostream>
#include <array>
using namespace std;

const int N=3;

typedef array<int,N> TFila;
typedef array<TFila,N> TMatriz;
 
void leerMatriz (TMatriz& m){
for (int fi=0; fi<N; fi++){
    for (int co=0; co<N; co++){
        cin>>m[fi][co];
    }

}
}
void mostrarMatriz (const TMatriz& m){
for (int fi=0; fi<N; fi++){
    for (int co=0; co<N; co++){
        cout<<m[fi][co]<<" ";
    }
    cout<<endl;
}
}

int sumaColumna(const TMatriz& m, int col ){
    int suma=0;
    for (int i=0; i<N; i++){
        suma=suma+m[i][col];
    }
    return suma;
}


bool columnasValidas(const TMatriz& m){
int i=0;
while ((i<N)&& (sumaColumna(m,i)==100)){
    i++;
}
return (i==N);
}


int sumaFila(TFila f){
    int suma=0;
    for (int i=0; i<N; i++){
        suma=suma+f[i];
    }
    return suma;
}



bool filasValidas(const TMatriz& m){
int i=0;
while ((i<N)&& (sumaFila(m[i])==100)){
    i++;
}
return (i==N);
}
bool valoresValidos(const TMatriz& m){
int i=0;
int j;
bool valido=true;
while (valido && i<N){
    j=0;
    while (valido && j<N){
            if((m[i][j]<0)||(m[i][j]>=100)){
                valido=false;
            }

    j++;
    }
i++;
}
return valido;
}
bool matrizEstocastica(const TMatriz& m){
 return (valoresValidos(m)&&(filasValidas(m)&&columnasValidas(m)));
}

int main(){
TMatriz m;

cout<<"Introduzca una matriz de tama�o ("<<N<<"X"<<N<<") por filas:"<< endl;

leerMatriz(m);

cout<<"La matriz introducida es:"<<endl;

mostrarMatriz(m);

if(matrizEstocastica(m)){

    cout<<"La matriz SI es doblemente estocastica normalizada";

}else{

    cout<<" La matriz NO es doblemente estocastica normalizada";
}
return 0;
}
