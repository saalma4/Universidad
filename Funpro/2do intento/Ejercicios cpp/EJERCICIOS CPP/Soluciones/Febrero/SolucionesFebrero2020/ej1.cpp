#include <iostream>
using namespace std;


bool esPrimo(int num){
  int divisor;
  bool res;
  if (num==1){
    res=false;
  }else{
    divisor = 2;
    while ((divisor < num) && (num % divisor != 0)) {
        divisor++;
    }
    res=divisor >= num;
  }
  return res;
}

int main(){

 int num;
 int mayor;
 cout<<"Introduzca una secuencia de numeros enteros positivos (0 para terminar):";

 cin>>num;
 mayor=-1;
 while (num!=0){
   if (esPrimo(num)){
       if(num>mayor){
            mayor=num;
               }
    }
    cin>>num;
}

if(mayor==-1){
  cout<<"No hay ningun primo en la secuencia";

}else{
  cout<<"El mayor primo de la secuencia es: "<<mayor;
}
return 0;



}
