#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<math.h>

#define M 13
#define p 13

typedef struct node{
	int key;
	struct node *next;
}*HashNode,HNode;

void print1(int HT1[]){
	int i;
	for(i=0;i<M;i++){
		printf("%d",HT1[i]);
		printf("  ");
	}
	printf("\n");
}

void print2(HashNode HT2[]){
	int i;
	HashNode s;
	for(i=0;i<M;i++){
		printf("%d:  ",i);
		s=HT2[i];
		if(s!=NULL){
			printf("%d  ",s->next->key);
			s=s->next;
		    while(s->next!=NULL){
			    printf("%d  ",s->next->key);
			    s=s->next;
		    }
		}
		printf("\n");
	}
}

void CreatHash(int HT1[],HashNode HT2[]){
	int n,i,j;
	HashNode r,s;
	j=0;
	printf("����ؼ�������(�ؼ��ָ�����ͬ��-1��ʾ����)\n");
	scanf("%d",&n);
	while(n!=-1&&j<(M-1)){
		i=n%p;
		r=(HashNode)malloc(sizeof(HNode));
		r->key=n;
		r->next=NULL;
		s=HT2[i];
		if(s==NULL){
			HT2[i]=(HashNode)malloc(sizeof(HNode));
			s=HT2[i];
			s->next=r;
			r->next=NULL;
		}
		else{
			while(s->next!=NULL&&s->next->key<n){
				s=s->next;
			}
			r->next=s->next;
			s->next=r;
		}
		while(HT1[i]!=-1){
			i++;
			if(i==M){
				i=0;
			}
		}
		HT1[i]=n;
		j++;
		scanf("%d",&n);
	}
	if(j==(M-1)&&n!=-1){
		printf("�ؼ������г�����ϣ��\n");
	}
	printf("HT1:\n");
	print1(HT1);
	printf("HT2:\n");
	print2(HT2);
}

int SearchHash1(int HT1[],int k){
	int n,i;
	n=k%p;
	i=0;
	while(HT1[n]!=-1&&HT1[n]!=k){
		n++;
		if(n==M){
			n=0;
		}
		i++;
	}
	if(HT1[n]==-1){
		i=-1;
	}
	else{
		i++;
	}
	return i;
}

int SearchHash2(HashNode HT2[],int k){
	int n,i;
	n=k%p;
	i=0;
	HashNode s;
	if(HT2[n]==NULL){
		i=-1;
	}
	else{
		s=HT2[n]->next;
		while(s!=NULL&&s->key!=k){
			s=s->next;
			i++;
		}
		if(s==NULL){
			i=-1;
		}
		else{
			i++;
		}
	}
	return i;
}

void ASL1(int HT1[]){
	int i,j,n;
	float T,F;
	T=0.0;
	F=0.0;
	j=0;
	for(i=0;i<M;i++){
		if(HT1[i]!=-1){
			j++;
			T=T+(float)SearchHash1(HT1,HT1[i]);
		}
	}
	if(j==0){
		T=0.0;
	}
	else{
		T=T/(float)j;
	}
	printf("HT1���в��ҳɹ���ASLΪ:%g\n",T);
	for(i=0;i<M;i++){
		j=i;
		n=0;
		while(HT1[j]!=-1){
			j++;
			if(j==M){
				j=0;
			}
			n++;
		}
		n++;
		F=F+(float)n;
	}
	F=F/(float)p;
	printf("HT1���в���ʧ�ܵ�ASLΪ%g\n",F);
}

void ASL2(HashNode HT2[]){
	int i,j,n;
	float T,F;
	HashNode s;
	T=0.0;
	F=0.0;
	j=0;
	for(i=0;i<M;i++){
		if(HT2[i]!=NULL){
			s=HT2[i]->next;
			while(s!=NULL){
				j++;
				T=T+(float)SearchHash2(HT2,s->key);
				s=s->next;
			}
		}
	}
	if(j==0){
		T=0.0;
	}
	else{
		T=T/(float)j;
	}
	printf("HT2���в��ҳɹ���ASLΪ:%g\n",T);
	for(i=0;i<M;i++){
		n=0;
		if(HT2[i]==NULL){
			n++;
		}
		else{
			s=HT2[i]->next;
			while(s!=NULL){
				n++;
				s=s->next;
			}
			n++;
		}
		F=F+(float)n;
	}
	F=F/(float)p;
	printf("HT2���в���ʧ�ܵ�ASLΪ%g\n",F);
}

void DeleteHash(int HT1[],int k){
	int n;
	n=SearchHash1(HT1,k);
	if(n==-1){
		printf("HT1���д˹ؼ��ֲ�����\n");
	}
	else{
		HT1[k%p+n-1]=0;
		printf("ɾ���ɹ�\n");
		printf("HT1:\n");
		print1(HT1);
	}
}

void InsertHash(int HT1[],int k){
	int n,i,j,m;
	n=SearchHash1(HT1,k);
	if(n!=-1){
		printf("HT1�����Ѵ��ڴ˹ؼ���\n");
	}
	else{
		j=0;
	    for(i=0;i<M;i++){
		    if(HT1[i]!=-1){
			    j++;
		    }
	    }
	    if(j==M-1){
	    	printf("��ϣ������\n");
		}
		else{
			m=k%p;
			while(HT1[m]!=-1){
				m++;
				if(m==M){
					m=0;
				}
			}
			HT1[m]=k;
			printf("����ɹ�\n");
			printf("HT1:\n");
			print1(HT1);
			
		}
	}
}

int main(){
	int HT1[M];
	HashNode HT2[M];
	int i,n,k,flag;
	for(i=0;i<M;i++){
		HT1[i]=-1;
	}
	for(i=0;i<M;i++){
		HT2[i]=NULL;
	}
	flag=1;
	while(flag){
		printf("��ϣ��\n0.�˳�  1.����  2.ASL  3.����  4.ɾ��  5.����\n");
	    printf("����������\n");
	    scanf("%d",&n);
	    switch(n){
		    case(0):
		    	flag=0;
		    	break;
		    case(1):
		    	for(i=0;i<M;i++){
		            HT1[i]=-1;
	            }
	            for(i=0;i<M;i++){
		            HT2[i]=NULL;
	            }
		    	CreatHash(HT1,HT2);
		    	break;
		    case(2):
		    	ASL1(HT1);
				ASL2(HT2);
				break;
			case(3):
				printf("������ҹؼ���\n");
				scanf("%d",&k);
				if(SearchHash1(HT1,k)==-1){
					printf("HT1���д˹ؼ��ֲ�����\n");
				}
				else{
					printf("HT1��Ƚϴ���Ϊ%d\n",SearchHash1(HT1,k));
				}
				if(SearchHash2(HT2,k)==-1){
					printf("HT2���д˹ؼ��ֲ�����\n");
				}
				else{
					printf("HT2��Ƚϴ���Ϊ%d\n",SearchHash2(HT2,k));
				}
				break;
			case(4):
				printf("����ɾ���Ĺؼ���\n");
				scanf("%d",&k);
				DeleteHash(HT1,k);
				break;
		    case(5):
		    	printf("�������Ĺؼ���\n");
		    	scanf("%d",&k);
		    	InsertHash(HT1,k);
		    	break;
		    default:printf("�������������\n");
	    }
	}
}
