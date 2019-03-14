#include <iostream>
#include <stdio.h>

/*
Да се напише програма во која од стандарден влез се вчитува N (бројот на производи), а потоа се вчитуваат податоците за N производи (име, цена, количина). Програмата треба на стандарден излез да ја отпечати листата на купени производи и вкупната сума која треба да се плати во следниот облик (пример):

1. Flips    10.00 x 3 = 30.00
2. CocaCola    75.00 x 2 = 150.00
3. ChokoBanana  5.00 x 10 = 50.00
Total: 230.00
*/

using namespace std;

typedef struct ks //Struktura so baranite elementi
{
    char ime[100];
    int cena;
    int kolicina;
}kosnicka;

int main()
{
    int n;

    cin>>n;

    kosnicka k[n+1]; //Kreiranje niza od strukturi

    for( int i=0; i<n ; i++)
    {
        cin>>k[i].ime>>k[i].cena>>k[i].kolicina; //Vnesuvanje na i-tite elementi
    }

    int total=0;

    for( int i=0; i<n ; i++) //Pecatenje po baraniot redosled
    {
        cout<<i+1<<". "<<k[i].ime<<"\t";
        cout<<k[i].cena<<".00 x "<<k[i].kolicina<<" = ";
        cout<<k[i].cena*k[i].kolicina<<".00"<<endl;
        total+=k[i].cena*k[i].kolicina;
    }
    cout<<"Total: "<<total<<".00";
    
    return 0;
}
