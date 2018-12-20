#include <iostream>
#include <conio.h>
#include <random>
#include <chrono>
#include <cstring>

//Range of p - main seed of RSA
//pMAX shouldn't be more than 1000 due to
//stability issues (in theory it could be higher)
#define pMIN 100
#define pMAX 999

//approximate difference between p1 and p2
//better no more than half of pMAX-pMIN
#define pSENS 100

//starting value of 'e' parameter.
//3 is optimal, have to be small prime number
#define e0 3

using namespace std;

//Function generating random number using "Random" library.
//Unfortunately there must be that third argument,
//witch allows to make following seeds differ (library don't provide it).
unsigned int rGen(unsigned int, unsigned int, int&);

//Function generating prime number, using rGen() as a base.
unsigned int rGenPrime(unsigned int, unsigned int, int&);

//Function returning Modular Power of given numbers.
//It uses specific algorithm, calculating it on small
//numbers, even for big input.
long long PowMod(long long, long long, long long);

//Main function for USER Alice.
//She generates keys of the code,
//and decrypts message at the end.
void Alice();

//Main function for USER Bob.
//He gets keys, encrypts his secret message,
//sends it to Alice
void Bob();

//*************************************************************//
//Main code
int main()
{
    while(1)
    {
        char chose;
        cout<<"0 - ALLICE"<<endl<<"1 - BOB"<<endl; chose=getch();
        if(chose=='0')
            Alice();
        else
            Bob();
        getch();
        cout<<endl<<endl<<"<--------------------------------------------------------->"<<endl;
    }
}

void Alice()
{
    int randC=0;    //variable to vary generation seeds
    string t;

//GENERATING KEYS
    //N key (public)
    long long p1=rGenPrime(pMIN,pMAX,randC);                //1 prime number (private)
    long long p2=rGenPrime(p1-pSENS,p1+pSENS,randC);        //2 prime number (private)
        while(p1==p2) p2=rGenPrime(p1-pSENS,p1+pSENS,randC);   //they shouldn't be same
    long long n=p1*p2;

    //Euler's function (fi) of n (private),
    //using feature that fi(p1*p2)=fi(p1)*fi(p2),
    //and that fi() for prime number 'p' = 'p-1'
    long long fiN=(p1-1)*(p2-1);

    //E key (public)
    long long e=e0;
        while(fiN%e==0) e+=2;   //e can't divide fi(n)

    //D key (private)
    long long k=1;      //it can be any number
    long long d=(k*fiN+1)/e;
    while((long long)(k*fiN+1)%e!=0)       //k must be chosen so (k*fiN+1)/e will be integer
    {
        k++;
        d=(k*fiN+1)/e;
        if(k>50)        //sometimes its hard to chose k, so it's
        {   e+=2;       //better to change 'e' a bit, and try again
            k=1;
        }
    }

//COMUNICATION PART
    //cout<<"p1= "<<p1;             //some hidden prints, for debug or looking into process
    //cout<<"; p2= "<<p2<<endl;
    cout<<endl<<"n= "<<n<<endl;
    //cout<<"fi(n)= "<<fiN<<endl;
    cout<<"e= "<<e<<endl;
    //cout<<"k= "<<k<<endl;
    //cout<<"d= "<<d<<endl;
    cout<<"Insert c: "; cin>>t;

//DECODING MESSAGE
    //my original algorithm witch let user to send
    //messages bigger than n (witch is normally prohibited).
    //that kind of message looks like this: 12.345
    //to decode it, program has to decode number 345,
    //and then add to it 12*n. It is far from ideal
    //because of poor safety level (most of the number
    //you can decrypt using only n public key),
    //but it is better than nothing.

    int mult=0;
    if(t.find('.',0)!=-1)       //if there is no dot, program runs only standard decryption
    {
        int f=t.find('.',0);
        string in;
        for(int i=0;i<f;i++)
            in+=t[i];
        mult=stoi(in);
        t.erase(0,f+1);        //deleting the dot
    }
    long long c;
    c=stoi(t);
    long long m=PowMod(c,d,n);  //basically it is whole decryption
    m+=n*mult;
    cout<<"Received message: "<<m;
}

void Bob()
{
    int randC=0;            //same as higher
    string t;

//COMUNICATOIN PART
    long long n;            //getting public keys
    cout<<"Insert n: "; cin>>n;
    long long e;
    cout<<"Insert e: "; cin>>e;
    long long m;
    cout<<"Your message: "; cin>>m;

//ENCRYPTING MESSAGE
    //sending part of my algorithm.
    //if message is bigger than n,
    //program subtracts n, and write
    //it before the dot
    int cnt=0;
    while(m>n)
    {
        m-=n;
        cnt++;
    }
    t="";
    long long c=PowMod(m,e,n);  //basically whole encryption part
    if(cnt>0)
    {
        t=to_string(cnt);
        t+='.';
    }
    t+=to_string(c);
    cout<<"c="<<t<<endl;
}

unsigned int rGen(unsigned int l, unsigned int h, int &c)
{
    //It uses some quite ugly way to differ seeds:
    //always divide time got from chrono lib. with is big number,
    //by c, increased every time.
    c++;
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count()/c*1.0);
    uniform_int_distribution<unsigned int> distribution(l,h);
    return distribution(generator);
}

unsigned int rGenPrime(unsigned int l, unsigned int h, int &c)
{
    //Function got from internet
    unsigned int prime = rGen(l,h-2,c);
    bool flag=1;
    while(flag==1 || prime==1)
    {
        prime--;
        int sq = sqrt(prime);
        flag=0;
        int a=2;
        while(a<=sq && flag==0)
        {
            if(prime%a==0) flag=1;
            a++;
        }
    }
    return prime;
}

long long PowMod(long long a, long long w, long long n)
{
    //Function got from internet as Moduar Power
    long long pot,wyn,q;
    pot = a; wyn = 1;
    for(q = w; q > 0; q /= 2)
    {
        if(q%2!=0) wyn = (wyn * pot) % n;
        pot = (pot * pot) % n;
    }
    return wyn;
}
