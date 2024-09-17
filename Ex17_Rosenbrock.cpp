#include <iostream>
#include <cstdio>
#include <cmath>
#include <array>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

double func_R(double x, double y) //funkcja do liczenia wartosci funkcji w danym punkcie
{
    double res = pow((1-x),2) + 100 * (pow(y-x*x,2));
    return res;
}

array<array<double,2>,2> Hesjan_LM(double x, double y, double lambda = 1/1024) // funkcja, ktora zwraca przyblizony hesjan [z metody Levenberga-Marquar] w punkcie (x,y)
{
    array<array<double,2>,2> H = {{

            {(2+800*x*x-400*(-x*x+y)) * (1+lambda),	-400*x},
            {	     	-400*x, 			        200*(1+lambda)}

        }};

    return H;

}

array<double, 2> Grad(double x, double y) // funkcja liczaca gradient funkcji Rosenbrocka w punkcie (x,y)
{
    array<double, 2>  grad_f = {
        -2*(1-x) - 400*x*(-x*x + y),
            200*(-x*x + y)

        };
    return grad_f;
}
array<double, 2> H_1_gradF (array<array<double,2>,2> Hes, array<double, 2> f, double lambda = 1/1024)
{
    // chce wiedziec ile wynosi H^-1 grad f = z, czyli wystarczy ze rozwiaze uklad rownan Hz = grad f
    //uzywam wzorow Cramera ze wzgledu na to, ze jest to macierz 2x2.
    double det = Hes[0][0]*Hes[1][1]-Hes[1][0]*Hes[0][1];
    double det_Z1 = f[0]*Hes[1][1] - Hes[0][1]*f[1];
    double det_Z2 = Hes[0][0]*f[1] - f[0]*Hes[1][0];
    array<double, 2>  z =   {
        det_Z1/det,
        det_Z2/det
    };
    return z;

}

array<double, 2> LM (double x, double y, double lambda_default = 1./1024.) // Algorytm Levenberga–Marquardta
{
	ofstream file("17_"+to_string((int)x)+"_"+to_string((int)y)+".txt"); //zapisuje dane do pliku, ktory nazywam zgodnie z punktem z ktorego zaczynam
	int t = 0;
    double lambda = lambda_default;
    array<double, 2> grad_f = Grad(x,y);
    array<double, 2> z;
    array<array<double,2>,2> Hes;
    double x_temp[1000][2] = {0};
    x_temp[0][0] = x;
    x_temp[0][1] = y ;//{x,y};
   int i =0;
   
   do
    {
        file << x_temp[i][0] <<"	" <<  x_temp[i][1] << "	" <<func_R(x_temp[i][0],x_temp[i][1]) << endl;
  
        Hes = Hesjan_LM(x_temp[i][0],x_temp[i][1],lambda);
  
        z = H_1_gradF(Hes,grad_f,lambda);
        //obliczamy x_test
        double x_test[2] = {
            x_temp[i][0]-z[0],
            x_temp[i][1]-z[1]
        };

        if(func_R(x_test[0],x_test[1])>func_R(x_temp[i][0],x_temp[i][1]))
        {
            lambda = 8*lambda;
            
            //wracam do punktu drugiego
         
            x_temp[i+1][0] = x_temp[i][0];
             x_temp[i+1][1] = x_temp[i][1];
             
          
        }
        else if(func_R(x_test[0],x_test[1])<func_R(x_temp[i][0],x_temp[i][1]))
        {
            lambda = lambda/8;
            x_temp[i+1][0] = x_test[0];
            x_temp[i+1][1] = x_test[1];
            x_test[0]=0;
            x_test[1]=0;
            //wracam do punktu pierwszego
            grad_f = Grad(x_temp[i+1][0],x_temp[i+1][1]);
      
        }
        else if(func_R(x_test[0],x_test[1])==func_R(x_temp[i][0],x_temp[i][1]))
        {
        	 t = i;
        	 break;
        	 
        }
        i++;
    } while (i<1000); //ograniczenie na liczbe krokow
    array<double, 2>  result = {
        x_temp[t][0],
        x_temp[t][1]
    };
    return result;
}
int main()
{
	srand(time(NULL));
    array<double, 2> LM_34 = LM(-3,-4);
    array<double, 2> test;
    for(int i = 0; i<20; i++)
    {
    	test = LM(rand() % 100, rand() % 100); //chce aby algorytm wykonal sie dla kilku losowych punktow
    }
}
