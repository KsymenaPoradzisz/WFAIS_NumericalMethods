//Author: Ksymena Poradzisz

#include <iostream>
#include <cstdio>
#include <cmath>
#include <complex>
#include <iterator>

using namespace std;
complex<double> P1(size_t n, complex<double> a[],complex<double> z)
{
    complex<double> p = (0,0);
    for(int i =0; i<n+1; i++)
    {
        p = p+ a[i]*pow(z,i);
    }
    return p;
}
complex<double> deriv(size_t n, complex<double> a[], complex<double> z)
{
    complex<double> temp = 0;
    for (int i = 0; i<n+1; i++)
    {
        double dumb = i; 
        temp += a[i]*dumb*pow(z,i-1);
    }
    return temp;
}
complex<double> lag(size_t n,complex<double> poly[],complex<double> z)
{
 //rzad wielomianu
    double n_d = n;
    complex<double> dpoly_coeff[n]= {0};
    for (int j =1; j<n+1; j++)
    {
        double dumbo = j;
        dpoly_coeff[j-1]=poly[j]*dumbo; // tablica ze wspolczynnikammi pierwszej pochodnej
    }

   while(true)
    {
        complex<double> war =  sqrt(   (n_d-1) * (   (n_d-1) * pow(deriv(n, poly, z),2) - n_d * P1(n,poly,z) * deriv(n-1, dpoly_coeff,z)   )    );
        complex<double> m1 = deriv(n, poly, z) + war;
        complex<double> m2 = deriv(n, poly, z) - war;

        complex<double> m = 0;
        if(abs(m1)>abs(m2))
        {
            m = m1;
        }
        else
        {
            m = m2;
        }
        complex<double> z1 = z - ( n_d * P1(n, poly, z )  )/(m);

        if(abs(z1-z) < pow(0.1,8))
        {
        	
            return z;
            break;
        }
        else
        {
            z = z1;
        }

    }
}


void give_me_all_ROOTS (size_t psize, complex<double> poly[]) // psize - rzad wielomianu
{

    complex<double> b[psize]= {0,0};
    if(psize == 0)
    {
        cout << "Brak pierwiastków" << endl;
    
    }
    else if(psize == 1)
    {
       cout << -poly[0]/poly[1] << endl;
    }

    complex<double> r[psize] = {0};
    for(int i =0; i<psize+1; i++)
    {
        r[i] = poly[i];
    }
    complex<double> roots[psize+1] = {0};
    int ex = 2;
    int rsize = psize;

    for(int krok = 0; krok <100; krok ++)
    {
        if (rsize == 2)
        {
            //delta 
            complex<double> delta = r[1]*r[1] - 4.0*r[0]*r[2];
            complex<double> sqrtDelta = sqrt(delta);
            roots[0] = (-r[1]+sqrtDelta)/(2.0*r[2]);
            roots[1] = (-r[1]-sqrtDelta)/(2.0*r[2]);
            break;
        }
        else
        {
        	complex<double> z410  (1,0);
            complex<double> guess = lag(rsize,r,z410);
            complex<double> root = lag(psize,poly, guess);
            roots[ex] = root;
            ex++;
            //dzielenie wielomianu
            b[rsize-1] = r[rsize];
            for(int i = 1; i<rsize; i++)
            {
            	
                b[rsize-i-1] =r[rsize-i] + root *b[rsize-i];      // wyliczam wspolczynniki wielomianu o rzedzie n-1
            }
            for(int i = 0; i<rsize; i++)
            {
                r[i] = {0,0}; //zeruje poprzedni wielomian i wypelnie te tablice nowym wielomianem
        
            }
       
            for(int i = 0; i< rsize; i++)
            {
                r[i] = b[i];
 
            }
            	
		rsize--;
		

        }
   }
    for(int i = 0; i< psize; i++)
    {
    	cout<< roots[i] << endl;
    }

   
}


int main() {


    complex<double> P1_a[8] = {16,-72,-28,558,-990,783,-486,243};
   complex<double> P1_b[11]  = {-4,-4, -12, -8, -11, -3, -1, 2, 3,1,1};
   complex<double> P1_c[5] = {{1,0},{0,-1},{-1,0},{0,1},{1,0}};
    give_me_all_ROOTS(7,P1_a);
    cout << endl;
    give_me_all_ROOTS(10,P1_b);
      cout << endl;
      give_me_all_ROOTS(4,P1_c);
}

