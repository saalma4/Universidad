#include <iostream>

using namespace std;

int main()
{
cout << "introduzca un numero ";
int numero;
cin >> numero;
int resto = numero % 2;
bool es_par = (resto == 0);
if(es_par)
{
    cout << "es gay." << endl;
}
else
{
    cout << "es hetero." << endl;
}

}