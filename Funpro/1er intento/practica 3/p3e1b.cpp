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
        int i = 0;
        while (i <= N)
        {
            total += i;
            ++i;
        }
         cout << "La suma es: " << total << endl;
    }

}