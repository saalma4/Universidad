#include <iostream>

using namespace std;

int main()
{
    int n1, n2, n3, nmayor;
    cout << "Introduzca tres números enteros: ";
    cin >> n1 >> n2 >> n3;
    if ((n1 == n2) && (n1 == n3))
    {
         cout << "No hay un único numero mayor" << endl;
    }
    else if (n1 == n2)
    {
        if (n1 > n3)
        {
            cout << "No hay un único numero mayor" << endl;
        }
        else
        {
            nmayor = n3;
            cout << "El numero mayor es " << nmayor << endl;
        }
    }
    
    else if (n1 > n2)
    {
        if(n1 == n3)
        {
            cout << "No hay un único numero mayor" << endl;
        }
        else if (n1 > n3)
        {
            nmayor = n1;
            cout << "El numero mayor es " << nmayor << endl;
        }
        else
        {
            nmayor = n3;
            cout << "El numero mayor es " << nmayor << endl;
        }

    }
    
    else 
    {
        if (n2 == n3)
        {
            cout << "No hay un único numero mayor" << endl;
        }
        else if (n2 > n3)
        {
            nmayor = n2;
            cout << "El numero mayor es " << nmayor << endl;
        }
        else 
        {
            nmayor = n3;
            cout << "El numero mayor es " << nmayor << endl;
        }
    }
 
}