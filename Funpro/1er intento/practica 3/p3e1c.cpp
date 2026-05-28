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
        if (i <= N)
        {
        
            do 
            {
                total += i;
                ++i;
            }
            while (i <= N);
        }
        
        cout << "La suma es: " << total << endl;
    }

}