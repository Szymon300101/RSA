#include <iostream>
#include <conio.h>
#include "..\@lib\BigInteger\BigInteger.cpp"
#include "..\@lib\Resource.hpp"

#define pMIN 30
#define pMAX 100
#define pSENS 20
#define e0 3

using namespace std;


BigInteger bigPow(BigInteger a,BigInteger b)
{
    BigInteger wynik = 1;

    for (BigInteger i = 0; i<b; i++)
        wynik*=a;

    return wynik;
}

void Alice()
{
    int randC=0;
    string t;
    int ra=rGenPrime(pMIN,pMAX,randC);
    BigInteger p1=ra;
    ra=rGenPrime(ra-pSENS,ra+pSENS,randC);
    BigInteger p2=ra;
        if(p1==p2) p2=rGenPrime(ra-pSENS,ra+pSENS,randC);
    BigInteger n=p1*p2;
    BigInteger fiN=(p1-1)*(p2-1);
    BigInteger e=e0;
        while(fiN%e==0) e+=2;
    BigInteger k=1;
    BigInteger d=(k*fiN+1)/e;
    while((k*fiN+1)%e!=0)
    {
        k++;
        d=(k*fiN+1)/e;
        if(k>50)
        {   e+=2;
            k=1;
        }
    }
//    t=p1;
//    cout<<"p1= "<<t;
//    t=p2;
//    cout<<"; p2= "<<t<<endl;
    t=n;
    cout<<endl<<"n= "<<t<<endl;
//    t=fiN;
//    cout<<"fi(n)= "<<t<<endl;
    t=e;
    cout<<"e= "<<t<<endl;
//    t=k;
//    cout<<"k= "<<t<<endl;
//    cout<<"d= "<<string(d)<<endl;
    cout<<"Podaj c: "; cin>>t;
    int mult=0;
    if(t.find('.',0)!=-1)
    {
        int f=t.find('.',0);
        string in;
        for(int i=0;i<f;i++)
            in+=t[i];
        mult=stoi(in);
        t.erase(0,f);
    }
    BigInteger c=t;
    BigInteger m=bigPow(c,d)%n;
    m+=n*mult;
    t=m;
    cout<<"Otrzymano: "<<t;
}

void Bob()
{
    int randC=0;
    string t;
    cout<<"Podaj n: "; cin>>t;
    BigInteger n=t;
    cout<<"Podaj e: "; cin>>t;
    BigInteger e=t;
    cout<<"Wpisz wiadomosc: "; cin>>t;
    BigInteger m=t;
    int cnt=0;
    while(m>n)
    {
        m-=n;
        cnt++;
    }
    t="";
    BigInteger c=bigPow(m,e)%n;
    if(cnt>0)
    {
        t=itos(cnt);
        t+='.';
    }
    t+=c;
    cout<<"c="<<t<<endl;
}

int main()
{
while(1)
{
char chose;
cout<<"0 - ALLICE"<<endl<<"1 - BOB"<<endl; chose=getch();
if(chose=='0')
{
    Alice();
}else
{
    Bob();
}
getch();
cout<<endl<<endl<<"<--------------------------------------------------------->"<<endl;
}
}
