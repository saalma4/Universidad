#include <iostream>
#include <string>
using namespace std;

const string FIN = "fin";
void leer_palabras(int& contador)
{
    contador = 0;
    string palabra;
    cout << "introduzca una serie de palabras: ";
    cin >> palabra;
    while(palabra != FIN)
    {
        if((palabra[0] == 'a') || (palabra[0] == 'e') ||(palabra[0] == 'i') ||(palabra[0] == 'o') ||(palabra[0] == 'u'))
        {
            contador++;
        }
        cin >> palabra;
    } 
    
}
void mostrar_resultado(int& contador)
{
    cout << "Hay " << contador << " palabras que empiezan por vocal.";
}
int main()
{
    int cont;
    leer_palabras(cont);
    mostrar_resultado(cont);
}