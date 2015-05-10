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


void sfft(float *X ,float *y,int m)
{
	if (fmod(m,2)==0)
	{
		printf("2有做到\n");
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
		sfft(x1,z,m);sfft(x2,u,m);
		for (k=0;k<=m-1;k++)
		{
                       
                           X[2*k]=x1[2*k]+cos(-M_PI*k/m)*x2[2*k]-sin(-M_PI*k/m)*x2[2*k+1];
                           X[2*k+1]=x1[2*k+1]+cos(-M_PI*k/m)*x2[2*k+1]+sin(-M_PI*k/m)*x2[2*k];
                           X[2*(k+m)]=x1[2*k]-cos(-M_PI*k/m)*x2[2*k]+sin(-M_PI*k/m)*x2[2*k+1];
                           X[2*(k+m)+1]=x1[2*k+1]-cos(-M_PI*k/m)*x2[2*k+1]-sin(-M_PI*k/m)*x2[2*k];
                       
        }
	}
	else if (fmod(m,3)==0)
	{
		printf("3有做到\n");
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
		sfft(x1,z,m);sfft(x2,u,m);sfft(x3,t,m);
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
	else if (fmod(m,5)==0)
	{
		printf("5有做到\n");
        m=m/5;
        float  *z,*u,*t,*p,*q,*x1,*x2,*x3,*x4,*x5;
        z=(float*)malloc(sizeof(float)*5*m );
        u=(float*)malloc(sizeof(float)*5*m );
        t=(float*)malloc(sizeof(float)*5*m );
        p=(float*)malloc(sizeof(float)*5*m );
        q=(float*)malloc(sizeof(float)*5*m );
        x1=(float*)malloc(sizeof(float)*5*m );
        x2=(float*)malloc(sizeof(float)*5*m );
        x3=(float*)malloc(sizeof(float)*5*m );
        x4=(float*)malloc(sizeof(float)*5*m );
        x5=(float*)malloc(sizeof(float)*5*m );
		int i,k;
		for(i=0;i<=m-1;i++) 
		{           
            z[2*i]=y[10*i];z[2*i+1]=y[10*i+1];
            u[2*i]=y[2+10*i];u[2*i+1]=y[3+10*i];
			t[2*i]=y[4+10*i];t[2*i+1]=y[5+10*i];
			p[2*i]=y[6+10*i];p[2*i+1]=y[7+10*i];
			q[2*i]=y[8+10*i];q[2*i+1]=y[9+10*i];	
		}
		sfft(x1,z,m);sfft(x2,u,m);sfft(x3,t,m);sfft(x4,p,m);sfft(x5,q,m);
		for (k=0;k<=m-1;k++)                                                                                                                                                                                                                                                                                                                                                                     
		{
  
                           X[2*k]=x1[2*k]+cos(-M_PI*k*2/(m*5))*x2[2*k]-sin(-M_PI*k*2/(m*5))*x2[2*k+1] + cos(-M_PI*k*2*2/(m*5))*x3[2*k]-sin(-M_PI*k*2*2/(m*5))*x3[2*k+1] + cos(-M_PI*k*2*3/(m*5))*x4[2*k]-sin(-M_PI*k*2*3/(m*5))*x4[2*k+1] + cos(-M_PI*k*2*4/(m*5))*x5[2*k]-sin(-M_PI*k*2*4/(m*5))*x5[2*k+1];
                           X[2*k+1]=x1[2*k+1]+cos(-M_PI*k*2/(m*5))*x2[2*k+1]+sin(-M_PI*k*2/(m*5))*x2[2*k] + cos(-M_PI*k*2*2/(m*5))*x3[2*k+1]+sin(-M_PI*k*2*2/(m*5))*x3[2*k] + cos(-M_PI*k*2*3/(m*5))*x4[2*k+1]+sin(-M_PI*k*2*3/(m*5))*x4[2*k] + cos(-M_PI*k*2*4/(m*5))*x5[2*k+1]+sin(-M_PI*k*2*4/(m*5))*x5[2*k];
                           X[2*(k+m)]=x1[2*k]+cos(-M_PI*2/5)*(cos(-M_PI*k*2/(m*5))*x2[2*k]-sin(-M_PI*k*2/(m*5))*x2[2*k+1])-sin(-M_PI*2/5)*(cos(-M_PI*k*2/(m*5))*x2[2*k+1]+sin(-M_PI*k*2/(5*m))*x2[2*k]) + cos(-M_PI*2*2/5)*(cos(-M_PI*2*k*2/(m*5))*x3[2*k]-sin(-M_PI*2*k*2/(5*m))*x3[2*k+1])-sin(-M_PI*2*2/5)*(cos(-M_PI*2*k*2/(5*m))*x3[2*k+1]+sin(-M_PI*2*k*2/(5*m))*x3[2*k]) + cos(-M_PI*3*2/5)*(cos(-M_PI*k*2*3/(m*5))*x4[2*k]-sin(-M_PI*k*2*3/(m*5))*x4[2*k+1])-sin(-M_PI*3*2/5)*(cos(-M_PI*k*2*3/(m*5))*x4[2*k+1]+sin(-M_PI*k*2*3/(m*5))*x4[2*k]) + cos(-M_PI*4*2/5)*(cos(-M_PI*k*2*4/(m*5))*x5[2*k]-sin(-M_PI*k*2*4/(m*5))*x5[2*k+1])-sin(-M_PI*4*2/5)*(cos(-M_PI*k*2*4/(m*5))*x5[2*k+1]+sin(-M_PI*k*2*4/(m*5))*x5[2*k]);
                           X[2*(k+m)+1]=x1[2*k+1]+sin(-M_PI*2/5)*(cos(-M_PI*k*2/(5*m))*x2[2*k]-sin(-M_PI*k*2/(5*m))*x2[2*k+1])+cos(-M_PI*2/5)*(cos(-M_PI*k*2/(5*m))*x2[2*k+1]+sin(-M_PI*k*2/(5*m))*x2[2*k]) + sin(-M_PI*2*2/5)*(cos(-M_PI*2*k*2/(5*m))*x3[2*k]-sin(-M_PI*2*k*2/(5*m))*x3[2*k+1])+cos(-M_PI*2*2/5)*(cos(-M_PI*2*k*2/(5*m))*x3[2*k+1]+sin(-M_PI*2*k*2/(5*m))*x3[2*k]) + sin(-M_PI*3*2/5)*(cos(-M_PI*k*2*3/(m*5))*x4[2*k]-sin(-M_PI*k*2*3/(m*5))*x4[2*k+1])+cos(-M_PI*3*2/5)*(cos(-M_PI*k*2*3/(m*5))*x4[2*k+1]+sin(-M_PI*k*2*3/(m*5))*x4[2*k]) + sin(-M_PI*4*2/5)*(cos(-M_PI*k*2*4/(m*5))*x5[2*k]-sin(-M_PI*k*2*4/(m*5))*x5[2*k+1])+cos(-M_PI*4*2/5)*(cos(-M_PI*k*2*4/(m*5))*x5[2*k+1]+sin(-M_PI*k*2*4/(m*5))*x5[2*k]);
                           X[2*(k+2*m)]=x1[2*k]+cos(-M_PI*2*2/5)*(cos(-M_PI*k*2/(5*m))*x2[2*k]-sin(-M_PI*k*2/(5*m))*x2[2*k+1])-sin(-M_PI*2*2/5)*(cos(-M_PI*k*2/(5*m))*x2[2*k+1]+sin(-M_PI*k*2/(5*m))*x2[2*k]) + cos(-M_PI*2*2*2/5)*(cos(-M_PI*2*k*2/(5*m))*x3[2*k]-sin(-M_PI*2*k*2/(5*m))*x3[2*k+1])-sin(-M_PI*2*2*2/5)*(cos(-M_PI*2*k*2/(5*m))*x3[2*k+1]+sin(-M_PI*2*k*2/(5*m))*x3[2*k]) + cos(-M_PI*3*2*2/5)*(cos(-M_PI*k*2*3/(m*5))*x4[2*k]-sin(-M_PI*k*2*3/(m*5))*x4[2*k+1])-sin(-M_PI*3*2*2/5)*(cos(-M_PI*k*2*3/(m*5))*x4[2*k+1]+sin(-M_PI*k*2*3/(m*5))*x4[2*k]) + cos(-M_PI*4*2*2/5)*(cos(-M_PI*k*2*4/(m*5))*x5[2*k]-sin(-M_PI*k*2*4/(m*5))*x5[2*k+1])-sin(-M_PI*4*2*2/5)*(cos(-M_PI*k*2*4/(m*5))*x5[2*k+1]+sin(-M_PI*k*2*4/(m*5))*x5[2*k]);
                           X[2*(k+2*m)+1]=x1[2*k+1]+sin(-M_PI*2*2/5)*(cos(-M_PI*k*2/(5*m))*x2[2*k]-sin(-M_PI*k*2/(5*m))*x2[2*k+1])+cos(-M_PI*2*2/5)*(cos(-M_PI*k*2/(5*m))*x2[2*k+1]+sin(-M_PI*k*2/(5*m))*x2[2*k]) + sin(-M_PI*2*2*2/5)*(cos(-M_PI*2*k*2/(5*m))*x3[2*k]-sin(-M_PI*2*k*2/(5*m))*x3[2*k+1])+cos(-M_PI*2*2*2/5)*(cos(-M_PI*2*k*2/(5*m))*x3[2*k+1]+sin(-M_PI*2*k*2/(5*m))*x3[2*k]) + sin(-M_PI*3*2*2/5)*(cos(-M_PI*k*2*3/(m*5))*x4[2*k]-sin(-M_PI*k*2*3/(m*5))*x4[2*k+1])+cos(-M_PI*3*2*2/5)*(cos(-M_PI*k*2*3/(m*5))*x4[2*k+1]+sin(-M_PI*k*2*3/(m*5))*x4[2*k]) + sin(-M_PI*4*2*2/5)*(cos(-M_PI*k*2*4/(m*5))*x5[2*k]-sin(-M_PI*k*2*4/(m*5))*x5[2*k+1])+cos(-M_PI*4*2*2/5)*(cos(-M_PI*k*2*4/(m*5))*x5[2*k+1]+sin(-M_PI*k*2*4/(m*5))*x5[2*k]);
						   X[2*(k+3*m)]=x1[2*k]+cos(-M_PI*3*2/5)*(cos(-M_PI*k*2/(5*m))*x2[2*k]-sin(-M_PI*k*2/(5*m))*x2[2*k+1])-sin(-M_PI*2*3/5)*(cos(-M_PI*k*2/(5*m))*x2[2*k+1]+sin(-M_PI*k*2/(5*m))*x2[2*k]) + cos(-M_PI*2*2*3/5)*(cos(-M_PI*2*k*2/(5*m))*x3[2*k]-sin(-M_PI*2*k*2/(5*m))*x3[2*k+1])-sin(-M_PI*2*2*3/5)*(cos(-M_PI*2*k*2/(5*m))*x3[2*k+1]+sin(-M_PI*2*k*2/(5*m))*x3[2*k]) + cos(-M_PI*3*3*2/5)*(cos(-M_PI*k*2*3/(m*5))*x4[2*k]-sin(-M_PI*k*2*3/(m*5))*x4[2*k+1])-sin(-M_PI*3*3*2/5)*(cos(-M_PI*k*2*3/(m*5))*x4[2*k+1]+sin(-M_PI*k*2*3/(m*5))*x4[2*k]) + cos(-M_PI*4*3*2/5)*(cos(-M_PI*k*2*4/(m*5))*x5[2*k]-sin(-M_PI*k*2*4/(m*5))*x5[2*k+1])-sin(-M_PI*4*3*2/5)*(cos(-M_PI*k*2*4/(m*5))*x5[2*k+1]+sin(-M_PI*k*2*4/(m*5))*x5[2*k]);
                           X[2*(k+3*m)+1]=x1[2*k+1]+sin(-M_PI*3*2/5)*(cos(-M_PI*k*2/(5*m))*x2[2*k]-sin(-M_PI*k*2/(5*m))*x2[2*k+1])+cos(-M_PI*2*3/5)*(cos(-M_PI*k*2/(5*m))*x2[2*k+1]+sin(-M_PI*k*2/(5*m))*x2[2*k]) + sin(-M_PI*2*2*3/5)*(cos(-M_PI*2*k*2/(5*m))*x3[2*k]-sin(-M_PI*2*k*2/(5*m))*x3[2*k+1])+cos(-M_PI*2*2*3/5)*(cos(-M_PI*2*k*2/(5*m))*x3[2*k+1]+sin(-M_PI*2*k*2/(5*m))*x3[2*k]) + sin(-M_PI*3*3*2/5)*(cos(-M_PI*k*2*3/(m*5))*x4[2*k]-sin(-M_PI*k*2*3/(m*5))*x4[2*k+1])+cos(-M_PI*3*3*2/5)*(cos(-M_PI*k*2*3/(m*5))*x4[2*k+1]+sin(-M_PI*k*2*3/(m*5))*x4[2*k]) + sin(-M_PI*4*3*2/5)*(cos(-M_PI*k*2*4/(m*5))*x5[2*k]-sin(-M_PI*k*2*4/(m*5))*x5[2*k+1])+cos(-M_PI*4*3*2/5)*(cos(-M_PI*k*2*4/(m*5))*x5[2*k+1]+sin(-M_PI*k*2*4/(m*5))*x5[2*k]);
						   X[2*(k+4*m)]=x1[2*k]+cos(-M_PI*4*2/5)*(cos(-M_PI*k*2/(5*m))*x2[2*k]-sin(-M_PI*k*2/(5*m))*x2[2*k+1])-sin(-M_PI*2*4/5)*(cos(-M_PI*k*2/(5*m))*x2[2*k+1]+sin(-M_PI*k*2/(5*m))*x2[2*k]) + cos(-M_PI*2*2*4/5)*(cos(-M_PI*2*k*2/(5*m))*x3[2*k]-sin(-M_PI*2*k*2/(5*m))*x3[2*k+1])-sin(-M_PI*2*2*4/5)*(cos(-M_PI*2*k*2/(5*m))*x3[2*k+1]+sin(-M_PI*2*k*2/(5*m))*x3[2*k]) + cos(-M_PI*3*4*2/5)*(cos(-M_PI*k*2*3/(m*5))*x4[2*k]-sin(-M_PI*k*2*3/(m*5))*x4[2*k+1])-sin(-M_PI*3*4*2/5)*(cos(-M_PI*k*2*3/(m*5))*x4[2*k+1]+sin(-M_PI*k*2*3/(m*5))*x4[2*k]) + cos(-M_PI*4*4*2/5)*(cos(-M_PI*k*2*4/(m*5))*x5[2*k]-sin(-M_PI*k*2*4/(m*5))*x5[2*k+1])-sin(-M_PI*4*4*2/5)*(cos(-M_PI*k*2*4/(m*5))*x5[2*k+1]+sin(-M_PI*k*2*4/(m*5))*x5[2*k]);
                           X[2*(k+4*m)+1]=x1[2*k+1]+sin(-M_PI*4*2/5)*(cos(-M_PI*k*2/(5*m))*x2[2*k]-sin(-M_PI*k*2/(5*m))*x2[2*k+1])+cos(-M_PI*2*4/5)*(cos(-M_PI*k*2/(5*m))*x2[2*k+1]+sin(-M_PI*k*2/(5*m))*x2[2*k]) + sin(-M_PI*2*2*4/5)*(cos(-M_PI*2*k*2/(5*m))*x3[2*k]-sin(-M_PI*2*k*2/(5*m))*x3[2*k+1])+cos(-M_PI*2*2*4/5)*(cos(-M_PI*2*k*2/(5*m))*x3[2*k+1]+sin(-M_PI*2*k*2/(5*m))*x3[2*k]) + sin(-M_PI*3*4*2/5)*(cos(-M_PI*k*2*3/(m*5))*x4[2*k]-sin(-M_PI*k*2*3/(m*5))*x4[2*k+1])+cos(-M_PI*3*4*2/5)*(cos(-M_PI*k*2*3/(m*5))*x4[2*k+1]+sin(-M_PI*k*2*3/(m*5))*x4[2*k]) + sin(-M_PI*4*4*2/5)*(cos(-M_PI*k*2*4/(m*5))*x5[2*k]-sin(-M_PI*k*2*4/(m*5))*x5[2*k+1])+cos(-M_PI*4*4*2/5)*(cos(-M_PI*k*2*4/(m*5))*x5[2*k+1]+sin(-M_PI*k*2*4/(m*5))*x5[2*k]);   
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
    float y[12]={1,1,2,0,3,0,4,1,5,2,6,2};
    float *X; 
    X=(float*)malloc(sizeof(float)* 2*m );
    //dft(y,X,m);
    sfft(X,y,m);
    for (i=0;i<=2*m-1;i++)
    {
    printf("%f\n",X[i]);
    }
    system("pause");                                                                                                                                                                                                                                                                                                                                                                                                                                                            
    return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  


