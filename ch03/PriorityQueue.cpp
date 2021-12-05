#include<stdio.h>
#include<stdlib.h>
#define MinPQSize (10)
#define MinData (-32767) 
#define MaxSize (1000)
struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;
PriorityQueue Initialize(int MaxElements);
void Destroy(PriorityQueue H);
void MakeEmpty(PriorityQueue H);
void Insert(int x,PriorityQueue H);
int DeleteMin(PriorityQueue H);
int FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue  H);

struct  HeapStruct
{
	int Capacity;
	int Size;
	int *Elements;
};
PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;
	if(MaxElements<MinPQSize)
	{
		printf(" Priority queue size too small");
		return NULL;
	}
	H=(HeapStruct*)malloc(sizeof(struct HeapStruct));
	if(H==NULL)
	    printf("Out of space!!!");
	H->Elements=(int*)malloc((MaxElements+1)*sizeof(int));
	if(H->Elements==NULL)
	    printf("Out of space!!!");
	H->Capacity=MaxElements;
	H->Size=0;
	H->Elements[0]=MinData;
	return H;
}

void Insert(int x,PriorityQueue H)
{
	int i;
	if(IsFull(H))
	{
		printf("Priority queue is full");
		return;
	}
	for(i=++H->Size;H->Elements[i/2]>x;i/=2)
	    H->Elements[i]=H->Elements[i/2];
	H->Elements[i]=x;
}
int DeleteMin(PriorityQueue H)
{
	int i,Child;
	int MinElement,LastElement;
	if(IsEmpty(H))
	{
		printf("Priority queue is empty");
		return H->Elements[0];
	}
	MinElement=H->Elements[1];
	LastElement=H->Elements[H->Size--];
	for(i=1;i*2<=H->Size;i=Child)
	{
		Child=i*2;
		if(Child!=H->Size&&H->Elements[Child+1]<H->Elements[Child])
		Child++;
		if(LastElement>H->Elements[Child])
		    H->Elements[i]=H->Elements[Child];
		else
		    break;
	}
	H->Elements[i]=LastElement;
	return MinElement;
}
int IsEmpty(PriorityQueue H)
{
	return H->Size==0;
}
int IsFull(PriorityQueue H)
{
	return H->Size==H->Capacity;
}
void Destroy(PriorityQueue H)
{
	free(H->Elements);
	free(H);
}
int main()
{
	PriorityQueue H;
	int i,j=0;
	
	H=Initialize(MaxSize);
	for(i=0,j=MaxSize/2;i<MaxSize;i++,j=(j+71)%MaxSize)
	Insert(j,H);
	j=0;
	while(!IsEmpty(H))
	if(DeleteMin(H)!=j++)
	   printf("Error in DeleteMin,%d\n",j);
	printf("Done...\n");
	return 0;
}
