//Author: Ksymena Poradzisz

#this code do LU decomposition on given matrices
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

void LU(double M[7][7], double b[7])
{
	double L[7][7]={0}, U[7][7]={0}, y[7]={0}, x[7]={0}, sum;
	
	for(int i = 0; i < 7; i++)
	{
		//U
		for(int j = 0; j<7; j++)
		{
			sum = 0;
			for(int k = 0; k<i; k++)
			{
				sum += (L[i][k] * U[k][j]);
			}
			U[i][j] = M[i][j] - sum;
		}
		//L
		for(int j = i; j<7; j++)
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
				L[j][i] = (M[j][i]-sum)/U[i][i];
			}
		}

	}
	
//solution of equation Ly = b with respect to y //
	for(int i =0; i<7; i++)
	{
		sum = 0;
		for(int j = 0; j<7; j++)
		{
			sum += L[i][j]*y[j];
		}
		y[i] = b[i] - sum;
	}
	// solution of equation Ux = y //
	for(int i = 6; i>=0; i--)
	{
		sum = 0;
		for(int j = 0; j<7; j++)
		{
			sum += U[i][j]*x[j];
		}
		x[i] = (y[i]-sum)/U[i][i];	
	}
	
	///////////////////// Puting matrices on a screen///////////////////// 
 	cout << "L:" << endl;
	for(int i = 0; i<7; i++)
	{
		for(int j=0; j<7; j++)
		{
			cout << L[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "U:" << endl;
	for(int i = 0; i<7; i++)
	{
		for(int j=0; j<7; j++)
		{
			cout << U[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Solution of equation Ly = b: " << endl;
	for(int i =0; i<7; i++)
	{
		cout << y[i] << endl;
	}
	cout << "Solution of equation Ux = y: " << endl;
	for(int i =0; i<7; i++)
	{
		cout << x[i] << endl;
	}
	
}

int main()
{
	double A[7][7] = 
	    { {4,1,0,0,0,0,0},
			  {1,4,1,0,0,0,0},
			  {0,1,4,1,0,0,0},
			  {0,0,1,4,1,0,0},
			  {0,0,0,1,4,1,0},
			  {0,0,0,0,1,4,1},
			  {0,0,0,0,0,1,4}  };
			
	double b[7] = {{1},{2},{3},{4},{5},{6},{7}};		  
	LU(A,b);
}
