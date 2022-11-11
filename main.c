#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 100
#define OK              1
#define ERROR           0
#define LAYER          20
/*
 *
 *  定义部分
 *
 */
typedef int Status;

typedef struct BTree
{
    int data;
    struct BTree *Lchild;
    struct BTree *Rchild;
}BiNode,*BiTree;//定义叶子节点与指向叶子结点的指针

typedef struct BStack
{
    BiTree NodeAddress[MAX_TREE_SIZE];
    int top;
}BiStack;
/*
 *
 *  函数原型声明部分
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
 *  主函数部分
 *
 */

int main()
{
    /*
    创建根节点
    */
    BiTree Root;
    int num;
    CreateTNode(&Root);
    printf("先序遍历");
    printf("\n");
    PreOrder(Root);
    printf("\n");
    NewPreOrder(Root);
    printf("\n");
    printf("中序遍历");
    printf("\n");
    InOrder(Root);
    printf("\n");
    NewInOrder(Root);
    printf("\n");
    printf("后序遍历");
    printf("\n");
    PostOrder(Root);
    printf("\n");
    NewPostOrder(Root);
    printf("\n");
    int len;
    len=TreeLength(Root);
    printf("二叉树深度为：\n");
    printf("%d",len);
    printf("\n");
    int Nodenumber;
    int Leafnumber;
    Nodenumber=NodeNumber(Root);
    printf("二叉树节点总数为\n%d\n",Nodenumber);
    Leafnumber=LeafNumber(Root);
    printf("二叉树叶子结点总数为\n%d\n",Leafnumber);
    /*
    各序遍历
    */
    return 0;
}
/*
 *
 *  函数定义部分
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
    (*pT)=NULL;//初始化根
    printf("请输入元素个数：\n");
    scanf("%d",&num);
    printf("请输入元素值：\n");
    for(int i=0;i<num;i++)
    {
        BiTree T1=(BiTree)malloc(sizeof(BiNode));
        scanf("%d",&n);
        T1->Lchild=NULL;
        T1->Rchild=NULL;
        T1->data=n;
        //排序
        if((*pT)==NULL)//若根为空则令第一个节点为根
            {(*pT)=T1;}
        else//若已有根节点
        {
            mark=(*pT);//令标记等于根
            while(mark!=NULL)//当标记不为空
            {
                if(mark->data>n)//新节点数据比标记根小
                {
                    if(mark->Lchild!=NULL)//新节点数据比标记根小且根有左孩子
                    {
                        mark=mark->Lchild;//移动标记到原本标记的左孩子处
                    }
                    else if(mark->Lchild==NULL)//若新节点数据比标记根小但是已经没有左孩子
                    {
                       mark->Lchild=T1;//直接将新节点作为标记的左孩子
                        mark=NULL;//新节点排序成功，退出循环
                    }

                }
                else if(mark->data<n)//新节点数据比标记根大
                {
                    if(mark->Rchild!=NULL)//新节点数据比标记根大且根有右孩子
                    {
                        mark=mark->Rchild;//移动标记到原本标记的右孩子处
                    }
                    else if(mark->Rchild==NULL)//若新节点数据比标记根大但是已经没有右孩子
                    {
                        mark->Rchild=T1;//直接将新节点作为标记的右孩子
                        mark=NULL;//新节点排序成功，退出循环
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
