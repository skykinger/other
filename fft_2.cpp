#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#define PI 3.14159


void dft(float *x,float *X,int m)
{
     int k,n;
     for(k=0;k<=m-1;k++)
     {
                        X[2*k]=0;
                        X[2*k+1]=0;
                        for(n=0;n<=m-1;n++)
                        {
                                           X[2*k]+=x[2*n]*cos(-2*PI*n*k/m)-x[2*n+1]*sin(-2*PI*n*k/m);
                                           X[2*k+1]+=x[2*n]*sin(-2*PI*n*k/m)+x[2*n+1]*cos(-2*PI*n*k/m);
                        }
     }
}
void myfft(float *X ,float *y,int m)
{
	if (fmod(m,2)==0)
	{
        m=m/2;
        float  *z,*u,*x1,*x2;
        z=(float*)malloc(sizeof(float)* 2*m );
        u=(float*)malloc(sizeof(float)* 2*m );
        x1=(float*)malloc(sizeof(float)* 2*m );
        x2=(float*)malloc(sizeof(float)* 2*m );
		//float  z[2*m],u[2*m],x1[2*m],x2[2*m];
		int i,k;
		for (i=0;i<=m-1;i++)
		{
            z[2*i]=y[4*i];z[2*i+1]=y[4*i+1];
            u[2*i]=y[2+4*i];u[2*i+1]=y[3+4*i];	
		}
		myfft(x1,z,m);myfft(x2,u,m);
		for (k=0;k<=m-1;k++)
		{
                       
                           X[2*k]=x1[2*k]+cos(-PI*k/m)*x2[2*k]-sin(-PI*k/m)*x2[2*k+1];
                           X[2*k+1]=x1[2*k+1]+cos(-PI*k/m)*x2[2*k+1]+sin(-PI*k/m)*x2[2*k];
                           X[2*(k+m)]=x1[2*k]-cos(-PI*k/m)*x2[2*k]+sin(-PI*k/m)*x2[2*k+1];
                           X[2*(k+m)+1]=x1[2*k+1]-cos(-PI*k/m)*x2[2*k+1]-sin(-PI*k/m)*x2[2*k];
                       
        }
	}
	else
	{
        dft(y,X,m);
    }
}

int main()
{
    int i,m=6;
    float y[12]={1,1,2,0,3,0,4,0,5,1,7,1};
    float *X;
    X=(float*)malloc(sizeof(float)* 2*m );
    myfft(X,y,m);
    for (i=0;i<=2*m-1;i++)
    {
    printf("%f\n",X[i]);
    }
    system("pause");
    return 0;
}     
