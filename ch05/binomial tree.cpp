#include <stddef.h> 
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct BinNode *Positon, *BinTree;
typedef struct Collection *BinQueue;
typedef int ElementType;

int MaxTrees = 100000;
int Capacity = 200000;
struct BinNode {
   ElementType Element;
   Positon LeftChild;
   Positon NextSibling;
};

struct Collection {
   int CurrentSize;
   BinTree TheTrees[1000000];
};

void Error(char *message) {
   printf("%s\n", message);
}

int IsEmpty(BinQueue H) {
   return H->CurrentSize == 0;
}

BinQueue Initialize() {
   BinQueue H = (Collection*)malloc(sizeof(struct Collection));
   H->CurrentSize = 0;

   int i;
   for (i = 0; i <= MaxTrees; i++) {
       H->TheTrees[i] = NULL;
   }
   return H;
}

BinTree CombineTrees(BinTree T1, BinTree T2) {
   if (T1->Element > T2->Element)
       return CombineTrees(T2, T1);
   T2->NextSibling = T1->LeftChild;
   T1->LeftChild = T2;
   return T1;
}

/* Merge two binomial queues */
/* Not optimized for early termination */
/* H1 contains merged result */
BinQueue Merge(BinQueue H1, BinQueue H2) {
   BinTree T1, T2, Carry = NULL;
   int i, j;

   if (H1->CurrentSize + H2->CurrentSize > Capacity)
       Error("Merged would exceed capacity");

   H1->CurrentSize += H2->CurrentSize;
   for (i = 0, j = 1; j <= H1->CurrentSize; i++, j *= 2) {
       T1 = H1->TheTrees[i];
       T2 = H2->TheTrees[i];

       switch (!!T1 + 2 * !!T2 + 4 * !!Carry) {
           case 0:/* No trees */
           case 1:/* Only H1 */
               break;
           case 2:/* Only H2 */
               H1->TheTrees[i] = T2;
               H2->TheTrees[i] = NULL;
               break;
           case 4:/* Only Carry */
               H1->TheTrees[i] = Carry;
               Carry = NULL;
               break;
           case 3:
               Carry = CombineTrees(T1, T2);
               H1->TheTrees[i] = H2->TheTrees[i] = NULL;
               break;
           case 5:
               Carry = CombineTrees(T1, Carry);
               H1->TheTrees[i] = NULL;
               break;
           case 6:
               Carry = CombineTrees(T2, Carry);
               H2->TheTrees[i] = NULL;
               break;
           case 7:
               H1->TheTrees[i] = Carry;
               Carry = CombineTrees(T1, T2);
               H2->TheTrees[i] = NULL;
               break;
       }

   }
   return H1;
}


ElementType DeleteMin(BinQueue H) {
   int i, j;
   int MinTree;
   BinQueue DeletedQueue;
   Positon DeletedTree, OldRoot;
   ElementType MinItem;

   if (IsEmpty(H)) {
       Error("Empty binomial queue");
       return -INFINITY;
   }

   MinItem = INFINITY;
   for (i = 0; i < MaxTrees; i++) {
       if (H->TheTrees[i] &&
           H->TheTrees[i]->Element < MinItem) {
           MinItem = H->TheTrees[i]->Element;
           printf("%d\n", MinItem);
           MinTree = i;
       }
   }

   DeletedTree = H->TheTrees[MinTree];
   OldRoot = DeletedTree;
   DeletedTree = DeletedTree->LeftChild;
   free(OldRoot);

   DeletedQueue = Initialize();
   DeletedQueue->CurrentSize = (1 << MinTree) - 1;
   for (j = MinTree - 1; j >= 0; j--) {
       DeletedQueue->TheTrees[j] = DeletedTree;
       DeletedTree = DeletedTree->NextSibling;
       DeletedQueue->TheTrees[j]->NextSibling = NULL;
   }

   H->TheTrees[MinTree] = NULL;
   H->CurrentSize -= DeletedQueue->CurrentSize + 1;

   Merge(H, DeletedQueue);
   return MinItem;
}

int main() {
   int i;
   BinQueue Q[1000];
   for (i = 0; i < 1000; i++) {
       Positon P = (BinNode*)malloc(sizeof(struct BinNode));
       P->Element = i;
       P->NextSibling = P->LeftChild = NULL;
       Q[i] = Initialize();
       Q[i]->CurrentSize = 1;
       Q[i]->TheTrees[0] = P;
   }
   BinQueue result = Merge(Q[0], Q[1]);
   for (i = 2; i < 1000; i++) {
       result = Merge(result, Q[i]);
   }
   int j = DeleteMin(result);
   printf("%d\n", j);
   return 0;
}

