/*

Given array A of N size and M operations of type:

	1.  Add v to all elements in a range.
	2.  Multiply v to all elements in a range.
	3.  Reset all items to v in a range.
	4.  Report sum in a range.

*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int MOD = 1000000007;

typedef unsigned long long int ll; 

struct Tree
{
	ll sum;
	ll mul;
	ll add;
	ll val;
};

void Create_Segment_Tree(int A[], struct Tree tree[], int low, int high, int pos)
{
	if(low == high)
	{
		tree[pos].sum = A[low];
		tree[pos].mul = 1;
		tree[pos].add = 0;
		tree[pos].val = -1;
		return;	
	}
	
	int mid = (low + high) / 2;
	Create_Segment_Tree(A,tree,low,mid,2*pos+1);
	Create_Segment_Tree(A,tree,mid+1,high,2*pos+2);
	
	int lc = 2*pos+1;
	int rc = 2*pos+2;
	
	tree[pos].sum = (tree[lc].sum + tree[rc].sum) % MOD;
	tree[pos].mul = 1;
	tree[pos].add = 0;
	tree[pos].val = -1;		
}

void Check_Laziness(struct Tree tree[], int low, int high, int x, int y, int pos)
{
	int lc = 2*pos + 1;
	int rc = 2*pos + 2;
	if(tree[pos].val != -1)
	{
		tree[pos].sum=((high - low + 1) * tree[pos].val) % MOD;
		if(high!=low)
		{
			tree[lc].val=tree[pos].val;
			tree[rc].val=tree[pos].val;
			tree[lc].add=tree[pos].add;
			tree[rc].add=tree[pos].add;
			tree[lc].mul=tree[pos].mul;
			tree[rc].mul=tree[pos].mul;
		}
	}
	else if(low != high)
	{
		tree[lc].add=(tree[lc].add * tree[pos].mul)%MOD;
		tree[lc].add=(tree[lc].add + tree[pos].add)%MOD;
		tree[lc].mul=(tree[lc].mul * tree[pos].mul)%MOD;
		tree[rc].add=(tree[rc].add * tree[pos].mul)%MOD;
		tree[rc].add=(tree[rc].add + tree[pos].add)%MOD;
		tree[rc].mul=(tree[rc].mul * tree[pos].mul)%MOD;
	}
	tree[pos].sum = (tree[pos].sum * tree[pos].mul) % MOD;
	tree[pos].sum = (tree[pos].sum + tree[pos].add * (high - low + 1)) % MOD;
	tree[pos].add=0;
	tree[pos].mul=1;
	tree[pos].val=-1;
}

void Range_Add(struct Tree tree[], ll v, int low, int high, int x, int y, int pos)
{
	if(tree[pos].mul != 1 || tree[pos].add != 0 || tree[pos].val != -1)
	{
		Check_Laziness(tree,low,high,x,y,pos);	
	}
	if(low > y || high < x)
	{
		return;
	}
	if(x <= low && y>= high)
	{
		tree[pos].sum = (tree[pos].sum + v * (high - low + 1)) % MOD;
		if(high != low)
		{
			ll lc = 2*pos+1;
			ll rc = 2*pos+2;
			tree[lc].add = (tree[lc].add + v) % MOD;
			tree[rc].add = (tree[rc].add + v) % MOD;
		}
		return;
	}
	int mid = (low + high)/2;
	Range_Add(tree,v,low,mid,x,y,2*pos+1);
	Range_Add(tree,v,mid+1,high,x,y,2*pos+2);
	tree[pos].sum = (tree[2*pos+1].sum + tree[2*pos+2].sum) % MOD;
}

void Range_Mul(struct Tree tree[], ll v, int low, int high, int x, int y, int pos)
{
	if(tree[pos].mul != 1 || tree[pos].add != 0 || tree[pos].val != -1)
	{
		Check_Laziness(tree,low,high,x,y,pos);
	}
	if(low > y || high < x)
	{
		return;
	}
	if(x <= low && y>= high)
	{
		tree[pos].sum = (tree[pos].sum * v) % MOD;
		if(high != low)
		{
			ll lc = 2*pos + 1;
			ll rc = 2*pos + 2;
			tree[lc].mul = (tree[lc].mul * v) % MOD;
			tree[lc].add = (tree[lc].add * v) % MOD;
			tree[rc].mul = (tree[rc].mul * v) % MOD;
			tree[rc].add = (tree[rc].add * v) % MOD;
		}
		return;
	}
	int mid = (low + high)/2;
	Range_Mul(tree,v,low,mid,x,y,2*pos+1);
	Range_Mul(tree,v,mid+1,high,x,y,2*pos+2);
	
	tree[pos].sum = (tree[2*pos+1].sum + tree[2*pos+2].sum) % MOD;
}

void Range_Init(struct Tree tree[], ll v, int low, int high, int x, int y, int pos)
{
	if(tree[pos].mul != 1 || tree[pos].add != 0 || tree[pos].val != -1)
	{
		Check_Laziness(tree,low,high,x,y,pos);
	}
	if(low > y || high < x)
	{
		return;
	}
	if(x <= low && y>= high)
	{
		tree[pos].sum = (v * (high - low + 1)) % MOD;
		if(high != low)
		{
			ll lc = 2*pos + 1;
			ll rc = 2*pos + 2;
			tree[lc].mul = 1;
			tree[rc].mul = 1;
			tree[lc].add = 0;
			tree[rc].add = 0;
			tree[lc].val = v;
			tree[rc].val = v;
		}
		return;
	}
	int mid = (low + high)/2;
	Range_Init(tree,v,low,mid,x,y,2*pos+1);
	Range_Init(tree,v,mid+1,high,x,y,2*pos+2);
	
	tree[pos].sum = (tree[2*pos+1].sum + tree[2*pos+2].sum) % MOD;
}

ll Range_Sum(struct Tree tree[], int low, int high, int x, int y, int pos)
{
	if(tree[pos].mul != 1 || tree[pos].add != 0 || tree[pos].val != -1)
	{
		Check_Laziness(tree,low,high,x,y,pos);
	}
	if(x > high || y < low)
	{
		return(0);	
	}
	if(x <= low && y>= high)
	{
		return(tree[pos].sum);
	}
	int mid = (low + high)/2;
	ll l_query = Range_Sum(tree,low,mid,x,y,2*pos+1);
	ll r_query = Range_Sum(tree,mid+1,high,x,y,2*pos+2);
	ll sum = (l_query + r_query) % MOD;
	return(sum);
}

int main()
{
	int n, q, i;
	scanf("%d %d",&n,&q);
	int A[n];
	for(i=0;i<n;i++)
	{
		scanf("%d",&A[i]);
	}
	ll s = (ceil(log2(n)));
	s = 2 * pow(2,s)-1;
	struct Tree * tree=(struct Tree *)malloc(sizeof(struct Tree) * s);
	for(i=0;i<s;i++)
	{
		tree[i].sum=0;
		tree[i].add=0;
		tree[i].mul=1;
		tree[i].val=-1;
	}
	Create_Segment_Tree(A,tree,0,n-1,0);
	/*for(i=0;i<4*n;i++)
	{
		printf("%llu ",tree[i].sum);
	}
	printf("\n");*/
	while(q--)
	{
		int t, x, y;
		ll v;
		scanf("%d",&t);
		if(t==1)
		{
			scanf("%d %d %llu",&x,&y,&v);
			Range_Add(tree,v,0,n-1,x-1,y-1,0);
		}
		else if(t==2)
		{
			scanf("%d %d %llu",&x,&y,&v);
			Range_Mul(tree,v,0,n-1,x-1,y-1,0);
		}
		else if(t==3)
		{
			scanf("%d %d %llu",&x,&y,&v);
			Range_Init(tree,v,0,n-1,x-1,y-1,0);
		}
		else
		{
			scanf("%d %d",&x,&y);
			printf("%llu\n",Range_Sum(tree,0,n-1,x-1,y-1,0));
		}
		/*for(i=0;i<15;i++)
		{
			printf("%llu %llu %llu %llu %llu\n",tree[i].sum,tree[i].val,tree[i].mul,tree[i].add,tree[i].range);
		}
		printf("\n");*/
	}
	return(0);
}
