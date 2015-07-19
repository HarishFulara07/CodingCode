#include<stdio.h>
#include<stdlib.h>

int ind = 0;

void InOrder(int arr[],int in_order[],int n,int pos)
{
	if(pos >= n)
	{
		return;
	}
	InOrder(arr,in_order,n,2*pos+1);
	in_order[ind] = arr[pos];
	//printf("%d ",);
	ind++;
	InOrder(arr,in_order,n,2*pos+2);
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n, i, k, flag = 0;
		scanf("%d",&n);
		int arr[n], in_order[n];
		for(i=0;i<n;i++)
		{
			scanf("%d",&arr[i]);
		}

		InOrder(arr,in_order,n,0);
		
		for(i=0;i<n-1;i++)
		{
			if(in_order[i] > in_order[i+1])
			{
				flag = 1;
				break;
			}
		}
		if(flag == 1)
		{
			printf("NO\n");
		}
		else
		{
			printf("YES\n");
		}
		ind = 0;
	}
	return(0);
}
	
