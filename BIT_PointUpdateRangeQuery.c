#include<stdio.h>

/*
	
* The following code implements Binary Indexed Trees to update an element of an array, and
* return the sum value of all elements in a range.
* Both operations are performed in O(logn)  	
	
*/

// The Update function will update value of A[index] to v

void Update(int BIT[],int n,int index,int v)
{
	int i;
	for(i=index;i<n;i += i&(-i))
	{
		BIT[i] += v;
	}			
}

int Sum_Index(int BIT[], int n, int index)
{
	int i, sum = 0;
	for(i=index;i>0;i -= i&(-i))
	{
		sum += BIT[i];
	}
	return(sum);
}

int Sum(int BIT[], int n, int x, int y)
{
	return(Sum_Index(BIT,n,y) - Sum_Index(BIT,n,x-1));
}

int main()
{
	int n, i, j;
	
	scanf("%d",&n);
	
	int A[n],BIT[n+1];
	
	for(i=0;i<n;i++)
	{
		scanf("%d",&A[i]);
	}
	
	for(i=0;i<=n;i++)
	{
		BIT[i] = 0;
	}	
	
	// The below code creates a BIT of the given array A
	 
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<=n;j += j&(-j))
		{
			BIT[j] += A[i]; 
		}
	}
	
	int q;		// Number of queries
	
	scanf("%d",&q);
	
	while(q--)
	{
		int t;
		// t = 1 means queries are of type "update an element of the array"
		// t = 2 means queries are of type "sum of elements in a range"
		scanf("%d",&t);
		if(t==1)
		{
			int index, v;
			// index is 1 indexed,i.e, index = 1 means A[0]
			scanf("%d %d",&index,&v);
			Update(BIT,n+1,index,v-A[index]);
		}
		else if(t==2)
		{
			int x,y;
			scanf("%d %d",&x,&y);
			// x and y are 1 indexed
			printf("%d\n",Sum(BIT,n+1,x,y));
		}
	}
	return(0);
}
