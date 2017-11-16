#include<stdio.h>
#include<stdlib.h>
#include<process.h>

#define MAX_VERTEX_NUM 20

typedef struct Arc{
	int adj;
	int *info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; 

typedef struct{
	char vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum,arcnum;
}MGraph;

void CreateUDN(MGraph &G){  //���������Ȩͼ 
	int i,j,k,w;
	char c,V1,V2;
	printf("���붥�����ͻ���\n");
	scanf("%d%d",&G.vexnum,&G.arcnum);
	for(i=0;i<G.vexnum;++i){
		printf("�����%d����������\n",i);
		c=getchar();
		scanf("%c",&G.vexs[i]); 
	}
	for(i=0;i<G.vexnum;++i){
		for(j=0;j<G.vexnum;++j){
			G.arcs[i][j].adj=9999;
		}
	}
	for(k=0;k<G.arcnum;++k){
		i=0;
		j=0;
		printf("���붥���Ȩֵ\n");
		c=getchar();
		scanf("%c%c%d",&V1,&V2,&w);
		while(G.vexs[i]!=V1){
			i++;
		}
		while(G.vexs[j]!=V2){
			j++;
		}
		G.arcs[i][j].adj=w;
	}
}

void Dijkstra(MGraph G,int v0,char p[][MAX_VERTEX_NUM],int *D){
	int v,w,vj,i,j,k,min;
	int s[G.vexnum];  //p��ʾ���·����D��ʾ��̾��� ��s��ʾ�Ƿ��������̾��� 
	for(v=0;v<G.vexnum;v++){  //��ʼ�� 
		s[v]=0;
		D[v]=G.arcs[v0][v].adj;
		for(j=0;j<G.vexnum;j++){
			p[v][j]='\0';
		}
		if(D[v]!=9999){
			p[v][0]=G.vexs[v0];
			p[v][1]=G.vexs[v];
		}
	}
	D[v0]=0;
	s[v0]=1;
	for(i=1;i<G.vexnum;i++){  //n-1����ѭ�� 
		min=9999;
		for(w=0;w<G.vexnum;w++){  //������ĵ� 
			if(s[w]==0&&D[w]<min){
				min=D[w];
				vj=w;
			}
		}
		s[vj]=1;
		for(w=0;w<G.vexnum;w++){  //����������·�� 
			if(s[w]==0&&min+G.arcs[vj][w].adj<D[w]){
				D[w]=min+G.arcs[vj][w].adj;
				for(k=0;p[vj][k]!='\0';k++){
					p[w][k]=p[vj][k];
				}
				p[w][k]=G.vexs[w];
				p[w][k+1]='\0';
			}
		}
	}
}

int main(){
	int flag,n,i,j,k;
	char c1,c2,c;
	char p[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int D[MAX_VERTEX_NUM];
	MGraph G;
	flag=1;
	while(flag){
		printf("0.�˳�  1.������·��ͨ��  2.�����·��\n");
		printf("����������\n");
		scanf("%d",&n);
		switch(n){
			case(0):
				flag=0;
				break;
			case(1):
				CreateUDN(G);
				c=getchar();
				if(G.vexnum==0){
					printf("�޶���\n");
				}
				else{
					printf("��·��ͨ���������\n");
				};
				break;
			case(2):
			    i=0;
			    j=0;
			    k=0;
				printf("�������\n");
				c=getchar();
				scanf("%c",&c1);
				while(G.vexs[i]!=c1&&i<G.vexnum){
					i++;
				}
				if(i==G.vexnum){
					printf("����������\n");
					break;
				}
				Dijkstra(G,i,p,D);
				printf("�����յ�\n");
				c=getchar();
				scanf("%c",&c2);
				while(G.vexs[j]!=c2&&j<G.vexnum){
					j++;
				}
				if(j==G.vexnum){
					printf("�յ��������\n");
					break;
				}
				if(D[j]==9999){
					printf("��·��\n");
				}
				else if(D[j]==0){
					printf("������յ��غ�\n");
				}
				else{
					printf("���·��Ϊ:");
					while(p[j][k]!='\0'){
						printf("%c",p[j][k]);
						k++;
					}
					printf("\n");
					printf("��̳���Ϊ:%d\n",D[j]);
				}
				break;
			default:printf("��������������\n");
		}
	}
	return 0;
}
