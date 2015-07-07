#include<stdio.h>

/*

Count frequencies of all elements in array in O(1) extra space and O(n) time where 
each element in an array can vary from 0 to n-1

*/

int main()
{
	int n, i, max, tmp;
	scanf("%d",&n);
	int arr[n];
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	max = n;
	for(i=0;i<n;i++)
	{
		while(1)
		{
			tmp = arr[i];
			if(tmp < 0)
			{
				break;
			}
			if(tmp == max)
			{
				arr[i] = max;
				arr[tmp] = -1;
			}
			if(arr[tmp] < 0)
			{
				arr[i] = max;
				arr[tmp]--;
				break;
			}
			else
			{
				arr[i] = arr[tmp];
				arr[tmp] = -1;
			}
		}
	}
	printf("The repeating numbers are : ");
	for(i=0;i<n;i++)
	{
		if(arr[i] < -1)
		{
			printf("%d ",i);
		}
	}
	printf("\n");
	return(0);
}
