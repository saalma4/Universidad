#include <array>
#include <iostream>
using namespace std;

int const TAM = 10;
typedef array<int, TAM> TArray;

void leerSecuencia(){
    int n;
    TArray array = {};
    cout << "introduzca una secuencia de digitos terminada en negativo: ";
    do{
        cin >> n;
        if(n >= 0){
            array[n]++;
        }
    }while(n >= 0);
    int mayor = 0;
    for(int i = 0; i < TAM; i++){
        if(array[i] > mayor){
            mayor = array[i];
        }
    }

    for(int f = mayor; f > 0; f--){
        for(int c = 0; c < TAM; c++){
            if(array[c] >= f){
                cout << "* " ;
            }else{
                cout << "  ";
            }
        }
        cout << endl;
    }
    for(int i = 0; i < TAM; i++){
        cout << i << " ";
    }
}

int main(){
    leerSecuencia();
}