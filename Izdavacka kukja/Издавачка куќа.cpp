#include <iostream>
#include <cstring>

using namespace std;

/*
Издавачката куќа FINKI-Education издава онлајн и печатени книги. За секоја книга се чуваат податоци за ISBN бројот (низа од најмногу 20 знаци), насловот (низа од најмногу 50 знаци), авторот (низа од најмногу 30 знаци) и основната цена изразена во $ (реален број). Класата за опишување на книгите е апстрактна (5 поени).

За секоја онлајн книга дополнително се чуваат податоци за url од каде може да се симне (динамички резервирана низа од знаци) и големината изразена во MB (цел број). За секоја печатена книга дополнително се чуваат податоци за масата изразена во килограми (реален број) и дали ја има на залиха (логичка променлива). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

Метод bookPrice, за пресметување на продажната цена на книгата на следниот начин: (10 поени)
За онлајн книга - цената се зголемува за 20% од основната цена ако книгата е поголема од 20MB

За печатена книга - цената се зголемува за 15% од основната цена ако масата на книгата е поголема од 0.7kg

Преоптоварен оператор > за споредба на две книги од каков било вид според нивната цена. (5 поени)
Преоптоварен оператор << за печатење на податоците за книгите во формат: (5 поени)

[ISBN]: [Наслов], [Автор] [Продажна цена]

Да се имплементира функција mostExpensiveBook со потпис:

void mostExpensiveBook (Book** books, int n)

во која се печати вкупниот број на онлајн, односно, печатени книги во проследената низа посебно. (5 поени) Потоа се наоѓа и печати најскапата книга. (5 поени)

Да се обезбедат сите потребни функции за правилно функционирање на програмата. (5 поени)
*/

class Book
{
protected:
    char ISBN[20];
    char naslov[50];
    char avtor[30];
    int cena;
public:
    Book(char *ISBN, char *naslov, char *avtor, int cena)
    {
        strcpy(this->ISBN,ISBN);
        strcpy(this->naslov,naslov);
        strcpy(this->avtor,avtor);
        this->cena=cena;
    }
    Book(){}

    void setISBN(char *i){ strcpy(ISBN,i); }
    virtual float bookPrice()=0;

    char *getISBN(){ return ISBN; }
    char *getNaslov(){ return naslov; }
    char *getAvtor(){ return avtor; }

    virtual ~Book(){}
};

class OnlineBook:public Book
{
private:
    char *url;
    int mb;
public:
    OnlineBook(char *ISBN, char *n, char *a, int c, char *u, int mb):Book(ISBN,n,a,c)
    {
        url = new char[strlen(u)+1];
        strcpy(url,u);
        this->mb=mb;
    }
    OnlineBook(){}

    OnlineBook(const OnlineBook &o)
    {
        strcpy(this->ISBN,o.ISBN);
        strcpy(this->naslov,o.naslov);
        strcpy(this->avtor,o.avtor);
        this->cena=o.cena;

        this->url = new char[strlen(o.url)+1];
        strcpy(url,o.url);
        this->mb=o.mb;
    }

    OnlineBook& operator=(const OnlineBook &o)
    {
        if(&o == this) return *this;

        strcpy(this->ISBN,o.ISBN);
        strcpy(this->naslov,o.naslov);
        strcpy(this->avtor,o.avtor);
        this->cena=o.cena;

        delete [] url;
        this->url = new char[strlen(o.url)+1];
        strcpy(url, o.url);

        mb = o.mb;
        return *this;
    }

    char *getUrl(){ return url; }
    int getMb(){ return mb; }

    float bookPrice()
    {
        if(mb>20)
            return cena*1.2;
        return cena;
    }

    virtual ~OnlineBook(){ delete [] url; }
};

class PrintBook:public Book
{
private:
    float kg;
    bool daliIma;
public:
    PrintBook(char *ISBN, char *n, char *a, int c, float kg, bool d):Book(ISBN,n,a,c)
    {
        this->kg=kg;
        daliIma=d;
    }
    PrintBook(){}

    PrintBook(const PrintBook &p)
    {
        kg=p.kg;
        daliIma=p.daliIma;
    }

    PrintBook& operator=(const PrintBook &p)
    {
        if(&p == this)  return *this;
        kg=p.kg;
        daliIma=p.daliIma;
        return *this;
    }

    float bookPrice()
    {
        if(kg>0.7)
            return cena*1.15;
        return cena;
    }

    virtual ~PrintBook(){}
};

bool operator>(Book &a, Book &b)
{
    Book *t1=&a;
    Book *t2=&b;
    return t1->bookPrice() > t2->bookPrice();
}

ostream& operator<<(ostream &out, Book &t)
{
    Book *tmp=&t;
    out<<tmp->getISBN()<<": "<<tmp->getNaslov()<<", "<<tmp->getAvtor()<<" "<<tmp->bookPrice()<<endl;
    return out;
}

void mostExpensiveBook(Book **books, int n)
{
    int i,ii,br=books[0]->bookPrice();
    int online=0,pecateni=0;
    for(i=0;i<n;i++)
    {
        OnlineBook *o = dynamic_cast<OnlineBook *>(books[i]);

        if(o!=0)
            online++;
        else
            pecateni++;

        if(books[i]->bookPrice() > br)
        {
            br=books[i]->bookPrice();
            ii=i;
        }
    }
    cout<<"FINKI-Education"<<endl;
    cout<<"Total number of online books: "<<online<<endl;
    cout<<"Total number of print books: "<<pecateni<<endl;
    cout<<"The most expensive book is: "<<endl;
    cout<<*books[ii];
}

int main(){

	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i<n; i++){

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);

			}
			else {
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}

		mostExpensiveBook(books, n);
	}

	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;
	return 0;
}

