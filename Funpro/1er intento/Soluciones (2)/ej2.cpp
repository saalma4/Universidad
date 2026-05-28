/*
 * ej2.cpp
 *
 *  Nombre: Mónica Pinto
 */

#include <iostream>
#include <array>
#include <string>

using namespace std;

bool esCorrecto(const string &cad){
    int i =0, tam;

    tam = int(cad.size());
    while (i<tam && cad[i]>='0' && cad[i]<='9'){
        i++;
    }

    return i >= tam;
}

void leerSeccion(string &cad, int l){
    do{
        cout << "(" << l << " digitos): ";
        cin >> cad;
    }while (int(cad.size()) != l || !esCorrecto(cad));
}

int convertirNum(char car){
    return int(car)-int('0');
}

char convertirChar(int num){
    return char(num + int('0'));
}

char calcularCodigo(const string &isbn){
    int calculo;
    char control;

    calculo = 0;
    for (int i=0; i<int(isbn.size()); i++){
        calculo = calculo + convertirNum(isbn[i])*(i+1);
    }

    calculo = calculo%11;
    if (calculo == 10){
        control = 'X';
    }else{
        control = convertirChar(calculo);
    }

    return control;
}

int main() {
    string grupo, editor, libro, isbn;
    char control;

    //Lee los codigos por separado
    cout << "Introduzca codigo del grupo ";
    leerSeccion(grupo,1);

    cout << "Introduzca codigo del editor ";
    leerSeccion(editor,4);

    cout << "Introduzca codigo del libro ";
    leerSeccion(libro,4);

    //Construye el ISBN
    isbn = grupo + editor + libro;

    //Calcula el codigo de control
    control = calcularCodigo(isbn);

    //Aniade el codigo de control al isbn
    isbn = isbn + control;

    cout << "El ISBN del libro es: " << isbn << endl;
}
