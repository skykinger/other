#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void separate(int *input,int first,int last,int *separate_point)
{
	int temp; 
    int x = input[first];
    int current_separate = first;
	for (int unknown = first+1; unknown <= last; unknown++)
	{
		if (input[unknown] < x)
		{
			(current_separate)++;
            temp=input[current_separate];
            input[current_separate]=input[unknown];
            input[unknown]=temp;
		}
	}
temp=input[first]; 
input[first]=input[current_separate];
input[current_separate]=temp;
*separate_point = current_separate;
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
	int *data;
	data=(int*)malloc(N*sizeof(int) );
	int *space;
	space=(int*)malloc(N*sizeof(int) );
	for (i=0;i<N;i++)
	{
		data[i]=rand()%100;
		printf("原本的data=%d\n",data[i]);
	}
	int first,last,separate_point;
	first=0;
	last=N-1;
	separate_point=0;
	qsort(data,first,last,separate_point);
	for (int i=0;i<N;i++)
	{
	printf("排完後=%d\n",data[i]);
    }
	return 0;
	system("pause");
}
