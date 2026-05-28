#include <iostream>

using namespace std;

//control 1 noviembre 2020

int main()
{
    int contador = 0, vmax = 0;
    char frase;
    bool isIn = false;
    bool haycomillas = false;
    cout << "introduzca una frase acabada en punto: ";
    cin.get(frase);
    while (frase != '.')
    {
        if ((!haycomillas) && (frase == '"'))
        {
            haycomillas = true;
        }

        if ((isIn) && (frase == '"'))
        {
            isIn = false;
            if (contador > vmax)
            {
            vmax = contador;
            }
            contador = 0;
        }
        else if (frase == '"')
        {
            isIn = true;
        }

        if ((isIn) && (frase != '"'))
        {
            contador++;    
        }
        cin.get(frase);
    }
    if ((!isIn) && (haycomillas))
    {
        cout << "la cita mas larga tiene " << vmax << " caracteres." << endl;

    }
    else if (isIn)
    {
        cout << "error cita inacabada." << endl;
    }
    else 
    {
        cout << "el texto no tiene citas." << endl;
    }

}