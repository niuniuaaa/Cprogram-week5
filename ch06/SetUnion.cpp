#include <stdio.h>
#include <stdlib.h>
const int NumSets = 11;
 
/*
 * Disjoint Set 不相交集 / 并查集
 * 主要操作为：查找和合并
 */
typedef int DisjSet[NumSets + 1]; // 为了下标对齐，这里设定数组大小为NumSets + 1，第0个元素起占位作用
typedef int SetType; // 父节点保存的元素的类型
typedef int ElementType;
 
// 初始化
void initialize(DisjSet set);
 
// （按树的大小）合并两个不相交集，root1和root2分别表示两棵要合并的树的根
void setUnion(DisjSet set, SetType root1, SetType root2);
 
// 查找x属于set中的哪个不相交集
SetType find(ElementType x, DisjSet set);
 
void
initialize(DisjSet set)
{
    /*
     * 初始化时，每个根节点中保存的值就是该树的大小的负值，也就是-1
     * 在这里，树的大小的意思是树中有多少个节点
     * 如果节点中保存的值为正数，那么该值表示父节点在数组中的下标
     *
     * 注意：
     * 数组的下标就是节点中保存的元素
     * 数组中的元素表示父节点中保存的元素或树的大小的负值
     */
    for (int i = NumSets; i > 0; i--)
        set[i] = -1;
    
    // do nothing with set[0]
}
 
void SetUnion(DisjSet S, SetType Root1, SetType Root2)
{
	S[Root2]=Root1;
}
/*
 * 按树的大小求并：较小的树成为较大的树的子树
 */
void
setUnion(DisjSet set, SetType root1, SetType root2)
{
    if (set[root1] >= 0 || set[root2] >= 0)
        printf("Fail to union: Root1 and Root2 is not a root of tree");
    
    if (set[root1] == set[root2]) // 同一棵树
        return;
    else
    {
        if (set[root1] > set[root2]) // -set[root1] < -set[root2]
            set[root1] = root2;
        else // -set[root1] > -set[root2]
            set[root2] = root1;
    }
}
SetType Find(int x,DisjSet S)
{
    if(S[x]<=0)
	    return x;
	else
	    return Find(S[x],S);	
} 
SetType
find(ElementType x, DisjSet set)
{
    if (x > NumSets)
    {
        printf("x is not in DisjSet");
        return 0;
    }
    
    if (set[x] == 0) // 空树或该节点指向占位的第0个数组元素，因此出错
    {
        printf("Error: set[x] can not be 0");
        return 0;
    }
    
    /*
     * 在查找到某个元素后，执行路径压缩算法
     * 注意：路径压缩算法和按大小合并算法兼容，和按树高度合并算法不兼容
     */
    if (set[x] < 0)
        return x;
    else
        return set[x] = find(set[x], set); // 沿上查找根节点，并设为x的父节点
}
int main()
{
    DisjSet S;
	int i=1,j=1,k=1,Set1,Set2;
	initialize(S);
	while(k<=3)
	{
	j=1;
	while(j<NumSets)
	{
	Set1=Find(j,S);
	Set2=Find(j+k,S);
	SetUnion(S,Set1,Set2);
	j+=2*k;	
	}	
	k*=2;
	}	
	for(i=1;i<=NumSets;i++)
	{
		Set1=Find(i,S);
		printf("%d**",Set1);
	}
	printf("\n");
	return 0;
} 
