/*
Да се дефинира класа Vozac во која се чуваат информации за:

име (низа од максимум 100 знаци)
возраст (цел број)
број на трки (цел број)
дали е ветеран (да/не).
Да се преоптоварат:

операторот << за печатење кој ќе ги печати името, возраст, бројот на трки и дали е ветеран (се печати VETERAN)
операторот == за споредување на два возачи според заработувачката по трка.
Од оваа класа да се изведат две нови класи Avtomobilist и Motociklist.

За автомобилистот дополнително се чува:

цена на автомобилот (децимален број).
За мотоциклистот дополнително се чува:

моќност на мотор (цел број).
Заработувачката по трка на возачите се пресметува како:

за автомобилостот заработувачката по трка е CENAAVTOMOBIL5
за мотоциклистот заработувачката по трка е MOKJNOSTNAMOTOR∗20
Секој автомобилист плаќа данок на заработка. Да се напишат соодветни методи за пресметување данок:

за автомобилисти: ако бројот на трки е поголем од 10 стапката на данок е 15% од заработката, инаку 10% од заработката.
за мотоциклисти: ако е ветеран стапката на данок е 25% од заработката, инаку 20% од заработката.
Да се напше надворешна функција soIstaZarabotuvachka која како аргументи прима низа од покажувачи од класата Vocac, нивниот број, како и покажувач кон ојбект од возач 
и враќа како резултат бројот на возачи кои имаат иста заработувачка по трка со проследениот возач.
*/

#include <iostream>
#include <cstring>

using namespace std;

class Vozac
{
protected:
    char ime[100];
    int vozrast;
    int trki;
    bool veteran;
public:
    Vozac(){}
    Vozac(char *ime="",int vozrast=0,int trki=0,bool veteran=0)
    {
        strcpy(this->ime,ime);
        this->vozrast=vozrast;
        this->trki=trki;
        this->veteran=veteran;
    }

    virtual float zarabotuvacka()=0;
    virtual float danok()=0;

    friend ostream &operator<<(ostream &out,Vozac &v)
    {
        out<<v.ime<<endl;
        out<<v.vozrast<<endl;
        out<<v.trki<<endl;
        if(v.veteran)
            out<<"VETERAN"<<endl;
        return out;
    }

    friend bool operator==(Vozac &a, Vozac &b)
    {
        return a.zarabotuvacka()==b.zarabotuvacka();
    }

    ~Vozac(){}
};

class Avtomobilist:public Vozac
{
private:
    float cena;
public:
    Avtomobilist(char *i="",int v=0,int t=0,int vet=0,float cena=0):Vozac(i,v,t,vet)
    {
        strcpy(ime,i);
        vozrast=v;
        trki=t;
        veteran=vet;
        this->cena=cena;
    }

    float zarabotuvacka()
    {
        return cena/5;
    }

    float danok()
    {
        if(trki>10)
            return cena/5*0.15;
        return cena/5*0.1;
    }
};

class Motociklist:public Vozac
{
private:
    int moknost;
public:
    Motociklist(char *i="",int v=0,int t=0,int vet=0,int moknost=0):Vozac(i,v,t,vet)
    {
        strcpy(ime,i);
        vozrast=v;
        trki=t;
        veteran=vet;
        this->moknost=moknost;
    }

    float zarabotuvacka()
    {
        return moknost*20;
    }

    float danok()
    {
        if(veteran)
            return moknost*20*0.25;
        return moknost*20*0.20;
    }
};

int soIstaZarabotuvachka(Vozac **vozaci, int n, Vozac *v)
{
    int i,br=0;
    for(i=0;i<n;i++)
    {
        if(vozaci[i]->zarabotuvacka()==v->zarabotuvacka())
            br++;
    }
    return br;
}

int main() {
	int n, x;
	cin >> n >> x;
	Vozac **v = new Vozac*[n];
	char ime[100];
	int vozrast;
	int trki;
	bool vet;
	for(int i = 0; i < n; ++i) {
		cin >> ime >> vozrast >> trki >> vet;
		if(i < x) {
			float cena_avto;
			cin >> cena_avto;
			v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
		} else {
			int mokjnost;
			cin >> mokjnost;
			v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
		}
	}
	cout << "=== DANOK ===" << endl;
	for(int i = 0; i < n; ++i) {
		cout << *v[i];
		cout << v[i]->danok() << endl;
	}
	cin >> ime >> vozrast >> trki >> vet;
	int mokjnost;
	cin >> mokjnost;
	Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
	cout << "=== VOZAC X ===" << endl;
	cout << *vx;
	cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
	cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
	return 0;
}
