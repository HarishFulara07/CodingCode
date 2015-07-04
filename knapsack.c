#include<stdio.h>

#define max(x,y) x >= y ? x : y

/*

* Given a bag which can only take certain weight W. 
* Given list of items with their weights and price. 
* How do you fill this bag to maximize value of items in the bag?

*/

void Knapsack_Problem(int max_weight, int n, int weight[], int value[], int knapsack[][max_weight+1])
{
	int i, j;
	for(i=1;i<n;i++)
	{
		int present_weight = weight[i];
		int present_value = value[i];
		
		for(j=0;j <= max_weight;j++)
		{
			if(j < present_weight)
			{
				knapsack[i][j] = knapsack[i-1][j];
			}
			else
			{
				knapsack[i][j] = max(knapsack[i-1][j], present_value + knapsack[i-1][j - present_weight]);
			}
		}
	}
}
 
int main()
{
	int max_weight, n;
	scanf("%d %d",&n,&max_weight);
	int weight[n], value[n], i;
	for(i=0;i<n;i++)
	{
		scanf("%d %d",&weight[i],&value[i]);
	}
	int knapsack[n][max_weight + 1];
	
	//This for loop initialises the knapsack array's 1st row 
	
	for(i=0;i <= max_weight;i++)
	{
		if(i < weight[0])
		{
			knapsack[0][i] = 0;
		}
		else
		{
			knapsack[0][i] = value[0];
		}
	}
	
	//Function to calculate the answer for our problem using dynamic programming
	
	Knapsack_Problem(max_weight,n,weight,value,knapsack);
	
	printf("%d\n",knapsack[n-1][max_weight]);
	
	return(0);
}
