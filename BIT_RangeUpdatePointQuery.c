#include<stdio.h>

/*
	
* The following code implements Binary Indexed Trees to update an element of an array, and
* return the sum value of all elements in a range.
* Both operations are performed in O(logn)  	
	
*/

// The Update function will update value of A[index] to v

void Update_Index(int BIT[],int n,int index,int v)
{
	int i;
	for(i=index;i<n;i += i&(-i))
	{
		BIT[i] += v;
	}			
}

void Update(int BIT[],int n,int x,int y,int v)
{
	Update_Index(BIT,n,x,v);
	Update_Index(BIT,n,y+1,-v);			
}

int Value_At_Index(int BIT[], int n, int index)
{
	int i, sum = 0;
	for(i=index;i>0;i -= i&(-i))
	{
		sum += BIT[i];
	}
	return(sum);
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
	
	int q;		// Number of queries
	
	scanf("%d",&q);
	
	while(q--)
	{
		int t;
		// t = 1 means queries are of type "update elements of the array in range x to y by adding value v to each of them"
		// t = 2 means queries are of type "value at an index of the array"
		scanf("%d",&t);
		if(t==1)
		{
			int x, y, v;
			// x and y are 1 indexed
			scanf("%d %d %d",&x,&y,&v);
			Update(BIT,n+1,x,y,v);
		}
		else if(t==2)
		{
			int index;
			scanf("%d",&index);
			// index is 1 indexed
			printf("%d\n",Value_At_Index(BIT,n+1,index) + A[index-1]);
		}
	}
	return(0);
}
