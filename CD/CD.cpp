#include <iostream>
#include <cstring>

using namespace std;

/*
Да се дефинира класата Pesna во која се чуваат информации за (5 поени):

име на песна (динамички алоцирано поле од знаци)
времетраење на песната во минути
тип на песна кој може да биде: поп, рап или рок (енумерација tip)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (10 поени)

Дополнително за оваа класа да се дефинира методот:

pecati() - функција во која ќе се печатат одделени со цртичка(-): името на песната во наводници и времетраењето на песната со постфикс min. (5 поени)
Да се креира класата CD во која се чуваат информации за (5 поени):

низа од песни снимени на CD-то (Поле од најмногу 10 објекти од класата Pesna )
број на песни снимени на CD-то
максимално времетраење на песните на CD-то (во минути)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (5 поени)

Дополнително за оваа класа да се дефинираат методите:

dodadiPesna (Pesna p) - со кој се додава песната p на CDто, но само ако има доволно преостанато место (земајќи го предвид максималното времетраење на песните на CDто и времетраењата на песните на CD-то) и ако има помалку од 10 песни на CD-то. (10 поени)
pecatiPesniPoTip(tip t) – со кој се печатат информациите за сите песни од тип t (поп, рап или рок). (10 поени)
Комплетна функционалност (5 поени).
*/

enum tip{ pop, rap, rok};

class Pesna
{
private:
    char ime[20];
    int minuti;
    tip t;      //Inicijaliziranje na el. na Pesna
public:
    Pesna(){}
    Pesna(const char *i, int minuti, tip tt) //Konstruktor
    {
        //ime = new char[strlen(i)+1];
        strcpy(ime,i);

        this->minuti = minuti;
        t = tt;
    }
    ~Pesna()
    {
        //delete [] ime; //Destruktor za din. al. memorija
    }

    void pecati()
    {
        cout<<"\""<<ime<<"\"-"<<minuti<<"min"<<endl;  //Funkcija za pecatenje
    }

    int getMinuti(){ return minuti; }
    char *getIme() { return ime; }
    int getTip(){ return t; }       //Get metodi
};

class CD
{
private:
    Pesna pesni[10];
    int snimeni,vreme;
public:
    CD(){}
    CD( int vreme )     //Konstruktor so eden argument za slobodnoto vreme na CD-to
    {
        snimeni=0;      //Bidejki pocetno nemame niedna Pesna na CD-to
        this->vreme=vreme;
    }
    /*CD(const Pesna *p, int snimeni, int vreme)
    {
        this->snimeni = snimeni;
        this->vreme = vreme;

        for(int i=0; i<snimeni; i++)
        {
            pesni[i] = p[i];
        }
    }*/
    ~CD(){}

    Pesna getPesna(int i)
    {
        return pesni[i];
    }
    int getSnimeni(){ return snimeni; }
    int getVreme(){ return vreme; }     //Get metodi

    void setSnimeni(int s){ snimeni = s; }  //Potrebna set metoda

    int vremeNaPesni()  //F-ja za proveruvanje na slobodno mesto za uste pesni na CD-to
    {
        int vkupno = 0;
        for(int i=0; i<snimeni; i++)
        {
            vkupno += pesni[i].getMinuti();
        }
        return vkupno;
    }

    void dodadiPesna(Pesna pp)  //Dodavanje pesna na CD-to
    {
        if( snimeni == 0)
        {
            if( vreme >= pp.getMinuti() )
            {
                pesni[snimeni] = pp;
                setSnimeni(snimeni+1);
            }
        }
        else
        {
            if( (getVreme() - vremeNaPesni() ) >= pp.getMinuti()&&snimeni<11)
            {
                pesni[snimeni]=pp;
                setSnimeni(snimeni+1);
            }
        }

    }

    void pecatiPesniPoTip(tip t1)   //Pecanjete pesni po tip(enum)
    {
        for(int i=0; i<10; i++)
        {
            if( pesni[i].getTip() == t1)
            {
                pesni[i].pecati();
            }
        }
    }
};

int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, minuti, kojtip;
	char ime[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
		p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<n; i++)
				(omileno.getPesna(i)).pecati();
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<omileno.getSnimeni(); i++)
				(omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

return 0;
}
