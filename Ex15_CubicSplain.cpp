//Author: Ksymena Poradzisz
//Ex: Sporzadz  naturalny splajn kubiczny na podstawie danych zawartych w pliku http://th-www.if.uj.edu.pl/zfs/gora/metnum16/dane.txt. Przedstaw graficznie punkty danych i znaleziony splajn.

#include <iostream>
#include <cmath>
#include<fstream>
using namespace std;

int main()
{
    fstream dane;
    dane.open("dane_numerki15.txt",ios::in);
    int N = 512; //liczba danych
    double x[N],fx[N], eta[N], A[N][N],L[N][N],U[N][N];
    double a1,a2,a3,a4,w,temp;
    for(int i = 0; i<N-1; i++)
    {
        dane >> x[i] >> fx[i];
        cout << x[i] << endl;
    }
    dane.close();
    double h = x[1]-x[0];
    ofstream wyniki("wyniki15.txt");
    eta[0] = 0;
    eta[N-1] = 0;
    for (int i = 0; i <N; i++)
    {
        for (int j = 0; j < N; j++) // >:C
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
    double wyraz_wolny[N]; //:C
    for(int i = 1; i<N-1; i++)
    {
        wyraz_wolny[i] = 6/(h*h) * (fx[i-1]-2*fx[i]+fx[i+1]);
    }

    for (int i = 1; i < N-1; i++)
    {
        // U
        for (int k = i; k < N-1; k++)
        {
            temp = 0;

            for (int j = 1; j < i; j++)
            {
                temp += (L[i][j] * U[j][k]);
            }


            U[i][k] = A[i][k] - temp;
        }

        //L
        for (int k = i; k <N-1; k++)
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

    double y[N] = {0};//,xr[8]={0};
    for(int i =1; i<N-1; i++)
    {
        temp = 0;
        for(int j = 1; j<i; j++)
        {
            temp += L[i][j]*y[j];
        }
        y[i] = (wyraz_wolny[i] - temp)/L[i][i];
    }
    // rozwiązanie równania Ux = y //
    for(int i = N-2; i>=1; i--)
    {
        temp = 0;
        for(int j = i; j<N-1; j++)
        {
            temp += U[i][j]*eta[j];
        }
        eta[i] = (y[i]-temp)/U[i][i];
       // cout << U[i][i] << endl;
        //cout << eta[i] << endl;
    }
//cout << x[N+1] << endl;
    for (double y=x[0]; y<=x[N-2]; y+=h/(16))
    {
        for(int i = 0; i<N ; i++)
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
