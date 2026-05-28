#include <iostream>
using namespace std;


bool esPrimo(int num){
    int divisor;
    bool respuesta;
    if(num == 1){
        respuesta = false;
    }else{
        divisor = 2;
        while(divisor < num && num % divisor != 0){
            divisor++;
        }
        respuesta = divisor >= num; 
    }

}
 int main(){
    int num;
    int mayor;

    cout << "Introduzca ua secuencia de numeros enteros positivos (0 para terminar)";

    cin >> num;
    mayor = -1;
    while(num != 0){
        if(esPrimo(num)){
            if(num > mayor){
                mayor = num;
            }
        }
        cin >> num;
    }
    
    if(mayor == -1){
        cout << "No hay ningun primo en la secuencia";
    }else{
        cout << "El mayor primo de la secuencia es " << mayor;
    }
    return 0;
}

