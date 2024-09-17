//Author: Ksymena Poradzisz
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

void Cholesky(double M[7][7], double b[7])
{
	double C[7][7]={0}, x[7]={0}, y[7]={0};
	double sum;
	
	for(int i = 0; i<7; i++)
	{
		for(int j=0; j<=i; j++)
		{
			//sum =0;
			//Diagonala
			if(j==i)
			{
				sum = 0;
				
				for(int k =0; k<j; k++)
				{
					sum += C[j][k]*C[j][k];
				}
				C[j][j] = sqrt(M[j][j]-sum);
			}
			else
			{
				sum = 0;
				for (int k = 0; k<j; k++)
				{
					sum += (C[i][k]*C[j][k]);
				}
				C[i][j] = (M[i][j]-sum) / C[j][j];
			}
		}
	}
	cout << "C:" << endl;
	for(int i = 0; i<7; i++)
	{
		for(int j=0; j<7; j++)
		{
			cout << C[i][j] << " ";
		}
		cout << endl;
	}
	
	//Cy = b
	for(int i=0; i<7; i++)
	{
		sum =0;
		for(int j=0; j<i; j++)
		{
			sum += C[i][j]*y[j];
		}
		y[i] = (b[i] - sum)/C[i][i];
	}
	//C^T x = y
	for(int i=7; i>=0; i--)
	{
		sum = 0;
		for(int j=0; j<i; j++)
		{
			sum += C[j][i]*x[j];
		}
		x[i] = (y[i]-sum)/C[i][i];
	}
	//wyswietlanie
	
	cout << "Rozwiazanie rownania Cy = b: " << endl;
	for(int i =0; i<7; i++)
	{
		cout << y[i] << endl;
	}
	cout << "Rozwiazanie rownania C^T x = y: " << endl;
	for(int i =0; i<7; i++)
	{
		cout << x[i] << endl;
	}
	
}
int main()
{
	double A[7][7] = { {4,1,0,0,0,0,1},
			  {1,4,1,0,0,0,0},
			  {0,1,4,1,0,0,0},
			  {0,0,1,4,1,0,0},
			  {0,0,0,1,4,1,0},
			  {0,0,0,0,1,4,1},
			  {1,0,0,0,0,1,4}  };
			
	double b[7] = {{1},{2},{3},{4},{5},{6},{7}};		  
	Cholesky(A,b);
}
