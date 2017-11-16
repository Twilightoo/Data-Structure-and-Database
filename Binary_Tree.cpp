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
			printf("����ռ�ʧ��\n");
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
		printf("����ռ�ʧ��\n");
	}
	Q.front->next=NULL;
}

void EnQueue(LinkQueue &Q,BiTree T){
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p){
		printf("����ռ�ʧ��\n");
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
		printf("�ն���\n");
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
		printf("���������㣺\n0.�˳�\n1.����\n2.����\n3.����\n4.����\n");
	    printf("����������\n");
	    scanf("%d",&n);
	    switch(n){
	    	case(0):
	    		flag=0;
	    		break;
	    	case(1):
	    		printf("���봴���Ķ��������\n");
				scanf("%d",&m);
				printf("����������������ֵ\n"); 
				CreateBiTree(a[m]);
				break; 
			case(2):
				printf("1.���� 2.���� 3.���� 4.����\n");
				printf("����������\n");
				scanf("%d",&n1);
				switch(n1){
					case(1):
						printf("��������Ķ��������\n");
						scanf("%d",&m);
						if(!a[m]){
							printf("�˶�����������\n");
						}
						else{
							PreOrderTraverse(a[m],print);
							printf("\n");
						}
						break;
					case(2):
						printf("��������Ķ��������\n");
						scanf("%d",&m);
						if(!a[m]){
							printf("�˶�����������\n");
						}
						else{
							MidOrderTraverse(a[m],print);
							printf("\n");
						}
						break;
					case(3):
						printf("��������Ķ��������\n");
						scanf("%d",&m);
						if(!a[m]){
							printf("�˶�����������\n");
						}
						else{
							BehOrderTraverse(a[m],print);
							printf("\n");
						}
						break;
					case(4):
						printf("��������Ķ��������\n");
						scanf("%d",&m);
						if(!a[m]){
							printf("�˶�����������\n");
						}
						else{
							LevOrderTraverse(a[m],print);
							printf("\n");
						}
						break;
					default:printf("��������������\n"); 
				}
				break;
			case(3):
				printf("1.����� 2.Ҷ���� 3.�߶� 4.���\n");
				printf("����������\n");
				scanf("%d",&n1);
				switch(n1){
					case(1):
						printf("�������Ķ��������\n");
						scanf("%d",&m);
						printf("�����Ϊ%d\n",Count1(a[m]));
						break;
					case(2):
						printf("�������Ķ��������\n");
						scanf("%d",&m);
						printf("Ҷ����Ϊ%d\n",Count2(a[m]));
						break;
					case(3):
					    printf("�������Ķ��������\n");
						scanf("%d",&m);
						printf("�߶�Ϊ%d\n",Height(a[m]));
						break;
					case(4):
						printf("�������Ķ��������\n");
						scanf("%d",&m);
						if(!a[m]){
							printf("���Ϊ0\n");
						}
						else{
							printf("���Ϊ%d\n",Wide(a[m]));
						}
						break;
					default:printf("��������������\n");
				}
				break;
			case(4):
			    printf("1.���� 2.����\n");
				printf("����������\n");
				scanf("%d",&n1);
				switch(n1){
					case(1):
						printf("���븴�ƵĶ�������ţ���ǰһ�����Ƶ���һ����\n");
						scanf("%d%d",&m1,&m2);
						Copy(a[m1],a[m2]);
						break;
					case(2):
						printf("�������ٵĶ��������\n");
						scanf("%d",&m);
						Destroy(a[m]);
						break;
					default:printf("��������������\n");
				}
				break;
			default:printf("��������������\n");
		}
	}
	return 0;
}
