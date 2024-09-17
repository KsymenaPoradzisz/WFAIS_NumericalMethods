#include <iostream>
#include <cstdio>
#include <cmath>

double f(double x) // funkcja podcalkowa
{
	double wynik = sin(M_PI*(1+sqrt(x))/(1+x*x))*exp(-x);
	return wynik;
}
using namespace std;
int main(){

////// metoda trapezow
///// e^(-A) = 10^(-7), gdy A = Log[10^7] czyli okolo A = 16.1181. Przyjmuje zatem A = 16.125, wtedy e^(-A) = 9.83119 * 10^-8
/// Calka _0 ^ A (od 0 do A)
	double A = 16.125;
	double result = A/2*f(A);
 // druga czesc calki pomijamy, poniewaz chcemy miec dokladnosc 10^(-7), a jej wartosc jest mniejsza niz 10^-7
	///metoda Romberga
		
	int N = 15;
	double h[N+1] ; double R[N+1][N+1];
	
	for(int i = 0; i<N+1; i++)
	{
		h[i] = A/pow(2,i);
	}
	
	R[0][0] = h[0]/2*f(A);
	
	for(int i = 1; i < N+1; ++i)
	{
		for(int k = 1; k<= pow(2,i-1); ++k)
		{
			temp += f((2*k-1)*h[i]);
		}
		
		R[i][0] = 0.5 * (R[i-1][0]+h[i-1]*temp);
	}
	for(int i = 1; i<N+1; ++i)
	{
		for(int j = 1; j <= i ; ++j)
		{
			R[i][j] = R[i][j-1] + (R[i][j-1]-R[i-1][j-1])/(pow(4,j)-1);
		}
	}
	
	
	for (int  i = 0; i<N; i++)
	{
		for(int j = 0; j<N; j++)
		{
			cout << R[i][j] << "	" ;
		}
		cout << endl;
	} 
}
