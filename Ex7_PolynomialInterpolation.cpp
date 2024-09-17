#include <iostream>
#include <cstdio>
#include <cmath>
#include <array>
using namespace std;

array<double, 8> Interpolate (array<double, 8> x, array<double, 8> y)
{
    double f[8][8] = {0},l[8]={0};
    double sum;
    array<double, 8> a;
    for(int i = 0; i<8; i++)
        
    {
        f[i][0] = y[i];
    }

    double licznik, mianownik;
    // l_i(0)
    for(int i =0; i<8; i++)
    {
    licznik = 1;
    mianownik = 1;
        for(int j = 0; j<8; j++)
        {
            if(i!=j)
            {
                mianownik = mianownik*(x[i]-x[j]);
                licznik = licznik*(-x[j]);
            }
        }
        l[i] = licznik/mianownik;
     //   cout << l[i] << endl;
    }

    for (int i = 0; i < 8; i++)
    {

	 sum = 0;
	 
        for (int j = 0; j < 8; j++)
        {
            sum +=  l[j] * f[j][i];  
        }
        a[i] = sum;
  
        for (int j = 0; j < 8; j++)
        {
            f[j][i+1] = (f[j][i] - a[i]) / x[j];
        }
    }
 
return a;

}


int main()
{

	    array<double, 8>  x = {0.0625, 0.1875, 0.3125, 0.4375, 0.5625, 0.6875, 0.8125, 0.9375};

    array<double, 8> y = {0.687979, 0.073443, -0.517558, -1.077264, -1.600455, -2.080815, -2.507266, -2.860307};
   array<double, 8> a= Interpolate(x,y);
      for (int i = 0; i < 8; i++)
    {
        cout << a[i] << endl; //wyniki

    }
    
}
