#include <iostream> 
#include <iomanip>

using namespace std;

const int SEG_1_MIN = 60;
const int MIN_1_HOR = 60;
const int HORA_1_DIA = 24;
const int DIAS_1_SEM = 7;
const int SEG_1_HORA = SEG_1_MIN * MIN_1_HOR;
const int SEG_1_DIA = SEG_1_HORA * HORA_1_DIA;
const int SEG_1_SEM = SEG_1_DIA * DIAS_1_SEM;

int main()
{
    int segundos, dias, horas, minutos, semanas, segundos_tot, segundos_rest;
    cout << "introduzca los segundos: ";
    cin >> segundos_tot;
    semanas = segundos_tot / SEG_1_SEM;
    segundos_rest = segundos_tot % SEG_1_SEM;
    dias = segundos_rest / SEG_1_DIA;
    segundos_rest = segundos_rest % SEG_1_DIA;
    horas = segundos_rest / SEG_1_HORA;
    segundos_rest = segundos_rest % SEG_1_HORA;
    minutos = segundos_rest / SEG_1_MIN;
    segundos_rest = segundos_rest % SEG_1_MIN;

    cout << segundos_tot << " equivalen a " << "[" << setfill (' ') << setw (3) << semanas << "]" << " semanas, ";
    cout << dias << " dias ";
    cout << setfill ('0') << setw (2) << horas << ":";
    cout << setfill ('0') << setw (2) << minutos << ":";
    cout << setfill ('0') << setw (2) << segundos_rest << endl;






    
}