#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int val;
	struct Node * next;
	struct Node * prev;
}node;
 
void Insert(int k,node ** head, node ** tail)
{
	node * new_node = (node *)malloc(sizeof(node));
	new_node->val = k;
	new_node->next = NULL;
	new_node->prev = NULL;
	if(*head == NULL && *tail == NULL)
	{
		*head = new_node;
		*tail = new_node;
		return;
	}
	(*tail)->next = new_node;
	new_node->prev = *tail;
	*tail = new_node;
}

void Swap(int * x, int * y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void QuickSort(node * head, node * tail, int l, int r)
{
	if(l < r)
	{
		node * pivot = head;
		node * i = head;
		node * j = tail;
		int count = l;
		int pos = r;
		while(count < pos)
		{
			while(i->val <= pivot->val && count <= r)
			{	
				if(count != r)
				{
					i = i->next;
				}
				count++;
			}
			while(j->val > pivot->val)
			{
				j = j->prev;
				pos--;
			}
			if(count < pos)
			{
				Swap(&(i->val),&(j->val));
			}
		}
		Swap(&(j->val),&(pivot->val));
		QuickSort(head,j->prev,l,pos-1);
		QuickSort(j->next,tail,pos+1,r);
	}
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n, i, k;
		node * head = NULL;
		node * tail = NULL;
		scanf("%d",&n);
		for(i=0;i<n;i++)
		{
			scanf("%d",&k);
			Insert(k,&head,&tail);
		}
		node * temp = head;
		QuickSort(head,tail,0,n-1);
		while(temp != NULL)
		{
			printf("%d ",temp->val);
			temp = temp->next;
		}
		printf("\n");
	}
	return(0);
}
