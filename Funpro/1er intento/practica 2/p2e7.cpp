#include <iostream>

using namespace std;

int main()
{
    int mes, numero_dias;
    bool error = false;
    cout << "Introduzca el número de mes (de 1 hasta 12): ";
    cin >> mes;
    

    switch (mes)
    {
        case 1:
        case 3: 
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            numero_dias = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            numero_dias = 30;
            break;
        case 2: 
            numero_dias = 28;
            break;
            
        default:
            cout << "Mes incorrecto";
            error = true;
            break;
    } 
    if (!error)
    {
        cout << "Este mes tiene " << numero_dias << " dias" << endl;
    }
    
}