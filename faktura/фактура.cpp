#include <stdio.h>
#include <string.h>

/*
Да се креира структура Proizvod во која се чуваат податоци за кодот напрозиводот (низа од 20 знаци), 
единична цена на производ (цел број), бројот на достапни производи кои ги има во еден магацин (цел број) .

Потоа да се креирa структура Narachka во која се чуваат податоци за името лицето кое ја прави нарачката 
(низи од 15 знаци), низа од Proizvodi (максимум 10) кои ги има во нарачката, низа од бројот на нарачани производи за 
секоја производ посебно (максимум10) и бројот на производи во нарачката .

Треба да се направи функција со потпис

void pecatiFaktura(Narachka n)

која што ќе ги отпечати една фактура за една нарачка (n) .

Во фактурата во првиот ред се печати: Faktura za XXXXX, каде XXXXX е името на лицето кое ја прави нарачката.

Ако сите производи може да се нарачаат печатат нарачаните производи, подредени по азбучен ред според кодот 
на производот. Во следните редови, во секој ред посебно се печати кодот на производот, единична цена на производот, 
број на нарачани производи и вкупната цена на производот (сите се одделени со едно празно место) . 
Исто така бројот на достапни производи од тој производ да се ажурира (да се намали за бројот на нарачани производи од тој производ). 
Во последниот ред да се отпечати: Vkupnata suma na fakturata e XXX, каде XXX е вкупната сума за цените за сите нарачани производи.

Ако постои производ кој не може да биде нарачан затоа што во магацинот не се достапни нарачаниот број 
производи тогаш не може да се изготви фактура за нарачката. На екранот да се отпечати: Fakturata ne moze da se izgotvi.
*/

//место за вашиот код

struct Proizvod
{
    char kod[20];   //Ime na proizvodot
    int cena;
    int dostapni_proizvodi; 
};

typedef struct Proizvod Proizvod;

struct Naracka
{
    char ime[15];   //Ime na naracatelot
    Proizvod p[10];
    int naracani[10];   //Sekoj posebno kolku proizvodi
    int n; //Broj na naracani proizvodi
};

typedef struct Naracka Naracka;

/*void sortiraj( Naracka na )
{
    int i,j;
    Proizvod tmp;
    for( i=0; i<na.n; i++)
    {
        for( j=0; j<na.n; j++)
        {
            if( strcmp( na.p[i].kod, na.p[j].kod )==-1 )    //Sporeduvanje kod
            {
                tmp=na.p[i];
                na.p[i]=na.p[j];
                na.p[j]=tmp;
            }
        }
    }
}*/

void pecatiFaktura(Naracka nar)
{
    printf("Faktura za %s\n",nar.ime);

    Proizvod tmp;
    
    int i,j,vkupno=0;
    
    for( i=0; i<nar.n; i++)
    {
        for( j=0; j<nar.n; j++)
        {
            if( strcmp( nar.p[i].kod, nar.p[j].kod )<0 )    //Sporeduvanje kod
            {
                tmp=nar.p[i];
                nar.p[i]=nar.p[j];
                nar.p[j]=tmp;
            }
        }
    }

    int flag=0;
    
    for(i=0; i<nar.n; i++)
    {
        if( nar.naracani[i] > nar.p[i].dostapni_proizvodi)
        {
            printf("Fakturata ne moze da se izgotvi");
            flag=1;
            break;
        }
        else
            printf("%s %d %d %d\n", nar.p[i].kod, nar.p[i].cena, nar.naracani[i], nar.p[i].cena*nar.naracani[i]); 
            
        vkupno+=nar.p[i].cena*nar.naracani[i];
    }
    if(!flag)
        printf("Vkupnata suma na fakturata e %d",vkupno);
}

int main() {

    struct Naracka narachka;

    scanf("%s",&narachka.ime);// внеси го името лицето кое ја прави нарачката
    scanf("%d",&narachka.n);// внеси го бројот на порачани производи во нарачката

    int i;

    for (i = 0; i < narachka.n; ++i) //за секој од нарачаните производи се внесуваат информации
    {
        scanf("%s",&narachka.p[i].kod);// внеси код
        scanf("%d",&narachka.p[i].cena);// внеси единицчна цена
        scanf("%d",&narachka.p[i].dostapni_proizvodi);// внеси број на производи во магацин
    }

    int j;
    
    for (j = 0; j < narachka.n; ++j) //за секој производ се внесува колку такви производи се порачани во нарачката
    {
       scanf("%d",&narachka.naracani[j]);//се внесува број на производи во нарачката
    }

    pecatiFaktura(narachka);// повик на функцијата pecatiFaktura

    return 0;
}
