#include <array>
#include <iostream>
using namespace std;

int const TAM = 10;
typedef array<int, TAM> TArray;

void leer(TArray &array){
    for(int i = 0; i < TAM; i++){
        cin >> array[i];
    }
}
int mayorDelArray(const TArray &a, int maxAnterior) {
    int mayor = 0;
    for (int x : a) {
        if (x > mayor && x < maxAnterior) {
            mayor = x;
        }
    }
    return mayor;
}
int mostrarMayor(const TArray& a, int maxAnteior){
    TArray ocurrencias{};
    int cnt = 0;
    int mayor = mayorDelArray(a, maxAnteior);
    for(int i = 0; i < TAM; i++){
        if(a[i] == mayor){
            cnt++;
            ocurrencias[i]= 1;
        }else{
            ocurrencias[i]= 0;
        }
    }
    cout << mayor << " aparece " << cnt << " veces, en posiciones ";
    for(int i = 0; i < TAM; i++){
        if(ocurrencias[i] ==1){
            cout << i+1 << " ";
        }
    }
    cout << endl;
    return cnt;
}

int main(){
    TArray a;
    int maxAnterior = 1000000;
    cout << "introduce una sucesion: ";
    leer(a);
    for(int i = 0; i < TAM;){
        int mayor = mayorDelArray(a, maxAnterior);
        maxAnterior = mayor;
        i += mostrarMayor(a, maxAnterior);
    }
}