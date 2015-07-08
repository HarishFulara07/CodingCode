#include<stdio.h>

/*

* Segment Tree can be used effectively for range update and range query type of problems
* Range update will update all the elements in range x to y by adding value v to all the elements in segment tree from x to y  
* Range query will return the sum of elements in range x to y
* Segment Tree with lazy propagation can be used to perform above two operations in O(lg(n)) 

*/

void Create_Segment_Tree(int A[], int tree[], int low, int high, int pos)
{
	if(low == high)
	{
		tree[pos] = A[low];
		return; 
	}
	int mid = (low + high)/2;
	Create_Segment_Tree(A,tree,low,mid,2*pos+1);
	Create_Segment_Tree(A,tree,mid+1,high,2*pos+2);
	tree[pos] = tree[2*pos+1] + tree[2*pos+2];
}

void update(int tree[], int lazy[], int v, int low, int high, int x, int y, int pos)
{
	if(lazy[pos] != 0)
	{
		tree[pos] += (high - low + 1) * lazy[pos];
		if(low != high)
		{
			lazy[2*pos + 1] += lazy[pos];
			lazy[2*pos + 2] += lazy[pos];
		}
		lazy[pos] = 0;	
	}
	if(x > high || y < low)
	{
		return;	
	}
	if(x <= low && y>= high)
	{
		tree[pos] += (high - low + 1) * v;
		if(low != high)
		{
			lazy[2*pos + 1] += v;
			lazy[2*pos + 2] += v;			
		}
		return;
	}
	int mid = (low + high)/2;
	update(tree,lazy,v,low,mid,x,y,2*pos+1);
	update(tree,lazy,v,mid+1,high,x,y,2*pos+2);
	tree[pos] = tree[2*pos + 1] + tree[2*pos + 2];
}

int query(int tree[], int lazy[], int low, int high, int x, int y, int pos)
{
	if(lazy[pos] != 0)
	{
		tree[pos] += (high - low + 1) * lazy[pos];
		if(low != high)
		{
			lazy[2*pos + 1] += lazy[pos];
			lazy[2*pos + 2] += lazy[pos];
		}
		lazy[pos] = 0;	
	}
	if(x > high || y < low)
	{
		return(0);	
	}
	if(x <= low && y>= high)
	{
		return(tree[pos]);
	}
	int mid = (low + high)/2;
	int l_query = query(tree,lazy,low,mid,x,y,2*pos+1);
	int r_query = query(tree,lazy,mid+1,high,x,y,2*pos+2);
	return(l_query + r_query);
}

int main()
{
	int n, q, i;				// n is the size of array and q is the number of queries
	scanf("%d %d",&n,&q);
	int A[n], tree[4*n], lazy[4*n];
	for(i=0;i<n;i++)
	{
		scanf("%d",&A[i]);
	}
	for(i=0;i<4*n;i++)
	{
		tree[i] = 0;
		lazy[i] = 0;
	}
	Create_Segment_Tree(A,tree,0,n-1,0);
	/*
	for(i=0;i<4*n;i++)
	{
		printf("%d ",tree[i]);
	}
	printf("\n");
	*/
	while(q--)
	{
		int t,x,y,v;
		scanf("%d %d %d",&t,&x,&y);
		if(t==1)
		{
			scanf("%d",&v);
			update(tree,lazy,v,0,n-1,x-1,y-1,0);
		}
		else if(t==2)
		{
			printf("%d\n",query(tree,lazy,0,n-1,x-1,y-1,0));
		}
		/*
		for(i=0;i<4*n;i++)
		{
			printf("%d ",tree[i]);
		}
		printf("\n");
		for(i=0;i<4*n;i++)
		{
			printf("%d ",lazy[i]);
		}
		printf("\n");
		*/
	}
	return(0);
}
