#include <iostream>
using namespace std;

const float GRADOS_A_RADIANES = 0.01745;

int main(){

    int grados, minutos,  segundos, total;
    float radianes, minutos_a_grados, segundos_a_grados;

    cout<<"Programa para convertir de grados a radianes.\n Introduzca un ángulo en grados, minutos y segundos: " << endl;
    cin>> grados;
    cin>>minutos;
    cin>>segundos;
    minutos_a_grados = minutos/60;
    segundos_a_grados = segundos/3600;
    total = grados + minutos_a_grados + segundos_a_grados;
    radianes = total * GRADOS_A_RADIANES;
    cout<<"El ángulo en radianes sería: ";
    cout<<radianes << endl;
    
}
