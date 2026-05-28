#include <iostream>

using namespace std;

int main()
{
   int x1;
   int x2;
   cout << "introduzca dos numeros ";
   cin >> x1 >> x2;
   int aux = x2;
   x2 = x1;
   x1 = aux;
   cout << "Los numeros intercambiados son " << x1 <<" " << x2 <<endl;


    return 0;
}