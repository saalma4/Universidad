#include <iostream> 
using namespace std;

bool esPrimo(int& num){
    bool esPrimo = false;
    if(num == 2){
        esPrimo = true;
    }
    if (num > 2){
        for(int i = 2; i < num -1; i++){
            if(num % i == 0){
                esPrimo = false;
            }else{
                esPrimo = true;
            }
        }
    }
    if (num < 2){
        esPrimo = false;
    }
    return esPrimo;
}

int main(){
    int num;
    int mayor = 0;
    cout << "Introduzca una secuencia de enteros positivos acabada en 0: ";
    cin >> num;
    while(num != 0){
        if(num > mayor && esPrimo(num)){
            mayor = num;
        }
        cin >> num;
    }
    if(mayor == 0){
        cout << "No hay ningun primo en la secuencia "<< endl;
    }else{
        cout << "El mayor primo de la secuencia es: " << mayor << endl;
    }
    return 0;
}