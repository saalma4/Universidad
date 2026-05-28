#include <iostream>

using namespace std;

int main()
{
    char operador;
    int op1, op2, resultado = 0;
    do
    {
        cout << "Operación (+ - * / &): ";
        cin >> operador;
        if (operador == '&')
        {
            cout << "FIN DEL PROGRAMA.";
        }
        else if ((operador != '+') && (operador != '*') && (operador != '-') && (operador != '/'))
        {
            throw "ERROR. Operación no válida.";
        }
        else
        {
            cout << "Operando 1: ";
            cin >> op1;
            cout << "Operando 2: ";
            cin >> op2;
            if (operador == '+')
            {
                resultado = op1 + op2;
                cout << "Resultado: " << resultado << endl;
            }
            else if (operador == '*')
            {
                resultado = op1 * op2;
                cout << "Resultado: " << resultado << endl;
            }
            else if (operador == '-')
            {
                resultado = op1 - op2;
                cout << "Resultado: " << resultado << endl;
            }
            else  if (operador == '/')
            {
                if (op2 == 0)
                {
                    cout << "Error" << endl;
                }
                else 
                {
                resultado = op1 / op2;
                cout << "Resultado: " << resultado << endl;
                }
            }
            
        }
    }
    while (operador != '&');
}

