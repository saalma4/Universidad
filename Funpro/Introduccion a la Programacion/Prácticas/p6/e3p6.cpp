#include <array>
#include <iostream>
using namespace std;

int const TAM = 10;
typedef array<int, TAM> TArray;

void leerSecuencia(){
    int n;
    TArray array {};
    cout << "introduzca una secuencia de digitos terminada en negativo: ";
    do{
        cin >> n;
        if(n >= 0){
            array[n]++;
        }
    }while(n >= 0);
    cout << "la frecuencia de cada digito es: " << endl;
    for(int i = 0; i < 10; i++){
        cout << i << ": " << array[i] << endl;
    }
}

int main(){
    leerSecuencia();
}