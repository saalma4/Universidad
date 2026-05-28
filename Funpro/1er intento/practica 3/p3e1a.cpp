#include <iostream>

using namespace std;

int main()
{
    int N, total;
    cout << "Introduzca un número: ";
    cin >> N;
    if (N < 0) 
    {
        cout << "Error" << endl;

    }
    else
    {
        for (int i = 0 ; i <= N ; ++i)
        {
            total += i;
        }

        cout << "La suma es: " << total << endl;
    }
}