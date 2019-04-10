#include <stdio.h>
#include <string.h>

/*
Во програмскиот јазик C да се креира структура Pacient и истата треба да содржи: (5 поени)

Име и презиме на пациентот ( низа од макс. 100 знаци)
Дали е здраствено осигуран (1-да, 0-не)
Број на прегледи во текот на последниот месец (цел број)
Да се креира структура MaticenDoktor, која во себе содржи: (5 поени)

Име на докторот (низа од 100 знаци)
Број на пациенти (цел број)
Листа од пациенти (низа од максимум 200 елементи од структурата Pacient)
Цена на преглед (децимален број)
Да се креираат метода najuspesen_doktor, која прима низа од променливи од типот MaticenDoktor и нивниот број; и го печати името, заработената сума и бројот на прегледи на оној доктор кој заработил најголема сума од пациенти кои ги прегледувал приватно (не се здраствено осигурани) (10 поени). Доколку два или повеќе доктори имаат иста сума, тогаш се печати оној доктор кој има направено најголем број на прегледи вкупно во текот на последниот месец. (20 поени)

Функционалност (5 поени).
*/

struct Pacient
{
    char ime[100];
    int zdravstveno;   //Mozebi treba bool
    int pregledi;
};

typedef struct Pacient pacient;

struct Maticen
{
    char ime[100];
    int br_pac;  //Broj na pacienti
    pacient niza[10];
    float cena;
};

typedef struct Maticen doktor;

void najuspesen_doktor(doktor *d, int n)    //Neosigurani/vkupno pregledi, suma, koj
{
    int i,j,k=0;
    
    int suma=0, neo=0, vkupni=0;

    int maxsuma=0, maxneo=0, maxvkupni=0;

    for(i=0; i<d[0].br_pac; i++)    //Max se' na prviot doktor
    {
        if( d[0].niza[i].zdravstveno==0 )
        {
            maxsuma+=( d[0].niza[i].pregledi * d[0].cena );
            maxneo+=d[0].niza[i].pregledi;
        }
        maxvkupni+=d[0].niza[i].pregledi;
    }

    for(i=1; i<n; i++)  //Izminuvanje na doktori
    {
        suma=neo=vkupni=0;

        for(j=0; j<d[i].br_pac; j++)    //Izminuvanje pacienti
        {
            if( d[i].niza[j].zdravstveno == 0 )
            {
                suma+=( d[i].niza[j].pregledi * d[i].cena );
                neo+=d[i].niza[j].pregledi;
            }
            vkupni+=d[i].niza[j].pregledi;
        }

        if( suma > maxsuma )
        {
            maxsuma = suma;
            k = i;
            maxvkupni = vkupni;
        }
        else
        {
            if( suma == maxsuma && vkupni>maxvkupni )
            {
                maxsuma = suma;
                k = i;
                maxvkupni = vkupni;
            }
        }
    }
    
    printf("%s %d.00 %d", d[k].ime, maxsuma, maxvkupni);
}

int main()
{
	int i, j, n;
	doktor md[10];
	scanf("%d", &n);
	for (i = 0; i < n; i++){
		//ime na doktor
		scanf("%s", md[i].ime);
		//broj na pacienti
		scanf("%d", &md[i].br_pac);
		//cena na pregled
		scanf("%f", &md[i].cena);

		for (j = 0; j < md[i].br_pac; j++){
			scanf("%s", md[i].niza[j].ime);
			scanf("%d", &md[i].niza[j].zdravstveno);
			scanf("%d", &md[i].niza[j].pregledi);
		}
	}

	najuspesen_doktor(md, n);

	return 0;
}
