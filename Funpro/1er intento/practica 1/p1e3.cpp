#include <iostream>

using namespace std;

int main()
{
    int x1, x2;
    cout << "introduzca un numero entero: ";
    cin >> x1;
    cout << "introduzca otro numero entero: ";
    cin >> x2;
    cout << "El valor del primer numero introducido es: " <<  x1 << endl;
    cout << "El valor del segundo numero introducido es: " << x2 << endl;
}
// En el primer caso no tiene ningun prblema ya que se coresponde el tipo 
// de dato introducido con el que se esperaba, en este caso int.
// En el segundo caso, lee bien el primer numero ya que se corresponde 
// a un int, pero sin embargo la palara (la cual no se corresponde con 
// int) no la lee y le asigna un valor inespecificado para almacenarse. 
// En el tercer caso, el primer valor introducido no se corresponde con el tipo 
// int, por lo tanto el programa no funciona mas hasta que se vuelva a correr.