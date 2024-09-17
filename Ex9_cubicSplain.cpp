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
  //  cout << x[3] << endl;
    double l[8]= {0};
    double eta[8] = {0};
    double A[8][8];
    double h = 2./8;
    eta[0]=0;
    eta[7] = 0;

    for (int i = 0; i <8; i++)
    {
        for (int j = 0; j < 8; j++) // >:C
        {
            if (i == j)
            {
                A[i][j] = 4.;
            }
            else if ((i - j) == 1 || (j - i )== 1)
            {
                A[i][j] = 1.;
            }

            else
            {
                A[i][j] = 0.;
            }
        }
    }
  

    double wyraz_wolny[7]; //:C
    for(int i = 1; i<7; i++)
    {
        wyraz_wolny[i] = 6/(h*h) * (fx[i-1]-2*fx[i]+fx[i+1]);
    }
    //rozwiazanie ukladu rownan poprzez metode LU
    double L[8][8]= {0}, U[8][8]= {0};
    double temp = 0;

    for (int i = 1; i < 7; i++)
    {
        // U
        for (int k = i; k < 7; k++)
        {
            temp = 0;

            for (int j = 1; j < i; j++)
            {
                temp += (L[i][j] * U[j][k]);
            }


            U[i][k] = A[i][k] - temp;
        }

        //L
        for (int k = i; k <7; k++)
        {
            if (i == k)
                L[i][i] = 1;
            else
            {

                temp = 0;
                for (int j = 1; j < i; j++)
                {
                    temp += (L[k][j] * U[j][i]);
                }


                L[k][i]  = (A[k][i] - temp) / U[i][i];
            }
        }
    }

    double y[8] = {0};//,xr[8]={0};
    for(int i =1; i<7; i++)
    {
        temp = 0;
        for(int j = 1; j<i; j++)
        {
            temp += L[i][j]*y[j];
        }
        y[i] = (wyraz_wolny[i] - temp)/L[i][i];
    }
    // rozwiązanie równania Ux = y //
    for(int i = 6; i>=1; i--)
    {
        temp = 0;
        for(int j = i; j<7; j++)
        {
            temp += U[i][j]*eta[j];
        }
        eta[i] = (y[i]-temp)/U[i][i];
        cout << eta[i] << endl;
    }
    ofstream wyniki("wyniki.txt");
    double a1,a2,a3,a4,w;
    for (double y=-7./8; y<=7./8; y+=1./(64))
    {
        for(int i = 0; i<8 ;i++)
        {
            if (y <=x[i+1] && y>=x[i])
            {
                a1 = (x[i+1]-y)/(x[i+1]-x[i]);
                a2 = (y - x[i])/(x[i+1]-x[i]);
                a3 = 1./6*(a1*a1*a1 - a1)*(x[i+1]-x[i])*(x[i+1]-x[i]);
                a4 = 1./6*(a2*a2*a2 - a2)*(x[i+1]-x[i])*(x[i+1]-x[i]);
                w = a1*fx[i] + a2*fx[i+1] + a3*eta[i] + a4*eta[i+1];
                wyniki<<y<<"	"<<w<<"	"<<endl;
            }

        }
    }
    wyniki.close();

}
