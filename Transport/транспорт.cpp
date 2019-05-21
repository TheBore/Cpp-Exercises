/*
Туристичка агенција нуди различни понуди за транспорт на патници. За секоја понуда се чуваат податоци за дестинацијата (низа од знаци), основна цена (цел број) и податок за растојанието до дестинацијата изразено во km (цел број).

Од класата Transport да се изведат класите AvtomobilTransport и KombeTransport за моделирање на понудите за транспорт кои нудат транспорт со автомобил или комбе, соодветно. За секоја понуда за транспорт со автомобил се чува податок за тоа дали во понудата има платен шофер (булова променлива), а за транспорт со комбе бројот на луѓе кои може да се превезат во комбето (цел број). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

конструктор со аргументи што одговараат на податочните членови и set и get методи за податочните членови (5 поени)
метод cenaTransport, за пресметување на цената на понудата на следниот начин:
За транспорт со автомобил - основната цена се зголемува за 20% ако има платен шофер
За транспорт со комбе - основната цена ќе се намали зависно од бројот на патници во комбето. За секој патник во комбето цената се намалува за 200 (10 поени)
преоптоварен оператор < за споредба на две понуди за транспорт на патник според растојанието до дестинацијата. (5 поени)
Да се имплементира функција pecatiPoloshiPonudi што на влез прима низа од понуди за транспорт на патник, бројот на елементите од низата и една понуда T. Функцијата ја печати дестинацијата, растојанието до дестинацијата и цената за понудите од низата кои се поскапи од понудата T сортирани во растечки редослед по растојанието до дестинацијата (погледни го повикот на функцијата) (10 поени)

Комплетна функционалност на кодот (5 поени)
*/

#include <iostream>
#include <cstring>

using namespace std;

class Transport
{
protected:
    char destinacija[100];
    int cena;
    int km;
public:
    Transport(){}
    Transport(char *destinacija, int cena, int km)
    {
        strcpy(this->destinacija,destinacija);
        this->cena=cena;
        this->km=km;
    }

    virtual int getKm()=0;
    virtual char *getDestinacija()=0;
    virtual int cenaTransport()=0;
    virtual int getCena()=0;

    bool operator<(Transport &a)
    {
        return this->getKm() < a.getKm();
    }

    ~Transport(){}
};

class AvtomobilTransport:public Transport
{
private:
    bool sofer;
public:
    AvtomobilTransport(char *d, int c, int km, int s):Transport(d,c,km)
    {
        strcpy(destinacija,d);
        cena=c;
        this->km=km;
        sofer=s;
    }

    AvtomobilTransport(AvtomobilTransport &a)
    {
        strcpy(destinacija,a.destinacija);
        cena=a.cena;
        this->km=a.km;
        sofer=a.sofer;
    }

    int cenaTransport()
    {
        if(sofer==true)
        {
            return cena*1.2;
        }
        return cena;
    }

    int getCena(){ return cena; }
    int getKm(){ return km; }
    char *getDestinacija(){ return destinacija; }

    ~AvtomobilTransport(){}
};

class KombeTransport:public Transport
{
private:
    int lugje;
public:
    KombeTransport(char *d, int c, int km, int k):Transport(d,c,km)
    {
        strcpy(destinacija,d);
        cena=c;
        this->km=km;
        lugje=k;
    }

    KombeTransport(KombeTransport &a)
    {
        strcpy(destinacija,a.destinacija);
        cena=a.cena;
        this->km=a.km;
        lugje=a.lugje;
    }

    int cenaTransport()
    {
        return cena-200*lugje;
    }

    int getCena(){ return cena; }
    int getKm(){ return km; }
    char *getDestinacija(){ return destinacija; }

    ~KombeTransport(){}
};

void pecatiPoloshiPonudi(Transport **ponudi, int n, Transport &t)
{
    Transport *tmp[n];
    int k=0,i,j;
    for(i=0;i<n;i++)
    {
        if( t.cenaTransport() < ponudi[i]->cenaTransport() )
        {
            tmp[k]=ponudi[i];
            k++;
        }
    }
    Transport *pom;
    for(i=0;i<k-1;i++)
    {
        for(j=1;j<k;j++)
        {
            if(tmp[i]->getKm() > tmp[j]->getKm())
            {
                pom=tmp[i];
                tmp[i]=tmp[j];
                tmp[j]=pom;
            }
        }
    }

    for(i=0;i<k;i++)
    {
        cout<< tmp[i]->getDestinacija() <<" "<< tmp[i]->getKm()<<" ";
        cout<< tmp[i]->cenaTransport() <<endl;
    }
}

int main()
{
    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
