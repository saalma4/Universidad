#include <iostream>
#include <array>
using namespace std;

const int N = 3;
typedef array<int, N> Tfila;
typedef array<Tfila, N> Tmatriz;

void leerMatriz(Tmatriz m){
    for (int fi = 0; fi < N; fi++){
        for (int co = 0; co < N; co++){
            cin >> m[fi][co];
        }
    }
}
void mostrarMatriz (const Tmatriz& m){
    for (int fi = 0; fi < N; fi++){
        for (int co = 0; co < N; ++co){
            cout << m[fi][co];
        }
        cout << endl;
    }
}
int sumaColumna(const Tmatriz& m, int co){
    int suma = 0;
    for(int i = 0; i < N; ++i){
        suma += m[i][co];
    }
    return suma;
}
int sumarFila (Tfila f){
    int suma = 0;
    for (int i = 0; i < N; ++i){
        suma += f[i];
    }
    return suma;
}
bool columnasValidas(const Tmatriz& m){
    int i = 0;
    while ((i < N) && (sumaColumna(m, i) == 100)){
        ++i;
    }
    return (i == N);
}
bool filasValidas(const Tmatriz& m){
    int i = 0;
    while ((i < N) && (sumarFila(m[i]) == 100))
    {
        ++i;
    }
    return (i == N);
}
bool valoresValidos(const Tmatriz& m){
    int i = 0;
    int j;
    bool valido = true;
    while (valido && i < N){
        j = 0;
        while (valido && j < N){
            if((m[i][j] < 0) || (m[i][j] >= 100)){
                valido = false;
            }
            ++j;
        } 
        ++i;
    }
    return valido;
    
}
bool matrizEstocastica(const Tmatriz& m){
    return (valoresValidos(m) && (filasValidas(m) && columnasValidas(m)));
}
int main (){
    Tmatriz m;

    cout << "Introduzca una matriz de tamaño (" << N << "X" << N << ") por filas: "<< endl;

    leerMatriz(m);

    cout << "La matriz introducida es: " << endl;

    mostrarMatriz(m);

    if(matrizEstocastica(m)){
        cout << "La matriz SI es doblemente estocastica normalizada";
    }else{
        cout << "La matriz No es doblemente estocastica normalizada";
    }
    return 0;
}