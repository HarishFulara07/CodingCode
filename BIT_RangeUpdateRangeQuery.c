#include<stdio.h>

void Update(int BIT[], int n, int index, int v)
{
	int i;
	for(i=index;i<n;i += i&(-i))
	{
		BIT[i] += v;
	}
}
	
void Range_Update(int BIT1[], int BIT2[], int n, int x, int y, int v)
{
	Update(BIT1,n,x,v);
	Update(BIT1,n,y+1,-v);
	Update(BIT2,n,x,v * (x - 1));
	Update(BIT2,n,y+1, -(v * y)); 
}

int Sum(int BIT[], int n, int index)
{
	int i, sum = 0;
	for(i=index;i>0;i -= i&(-i))
	{
		sum += BIT[i]; 
	}
	return(sum);
}

int Range_Sum(int BIT1[], int BIT2[], int n, int x, int y)
{
	int sum1 = (Sum(BIT1,n,y) * y) - Sum(BIT2,n,y);
	int sum2 = (Sum(BIT1,n,x-1) * (x-1)) - Sum(BIT2,n,x-1);
	//printf("%d %d",sum1,sum2);
	return(sum1 - sum2); 
}

int main()
{
	int n, q, i;
	scanf("%d %d",&n,&q);
	int A[n], BIT1[n+1], BIT2[n+1];
	for(i=0;i<=n;i++)
	{
		BIT1[i] = 0;
		BIT2[i] = 0;
	}
	for(i=0;i<n;i++)
	{
		scanf("%d",&A[i]);
		Range_Update(BIT1,BIT2,n+1,i+1,i+1,A[i]);
	}
	while(q--)
	{
		int t;
		scanf("%d",&t);
		// t = 1 is a range update type query
		// t = 2 is a range sum type query
		if(t==1)
		{
			int x,y,v;
			// x and y are 1 indexed
			scanf("%d %d %d",&x,&y,&v);
			Range_Update(BIT1,BIT2,n+1,x,y,v);
		}
		else if(t==2)
		{
			int x,y;
			// x and y are 1 indexed
			scanf("%d %d",&x,&y);
			printf("%d\n",Range_Sum(BIT1,BIT2,n+1,x,y));
		}
		/*
		for(i=0;i<=n;i++)
		{
			printf("%d ",BIT1[i]);
		}
		printf("\n");
		for(i=0;i<=n;i++)
		{
			printf("%d ",BIT2[i]);
		}
		printf("\n");
		*/
	}
	return(0);
}
