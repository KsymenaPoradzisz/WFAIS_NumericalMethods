//Author: Ksymena Poradzisz
//Układ równań dany macierzą 128x128 trzeba rozwiązać za pomocą metody gradientów sprzężonych
oraz metodą Gausa Seidela i porównać ich zbieżności
#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <array>
#include <fstream>
#include <string>
using namespace std;

array<double, 128> wyraz_wolny() // tworze wyraz wolny
{
    array<double, 128> e;
    for(int i =0; i<128; i++)
    {
        e[i] = 1;
    }
    return e;
}
array<array<double, 128>,128> CG_results(array<double, 128> b) //metoda gradientow sprzezonych
{
    array<double, 128> alfa, beta;
    array<array<double, 128>,128> r,p, Ap,X;
    for(int j = 0; j<128; j++)
    {
        X[j][0] = 1; //ustalam startowe wartosci x_i=1
    }
    //Definiuje wartości r_1 i p_1
    r[0][0] = b[0] - (4*X[0][0]+X[1][0]);

    for(int i = 1; i<127; i++)
    {
        if(i>0&&i<4)
        {
            r[i][0] = b[i] - (X[i-1][0]+4*X[i][0]+X[i+1][0]+X[i+4][0]);
        }
        else if(i>=4 && i<=123)
        {
            r[i][0] = -(X[i-4][0]+X[i-1][0]+4*X[i][0]+X[i+1][0]+X[i+4][0])+b[i];
        }
        else if(i>123 && i<127)
        {
            r[i][0] = -(X[i-4][0]+X[i-1][0]+4*X[i][0]+X[i+1][0])+b[i];
        }
    }
    r[127][0] = -(X[123][0]+X[126][0]+4*X[127][0])+b[127];
    for (int j=0; j<128; j++)
    {
        p[j][0]=r[j][0];
    }
    //wyliczam wektor Ap_1
    Ap[0][0] = 4*p[0][0]+p[1][0];

    for(int i = 1; i<127; i++)
    {

        if(i>0 && i <4)
        {
            Ap[i][0] = p[i-1][0]+4*p[i][0]+p[i+1][0]+p[i+4][0];
        }
        else if(i>=4 && i<=123)
        {
            Ap[i][0] = p[i-4][0]+p[i-1][0]+4*p[i][0]+p[i+1][0]+p[i+4][0];
        }
        else if(i>123 && i<127)
        {
            Ap[i][0] = p[i-4][0]+p[i-1][0]+4*p[i][0]+p[i+1][0];
        }

    }
    Ap[127][0] =p[123][0]+p[126][0]+4*p[127][0];

    double temp1,temp2,temp3;

    for (int k = 1; k <128; k++) //iteracje
    {
        temp1=0;
        temp2 =0;
        temp3=0;
        for(int j=0; j<128; j++)
        {
            temp1 += r[j][k-1]*r[j][k-1];
            temp2 += p[j][k-1]*Ap[j][k-1];

        }
        for(int i = 0; i<128; i++)
        {
            alfa[k-1] = temp1/temp2;
            r[i][k] = r[i][k-1]-alfa[k-1]*Ap[i][k-1];
        }
        for(int z = 0; z<128; z++)
        {
            temp3 += r[z][k]*r[z][k];
        }

        beta[k-1]= temp3/temp1;
        for(int i=0; i<128; i++ )
        {
            p[i][k] = r[i][k]+beta[k-1]*p[i][k-1];
            X[i][k] = X[i][k-1]+alfa[k-1]*p[i][k-1];
        }
        //tworze wartosci Ap_k
        Ap[0][k] = 4*p[0][k]+p[1][k];

        for(int i = 1; i<127; i++)
        {

            if(i>0 && i <4)
            {
                Ap[i][k] = p[i-1][k]+4*p[i][k]+p[i+1][k]+p[i+4][k];
            }
            else if(i>=4 && i<=123)
            {
                Ap[i][k] = p[i-4][k]+p[i-1][k]+4*p[i][k]+p[i+1][k]+p[i+4][k];
            }
            else if(i>123 && i<127)
            {
                Ap[i][k] = p[i-4][k]+p[i-1][k]+4*p[i][k]+p[i+1][k];
            }

        }
        Ap[127][k] =p[123][k]+p[126][k]+4*p[127][k];

      

    }

    return X;
}

array<array<double, 128>,128> Gaus_Seidel( array<double, 128> b) //metoda gausa seidela
{
	array<array<double, 128>,128>  X;
	for(int j = 0; j<128; j++)
	{
		X[j][0] = 1; //ustalam startowe wartosci x_i=1
	}
	for(int k =1;k<128;k++) //step
	{
		X[0][k] = (b[0] - (4*X[0][k-1] + X[1][k-1]))/4;
		

		for(int i = 1; i<127; i++)
		{
		
			
			if(i>0 && i <4)
			{		
				X[i][k] = (b[i] -(X[i-1][k] + X[i+1][k-1]+X[i+4][k-1]))/4;
	
			} 
			else if(i>=4 && i<=123)
			{
				
				X[i][k] = (b[i]-(X[i-4][k]+X[i-1][k]+X[i+4][k-1]))/4;
				
			}
			else if(i>123 && i<127)
			{
				X[i][k] = (b[i]-(X[i+1][k-1]+X[i-1][k]+X[i-4][k]))/4;
			}
			X[127][k] = (b[127]-X[126][k]-X[123][k])/4;  
		}
		
	}

        return X;
}

void norma_do_pliku(array<array<double, 128>,128> X, string nazwa_pliku)
{
    ofstream grad;
    grad.open(nazwa_pliku +".txt",ios::out);
    double norma =0;
    double t=0;
    for (int k =1; k < 128; k++)
    {
        for(int i =0; i<128; i++)
        {
            norma +=  (X[i][k]-X[i][k-1])* (X[i][k]-X[i][k-1]);
        }
        t=sqrt(norma);
        grad << t << endl;
        norma = 0;

    }
    grad.close();
}

int main()
{
	array<double, 128> b = wyraz_wolny();
	array<array<double, 128>,128> X_CG = CG_results(b);
	array<array<double, 128>,128> X_GS = Gaus_Seidel(b);
	norma_do_pliku(X_CG, "CG_method");
	norma_do_pliku(X_GS, "Gaus_seidel_method");
	
}
