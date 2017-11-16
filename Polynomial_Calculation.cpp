#include<stdio.h>
#include<stdlib.h> 
#include<process.h>

typedef struct Node{
	float coef;
	int expn;
	struct Node *next;
}LNode,*LinkList;
typedef LinkList polynomail;

void InitPolyn(polynomail &L){  //创建结点
	L = (LinkList)malloc(sizeof(LNode));
	if (!L) 
		printf("开辟结点失败");
}

void OrderInsert(polynomail &L,LinkList h){  //顺序插入结点 
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

void CreatPolyn(polynomail &L){  //创建多项式
	InitPolyn(L);
	L->next=NULL;
	LinkList h;
	float m;
	int n;
	printf("请输入系数和指数\n");
	scanf("%f%d", &m, &n);
	while(m){
		InitPolyn(h);
		h->coef=m;
		h->expn=n;
		h->next=NULL;
		OrderInsert(L,h);
		printf("请输入系数和指数\n");
	    scanf("%f%d", &m, &n);
	}
	printf("创建完毕\n"); 
}

void PrintPolyn(polynomail L){  //打印多项式
	if (L == NULL)
		printf("无此多项式\n");
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

void CopyPolyn(polynomail &L1, polynomail L2){  //复制多项式
	if (L2 == NULL)
		printf("复制的多项式不存在\n");
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

void AddPolyn(polynomail L1,polynomail L2,polynomail &L3){  //多项式求和 
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

void SubtractPolyn(polynomail L1,polynomail L2,polynomail &L3){  //多项式求差 
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

float ValuePolyn(polynomail L,float b){  //多项式求值 
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

void DestroyPolyn(polynomail &L){  //销毁多项式 
	LinkList p,q;
	if(L==NULL){
		printf("此多项式不存在\n");
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
		printf("多项式已销毁\n");
	}
}

void EmptyPolyn(polynomail &L){  //清空多项式 
	LinkList p,q;
	if(L==NULL){
		printf("此多项式不存在\n");
	}
	else if(L->next==NULL){
		printf("无需清空\n");
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
		printf("多项式已清空\n");
	}
}

void InsertPolyn(polynomail &L){  //插入新结点 
	if(L==NULL){
		printf("此多项式不存在\n");
	}
	else{
		LinkList p;
		float m;
		int n;
		printf("输入系数和指数\n");
		scanf("%f%d",&m,&n);
		if(m==0){
			printf("不插入新的结点\n");
		}
		else{
			InitPolyn(p);
			p->coef=m;
			p->expn=n;
			p->next=NULL;
			OrderInsert(L,p);
			printf("插入完毕\n");
		}
	}
}

void DeletePolyn(polynomail &L){  //删除结点 
	if(L==NULL){
		printf("此多项式不存在\n");
	}
	else{
		int n;
		LinkList p,q;
		p=L->next;
		q=L;
		printf("输入删除结点的指数\n");
		scanf("%d",&n);
		while(p!=NULL&&n>p->expn){
			q=p;
			p=p->next;
		}
		if(n==p->expn){
			q->next=p->next;
			free(p);
			printf("已删除指定结点\n");
		}
		else{
			printf("未找到指定结点\n");
		}
	}
}

void AmendPolyn(polynomail &L){  //修改结点 
	if(L==NULL){
		printf("此多项式不存在\n");
	}
	else{
		int n,n1;
		float m1;
		LinkList p,q;
		p=L->next;
		q=L;
		printf("输入修改结点的指数\n");
		scanf("%d",&n);
		while(p!=NULL&&n>p->expn){
			q=p;
			p=p->next;
		}
		if(n==p->expn){
			printf("输入修改后结点的系数和指数\n");
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
			printf("已修改指定结点\n");
		}
		else{
			printf("未找到指定结点\n"); 
		}
	}
}

void DifferentialPolyn1(polynomail L1,polynomail &L2){  //多项式一阶微分 
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

void DifferentialPolyn(polynomail L1,polynomail &L2,int n){  //多项式n阶微分 
	if(L1==NULL){
		printf("此多项式不存在\n");
	}
	else{
		LinkList a[n];
	    int i;
	    DifferentialPolyn1(L1,a[0]);
	    for(i=1;i<n;i++){
		    DifferentialPolyn1(a[i-1],a[i]);
	    }
	    CopyPolyn(L2,a[n-1]);
	    printf("求导完毕\n"); 
	} 
}

void IntegralPolyn(polynomail L1,polynomail &L2){  //求多项式的不定积分 
	if(L1==NULL){
		printf("此多项式不存在\n");
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
		printf("求不定积分完毕\n"); 
	}
}

void DitegralPolyn(polynomail L1,float s,float t){  //求多项式的定积分 
	if(L1==NULL){
		printf("此多项式不存在\n");
	}
	else{
		LinkList L2;
		IntegralPolyn(L1,L2);
		float value;
		value=ValuePolyn(L2,t)-ValuePolyn(L2,s);
		printf("定积分的值为：%g\n",value);
	}
}

void MultipliPolyn(polynomail L1,polynomail L2,polynomail &L3){  //多项式的乘法 
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

void  MultipliPolyn1(polynomail L1,int n,polynomail &L3){  //多项式的乘方 
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

void DivisionPolyn(polynomail L1,polynomail L2,polynomail &L3,polynomail &L4){  //多项式的除法 
	if(L2->next==NULL){
		printf("输入错误\n");
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

void CommondivisorPolyn(polynomail L1,polynomail L2,polynomail &L3){  //多项式的最大公约式 
	if(L1->next==NULL||L2->next==NULL){
		printf("没有公约数\n");
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

void CommonmultiplePolyn(polynomail L1,polynomail L2,polynomail &L3){  //多项式的最小公倍式 
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

int main(){  //主函数
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
		printf("稀疏一元多项式运算器\n0.退出\n1.创建\n2.显示\n3.复制\n4.求和\n5.求差\n6.求值\n7.销毁\n8.清空\n9.修改（插入新的结点、删除已有结点、修改已有结点的系数和指数）\n");
		printf("10.微分（N阶导数）\n11.不定积分\n12.定积分\n13.乘法和乘方\n14.除法\n15.最大公约式和最小公倍式\n");
		printf("输入操作对应的数字\n");
		scanf("%d", &n);
		switch (n){
		case(0) : flag = 0; break;  //退出
		case(1) : printf("输入需要创建的多项式编号\n");  //创建
			scanf("%d", &m);
			CreatPolyn(a[m]);
			break;
		case(2) : printf("输入打印的多项式编号\n");  //打印
			scanf("%d", &m);
			PrintPolyn(a[m]);
			break;
		case(3):printf("输入复制的多项式编号（前一个复制后一个）\n");  //复制 
			scanf("%d%d",&m1,&m2);
			CopyPolyn(a[m1],a[m2]);
			break;
		case(4):printf("输入求和的多项式编号（将第一个和第二个相加存入第三个）\n") ;  //求和 
			scanf("%d%d%d",&m1,&m2,&m3);
			AddPolyn(a[m1],a[m2],a[m3]);
			break;
		case(5):printf("输入求差的多项式编号（将第一个和第二个相减存入第三个）\n") ;  //求差 
			scanf("%d%d%d",&m1,&m2,&m3);
			SubtractPolyn(a[m1],a[m2],a[m3]);
			break;
		case(6):printf("输入求值的多项式编号和x的值\n");  //求值 
			scanf("%d%f",&m,&x);
			if(a[m]==NULL){
				printf("此多项式不存在\n");
			}
			else{
				c=ValuePolyn(a[m],x);
				printf("此多项式的值为：%f\n",c);
			}
			break;
		case(7):printf("输入销毁的多项式编号\n"); //销毁 
			scanf("%d",&m);
			DestroyPolyn(a[m]);
			break; 
		case(8):printf("输入清空的多项式编号\n");  //清空 
			scanf("%d",&m);
			EmptyPolyn(a[m]);
			break;
		case(9):printf("1.插入新的结点  2.删除已有的结点  3.修改已有结点的系数和指数\n输入操作对应的数字\n");  //修改 
			scanf("%d",&n1);
			switch(n1){
				case(1):printf("输入插入结点的多项式编号\n");
					scanf("%d",&m);
					InsertPolyn(a[m]);
					break;
				case(2):printf("输入删除结点的多项式编号\n");
					scanf("%d",&m);
					DeletePolyn(a[m]);
					break;
				case(3):printf("输入修改结点的多项式编号\n");
					scanf("%d",&m);
					AmendPolyn(a[m]);
					break;
				default:printf("输入数字有误\n");
			}
			break;
		case(10):printf("输入微分和存储的多项式编号和求导阶数\n");  //微分 
			scanf("%d%d%d",&m1,&m2,&y);
			DifferentialPolyn(a[m1],a[m2],y);
			break;
		case(11):printf("输入求不定积分和存储的多项式编号\n");  //不定积分 
			scanf("%d%d",&m1,&m2);
			IntegralPolyn(a[m1],a[m2]);
			break;
		case(12):printf("输入求定积分的多项式编号、下限和上限\n");  //定积分 
			scanf("%d%f%f",&m,&s,&t);
			DitegralPolyn(a[m],s,t);
			break;
		case(13):printf("1.乘法  2.乘方\n输入操作对应的数字\n");   //乘法或乘方 
			scanf("%d",&n1);
			switch(n1){
				case(1):printf("输入相乘的多项式编号（第一个乘第二个存入第三个）\n");
					scanf("%d%d%d",&m1,&m2,&m3);
					MultipliPolyn(a[m1],a[m2],a[m3]);
					break;
				case(2):printf("输入乘方的多项式编号、次数以及存储的多项式编号\n");
					scanf("%d%d%d",&m1,&y,&m3);
					MultipliPolyn1(a[m1],y,a[m3]);
					break;
				default:printf("输入数字有误\n");
			}
			break; 
		case(14):printf("输入相除的多项式编号（第一个除以第二个的商存入第三个，余数存入第四个）\n");   //除法 
			scanf("%d%d%d%d",&m1,&m2,&m3,&m4);
			DivisionPolyn(a[m1],a[m2],a[m3],a[m4]);
			break;
		case(15):printf("1.最大公约式 2.最小公倍式\n输入操作对应的数字\n");  //最大公约式或最小公倍式 
			scanf("%d",&n1);
			switch(n1){
				case(1):printf("输入多项式编号（第一个与第二个的最大公因式存入第三个）\n");
				    scanf("%d%d%d",&m1,&m2,&m3);
				    CommondivisorPolyn(a[m1],a[m2],a[m3]);
				    break;
				case(2):printf("输入多项式编号（第一个与第二个的最小公倍式存入第三个）\n");
					scanf("%d%d%d",&m1,&m2,&m3);
					CommonmultiplePolyn(a[m1],a[m2],a[m3]);
					break;
				default:printf("输入数字有误\n");
			}
			break;
		default:printf("输入数字有误\n");
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
