#include<stdio.h>
#include<stdlib.h> 
#include<process.h>

typedef struct Node{
	float coef;
	int expn;
	struct Node *next;
}LNode,*LinkList;
typedef LinkList polynomail;

void InitPolyn(polynomail &L){  //�������
	L = (LinkList)malloc(sizeof(LNode));
	if (!L) 
		printf("���ٽ��ʧ��");
}

void OrderInsert(polynomail &L,LinkList h){  //˳������� 
	LinkList p,q;
	p=L->next;
	q=L;
	while(p!=NULL&&h->expn>p->expn){
		q=p;
		p=p->next;
	}
	if(p==NULL||h->expn<p->expn){
		q->next=h;
		h->next=p;
	}
	else{
		if((h->coef+p->coef)==0){
			q->next=p->next;
			free(p);
		}
		else{
			p->coef=h->coef+p->coef;
		}
	}
}

void CreatPolyn(polynomail &L){  //��������ʽ
	InitPolyn(L);
	L->next=NULL;
	LinkList h;
	float m;
	int n;
	printf("������ϵ����ָ��\n");
	scanf("%f%d", &m, &n);
	while(m){
		InitPolyn(h);
		h->coef=m;
		h->expn=n;
		h->next=NULL;
		OrderInsert(L,h);
		printf("������ϵ����ָ��\n");
	    scanf("%f%d", &m, &n);
	}
	printf("�������\n"); 
}

void PrintPolyn(polynomail L){  //��ӡ����ʽ
	if (L == NULL)
		printf("�޴˶���ʽ\n");
	else if (L->next == NULL)
		printf("0\n");
	else{
		float m;
		int n;
		L = L->next;
		while (L ->next!= NULL){
			m = L->coef;
			n = L->expn;
			printf("%g*x^%d+", m, n);
			L = L->next;
		}
		m = L->coef;
		n = L->expn;
		printf("%g*x^%d\n", m, n);
	}
}

void CopyPolyn(polynomail &L1, polynomail L2){  //���ƶ���ʽ
	if (L2 == NULL)
		printf("���ƵĶ���ʽ������\n");
	else if (L2->next == NULL){
		InitPolyn(L1);
		L1->next = NULL;
	}
	else{
		InitPolyn(L1);
		LinkList p, q, r;
		p = L1;
		q = L2->next;
		while (q != NULL){
			InitPolyn(r);
			r->coef = q->coef;
			r->expn = q->expn;
			r->next = q->next;
			p->next = r;
			q = q->next;
			p = p->next;
		}
	}
}

void AddPolyn(polynomail L1,polynomail L2,polynomail &L3){  //����ʽ��� 
	CopyPolyn(L3,L1);
	LinkList p,q;
	p=L2->next;
	while(p!=NULL){
		InitPolyn(q);
		q->coef=p->coef;
		q->expn=p->expn;
		q->next=p->next;
		OrderInsert(L3,q);
		p=p->next;
	}
}

void SubtractPolyn(polynomail L1,polynomail L2,polynomail &L3){  //����ʽ��� 
	CopyPolyn(L3,L1);
	LinkList p,q;
	p=L2->next;
	while(p!=NULL){
		InitPolyn(q);
		q->coef=0-p->coef;
		q->expn=p->expn;
		q->next=p->next;
		OrderInsert(L3,q);
		p=p->next;
	}
}

float ValuePolyn(polynomail L,float b){  //����ʽ��ֵ 
	LinkList p;
	float c,d,m;
	int n,i;
	c=0.0;
	p=L->next;
	while(p!=NULL){
		d=1.0;
		m=p->coef;
		n=p->expn;
		for(i=1;i<=n;i++){
			d*=b;
		}
		c+=m*d;
		p=p->next;
	}
	return c;
}

void DestroyPolyn(polynomail &L){  //���ٶ���ʽ 
	LinkList p,q;
	if(L==NULL){
		printf("�˶���ʽ������\n");
	}
	else{
		p=L->next;
		q=L;
		while(p!=NULL){
			free(q);
			q=p;
			p=p->next;
		} 
		free(q);
		L=NULL;
		printf("����ʽ������\n");
	}
}

void EmptyPolyn(polynomail &L){  //��ն���ʽ 
	LinkList p,q;
	if(L==NULL){
		printf("�˶���ʽ������\n");
	}
	else if(L->next==NULL){
		printf("�������\n");
	}
	else{
		p=L->next->next;
		q=L->next;
		while(p!=NULL){
			free(q);
			q=p;
			p=p->next;
		}
		free(q);
		L->next=NULL;
		printf("����ʽ�����\n");
	}
}

void InsertPolyn(polynomail &L){  //�����½�� 
	if(L==NULL){
		printf("�˶���ʽ������\n");
	}
	else{
		LinkList p;
		float m;
		int n;
		printf("����ϵ����ָ��\n");
		scanf("%f%d",&m,&n);
		if(m==0){
			printf("�������µĽ��\n");
		}
		else{
			InitPolyn(p);
			p->coef=m;
			p->expn=n;
			p->next=NULL;
			OrderInsert(L,p);
			printf("�������\n");
		}
	}
}

void DeletePolyn(polynomail &L){  //ɾ����� 
	if(L==NULL){
		printf("�˶���ʽ������\n");
	}
	else{
		int n;
		LinkList p,q;
		p=L->next;
		q=L;
		printf("����ɾ������ָ��\n");
		scanf("%d",&n);
		while(p!=NULL&&n>p->expn){
			q=p;
			p=p->next;
		}
		if(n==p->expn){
			q->next=p->next;
			free(p);
			printf("��ɾ��ָ�����\n");
		}
		else{
			printf("δ�ҵ�ָ�����\n");
		}
	}
}

void AmendPolyn(polynomail &L){  //�޸Ľ�� 
	if(L==NULL){
		printf("�˶���ʽ������\n");
	}
	else{
		int n,n1;
		float m1;
		LinkList p,q;
		p=L->next;
		q=L;
		printf("�����޸Ľ���ָ��\n");
		scanf("%d",&n);
		while(p!=NULL&&n>p->expn){
			q=p;
			p=p->next;
		}
		if(n==p->expn){
			printf("�����޸ĺ����ϵ����ָ��\n");
			scanf("%f%d",&m1,&n1);
			q->next=p->next;
			p->coef=m1;
			p->expn=n1;
			p->next=NULL;
			if(m1!=0){
				OrderInsert(L,p);
			} 
			else{
				free(p);
			}
			printf("���޸�ָ�����\n");
		}
		else{
			printf("δ�ҵ�ָ�����\n"); 
		}
	}
}

void DifferentialPolyn1(polynomail L1,polynomail &L2){  //����ʽһ��΢�� 
	InitPolyn(L2);
	LinkList p,q,r;
	if(L1->next==NULL||(L1->next->expn==0&&L1->next->next==NULL)){
		L2->next=NULL;
	}
	else{
		p=L1->next;
		r=L2;
		if(L1->next->expn==0){
			p=p->next;
		}
		while(p!=NULL){
			InitPolyn(q);
			q->coef=p->coef*(float)p->expn;
			q->expn=p->expn-1;
			q->next=p->next;
			r->next=q;
			r=r->next;
			p=p->next;
		}
	}
}

void DifferentialPolyn(polynomail L1,polynomail &L2,int n){  //����ʽn��΢�� 
	if(L1==NULL){
		printf("�˶���ʽ������\n");
	}
	else{
		LinkList a[n];
	    int i;
	    DifferentialPolyn1(L1,a[0]);
	    for(i=1;i<n;i++){
		    DifferentialPolyn1(a[i-1],a[i]);
	    }
	    CopyPolyn(L2,a[n-1]);
	    printf("�����\n"); 
	} 
}

void IntegralPolyn(polynomail L1,polynomail &L2){  //�����ʽ�Ĳ������� 
	if(L1==NULL){
		printf("�˶���ʽ������\n");
	}
	else{
		InitPolyn(L2);
		LinkList p,q,r;
		if(L1->next==NULL){
			L2->next==NULL;
		}
		else{
			p=L1->next;
			r=L2;
			while(p!=NULL){
				InitPolyn(q);
				q->coef=p->coef/(float)(p->expn+1);
				q->expn=p->expn+1;
				q->next=p->next;
				r->next=q;
				r=r->next;
				p=p->next;
			}
		}
		printf("�󲻶��������\n"); 
	}
}

void DitegralPolyn(polynomail L1,float s,float t){  //�����ʽ�Ķ����� 
	if(L1==NULL){
		printf("�˶���ʽ������\n");
	}
	else{
		LinkList L2;
		IntegralPolyn(L1,L2);
		float value;
		value=ValuePolyn(L2,t)-ValuePolyn(L2,s);
		printf("�����ֵ�ֵΪ��%g\n",value);
	}
}

void MultipliPolyn(polynomail L1,polynomail L2,polynomail &L3){  //����ʽ�ĳ˷� 
    InitPolyn(L3);
	if(L1->next==NULL||L2->next==NULL){
		L3->next=NULL;
	}
	else{
		L3->next=NULL;
		LinkList p,q,r;
		InitPolyn(p);
		InitPolyn(q);
		p=L1->next;
		while(p!=NULL){
			q=L2->next;
			while(q!=NULL){
				InitPolyn(r);
				r->coef=p->coef*q->coef;
				r->expn=p->expn+q->expn;
			    r->next=NULL;
			    OrderInsert(L3,r);
			    q=q->next;
			}
			p=p->next;
		} 
	}
}

void  MultipliPolyn1(polynomail L1,int n,polynomail &L3){  //����ʽ�ĳ˷� 
	if(n==1){
		CopyPolyn(L3,L1);
	}
	else{
		int i;
		i=1;
		InitPolyn(L3);
		LinkList a[n];
		CopyPolyn(a[0],L1);
		while(i<n){
			MultipliPolyn(a[i-1],L1,a[i]);
			i++;
		}
		CopyPolyn(L3,a[n-1]);
	}
}

void DivisionPolyn(polynomail L1,polynomail L2,polynomail &L3,polynomail &L4){  //����ʽ�ĳ��� 
	if(L2->next==NULL){
		printf("�������\n");
	}
	else if(L1->next==NULL){
		InitPolyn(L3);
		InitPolyn(L4);
		L3->next=NULL;
		L4->next=NULL;
	}
	else{
		LinkList p,q,r,r1,t1,t2;
		InitPolyn(L3);
		L3->next=NULL;
		p=L1;
		q=L2;
		while(p->next!=NULL){
			p=p->next;
		}
		while(q->next!=NULL){
			q=q->next;
		}
		while(L1->next!=NULL&&p->expn>=q->expn){
			InitPolyn(r);
			r->coef=p->coef/q->coef;
			r->expn=p->expn-q->expn;
			r->next=NULL;
			OrderInsert(L3,r);
			InitPolyn(r1);
			r1->next=r;
			MultipliPolyn(L2,r1,t1);
			SubtractPolyn(L1,t1,t2);
			CopyPolyn(L1,t2);
			p=L1;
			while(p->next!=NULL){
				p=p->next;
		    }
		}
		CopyPolyn(L4,L1);
	}
}

void CommondivisorPolyn(polynomail L1,polynomail L2,polynomail &L3){  //����ʽ�����Լʽ 
	if(L1->next==NULL||L2->next==NULL){
		printf("û�й�Լ��\n");
	}
	else{
		LinkList a[20],p,q;
		int i;
		i=1;
		p=L1->next;
		q=L2->next;
		while(p->next!=NULL){
			p=p->next;
		}
		while(q->next!=NULL){
			q=q->next;
		}
		if(p->expn>q->expn){
			CopyPolyn(a[0],L1);
			CopyPolyn(a[1],L2);
		}
		else{
			CopyPolyn(a[0],L2);
			CopyPolyn(a[1],L1);
		}
		DivisionPolyn(a[0],a[1],a[2],a[3]);
		while(a[i+2]->next!=NULL){
			i=i+2;
			DivisionPolyn(a[i-2],a[i],a[i+1],a[i+2]);
		}
		CopyPolyn(L3,a[i]);
	}
}

void CommonmultiplePolyn(polynomail L1,polynomail L2,polynomail &L3){  //����ʽ����С����ʽ 
	if(L1->next==NULL||L2->next==NULL){
		InitPolyn(L3);
		L3->next=NULL;
	}
	else{
		LinkList p,q,r;
		CommondivisorPolyn(L1,L2,p);
		MultipliPolyn(L1,L2,q);
		DivisionPolyn(q,p,L3,r); 
	}
}

int main(){  //������
	LinkList a[20];
	int i,n,n1,m,m1,m2,m3,m4,flag,y;
	float x,c,s,t;
	flag = 1;
	i=0;
	while(i<20){
		a[i]=NULL;
		i++;
	}
	while (flag == 1){
		printf("ϡ��һԪ����ʽ������\n0.�˳�\n1.����\n2.��ʾ\n3.����\n4.���\n5.���\n6.��ֵ\n7.����\n8.���\n9.�޸ģ������µĽ�㡢ɾ�����н�㡢�޸����н���ϵ����ָ����\n");
		printf("10.΢�֣�N�׵�����\n11.��������\n12.������\n13.�˷��ͳ˷�\n14.����\n15.���Լʽ����С����ʽ\n");
		printf("���������Ӧ������\n");
		scanf("%d", &n);
		switch (n){
		case(0) : flag = 0; break;  //�˳�
		case(1) : printf("������Ҫ�����Ķ���ʽ���\n");  //����
			scanf("%d", &m);
			CreatPolyn(a[m]);
			break;
		case(2) : printf("�����ӡ�Ķ���ʽ���\n");  //��ӡ
			scanf("%d", &m);
			PrintPolyn(a[m]);
			break;
		case(3):printf("���븴�ƵĶ���ʽ��ţ�ǰһ�����ƺ�һ����\n");  //���� 
			scanf("%d%d",&m1,&m2);
			CopyPolyn(a[m1],a[m2]);
			break;
		case(4):printf("������͵Ķ���ʽ��ţ�����һ���͵ڶ�����Ӵ����������\n") ;  //��� 
			scanf("%d%d%d",&m1,&m2,&m3);
			AddPolyn(a[m1],a[m2],a[m3]);
			break;
		case(5):printf("�������Ķ���ʽ��ţ�����һ���͵ڶ�����������������\n") ;  //��� 
			scanf("%d%d%d",&m1,&m2,&m3);
			SubtractPolyn(a[m1],a[m2],a[m3]);
			break;
		case(6):printf("������ֵ�Ķ���ʽ��ź�x��ֵ\n");  //��ֵ 
			scanf("%d%f",&m,&x);
			if(a[m]==NULL){
				printf("�˶���ʽ������\n");
			}
			else{
				c=ValuePolyn(a[m],x);
				printf("�˶���ʽ��ֵΪ��%f\n",c);
			}
			break;
		case(7):printf("�������ٵĶ���ʽ���\n"); //���� 
			scanf("%d",&m);
			DestroyPolyn(a[m]);
			break; 
		case(8):printf("������յĶ���ʽ���\n");  //��� 
			scanf("%d",&m);
			EmptyPolyn(a[m]);
			break;
		case(9):printf("1.�����µĽ��  2.ɾ�����еĽ��  3.�޸����н���ϵ����ָ��\n���������Ӧ������\n");  //�޸� 
			scanf("%d",&n1);
			switch(n1){
				case(1):printf("���������Ķ���ʽ���\n");
					scanf("%d",&m);
					InsertPolyn(a[m]);
					break;
				case(2):printf("����ɾ�����Ķ���ʽ���\n");
					scanf("%d",&m);
					DeletePolyn(a[m]);
					break;
				case(3):printf("�����޸Ľ��Ķ���ʽ���\n");
					scanf("%d",&m);
					AmendPolyn(a[m]);
					break;
				default:printf("������������\n");
			}
			break;
		case(10):printf("����΢�ֺʹ洢�Ķ���ʽ��ź��󵼽���\n");  //΢�� 
			scanf("%d%d%d",&m1,&m2,&y);
			DifferentialPolyn(a[m1],a[m2],y);
			break;
		case(11):printf("�����󲻶����ֺʹ洢�Ķ���ʽ���\n");  //�������� 
			scanf("%d%d",&m1,&m2);
			IntegralPolyn(a[m1],a[m2]);
			break;
		case(12):printf("�����󶨻��ֵĶ���ʽ��š����޺�����\n");  //������ 
			scanf("%d%f%f",&m,&s,&t);
			DitegralPolyn(a[m],s,t);
			break;
		case(13):printf("1.�˷�  2.�˷�\n���������Ӧ������\n");   //�˷���˷� 
			scanf("%d",&n1);
			switch(n1){
				case(1):printf("������˵Ķ���ʽ��ţ���һ���˵ڶ��������������\n");
					scanf("%d%d%d",&m1,&m2,&m3);
					MultipliPolyn(a[m1],a[m2],a[m3]);
					break;
				case(2):printf("����˷��Ķ���ʽ��š������Լ��洢�Ķ���ʽ���\n");
					scanf("%d%d%d",&m1,&y,&m3);
					MultipliPolyn1(a[m1],y,a[m3]);
					break;
				default:printf("������������\n");
			}
			break; 
		case(14):printf("��������Ķ���ʽ��ţ���һ�����Եڶ������̴��������������������ĸ���\n");   //���� 
			scanf("%d%d%d%d",&m1,&m2,&m3,&m4);
			DivisionPolyn(a[m1],a[m2],a[m3],a[m4]);
			break;
		case(15):printf("1.���Լʽ 2.��С����ʽ\n���������Ӧ������\n");  //���Լʽ����С����ʽ 
			scanf("%d",&n1);
			switch(n1){
				case(1):printf("�������ʽ��ţ���һ����ڶ����������ʽ�����������\n");
				    scanf("%d%d%d",&m1,&m2,&m3);
				    CommondivisorPolyn(a[m1],a[m2],a[m3]);
				    break;
				case(2):printf("�������ʽ��ţ���һ����ڶ�������С����ʽ�����������\n");
					scanf("%d%d%d",&m1,&m2,&m3);
					CommonmultiplePolyn(a[m1],a[m2],a[m3]);
					break;
				default:printf("������������\n");
			}
			break;
		default:printf("������������\n");
		}
	}
	i--;
	while(i>=0){
		if(a[i]!=NULL){
			DestroyPolyn(a[i]);
		}
		i--;
	}
	return 0;
}
