#include<stdio.h>

void Swap(int * x, int * y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void QuickSort(int * a, int l, int r)
{
	if(l < r)
	{
		int pivot = l;
		int i = l;
		int j = r;
		while(i < j)
		{
			while(a[i] <= a[pivot] && i <= r)
			{
				i++;
			}
			while(a[j] > a[pivot])
			{
				j--;
			}
			if(i < j)
			{
				Swap(&a[i],&a[j]);
			}
		}
		Swap(&a[j],&a[pivot]);
		QuickSort(a,l,j-1);
		QuickSort(a,j+1,r);
	}
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n, i;
		scanf("%d",&n);
		int a[n];
		for(i=0;i<n;i++)
		{
			scanf("%d",&a[i]);
		}
		QuickSort(a,0,n-1);
		for(i=0;i<n;i++)
		{
			printf("%d ",a[i]);
		}
		printf("\n");
	}
	return(0);
}
