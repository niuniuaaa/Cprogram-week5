#include<stdio.h>
#include<stdlib.h>
#define MinTableSize (10)
#define NumItems 400
typedef unsigned int Index;
struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;
HashTable InitializeTable(int TableSize);
void DestoryTable(HashTable H);
Position Find(int key,HashTable H);
void Insert(int key,HashTable H);
int Retrieve(Position P);

struct ListNode
{
	int data;
	Position Next;
};
typedef Position List;

struct HashTbl
{
	int TableSize;
	List *TheLists;
};
int Retrieve(Position P){return P->data;}
int NextPrime(int N)
{
	int i;
	if(N%2==0) N++;
	for(;;N+=2)
	{
	    for(i=3;i*i<=N;i+=2)
		    if(N%i==0)
			goto ContOuter;
	return N;
	ContOuter:;	
	}
}
Index Hash(int key,int TableSize)
{
	return key%TableSize;
}
//³õÊ¼»¯
HashTable InitializeTable(int TableSize)
{
    HashTable H;
	int i;	
	if(TableSize<MinTableSize)
	{
		printf("Table size too small");
		return NULL;
	}
	H=(HashTbl*)malloc(sizeof(struct HashTbl));
	if(H==NULL)
	    printf("Out of space!!!");
	H->TableSize=NextPrime(TableSize);
	H->TheLists=(List*)malloc(sizeof(List)*H->TableSize);
	if(H->TheLists==NULL)
	    printf("Out of space!!!");
	for(i=0;i<H->TableSize;i++)
	{
		if(H->TheLists[i]==NULL)
		    printf("Out of space!!!");
		else
		    H->TheLists[i]->Next=NULL;//??????????????????????????????????????????//
	}
	return H;
} 
Position Find(int key,HashTable H)
{
	Position P;
	List L;
	L=H->TheLists[Hash(key,H->TableSize)];
	P=L->Next;
	while(P!=NULL&&P->data!=key)
	    P=P->Next;
	    return P;
}

void Insert(int key,HashTable H)
{
	Position Pos,NewCell;
	List L;
	Pos=Find(key,H);
	if(Pos==NULL)
	{
		NewCell=(ListNode*)malloc(sizeof(struct ListNode));
		if(NewCell==NULL)
		    printf("Out of space!!");
		else
		{
			L=H->TheLists[Hash(key,H->TableSize)];
			NewCell->Next=L->Next;
			NewCell->data=key;
			L->Next=NewCell;
		}
	}
}
void DestroyTable(HashTable H)
{
	int i;
	
	for(i=0;i<H->TableSize;i++)
	{
		Position P=H->TheLists[i];
		Position Tmp;
		while(P!=NULL)
		{
			Tmp=P->Next;
			free(P);
			P=Tmp;
		}
	}
	free(H->TheLists);
	free(H);
}
int main()
{
	HashTable H;
	Position P;
	int i;
	int j=0;
	int CurrentSize;
	H=InitializeTable(CurrentSize=13);
	for(i=0;i<NumItems;i++,j+=71)
	{
	Insert(j,H);	
	} 
	for(i=0,j=0;i<NumItems;i++,j+=71)
	if((P=Find(j,H))==NULL||Retrieve(P)!=j)
	    printf("Error at %d\n",j);
	printf("End of program.\n");
	return 0;
}
