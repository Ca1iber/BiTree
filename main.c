#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 100
#define OK              1
#define ERROR           0
#define LAYER          20
/*
 *
 *  ���岿��
 *
 */
typedef int Status;

typedef struct BTree
{
    int data;
    struct BTree *Lchild;
    struct BTree *Rchild;
}BiNode,*BiTree;//����Ҷ�ӽڵ���ָ��Ҷ�ӽ���ָ��

typedef struct BStack
{
    BiTree NodeAddress[MAX_TREE_SIZE];
    int top;
}BiStack;
/*
 *
 *  ����ԭ����������
 *
 */
void CreateTNode(BiTree *pT);
void InOrder(BiTree T);
void process(BiTree T);
void PreOrder(BiTree T);
void PostOrder(BiTree T);
void NewInOrder(BiTree T);
void NewPreOrder(BiTree T);
void NewPostOrder(BiTree T);
int TreeLength(BiTree T);
int NodeNumber(BiTree T);
int LeafNumber(BiTree T);
/*
 *
 *  ����������
 *
 */

int main()
{
    /*
    �������ڵ�
    */
    BiTree Root;
    int num;
    CreateTNode(&Root);
    printf("�������");
    printf("\n");
    PreOrder(Root);
    printf("\n");
    NewPreOrder(Root);
    printf("\n");
    printf("�������");
    printf("\n");
    InOrder(Root);
    printf("\n");
    NewInOrder(Root);
    printf("\n");
    printf("�������");
    printf("\n");
    PostOrder(Root);
    printf("\n");
    NewPostOrder(Root);
    printf("\n");
    int len;
    len=TreeLength(Root);
    printf("���������Ϊ��\n");
    printf("%d",len);
    printf("\n");
    int Nodenumber;
    int Leafnumber;
    Nodenumber=NodeNumber(Root);
    printf("�������ڵ�����Ϊ\n%d\n",Nodenumber);
    Leafnumber=LeafNumber(Root);
    printf("������Ҷ�ӽ������Ϊ\n%d\n",Leafnumber);
    /*
    �������
    */
    return 0;
}
/*
 *
 *  �������岿��
 *
 */
void NewPreOrder(BiTree T)
{
    BiTree NodeAdd[MAX_TREE_SIZE];
    int top=0;
    BiTree p=T;
    while(p!=NULL||top!=0)
    {
        if(p!=NULL)
        {
            process(p);
            NodeAdd[top]=p;
            top++;
            p=p->Lchild;
        }//Push Stack
        else
        {
            p=NodeAdd[top-1];
            top--;
            p=p->Rchild;
        }//Pop Stack
    }
}

void NewInOrder(BiTree T)
{
    BiTree NodeAdd[MAX_TREE_SIZE];
    int top=0;
    BiTree p=T;
    while(p!=NULL||top!=0)
    {
        if(p!=NULL)
        {
            NodeAdd[top]=p;
            top++;
            p=p->Lchild;
        }//Push Stack
        else
        {
            p=NodeAdd[top-1];
            top--;
            process(p);
            p=p->Rchild;
        }//Pop Stack
    }
}
void NewPostOrder(BiTree T)
{
    BiTree NodeAdd[MAX_TREE_SIZE];
    int top=0;
    BiTree p=T;
    BiTree pre=NULL;
    while(p!=NULL||top!=0)
    {
        while(p!=NULL)
        {
            NodeAdd[top]=p;
            top++;
            p=p->Lchild;
        }
        p=NodeAdd[top-1];
        top--;
        if(p->Rchild==NULL)
        {
            pre=p;
            process(p);
            p=p->Rchild;
        }
        else if(p->Rchild==pre)
        {
            pre=p;
            process(p);
            p=NULL;
        }
        else
        {
            NodeAdd[top]=p;
            top++;
            p=p->Rchild;
        }
    }
}


void CreateTNode(BiTree *pT)
{
    BiTree mark;
    int num;
    int n;
    (*pT)=NULL;//��ʼ����
    printf("������Ԫ�ظ�����\n");
    scanf("%d",&num);
    printf("������Ԫ��ֵ��\n");
    for(int i=0;i<num;i++)
    {
        BiTree T1=(BiTree)malloc(sizeof(BiNode));
        scanf("%d",&n);
        T1->Lchild=NULL;
        T1->Rchild=NULL;
        T1->data=n;
        //����
        if((*pT)==NULL)//����Ϊ�������һ���ڵ�Ϊ��
            {(*pT)=T1;}
        else//�����и��ڵ�
        {
            mark=(*pT);//���ǵ��ڸ�
            while(mark!=NULL)//����ǲ�Ϊ��
            {
                if(mark->data>n)//�½ڵ����ݱȱ�Ǹ�С
                {
                    if(mark->Lchild!=NULL)//�½ڵ����ݱȱ�Ǹ�С�Ҹ�������
                    {
                        mark=mark->Lchild;//�ƶ���ǵ�ԭ����ǵ����Ӵ�
                    }
                    else if(mark->Lchild==NULL)//���½ڵ����ݱȱ�Ǹ�С�����Ѿ�û������
                    {
                       mark->Lchild=T1;//ֱ�ӽ��½ڵ���Ϊ��ǵ�����
                        mark=NULL;//�½ڵ�����ɹ����˳�ѭ��
                    }

                }
                else if(mark->data<n)//�½ڵ����ݱȱ�Ǹ���
                {
                    if(mark->Rchild!=NULL)//�½ڵ����ݱȱ�Ǹ����Ҹ����Һ���
                    {
                        mark=mark->Rchild;//�ƶ���ǵ�ԭ����ǵ��Һ��Ӵ�
                    }
                    else if(mark->Rchild==NULL)//���½ڵ����ݱȱ�Ǹ������Ѿ�û���Һ���
                    {
                        mark->Rchild=T1;//ֱ�ӽ��½ڵ���Ϊ��ǵ��Һ���
                        mark=NULL;//�½ڵ�����ɹ����˳�ѭ��
                    }
                }
            }
        }

    }
}
void InOrder(BiTree T)
{
    if( T->Lchild != NULL)
		InOrder(T->Lchild);
	process(T);
	if( T->Rchild != NULL)
		InOrder(T->Rchild);
}

void PreOrder(BiTree T)
{
	process(T);
    if( T->Lchild != NULL)
		PreOrder(T->Lchild);
	if( T->Rchild != NULL)
		PreOrder(T->Rchild);

}
void PostOrder(BiTree T)
{
    if( T->Lchild != NULL)
		PostOrder(T->Lchild);
	if( T->Rchild != NULL)
		PostOrder(T->Rchild);
	process(T);
}

void process(BiTree T)
{
    printf("%d  ",T->data);
}


int TreeLength(BiTree T)
{
    int len1=0,len2=0;
    if(T==NULL)
        return 0;
    len1=TreeLength(T->Lchild);
    len2=TreeLength(T->Rchild);
    return (len1>len2?len1+1:len2+1);
}

int NodeNumber(BiTree T)
{
    int ln=0,rn=0;
    if(T==NULL)
        return 0;
    else
    {
        ln=NodeNumber(T->Lchild);
        rn=NodeNumber(T->Rchild);
        return ln+rn+1;
    }
}
int LeafNumber(BiTree T)
{
    int ll=0,rl=0;
    if(T==NULL)
        return 0;
    if(T->Lchild==NULL&&T->Rchild==NULL)
        return 1;
    ll=LeafNumber(T->Lchild);
    rl=LeafNumber(T->Rchild);
    return (ll+rl);
}
/*

*/
