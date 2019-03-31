#include <iostream>
#include <cstring>

/*
Да се креира структура Воз во која се чуваат податоци за релацијата по која се движи возот (низа од најмногу 50 знаци), предвиден бројот на километри што треба да се поминат (реален број), како и бројот на патници во возот (цел број).

Потоа да се креирa структура ZeleznickaStanica во која се чуваат податоци за градот во кој се наоѓа (низа од 20 знаци), низа од возови што поаѓаат од станицата (најмногу 30) и бројот на возови (цел број).

Треба да се направи функција со потпис

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)

во која се печати релацијата и бројот на километри на возот што поминува најкратка релација (најмалку километри), а поаѓа од железничката станица од градот што се проследува како влезен аргумент. Ако има повеќе возови со ист најмал број на километри, да се испечати релацијата на последниот таков.
*/

using namespace std;

struct Voz  //Struktura za eden voz
{
    char relacija[50];
    float km;
    int patnici;
};

struct Stanica  //Struktura za stanica
{
    char grad[20];
    Voz vozovi[30]; //Vozovi koisto trgnuvaat od dadenata stan
    int brvozovi;
};

void najkratkaRelacija(Stanica* zs, int n, char* grad)
{
    //Gresno! float min = zs[0].vozovi[0].km;
    int ii,jj,first = 1;
    for( int i=0; i<n; i++)
    {
        if( !strcmp(zs[i].grad,grad) )  //Dali stanica odgovara na vneseniot grad
        {
            float min = zs[i].vozovi[0].km;
            for (int j=0; j<zs[i].brvozovi; j++)
            {
                if(zs[i].vozovi[j].km <= min)   //Minimalni kilometri
                {
                    min = zs[i].vozovi[j].km;
                    ii = i;
                    jj = j;     //Zacuvuvanje na podatocite na posakuvanata stanica
                }
            }
        }
    }
    cout<<"Najkratka relacija: "<<zs[ii].vozovi[jj].relacija<<" ("<<zs[ii].vozovi[jj].km<<" km)";   //Pecatenje na stanicata
}

int main(){

    int n;
	cin>>n; //se cita brojot na zelezlnichki stanici

    char rel[50], gradot[20];

    Stanica zStanica[100];

    for (int i=0;i<n;i++){
        //se citaat infomracii za n zelezlnichkite stanici i se zacuvuvaat vo poleto zStanica
        cin>>zStanica[i].grad;
        cin>>zStanica[i].brvozovi;
        for ( int j=0; j<zStanica[i].brvozovi; j++)
        {
            cin>>zStanica[i].vozovi[j].relacija;
            cin>>zStanica[i].vozovi[j].km;
            cin>>zStanica[i].vozovi[j].patnici;
        }
    }

    char grad[25];
    cin>>grad;

	najkratkaRelacija(zStanica,n,grad);
	return 0;
}
