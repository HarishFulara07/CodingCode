#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ind = -1;

void Swap(int * x, int * y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

int Min(int * heap, int l, int r)
{
	if(r > ind && l > ind)
	{
		return(-1);
	}
	if(r > ind)
	{
		return(l);
	}
	if(heap[l] <= heap[r])
	{
		return(l);
	}
	return(r);
}

void PercolateUp(int * heap, int pos)
{
	if(pos == 0)
	{
		return;
	}
	int p = (pos - 1)/2;
	if(heap[pos] >= heap[p])
	{
		return;
	}
	while(heap[pos] < heap[p] && p >= 0)
	{
		Swap(&heap[pos],&heap[p]);
		pos = p;
		p = (pos - 1)/2;
	}
}

void PercolateDown(int * heap, int pos)
{
	int l = 2*pos + 1;
	int r = 2*pos + 2;
	if(l > ind && r > ind)
	{
		return;
	}
	int min = Min(heap,l,r);
	if(heap[pos] <= heap[min])
	{
		return;
	}
	while(heap[pos] > heap[min] && min != -1)
	{
		Swap(&heap[pos],&heap[min]);
		pos = min;
		l = 2*pos + 1;
		r = 2*pos + 2;
		min = Min(heap,l,r);
	}
}

void Insert(int * heap, int val)
{
	ind++;
	heap[ind] = val;
	PercolateUp(heap,ind);
}

void Delete(int * heap, int pos)
{
	Swap(&heap[pos],&heap[ind]);
	ind--;
	PercolateDown(heap,pos);
}

void DecreaseKey(int * heap, int pos, int dec)
{
	heap[pos] -= dec;
	PercolateUp(heap,pos);
}

void IncreaseKey(int * heap, int pos, int inc)
{
	heap[pos] += inc;
	PercolateDown(heap,pos);
}

int main()
{
	int size;
	scanf("%d",&size);
	int heap[size];
	char ch[20];
	while(1)
	{
		scanf("%s",ch);
		if(strcasecmp(ch,"insert")==0)
		{
			int val;
			scanf("%d",&val);
			Insert(heap,val);
		}
		else if(strcasecmp(ch,"delete")==0)
		{
			int pos;
			scanf("%d",&pos);
			Delete(heap,pos-1);			//pos is 1 indexed
		}
		else if(strcasecmp(ch,"min")==0)
		{
			printf("%d\n",heap[0]);
		}
		else if(strcasecmp(ch,"deletemin")==0)
		{
			Delete(heap,0);
		}
		else if(strcasecmp(ch,"decreasekey")==0)
		{
			int pos, dec;
			scanf("%d %d",&pos,&dec);		//pos is 1 indexed
			DecreaseKey(heap,pos-1,dec);
		}
		else if(strcasecmp(ch,"increasekey")==0)
		{
			int pos, inc;
			scanf("%d %d",&pos,&inc);		//pos is 1 indexed
			IncreaseKey(heap,pos-1,inc);
		}
		else if(strcasecmp(ch,"print")==0)
		{
			int i;
			for(i=0;i<=ind;i++)
			{
				printf("%d ",heap[i]);
			}
			printf("\n");
		}
		else if(strcasecmp(ch,"exit")==0)
		{
			break;
		}
	}
	return(0);
}
