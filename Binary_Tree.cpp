#include<stdio.h>
#include<stdlib.h>
#include<process.h>

typedef struct BitreeNode{
	int data;
	struct BitreeNode *lchild,*rchild;
}BiTNode,*BiTree; 

typedef struct Node{
	BiTree data;
	struct Node *next;
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

void CreateBiTree(BiTree &T){
	int ch;
	scanf("%d",&ch);
	if(!ch){
		T=NULL;
	}
	else{
		if(!(T=(BiTNode*)malloc(sizeof(BiTNode)))){
			printf("分配空间失败\n");
		}
		else{
			T->data=ch;
			CreateBiTree(T->lchild);
			CreateBiTree(T->rchild);
		}
	}
}

void print(int e){
	printf("%d",e);
}

void PreOrderTraverse(BiTree T,void(*visit)(int e)){
	if(T){
		visit(T->data);
		PreOrderTraverse(T->lchild,visit);
		PreOrderTraverse(T->rchild,visit);
	}
}

void MidOrderTraverse(BiTree T,void(*visit)(int e)){
	if(T){
		MidOrderTraverse(T->lchild,visit);
		visit(T->data);
		MidOrderTraverse(T->rchild,visit);
	}
}

void BehOrderTraverse(BiTree T,void(*visit)(int e)){
	if(T){
		BehOrderTraverse(T->lchild,visit);
		BehOrderTraverse(T->rchild,visit);
		visit(T->data);
	}
}

void InitQueue(LinkQueue &Q){
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front){
		printf("分配空间失败\n");
	}
	Q.front->next=NULL;
}

void EnQueue(LinkQueue &Q,BiTree T){
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p){
		printf("分配空间失败\n");
	}
	else{
		p->data=T;
		p->next=NULL;
		Q.rear->next=p;
		Q.rear=p;
	}
}

void DeQueue(LinkQueue &Q,BiTree &T){
	if(Q.front==Q.rear){
		printf("空队列\n");
	}
	else{
		QueuePtr p;
		p=Q.front->next;
		T=p->data;
		Q.front->next=p->next;
		if(Q.rear==p){
			Q.rear=Q.front;
		}
		free(p);
	}
}

void LevOrderTraverse(BiTree T,void(*visit)(int e)){
	LinkQueue Q;
	BiTree L;
	InitQueue(Q);
	EnQueue(Q,T);
	while(Q.front!=Q.rear){
		DeQueue(Q,L);
		if(L->lchild){
			EnQueue(Q,L->lchild);
		}
		if(L->rchild){
			EnQueue(Q,L->rchild);
		}
		visit(L->data);
	}
}

int Count1(BiTree T){
	if(T==NULL){
		return 0;
	}
	else{
		return(1+Count1(T->lchild)+Count1(T->rchild));
    }
}

int Count2(BiTree T){
	if(T==NULL){
		return 0;
	}
	else if(T->lchild==NULL&&T->rchild==NULL){
		return 1;
	}
	else{
		return(Count2(T->lchild)+Count2(T->rchild));
	}
}

int Height(BiTree T){
	if(T==NULL){
		return 0;
	}
	else{
		int m;
		int n;
		m=Height(T->lchild);
		n=Height(T->rchild);
		return((m>n)?m+1:n+1);
	}
}

int Wide(BiTree T){
    LinkQueue Q;
    BiTree L;
    QueuePtr last;
    int n,t;
	InitQueue(Q);
	EnQueue(Q,T);
	n=0;
	last=Q.rear;
	while(Q.front!=Q.rear){
		t=0;
		while(Q.front->next!=last){
			DeQueue(Q,L);
		    if(L->lchild){
			    EnQueue(Q,L->lchild);
		    }
		    if(L->rchild){
			    EnQueue(Q,L->rchild);
		    }
		    t++;
		}
	    DeQueue(Q,L);
		if(L->lchild){
			EnQueue(Q,L->lchild);
		}
		if(L->rchild){
			EnQueue(Q,L->rchild);
		}
		t++;
		if(t>n){
			n=t;
		}
		last=Q.rear;
	}
	return n;
}

void Copy(BiTree T1,BiTree &T2){
	if(!T1){
		T2=NULL;
	}
	else{
		BiTree l,r;
		Copy(T1->lchild,l);
		Copy(T1->rchild,r);
		T2=(BiTNode*)malloc(sizeof(BiTNode));
		T2->data=T1->data;
		T2->lchild=l;
		T2->rchild=r;
	}
}

void Destroy(BiTree &T){
	if(T){
		Destroy(T->lchild);
		Destroy(T->rchild);
		T=NULL;
	}
}

int main(){
	int flag,i,n,n1,m,m1,m2;
	BiTree a[20];
	for(i=0;i<20;i++){
		a[i]=NULL;
	}
	flag=1;
	while(flag){
		printf("二叉树运算：\n0.退出\n1.创建\n2.遍历\n3.计算\n4.处理\n");
	    printf("输入操作编号\n");
	    scanf("%d",&n);
	    switch(n){
	    	case(0):
	    		flag=0;
	    		break;
	    	case(1):
	    		printf("输入创建的二叉树编号\n");
				scanf("%d",&m);
				printf("按先序序列输入结点值\n"); 
				CreateBiTree(a[m]);
				break; 
			case(2):
				printf("1.先序 2.中序 3.后序 4.层序\n");
				printf("输入操作编号\n");
				scanf("%d",&n1);
				switch(n1){
					case(1):
						printf("输入遍历的二叉树编号\n");
						scanf("%d",&m);
						if(!a[m]){
							printf("此二叉树不存在\n");
						}
						else{
							PreOrderTraverse(a[m],print);
							printf("\n");
						}
						break;
					case(2):
						printf("输入遍历的二叉树编号\n");
						scanf("%d",&m);
						if(!a[m]){
							printf("此二叉树不存在\n");
						}
						else{
							MidOrderTraverse(a[m],print);
							printf("\n");
						}
						break;
					case(3):
						printf("输入遍历的二叉树编号\n");
						scanf("%d",&m);
						if(!a[m]){
							printf("此二叉树不存在\n");
						}
						else{
							BehOrderTraverse(a[m],print);
							printf("\n");
						}
						break;
					case(4):
						printf("输入遍历的二叉树编号\n");
						scanf("%d",&m);
						if(!a[m]){
							printf("此二叉树不存在\n");
						}
						else{
							LevOrderTraverse(a[m],print);
							printf("\n");
						}
						break;
					default:printf("操作编号输入错误\n"); 
				}
				break;
			case(3):
				printf("1.结点数 2.叶子数 3.高度 4.宽度\n");
				printf("输入操作编号\n");
				scanf("%d",&n1);
				switch(n1){
					case(1):
						printf("输入计算的二叉树编号\n");
						scanf("%d",&m);
						printf("结点数为%d\n",Count1(a[m]));
						break;
					case(2):
						printf("输入计算的二叉树编号\n");
						scanf("%d",&m);
						printf("叶子数为%d\n",Count2(a[m]));
						break;
					case(3):
					    printf("输入计算的二叉树编号\n");
						scanf("%d",&m);
						printf("高度为%d\n",Height(a[m]));
						break;
					case(4):
						printf("输入计算的二叉树编号\n");
						scanf("%d",&m);
						if(!a[m]){
							printf("宽度为0\n");
						}
						else{
							printf("宽度为%d\n",Wide(a[m]));
						}
						break;
					default:printf("操作编号输入错误\n");
				}
				break;
			case(4):
			    printf("1.复制 2.销毁\n");
				printf("输入操作编号\n");
				scanf("%d",&n1);
				switch(n1){
					case(1):
						printf("输入复制的二叉树编号（将前一个复制到后一个）\n");
						scanf("%d%d",&m1,&m2);
						Copy(a[m1],a[m2]);
						break;
					case(2):
						printf("输入销毁的二叉树编号\n");
						scanf("%d",&m);
						Destroy(a[m]);
						break;
					default:printf("操作编号输入错误\n");
				}
				break;
			default:printf("操作编号输入错误\n");
		}
	}
	return 0;
}
