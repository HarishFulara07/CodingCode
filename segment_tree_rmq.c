#include<stdio.h>
#define MAX 1000000010

/*

* The program implements range minimum query using segment tree
* Segement Tree is implemented using arrays

*/

int min(int x,int y)
{
	return(x <= y ? x : y);	
}

/*

* Function to create Segmet Tree array b[] using the original array a[] 

*/

void Create_Segment_Tree(int a[], int b[], int low, int high, int pos)
{
	if(low == high)
	{
		b[pos] = a[low];
		return;
	}
	int mid = (low + high)/2;
	Create_Segment_Tree(a,b,low,mid,2*pos + 1);
	Create_Segment_Tree(a,b,mid+1,high,2*pos + 2);
	b[pos] = min(b[2*pos + 1],b[2*pos + 2]);	
}

/*

* Function to find minimum over a queried range from l to r
* low and high is actual range from 0 to n-1

*/ 

int RMQ(int b[], int low, int high, int l, int r, int pos)
{
	if(l <= low && r >= high)
	{
		return(b[pos]);
	}
	if(high < l || low > r)
	{
		return(MAX);
	}
	int mid = (low + high)/2;
	return(min(RMQ(b,low,mid,l,r,2*pos + 1),RMQ(b,mid+1,high,l,r,2*pos + 2)));
}

int main()
{
	int n, q, i;
	scanf("%d %d",&n,&q);
	int a[n];
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	int b[4 * n];
	for(i=0;i<4*n;i++)
	{
		b[i] = MAX;
	}
	Create_Segment_Tree(a,b,0,n-1,0);
	while(q--)
	{
		int l, r;
		scanf("%d %d",&l,&r);
		printf("%d\n",RMQ(b,0,n-1,l,r,0));
	}
	return(0);
}
