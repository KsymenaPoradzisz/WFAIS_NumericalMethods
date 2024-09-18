//Author: Ksymena Poradzisz

#include <iostream>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <array>
#include<string>
#define N 6//stopien wielomianu +1
using namespace std;
double Poly( double a[],double z, size_t size=N)
{
    double p = 0;
    for(int i =0; i<size+1; i++)
    {
        p = p+ a[i]*pow(z,i);
    }
    return p;
}
double Q(size_t size_A, double ATy[], double p[], double yty)  //size_A - ktorego stopnia jest wielomian
{
    double q = 0;
    double ptAy=0;
    for(int i = 0; i<size_A+1; i++)
    {
        ptAy += p[i]*ATy[i];

    }
    q = -1./2* ptAy +1./2*yty;

    return q;

}
array<double,N> Gaus2(double M[N][N],double b[N])
{
    double Mb[N][N+1] ={0}; //dolaczona
    double br = 0;
    double h;
    array<double,N> rozw;
    double x[N]; // rozwiazanie
    for(int i =0; i<N; i++)
    {
        for (int j = 0; j<N; j++)
        {
            Mb[i][j] = M[i][j];
        }
        Mb[i][N] = b[i];
    }


    for (int i = 0; i < N; i++)
    {

        for (int j = i + 1; j < N; j++)
        {
            // pivoting

            if (abs(Mb[i][i]) < abs(Mb[j][i]))
            {
                for (int l = 0; l < N+1; l++)
                {
                    swap(Mb[i][l],Mb[j][l]);
                }
            }
        }

        if(Mb[i][i] == 0.)
        {
           // cout<<"uklad jest nierozwiazywalny"<<endl;
            br=1;
            break;
        }
    }


    //eliminacja
    for (int i = 0; i < N; i++)
    {

        if(br==1)
            break;
        for (int j = i + 1; j < N; j++)
        {
            h = Mb[j][i]/Mb[i][i];
            for (int l = 0; l < N+1; l++)
            {
                Mb[j][l] = Mb[j][l] - Mb[i][l] *h;
            }
        }
    }

  
    for (int i = N-1; i >= 0; i--)
    {
        if(br==1)
        {
            break;
        }
        x[i] = Mb[i][N];

        for (int j = i+1; j < N; j++)
        {

            x[i] -= Mb[i][j] * x[j];
        }
        x[i]= x[i] / Mb[i][i];
    }

    if(br==0){

    for (int i = 0; i < N; i++)
    {
   
       rozw[i] = x[i];
      
    }
	}
	else
	{
//nie ma rozwiazania
		br = 0;
		return {};
	}

return rozw;

}
array<array<double, N>,N> Macierz_odwrotna(double M[N][N])
{
	double Identity[N][N]={0};
	for(int i = 0; i<N; i++)
	{
		Identity[i][i] = 1;
	}
	array<array<double, N>,N> odwrotnosc;
	array<double,N> Ei;
	for(int j = 0; j<N; j++)
	{
		Ei =  Gaus2(M, Identity[j]);
		for(int i = 0; i<N; i++)
		{
			
			odwrotnosc[i][j] = Ei[i];
			//cout << odwrotnosc[i][j] << "	";
		}
		//cout << endl;
	}
	return odwrotnosc;
}

int main()
{
    int N_dane = 128; // liczba danych

    ifstream dane;
    dane.open("/home/korizekori/Pobrane/dane_numerki.txt");


    double A2[128][3]; // dla funkcji kwadratowej ax^2 + bx + c
    array<double,3>  tp2;
    double p2[3]; // wektor wspolczynnikow dla f. kwadratowej: (a,b,c)

    double A3[128][4]; // dla wielomianu 3-go stopnia
      array<double,4>  tp3;
    double p3[4]; //wspolczynniki 3-stopien

    double A4[128][5]; // dla wielomiany 4-go stopnia
       array<double,5>  tp4;
    double p4[5];

    double A5[128][6];//dla wielomianu 5-go stopnia
       array<double,6>  tp5;
    double p5[6];

    double x[128]; // na dane
    double y[128] ;//wartości dla x-ów (dane)

    for(int i =0; i<128; i++)
    {
        dane >> x[i] >> y[i] ;
    }



    //Gdy pomiary są nieskorelowane i ich niepewności są takie same (a takie mamy założenia), to G = sigma^2 * IdentityMatrix. W równaniu (7) z wykladu 6 z metnum18 G^-1 pojawia się z obu stron, wiec mogę skrócić sigma^2 i zostanie mi jedynie macierz jednostkowa.
    //Muszę zatem rozwiązać równanie A^T * A p = A^T y. Obliczam zatem wartości A


    for(int i = 0; i<128; i++)
    {
   
        //A2:ax^2+bx+c
        A2[i][2] = 1;
        A2[i][1] = x[i];
        A2[i][0] = x[i]*x[i];
        //A3: ax^3 + bx^2+ cx + d
        A3[i][3] = 1;
        A3[i][2] = x[i];
        A3[i][1]= x[i]*x[i];
        A3[i][0] = pow(x[i],3);
        //A4: ax^4+bx^3+cx^2+dx+e
        A4[i][4] = 1;
        A4[i][3] = x[i];
        A4[i][2] = x[i]*x[i];
        A4[i][1] = pow(x[i],3);
        A4[i][0] = pow(x[i],4);
        //A5: ax^5 + bx^4 + cx^3 +dx^2 + ex + f
        A5[i][5] = 1;
        A5[i][4] = x[i];
        A5[i][3] = x[i]*x[i];
        A5[i][2] = pow(x[i],3);
        A5[i][1] = pow(x[i],4);
        A5[i][0] = pow(x[i],5);
    }

    //definiuje wektory A^T y i AAT:

    double ATy2[3] = {0};
    double AAT2[3][3] = {0};

    double ATy3[4] = {0};
    double AAT3[4][4] = {0};

    double ATy4[5] = {0};
    double AAT4[5][5] = {0};

    double ATy5[6] = {0};
    double AAT5[6][6] = {0};

    double temp1,temp2;
    //Obliczam A^T y, ale jednocześnie też A^T A

    //A2
    for(int i =0; i<3; i++)
    {
        temp1 = 0;
        temp2 = 0;
        for(int sus = 0; sus<128; sus++)
        {
            temp1 += A2[sus][i] * y[sus];

        }
        ATy2[i] = temp1;
    }
    for(int sos = 0; sos<3; sos++)
    {
        for(int sus = 0; sus<3; sus++)
        {
            for(int daj_normalne_zmienne = 0; daj_normalne_zmienne < 128; daj_normalne_zmienne ++)
            {
                temp2 += A2[daj_normalne_zmienne][sos] * A2[daj_normalne_zmienne][sus];
            }
            AAT2[sos][sus] = temp2;
        }
    }
    //A3
    for(int i =0; i<4; i++)
    {
        temp1 = 0;
        temp2 = 0;
        for(int sus = 0; sus<128; sus++)
        {
            temp1 += A3[sus][i] * y[sus];

        }
        ATy3[i] = temp1;
    }
    for(int sos = 0; sos<4; sos++)
    {
        for(int sus = 0; sus<4; sus++)
        {
            for(int daj_normalne_zmienne = 0; daj_normalne_zmienne < 128; daj_normalne_zmienne ++)
            {
                temp2 += A3[daj_normalne_zmienne][sos] * A3[daj_normalne_zmienne][sus];
            }
            AAT3[sos][sus] = temp2;
        }
    }
    //A4
    for(int i =0; i<5; i++)
    {
        temp1 = 0;
        temp2 = 0;
        for(int sus = 0; sus<128; sus++)
        {
            temp1 += A4[sus][i] * y[sus];

        }
        ATy4[i] = temp1;
    }
    for(int sos = 0; sos<5; sos++)
    {
        for(int sus = 0; sus<5; sus++)
        {
            for(int daj_normalne_zmienne = 0; daj_normalne_zmienne < 128; daj_normalne_zmienne ++)
            {
                temp2 += A4[daj_normalne_zmienne][sos] * A4[daj_normalne_zmienne][sus];
            }
            AAT4[sos][sus] = temp2;
        }
    }
    //a5
    for(int i =0; i<6; i++)
    {
        temp1 = 0;
        temp2 = 0;
        for(int sus = 0; sus<128; sus++)
        {
            temp1 += A5[sus][i] * y[sus];

        }
        ATy5[i] = temp1;
    }
    for(int sos = 0; sos<6; sos++)
    {
        for(int sus = 0; sus<6; sus++)
        {
            for(int daj_normalne_zmienne = 0; daj_normalne_zmienne < 128; daj_normalne_zmienne ++)
            {
                temp2 += A5[daj_normalne_zmienne][sos] * A5[daj_normalne_zmienne][sus];
            }
            AAT5[sos][sus] = temp2;
        }
    }
    double yty;

    for(int t = 0; t<128; t++)
    {
        yty += y[t]*y[t];
    }

ofstream wyniki("Wielomian_stopnia"+to_string(N-1)+".txt");
    tp4=  Gaus2(AAT4,ATy4);
    for(int i =0; i<N; i++)
    {
       p4[i]=tp4[i];
       wyniki<< "wspolczynnik przy x^"+to_string(N-1-i)<< "	"  << p5[i] << endl;
    }
    double suma = 0;
    for(int i=0; i<N_dane; i++)
    {
    	suma+= (y[i]-Poly(p4,x[i]))*(y[i]-Poly(p4,x[i]));
    	
    }
    double sigma2 = 1./N_dane *(suma);
   double Q4 = Q(N-1, ATy5, p4, yty)/sigma2;
   wyniki<< "Q= " <<  Q4 << endl;
   double AIC = log(Q4) + 2*N/(N_dane);
   wyniki << "AIC = " << AIC << endl;
array<array<double, N>,N> W = Macierz_odwrotna(AAT4); //Macierz odwrotna do AAT
array<array<double, N>,N> Cp ;//macierz kowariancji estymatorow 
 for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            Cp[i][j] = W[i][j]*sigma2;
        }
       
    }

   wyniki<< "Macierz estymatorow:"<< endl;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            wyniki<<Cp[i][j]<<" ";
        }
       wyniki<<endl;
    }
}
