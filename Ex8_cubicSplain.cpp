//Author: Ksymena Poradzisz
#include <cmath>
#include <iostream>
#include <cstdio>
#include <fstream>
using namespace std;
double f(double x)
{
    double temp = 1./(1+5*x*x);
    return temp;
}
int main()
{
    double fx[8] = {  f(-7./8), f(-5./8), f(-3./8), f(-1./8), f(1./8),f(3./8), f(5./8), f(7./8)   };
    double x[8] = { -7./8, -5./8, -3./8, -1./8, 1./8,3./8, 5./8, 7./8};
    double l[8]= {0};
double sum, licznik, mianownik,w;
ofstream wyniki("zad8_wyniki.txt");
  for (double y=-7./8; y<=7./8; y+=1./16)
{
	sum = 0;
	for(int i = 0; i<8; i++)
	{
		licznik = 1;
		mianownik = 1;
		for(int j = 0; j<8;j++)
		{
			if(i != j)
			{
			licznik = licznik* (y- x[j]);
			mianownik = mianownik * (x[i] - x[j]);
		}
		}
		l[i] = licznik/mianownik;
		sum+=fx[i] * l[i];
	}
	w = sum;
	wyniki << y << "	" << w << "	" << endl;
}

   
}
