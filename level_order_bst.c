#include<stdio.h>
#include<stdlib.h>

typedef struct _node
{
	int data;
	struct _node * left;
	struct _node * right;
}node;

node* Insert_Node(int k,node * root)
{
	if(root==NULL)
	{	
		root = (node*)malloc(sizeof(node));
		root->data = k;
		root->left = NULL;
		root->right = NULL;
		return(root);
	}
	if(k < root->data)
	{
		root->left = Insert_Node(k,root->left);
	}
	if(k > root->data)
	{
		root->right = Insert_Node(k,root->right);
	}
	return(root);
}

int Height(node * root)
{
	if(root == NULL)
	{
		return(0);
	}
	int lh = Height(root->left);
	int rh = Height(root->right);
	if(lh > rh)
	{
		return(lh + 1);
	}
	else
	{
		return(rh + 1);
	}
}

void Level_Order(int height, node * root)
{
	if(root == NULL)
	{
		return;
	}
	if(height == 1)
	{
		printf("%d ",root->data);
	}
	else if(height > 1)
	{
		Level_Order(height-1,root->left);
		Level_Order(height-1,root->right);
	}
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n, i, k;
		node * root = NULL;
		scanf("%d",&n);
		for(i=0;i<n;i++)
		{
			scanf("%d",&k);
			root = Insert_Node(k,root);
		}
		int height = Height(root);
		for(i=1;i<=height;i++)
		{
			Level_Order(i,root);
			printf("\n");
		}
	}
	return(0);
}
