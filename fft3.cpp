#include<stdlib.h>
#include<math.h>
#include<iostream>



void dft(float *x,float *X,int m)
{
     int k,n;
     for(k=0;k<=m-1;k++)
     {
                        X[2*k]=0;
                        X[2*k+1]=0;
                        for(n=0;n<=m-1;n++)
                        {
                                           X[2*k]+=x[2*n]*cos(-2*M_PI*n*k/m)-x[2*n+1]*sin(-2*M_PI*n*k/m);
                                           X[2*k+1]+=x[2*n]*sin(-2*M_PI*n*k/m)+x[2*n+1]*cos(-2*M_PI*n*k/m);
                        }
     }
}


void myfft(float *X ,float *y,int m)
{
	if (fmod(m,3)==0)
	{
        m=m/3;
        float  *z,*u,*t,*x1,*x2,*x3;
        z=(float*)malloc(sizeof(float)*3*m );
        u=(float*)malloc(sizeof(float)*3*m );
        t=(float*)malloc(sizeof(float)*3*m );
        x1=(float*)malloc(sizeof(float)*3*m );
        x2=(float*)malloc(sizeof(float)*3*m );
        x3=(float*)malloc(sizeof(float)*3*m );
		int i,k;
		for (i=0;i<=m-1;i++)
		{
            z[2*i]=y[6*i];z[2*i+1]=y[6*i+1];
            u[2*i]=y[2+6*i];u[2*i+1]=y[3+6*i];
			t[2*i]=y[4+6*i];t[2*i+1]=y[5+6*i];	
		}
		myfft(x1,z,m);myfft(x2,u,m);myfft(x3,t,m);
		for (k=0;k<=3*m-1;k++)
		{
            if (k<=m-1)
            {
                       
                           X[2*k]=x1[2*k]+cos(-M_PI*k*2/(m*3))*x2[2*k]-sin(-M_PI*k*2/(m*3))*x2[2*k+1] + cos(-M_PI*k*2*2/(m*3))*x3[2*k]-sin(-M_PI*k*2*2/(m*3))*x3[2*k+1];
                           X[2*k+1]=x1[2*k+1]+cos(-M_PI*k*2/(m*3))*x2[2*k+1]+sin(-M_PI*k*2/(m*3))*x2[2*k] + cos(-M_PI*k*2*2/(m*3))*x3[2*k+1]+sin(-M_PI*k*2*2/(m*3))*x3[2*k];
                           X[2*(k+m)]=x1[2*k]+cos(-M_PI*2/3)*(cos(-M_PI*k*2/(m*3))*x2[2*k]-sin(-M_PI*k*2/(m*3))*x2[2*k+1])-sin(-M_PI*2/3)*(cos(-M_PI*k*2/(m*3))*x2[2*k+1]+sin(-M_PI*k*2/(3*m))*x2[2*k]) + cos(-M_PI*4/3)*(cos(-M_PI*2*k*2/(m*3))*x3[2*k]-sin(-M_PI*2*k*2/(3*m))*x3[2*k+1])-sin(-M_PI*4/3)*(cos(-M_PI*2*k*2/(3*m))*x3[2*k+1]+sin(-M_PI*2*k*2/(3*m))*x3[2*k]);
                           X[2*(k+m)+1]=x1[2*k+1]+sin(-M_PI*2/3)*(cos(-M_PI*k*2/(3*m))*x2[2*k]-sin(-M_PI*k*2/(3*m))*x2[2*k+1])+cos(-M_PI*2/3)*(cos(-M_PI*k*2/(3*m))*x2[2*k+1]+sin(-M_PI*k*2/(3*m))*x2[2*k]) + sin(-M_PI*4/3)*(cos(-M_PI*2*k*2/(3*m))*x3[2*k]-sin(-M_PI*2*k*2/(3*m))*x3[2*k+1])+cos(-M_PI*4/3)*(cos(-M_PI*2*k*2/(3*m))*x3[2*k+1]+sin(-M_PI*2*k*2/(3*m))*x3[2*k]);
                           X[2*(k+2*m)]=x1[2*k]+cos(-M_PI*2*2/3)*(cos(-M_PI*k*2/(3*m))*x2[2*k]-sin(-M_PI*k*2/(3*m))*x2[2*k+1])-sin(-M_PI*2*2/3)*(cos(-M_PI*k*2/(3*m))*x2[2*k+1]+sin(-M_PI*k*2/(3*m))*x2[2*k]) + cos(-M_PI*4*2/3)*(cos(-M_PI*2*k*2/(3*m))*x3[2*k]-sin(-M_PI*2*k*2/(3*m))*x3[2*k+1])-sin(-M_PI*4*2/3)*(cos(-M_PI*2*k*2/(3*m))*x3[2*k+1]+sin(-M_PI*2*k*2/(3*m))*x3[2*k]);
                           X[2*(k+2*m)+1]=x1[2*k+1]+sin(-M_PI*2*2/3)*(cos(-M_PI*k*2/(3*m))*x2[2*k]-sin(-M_PI*k*2/(3*m))*x2[2*k+1])+cos(-M_PI*2*2/3)*(cos(-M_PI*k*2/(3*m))*x2[2*k+1]+sin(-M_PI*k*2/(3*m))*x2[2*k]) + sin(-M_PI*4*2/3)*(cos(-M_PI*2*k*2/(3*m))*x3[2*k]-sin(-M_PI*2*k*2/(3*m))*x3[2*k+1])+cos(-M_PI*4*2/3)*(cos(-M_PI*2*k*2/(3*m))*x3[2*k+1]+sin(-M_PI*2*k*2/(3*m))*x3[2*k]); 
			}
            
        }
	}
	else
	{
        dft(y,X,m);
    }
}

int main()
{
    int i,m=9;
    float y[18]={1,1,2,0,3,0,4,0,5,1,6,0,5,1,3,7,9,1};
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
