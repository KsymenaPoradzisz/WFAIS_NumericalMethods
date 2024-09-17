#include <iostream>
#include <cstdio>
#include <cmath>
#include <array>
using namespace std;

array<double, 5> wektor_wlasny( array<array<double, 5>,5> A, double tau = 0.38197) // tau - przyblizona wartosc wlasna
{
    array<array<double, 5>,5> Rezolwenta;
    double L[5][5]= {0}, U[5][5]= {0},sum, y[5][128]= {0}, z[5][128]= {0};
    double a[5][100] = {0},norma = 0;
    double w[5][100] = {0};
    array<double, 5> x;
y[0][0] = 1;

 for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            if(i==j)
            {
                Rezolwenta[i][j] = A[i][j]-1*tau;
                }
            else
            {
               Rezolwenta[i][j] = A[i][j];
               }
        }
    }

    //faktoryzacja LU//

   for(int i = 0; i < 5; i++)
	{
		//U
		for(int j = 0; j<5; j++)
		{
			sum = 0;
			for(int k = 0; k<i; k++)
			{
				sum += (L[i][k] * U[k][j]);
			}
			U[i][j] = Rezolwenta[i][j] - sum;
		}
		//L
		for(int j = i; j<5; j++)
		{
			if(i == j)
			{
				L[i][i] = 1;
			}
			else
			{
				sum = 0;
				for(int k = 0; k<i; k++)
				{
					sum += (L[j][k]*U[k][i]);
				}
				L[j][i] = (Rezolwenta[j][i]-sum)/U[i][i];
			}
		}

	}
	 for (int k = 0; k<100; k++)
    {
	//rozwiazanie rownania Lw = y ze wzgledu n w
   for (int i = 0; i < 5; i++)
        {
            sum = 0;
            for (int j = 0; j < i; j++)
            {
                sum+= L[i][j] * w[j][k];

            }
            w[i][k] = (y[i][k] - sum) / L[i][i];
           // cout << w[i][k]<<endl;
        }
        ////rozwiazanie rownania Uz = w ze wzgledu n z

for (int i = 4; i >= 0; i--)
        {
            z[i][k] = w[i][k];

            for (int j = i; j < 5; j++)
            {
                if (i != j)
                {
                    z[i][k] = z[i][k] - U[i][j] * z[j][k];
                }
            }
            z[i][k] = z[i][k] / U[i][i];
        }
        //wykonywanie iteracji y[k+1] = z[k]/||z[k]||
        for(int i = 0; i<5; i++)
        {
            norma+= z[i][k] * z[i][k];
        }
        for(int i=0; i<5; i++)
        {
            y[i][k+1] = z[i][k]/sqrt( norma);
        }
         norma = 0;
    }
    


    for (int i =0; i<5; i++)
    {
        x[i]=y[i][98];
    }
    return x;
}
int main()
{
    array<array<double, 5>,5>  A = {{
            {2,-1,0,0,1},
            {-1,2,1,0,0},
            {0,1,1,1,0},
            {0,0,1,2,-1},
            {1,0,0,-1,2}
        }};
    array<double, 5> eigenvector = wektor_wlasny(A);
        for (int i =0; i<5; i++)
    {
       cout << eigenvector[i] << endl;
    }
  
}
