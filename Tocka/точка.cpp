#include <iostream>
#include <cmath>
#include <stdio.h>

/*
Да се надополни програмата со следните барања:

да се креира структура на точка во тродимензионален простор и да се напише функција која ќе го пресметува растојанието помеѓу две такви точки.
да се напише функција која како аргумент прима три точки во дводимензионален простор и ќе проверува дали тие точки лежат на иста права.
*/

using namespace std;

typedef struct t2D //Kreiranje 2D struktura za tocka
{
    float x;
    float y;
}tocka2D;

typedef struct t3D //Kreiranje 3D struktura za tocka
{
    float x;
    float y;
    float z;
}tocka3D;

float rastojanie(tocka2D prva, tocka2D vtora) //d^2=(x2-x1)^2+(y2-y1)^2
{
    return sqrt( (vtora.x-prva.x)*(vtora.x-prva.x) + (vtora.y-prva.y)*(vtora.y-prva.y) );
}

float rastojanie3D(tocka3D prva, tocka3D vtora) //d^2=(x2-x1)^2+(y2-y1)^2+(z2-z1)^2
{
    return sqrt( pow((prva.x-vtora.x),2) + pow((prva.y-vtora.y),2) + pow((prva.z-vtora.z),2));
}

int ista_prava(tocka2D prva, tocka2D vtora, tocka2D treta) //Na linija so po red tocki A,B,C: AB+BC=AC
{
    float d1=rastojanie(prva,vtora), d2=rastojanie(prva,treta), d3=rastojanie(vtora,treta),maxi,a,b;

    if(d1>d2 && d1>d3)
    {
        maxi=d1;
        a=d2;
        b=d3;
    }

    if(d2>d1 && d2>d3)
    {
        maxi=d2;
        a=d1;
        b=d3;
    }

    if(d3>d1 && d3>d2)
    {
        maxi=d3;
        a=d1;
        b=d2;
    }

    if( (a+b)==maxi )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    float x1, y1, x2, y2;

    scanf("%f %f", &x1, &y1);
	scanf("%f %f", &x2, &y2);

	tocka2D t1 = { x1, y1 };
	tocka2D t2 = { x2, y2 };

	printf("%.2f\n", rastojanie(t1, t2));

    float z1, z2;

    scanf("%f %f", &z1, &z2);

    tocka3D t3 = {x1, y1, z1};
    tocka3D t4 = {x2, y2, z2};

    printf("%.2f\n", rastojanie3D(t3, t4));

    tocka2D t5 = {z1, z2};

    printf("%d\n", ista_prava(t1, t2, t5));
	return 0;
}
