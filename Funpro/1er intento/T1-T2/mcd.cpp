#include <iostream>

using namespace std;

int main()
{
    int m, n;
    cout << "Introduce dos numeros: ";
    cin >> m >> n;
    if ((m<=0) && (n<=0))
    {
        cout << "error" << endl;
    }
    else 
    {
        while (m !=n )
        {
            if (m>n)
            {
                m = m-n;
            }
            else
            {
                n = n-m;
            }
        }
       
    cout << "mcd: " << m << endl;
        
    }
}