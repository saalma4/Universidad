#include <iostream>
#include <string>
using namespace std;

void leer_cadena(string& cadena){
    cout << "Introduzca una cadena: ";
    getline(cin, cadena);
}
bool es_vocal(char c)
{
    return (c == 'a') || (c == 'e') || (c == 'i')
    || (c == 'o') || (c == 'u');
}
string eliminar_vocales(string& cadena){
    string aux = "";
    for(int i = 0; i < int(cadena.size()); ++i){
        if(!es_vocal(cadena[i])){
            aux += cadena[i];
        }

    }
    return aux;
}
void mostrar_original(string& cadena){
    cout << "Cadena original: " << cadena << endl;
}
void mostrar_cresultado(string& cadena){
    cout << "Cadena resultado : " << cadena << endl;
}
void mostar_resultado(string& cadena, string& aux){
    mostrar_original(cadena);
    mostrar_cresultado(aux);
}
int main(){
    string cadena;
    leer_cadena(cadena);
    string aux = eliminar_vocales(cadena);
    mostar_resultado(cadena, aux);
}
