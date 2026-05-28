#include <iostream>

using namespace std;

// diapositiva 37

int main()
{
   
    cout << "Introduzca dos numeros y una letra: ";
    int x;
    int y;
    char c;
    cin >> x >> y >> c;
    bool condicion_1 = (x == 3) || (x == 4) || (x == 5) || (x == 6) || (x == 7);
    bool condicion_2 = (x == 1) || (x == 2) || (x == 3) || (x == 7) || (x == 8) || (x == 9);
    bool condicion_3 = (x == 1) || (x == 3) || (x == 5) || (x == 7) || (x == 9);
    bool condicion_4 = (x == 2) || (x == 5) || (x == 6) || (x == 7) || (x == 8) || (x == 9);
    bool condicion_5 = ((x == 3) || (x == 4) || (x == 6) || (x == 8) || (x == 9)) && ((y == 6) || (y == 7) || (y == 8) || (y == 3));
    bool condicion_6 = (x < 10) && (y < 10);
    bool condicion_7 = (x % y!= 0);
    bool condicion_8 = (int(c) >= int('A')) && (int(c) <= int('Z'));
    bool condicion_9 = ((int(c) >= int('A')) && (int(c) <= int('Z'))) || ((int(c) >= int('a')) && (int(c) <= int('z')));
    bool condicion_10 = ((int(c) >= int('A')) && (int(c) <= int('Z'))) || ((int(c) >= int('a')) && (int(c) <= int('z'))) || ((int(c) <= int('9') && (int(c) >= int('0'))));
    cout << boolalpha << condicion_1 <<  " " << boolalpha << condicion_2 << " " << boolalpha << condicion_3 << " " << boolalpha
     << condicion_4 << " " << boolalpha << condicion_5  << " " << boolalpha << condicion_6 << " " << boolalpha << condicion_7 << 
      " " << boolalpha << condicion_8 << " " <<  boolalpha << condicion_9 << " " <<
       boolalpha << condicion_10 << " " <<  endl;

}