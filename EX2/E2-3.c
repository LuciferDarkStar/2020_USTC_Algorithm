#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LH 1
#define EH 0
#define RH -1
int temp;
typedef struct BiTNode
{
	int data;
	int h;
	int bf;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
void R_Rotate(BiTree *P)
{
	BiTree L;
	L=(*P)->lchild;//Lָ��P�������������
	(*P)->lchild=L->rchild;//L���������ҽ�ΪP��������
	L->rchild=(*P);
	*P=L;//Pָ���µĸ����
}
void L_Rotate(BiTree *P)
{
	BiTree R;
	R=(*P)->rchild;//Rָ��P�������������
	(*P)->rchild=R->lchild;//R���������ҽ�ΪP��������
	R->lchild=(*P);
	*P=R;//Pָ���µĸ����
}
void LeftBalance(BiTree *T)
{
	BiTree L,Lr;
	L=(*T)->lchild;//Lָ��T�������������
	switch(L->bf)
	{
		//���T��������ƽ��ȣ�������Ӧƽ�⴦��
		case LH://�½�������T�����ӵ��������ϣ�Ҫ������������
			(*T)->bf=L->bf=EH;
			R_Rotate(T);
			break;
		case RH://�½�������T�����ӵ��������ϣ�Ҫ��˫������
			Lr=L->rchild;
			switch(Lr->bf)//�޸�T�������ӵ�ƽ������
			{
				case LH:
					(*T)->bf=RH;
					L->bf=EH;
					break;
				case EH:
					(*T)->bf=L->bf=EH;
					break;
				case RH:
					(*T)->bf=EH;
					L->bf=LH;
					break;
			 }
			 Lr->bf=EH;
			 L_Rotate(&(*T)->lchild);
			 R_Rotate(T);
	 }
 }
//����TΪ���ڵ�Ķ���������ƽ����ת����
void RightBalance(BiTree *T)
{
	BiTree R,Rl;
	R=(*T)->rchild;
	switch(R->bf)
	{
		//���T��������ƽ��ȣ�������Ӧƽ�⴦��
		case RH://�½�������T�����ӵ��������ϣ�Ҫ������������
			(*T)->bf=R->bf=EH;
			L_Rotate(T);
			break;
		case LH://�½�������T�����ӵ��������ϣ�Ҫ��˫������
			Rl=R->lchild;
			switch(Rl->bf)//�޸�T�������ӵ�ƽ������
			{
				case RH:
					(*T)->bf=LH;
					R->bf=EH;
					break;
				case EH:
					(*T)->bf=R->bf=EH;
					break;
				case LH:
					(*T)->bf=EH;
					R->bf=RH;
					break;
			 }
			 Rl->bf=EH;
			 R_Rotate(&(*T)->rchild);
			 L_Rotate(T);
	 }
 }
 int InsertAVL(BiTree *T,int e,int h,int *taller)
{
	if(!*T)
	{
		//�����½�㣬�����ߣ���tallerΪ1
		*T=(BiTree)malloc(sizeof(BiTNode));
		(*T)->data=e;
		(*T)->h=h;
		(*T)->lchild=(*T)->rchild=NULL;
		(*T)->bf=EH;
		*taller=1;
	}
	else
	{
		if((e>=(*T)->data&&e<=(*T)->h)||(h>=(*T)->data&&h<=(*T)->h)||(e<=(*T)->data&&h>=(*T)->h))
		{
			//�����Ѵ��ں�e��ͬ�ؼ��ֵĽ�����ٲ���
			*taller=0;
			return 0;
		}
		if(e<(*T)->data)
		{
			//Ӧ������T���������н�������
			if(!InsertAVL(&(*T)->lchild,e,h,taller))//δ����
				return 0;
			if(*taller)//�Ѳ��뵽T�����������������������ߡ�
			{
				switch((*T)->bf)
				{
					case LH://ԭ�����������������ߣ���Ҫ����ƽ�⴦��
						LeftBalance(T);
						*taller=0;
						break;
					case EH://ԭ�����������ȸߣ��������������߶�������
						(*T)->bf=LH;
						*taller=1;
						break;
					case RH://ԭ�����������������ߣ������������ȸ�
						(*T)->bf=EH;
						*taller=0;
						break;
				}
			 }
		}
	else	{
			//Ӧ������T���������н�������
			if(!InsertAVL(&(*T)->rchild,e,h,taller))
				return 0;
			if(*taller)//�Ѳ��뵽T�����������������������ߡ�
			{
				switch((*T)->bf)
				{
					case LH://ԭ�����������������ߣ������������ȸ�
						(*T)->bf=EH;
						*taller=0;
						break;
					case EH://ԭ�����������ȸߣ��������������߶�������
						(*T)->bf=RH;
						*taller=1;
						break;
					case RH://ԭ�����������������ߣ���Ҫ����ƽ�⴦��
						RightBalance(T);
						*taller=0;
						break;
				}
			 }
		}
	}
	return 1;
 }

void Find(BiTree T,int a_id)
{
    BiTree t;;
    t=T;
    while(t!=NULL)
    {
        if(a_id==t->data)
        {
            printf("%d\n",t->data);
            break;
        }
        else
            if(a_id<t->data)
                t=t->lchild;
        else
            {
                temp=t->data;
                t=t->rchild;
            }
    }
    if(t==NULL)
        printf("%d\n",temp);
}
int main()
{
    int n,i;
    int e,h;
    int taller;
    BiTree T=NULL;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&e);
        scanf("%d",&h);
        temp=InsertAVL(&T,e,h,&taller);
        if(temp==1)
            printf("0\n");
        else
            printf("-1\n");
    }
    return 0;
}
