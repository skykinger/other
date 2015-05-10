#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void swap(int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

void separate(int *input,int first,int last,int *separate_point)
{
	int temp;
	int k; 
    int x = input[first];
    int nseparate = first;
	for (int unknown = first+1; unknown <= last; unknown++)
	{
		if (input[unknown] < x)
		{
			k++;
			nseparate++;
			swap(&input[nseparate],&input[unknown]);
		}
	}
swap(&input[first],&input[nseparate]);
*separate_point = nseparate;
}

int mid_qsort(int *input,int first, int last,int separate_point,int find)
{
	if (first <= last) 
	{
		separate(input, first, last, &separate_point);
		if (find==separate_point )
		{
			int g;
			g=input[find];
			return g;
		}
		else if(find<separate_point)
		{
		mid_qsort(input, first, separate_point-1,separate_point,find);
	    }
		else if(find>separate_point)
		{  
		mid_qsort(input, separate_point+1, last,separate_point,find);
		} 
	}
}

void qsort(int *input,int first, int last,int separate_point)
{
	if (first < last) 
	{
		separate(input, first, last, &separate_point);
		qsort(input, first, separate_point-1,separate_point);
		qsort(input, separate_point+1, last,separate_point);
	}
}  


int main()
{
	time_t T=0;
    srand(time(&T));
    int i;
	int N;
	printf("請輸入N值:");
	scanf("%d",&N);
	int *data,*mid_data;
	data=(int*)malloc(N*sizeof(int) );
	mid_data=(int*)malloc(N*sizeof(int) );
	for (i=0;i<N;i++)
	{
		data[i]=rand()%100;
		mid_data[i]=data[i];
		printf("原本的data=%d\n",data[i]);
	}
	int first,last,separate_point;
	first=0;
	last=N-1;
	separate_point=0;
	int mid=(first+last)/2;
	int mid_term;
	mid_term=mid_qsort(mid_data,first, last,separate_point,mid);
	qsort(data,first,last,separate_point);
	for (int i=0;i<N;i++)
	{
	printf("i=%d 排完後=%d\n",i,data[i]);
    }
    printf("第幾個數=%d 中位數=%d\n",mid,mid_term);
	return 0;
	system("pause");
}
