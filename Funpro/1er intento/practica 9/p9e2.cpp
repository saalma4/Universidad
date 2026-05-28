#include <iostream>
#include <array>
using namespace std;

const int NFILAS = 5;
const int NCOLUMNAS = 7;

typedef array <int, NFILAS> Fila;
typedef array <Fila, NCOLUMNAS> SalaCine;

void inicializar (SalaCine& sc){

}
void mostrar(const SalaCine& sc){

}
void comprar_ticket_consecutivo(SalaCine& sc, int fila_1, int fila_2, int n,
bool& ok, int& fil_sel, int& col_sel){

}
void cancelar_ticket(SalaCine& sc, int fila, int columna, bool& ok){

}

int main(){
    SalaCine m;
    inicializar(m);
    mostrar(m);
    comprar_ticket_consecutivo(m)
}