#include<stdio.h>
#include<stdlib.h>
#define MinTableSize (10)
#define NumItems 400
typedef unsigned int Index;
typedef Index Position;

struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(int key,HashTable H);
void Insert(int key,HashTable H);
int Retrieve(Position P,HashTable H);
HashTable Rehash(HashTable H);

enum KindOfEntry{Legitimate,Empty,Deleted};
struct HashEntry
{
	int data;
	enum KindOfEntry Info;
};
typedef struct HashEntry Cell;

struct HashTbl
{
	int TableSize;
	Cell *TheCells;
};
HashTable InitializeTable(int TableSize)
{
    HashTable H;
	int i;	
	if(TableSize<MinTableSize)
	{
		printf("Table size too small");
		return NULL;
	}
	H=malloc(sizeof(struct HashTbl));
	if(H==NULL)
	    printf("Out of space!!!");
	H->TableSize=NextPrime(TableSize);
	H->TheCells=malloc(sieof(Cell)*H->TableSize);
	if(H->TheCells==NULL)
	    printf("Out of space!!!");
	for(i=0;i<H->TableSize;i++)
	{
		H->TheCells[i].Info=Empty;
	}
	return H;
} 
//²éÕÒ
Position Find(int key,HashTable H)
{
	Position CurrentPos;
	int CollisionNum=0;
	CurrentPos=Hash(key,H->TableSize);
	while(H->TheCells[CurrentPos].Info!=Empty&&
	H->TheCells[CurrentPos].data!=key)
	{
		CurrentPos+=2*++CollisionNum-1;
		if(CurrentPos>=H->TableSize)
		   CurrentPos-=H->TableSize;
	}
	    return CurrentPos;
}
void Insert(intkey,HashTable H)
{
	Position P;
	Pos=Find(key,H);
	if(H->TheCells[Pos].Info!=Legitimate)
	{
		H->TheCells[Pos].Info=Legitimate
		H->TheCells[Pos].data=key;
	}
}
HashTable Rehash(HashTable H)
{
	int i,OldSize;
	Cell *OldCells;
	OldCells=H->TheCells;
	OldSize=H->TableSize;
	H=InitializeTable(2*OldSize);
	for(i=0;i<OldSize;i++)
	    if(OldCells[i].Info==Legitimate)
		    Insert(OldCells[i].data,H);
	free(OldCells);
	return H;    
}
