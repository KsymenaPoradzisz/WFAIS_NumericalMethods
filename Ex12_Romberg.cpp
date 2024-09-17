//Author: Ksymena Poradzisz

#include <iostream>
#include <cstdio>
#include <cmath>
#include <fstream>
using namespace std;
double f(double x)
{
    double wynik  = cos((1+x)/(0.04+x*x))*exp(-x*x);
    return wynik;
}
int main()
{
	//Aby wyliczyć całkę z dokładnością 1e-8 (granice z x-> infty) to wystarczy policzyć ją w granicach -4, 4.
	//Metoda Romberga
	 int N = 10;
	 double a = -4;
	 ofstream output("12.txt");
    double h[N+1] ;
    double R[N+1][N+1];
for(double b=a; b<=4.0001; b+=0.0001)
{
    for(int i = 0; i<N+1; i++)
    {
        h[i] = (b-a)/pow(2,i);
 
    }

    R[0][0] = h[0]/2*(f(a)+f(b));

    for(int i = 1; i < N+1; ++i)
    {
        double temp = 0;
        for(int k = 1; k<= pow(2,i-1); ++k)
        {
          
            temp += f((2*k-1)*h[i]+a);
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
    output << b << "	" << R[N][N];
    }
cout << "Lim x-> Infty " << R[N][N] << endl;
}
