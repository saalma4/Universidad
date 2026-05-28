#include <iostream>
#include <string>
using namespace std;

void leer_valor(string& valor){
    cout << "Introduzca un valor numerico: ";
    getline(cin, valor);
}
int string_to_int(const string& valor){
    int res = 0;
    for (int i = 0; i < int(valor.size()); ++i){
        res = res * 10 + (int(valor[i]) - '0');
    }
    return res;
}
void mostrar_entrada(string& valor){
    cout << "Entrada: " << valor << endl;
}
void mostrar_valor(int valor){
    cout << "Valir: " << valor << endl;
}
void mostrar_doble(int res){
    cout << "Doble: " << res << endl;
}
void mostrar_resultado(string& cadena, int valor, int doble){
    mostrar_entrada(cadena);
    mostrar_valor(valor);
    mostrar_doble(doble);

}

int main(){
    string valor;
    leer_valor(valor);
    int resultado = string_to_int(valor);
    int doble = resultado * 2;;
    mostrar_resultado(valor, resultado, doble);
    
}