#include<stdio.h>
#include<stdlib.h> 
#include<process.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct{
	char *base;
	char *top;
	int stacksize;
}SqStack;

void InitStack(SqStack &S){  //构造空栈 
	S.base=(char*)malloc(STACK_INIT_SIZE*sizeof(char));
	if(!S.base){
		printf("开辟空间失败\n"); 
	}
	else{
		S.top=S.base;
		S.stacksize=STACK_INIT_SIZE;
	}
}

void Push(SqStack &S,char c){  //插入元素 
	if(S.top-S.base>=S.stacksize){
		char *p;
		p=(char*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(char));
		if(!p){
			printf("开辟空间失败\n");
		}
		else{
			S.base=p;
			S.top=S.base+S.stacksize;
			S.stacksize+=STACKINCREMENT;
		}
	}
	*S.top++=c;
}

void Pop(SqStack &S,char &c){  //退栈 
	c=*--S.top;
}

void ClearStack(SqStack &S){  //栈置空 
	S.top=S.base;
}

void DestroyStack(SqStack &S){  //栈销毁 
	free(S.base);
	free(S.top);
}

int main(){
	int i;
	SqStack S,S1;
	InitStack(S);
	InitStack(S1);
	char c,c1,c2;
	printf("1.行编辑器  2.文本文件编辑\n");
	scanf("%d",&i);
	switch(i){
		case(1):  //行编辑器 
	        c=getchar();
	        while(c!=EOF){
		        while(c!=EOF&&c!='\n'){
			        switch(c){
				        case'#':
					        if(S.base!=S.top){
					            Pop(S,c1);
					        }
					        break;
				        case'@':
				 	        ClearStack(S);
				            break;
				        default:
					        Push(S,c);			
			        }
			        c=getchar(); 
		        }
		        while(S.base!=S.top){
			        Pop(S,c2);
			        Push(S1,c2);		
		        }
		        while(S1.base!=S1.top){
			        Pop(S1,c2);
		 	        printf("%c",c2);
		        }
		        printf("\n");
		        if(c!=EOF){
			        c=getchar();
		        }
	        }
	        DestroyStack(S);
	        break;
	    case(2):  //文本文件编辑 
	    	FILE *in,*out;
            if((in=fopen("rfile.txt","r"))==NULL){
                printf("cannot open infile.txt\n");
                break;
            }
            if((out=fopen("wfile.txt","w"))==NULL){
                printf("cannot open outfile.txt\n");
                break;
            }
            c=fgetc(in);
            while(c!='!'){
		        while(c!='!'&&c!='\n'){
			        switch(c){
				        case'#':
					        if(S.base!=S.top){
					            Pop(S,c1);
					        }
					        break;
				        case'@':
				 	        ClearStack(S);
				            break;
				        default:
					        Push(S,c);			
			        }
			        c=fgetc(in); 
		        }
		        while(S.base!=S.top){
			        Pop(S,c2);
			        Push(S1,c2);		
		        }
		        while(S1.base!=S1.top){
			        Pop(S1,c2);
		 	        fputc(c2,out);
		        }
		        fputc('\n',out);
		        if(c!='!'){
			        c=fgetc(in);
		        }
	        }
	        DestroyStack(S);
	        break;
    }
    return 0;
}
