#include <iostream>
using namespace std;
int main()
{
int a = 6;
int b = 14;
int auxiliar;
cout << "a vale " << a << " y b vale " << b << endl;
// ¿Qué hacen estas tres sentencias?
auxiliar = a;
a = b;
b = auxiliar;
cout << "a vale " << a << " y b vale " << b << endl;
}
//esta guardando el valor de a en otra variable para poder cambiar el orden de estos y que no se pierda el valor de b.