#include <iostream>

using namespace std;

int main()
{
    char letra_mayus;
    cout << "escriba una letra mayuscula: ";
    cin >> letra_mayus;
    int distancia = int(letra_mayus) - int('A');
   char letra_minuscula = char(int('a') + distancia);
   cout << letra_minuscula << endl;
}