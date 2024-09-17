//Author: Ksymena Poradzisz
//

#include <iostream>
#include <cmath>
#include<array>
using namespace std;
array<double,2> Rozwiazanie(double x_start, double y_start)
{
	array<double,2> rozw;
	double x[2][128];
	double J[2][2][128]; // jakobian
	double gx[2][128];
	double z[2][128];
	double det,det1,det2;
	
	x[0][0] = x_start ; x[1][0] = y_start; // startowa iteracja
	for(int i = 0; i<128; i++)
	{
		gx[0][i] = 2 * x[0][i] * x[0][i] + x[1][i] * x[1][i] - 2;
       	 gx[1][i] = (x[0][i] - 1./2) * (x[0][i] - 1./2) + (x[1][i] - 1) * (x[1][i] - 1) - 1./4; //definicja g
                  
                    J[0][0][i] = 4 * x[0][i];
                     J[0][1][i] = 2 * x[1][i];
       	 J[1][0][i] = 2 * x[0][i] - 1; 
       	 J[1][1][i] = 2 * x[1][i] - 2; //definicja J
       	 
       	 //rozwiazuje uklad rownan Jz = g wzorami cramera
       	   det = J[0][1][i] * J[1][0][i] - J[0][0][i] * J[1][1][i];
       	   det1 =   gx[1][i] * J[0][1][i] -gx[0][i] * J[1][1][i] ;
       	   det2 = gx[0][i] * J[1][0][i] - gx[1][i] * J[0][0][i];
       	   z[0][i] = det1/det;
       	   z[1][i] = det2/det;
       	   x[0][i+1] = x[0][i] - z[0][i];
       	   x[1][i+1] = x[1][i] - z[1][i];
       	   
	}
	rozw[0] = x[0][127]; rozw[1] = x[1][127];
	cout << "Rozwiazanie dla startowego x= " << x_start << " i y = " << y_start << endl;
	cout << "x = " << rozw[0] << endl;
	cout << "y = " << rozw[1] << endl;
	cout << endl;
	return rozw;
}
int main()
{
	//Interpretuje uklad rownan geometycznie -> biore jedynie rzeczywiste rozwiazania
	array<double,2> x1 = Rozwiazanie(0,1);
	array<double,2> x2 = Rozwiazanie(1,1); // trafiam do dwoch roznych basenow atrakcji
}
