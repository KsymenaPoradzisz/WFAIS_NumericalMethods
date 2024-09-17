#include <iostream>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <array>
using namespace std;

int main()
{
    array<array<double, 6>,6> A = {{
            {19./12., 13./12., 10./12., 10./12., 13./12., -17./12.},
            {13./12., 13./12., 10./12., 10./12., -11./12., 13./12.},
            {10./12., 10./12., 10./12., -2./12., 10./12., 10./12.},
            {10./12., 10./12., -2./12., 10./12., 10./12., 10./12.},
            {13./12., -11./12., 10./12., 10./12., 13./12., 13./12.},
            {-17./12., 13./12., 10./12., 10./12., 13./12., 19./12.}
        }
    };
    int iterat = 128;
    double temp1 = 0, temp_norm = 0;
    array<array<double, 6>,128> y1 = {{0}};
    array<array<double, 6>,128> z1 = {{0}};
    array<double, 128> norm,norm2;
    //Szukamy największej wartości własnej i wektora własnego do tej wartości
    y1[0][0]=1;
    for(int k =0; k<iterat-1; k++)
    {
        for(int i = 0; i<6; i++)
        {
            for(int j =0; j<6; j++)
            {
                temp1 += A[i][j] * y1[j][k];
            }
            z1[i][k] = temp1;
            temp1 = 0;
        }

        for(int i =0; i<6; i++)
        {
            temp_norm += z1[i][k]*z1[i][k];
        }
        norm[k] = sqrt(temp_norm);
        temp_norm = 0;
        for(int i  = 0; i<6; i++)
        {
            y1[i][k + 1] = z1[i][k] / norm[k];
        }
    }
    cout << "Najwieksza wartosc wlasna to: " << norm[iterat-2] << endl;
    cout << "Do wektora wlasnego" << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << y1[i][iterat - 2] << endl;

    }
    //pora na druga najwieksza wartosc wlasna i wektor do tej wartosci
    array<array<double, 6>,128> y2 = {{0}};
    array<array<double, 6>,128> z2 = {{0}};
    double temp_norm2 = 0,product;
    y2[0][0] = -y1[0][iterat-2];
    y2[1][0] = y1[0][iterat-2];
    y2[2][0] = -y1[0][iterat-2];
    y2[3][0] = y1[0][iterat-2];
    y2[4][0] = -y1[0][iterat-2];
    y2[5][0] = y1[0][iterat-2];
    for(int k = 0; k<iterat - 1; k++)
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                temp1 += A[i][j] * y2[j][k];
            }
            z2[i][k] = temp1;
            temp1=0;
        }
        for (int i = 0; i < 6; i++)
        {
            temp_norm2 += z2[i][k] * z2[i][k];
        }
        norm2[k] = sqrt(temp_norm2);
        temp_norm2 = 0;
        for (int i =0; i<6; i++)
        {
            temp_norm2+= y1[i][iterat-2] * z2[i][k];
        }
        product =  temp_norm2;
        temp_norm2 = 0;
        for (int i =0; i<6; i++)
        {
            z2[i][k] -= y1[i][iterat-2]*product;
        }
        for (int j = 0; j < 6; j++)
        {
            y2[j][k + 1] = z2[j][k] / norm2[k];
        }
    }
        cout << "Najwieksza wartosc wlasna to: " << norm2[iterat-2] << endl;
    cout << "Do wektora wlasnego" << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << y2[i][iterat - 2] << endl;

    }
}
