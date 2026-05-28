#include <iostream>
using namespace std;
int main()
{
int num1, num2;
cout << "Introduzca el primer número entero: ";
cin >> num1;
cout << "Introduzca el segundo número entero: ";
cin >> num2;
int suma = num1 + num2;
cout << "Primer número: " << num1 << endl;
cout << "Segundo número: " << num2 << endl;
cout << "Resultado (num1 + num2): " << suma << endl;
}
//el programa se desborda porque el int tiene un valor maximo, para el cual no se pueden poner numeros mas grandes.
//para poner numeros mayores habria que poner la variable long.