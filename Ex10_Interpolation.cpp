//Author: Ksymena Poradzisz
//


#include<cmath>
#include <iostream>
#include <cstdio>
#include <fstream>
using namespace std;
double f(double x)
{
    double temp = 1./(1.+5.*x*x);
    return temp;
}
int main()
{
    double fx[8] = {  f(-7./8), f(-5./8), f(-3./8), f(-1./8), f(1./8),f(3./8), f(5./8), f(7./8)   };
    
    double x[8] = { -7./8, -5./8, -3./8, -1./8, 1./8, 3./8, 5./8, 7./8};
 double w[8] = {-1,4,-7,8,-8,7,-4,1} ;// Policzone recznie. Ze wzgledu na to, ze jest ich malo, nie wypełniam tablicy w eętli tylko ręcznie deklaruje wielkosci
 double licznik, mianownik;
int t = 16;
 bool za_blisko ;//= false;
 double wartosc; // wartosc wielomianu interpolacyjnego w danym ponkcie
 ofstream wyniki("zad_10_wyniki.txt");
 for (double y=-7./8; y<=7./8; y+=1./(64))
 {
 	licznik = 0;
 	mianownik = 0;
 	za_blisko = false;
	 for(int k  =0; k<8; k++)
	 {
	 	if(abs(y-x[k])<1./1024)
	 	{
	 		t= k;
	 		za_blisko = true;
	 		break;
	 	}
	 	licznik += w[k] * fx[k] /(y-x[k]);
	 	mianownik += w[k] /(y-x[k]);
	 }
	 if(za_blisko)
	 {
	 	wartosc = fx[t];
	 }
	 else
	 {
	 	wartosc = licznik/mianownik;
	 }
	 wyniki << y <<"	" <<  wartosc << endl;
	 
 }

}
