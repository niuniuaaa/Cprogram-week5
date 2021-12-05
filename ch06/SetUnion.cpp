#include <stdio.h>
#include <stdlib.h>
const int NumSets = 11;
 
/*
 * Disjoint Set ���ཻ�� / ���鼯
 * ��Ҫ����Ϊ�����Һͺϲ�
 */
typedef int DisjSet[NumSets + 1]; // Ϊ���±���룬�����趨�����СΪNumSets + 1����0��Ԫ����ռλ����
typedef int SetType; // ���ڵ㱣���Ԫ�ص�����
typedef int ElementType;
 
// ��ʼ��
void initialize(DisjSet set);
 
// �������Ĵ�С���ϲ��������ཻ����root1��root2�ֱ��ʾ����Ҫ�ϲ������ĸ�
void setUnion(DisjSet set, SetType root1, SetType root2);
 
// ����x����set�е��ĸ����ཻ��
SetType find(ElementType x, DisjSet set);
 
void
initialize(DisjSet set)
{
    /*
     * ��ʼ��ʱ��ÿ�����ڵ��б����ֵ���Ǹ����Ĵ�С�ĸ�ֵ��Ҳ����-1
     * ��������Ĵ�С����˼�������ж��ٸ��ڵ�
     * ����ڵ��б����ֵΪ��������ô��ֵ��ʾ���ڵ��������е��±�
     *
     * ע�⣺
     * ������±���ǽڵ��б����Ԫ��
     * �����е�Ԫ�ر�ʾ���ڵ��б����Ԫ�ػ����Ĵ�С�ĸ�ֵ
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
 * �����Ĵ�С�󲢣���С������Ϊ�ϴ����������
 */
void
setUnion(DisjSet set, SetType root1, SetType root2)
{
    if (set[root1] >= 0 || set[root2] >= 0)
        printf("Fail to union: Root1 and Root2 is not a root of tree");
    
    if (set[root1] == set[root2]) // ͬһ����
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
    
    if (set[x] == 0) // ������ýڵ�ָ��ռλ�ĵ�0������Ԫ�أ���˳���
    {
        printf("Error: set[x] can not be 0");
        return 0;
    }
    
    /*
     * �ڲ��ҵ�ĳ��Ԫ�غ�ִ��·��ѹ���㷨
     * ע�⣺·��ѹ���㷨�Ͱ���С�ϲ��㷨���ݣ��Ͱ����߶Ⱥϲ��㷨������
     */
    if (set[x] < 0)
        return x;
    else
        return set[x] = find(set[x], set); // ���ϲ��Ҹ��ڵ㣬����Ϊx�ĸ��ڵ�
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
