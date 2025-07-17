#include<stdio.h>
#include<stdlib.h>
int stack[100];
int top=-1;
int cyclic=0;
int count;
int dcount;
struct node 
{
	int info;
	struct node* next;
};
struct Graph
{
	int vertices;
	int *visit;
	int *path;
	struct node** adjLists;
};
typedef struct node* Node;
Node create(int n)
{
	Node new=(Node)malloc(sizeof(struct node));
	new->info=n;
	new->next=NULL;
	return new;
}
struct Graph* creategraph(int vertices)
{
	struct Graph* g=malloc(sizeof(struct Graph));
	g->vertices=vertices;
	g->adjLists=malloc(vertices * sizeof(struct node*));
	g->visit=malloc(vertices * sizeof(int));
	g->path=malloc(vertices * sizeof(int));
	for(int i=0;i<vertices;i++)
	{
		g->adjLists[i]=NULL;
		g->visit[i]=0;
		g->path[i]=0;
	}
	return g;
}
void dfs(struct Graph* g,int vertex)
{
	struct node* temp=g->adjLists[vertex];
	g->visit[vertex]=1;
	g->path[vertex]=1;
	count++;
	while(temp)
	{
		dcount++;
		int connectedVertex=temp->info;
		if(g->visit[connectedVertex] && g->path[connectedVertex])
			cyclic=1;
		if(g->visit[connectedVertex]==0)
		{
			dfs(g,connectedVertex);
		}
		temp=temp->next;

	}
	dcount++;
	g->path[vertex]=0;
	stack[++top]=vertex;
}
void tester()
{
 int n;
 printf("Enter the number of vertices\n");
 scanf("%d",&n);
 struct Graph* g=creategraph(n);
 Node temp;
 int key;
 printf("Enter the adjacency LIST \n");
 for(int i=0;i<g->vertices;i++)
{
	printf("Enter 1 for the vertices adjacent to vertex %c\n",i+65);
 	for(int j=0;j<g->vertices;j++)
 	{
	  printf("\nVertex %c : ",g->vertices-j-1+65);
 	  scanf("%d",&key);
	  if(key==1)
 	  {
 		Node nn=create(g->vertices-j-1);
 		nn->next = g->adjLists[i];
		g->adjLists[i] = nn;
 	  }
 	}
}
 for(int i=0;i<g->vertices;i++)
 {
 	temp=g->adjLists[i];
	printf("The vertex adjacent to  %c : ",i+65);
	while(temp!=NULL)
 	{
	 printf("%c ",temp->info+65);
	 temp=temp->next;
	}
	 printf("\n");
 }
 int dfscount=0;
 count=0;
 printf("\nDFS TRAVERSAL STARTING FROM NODE %C\n",65);
 dfs(g,0);
 dfscount++;
 int start=1;
 while(count!=g->vertices)
 {
 	if(g->visit[start]!=1)
 	{
	  printf("\n");
	  dfs(g,start);
	  dfscount++;
 	}
	  start++;
 }
 if(cyclic)
 {
	 printf("\nTHE GRAPH HAS A CYCLE \n");
 }
 else
 {
 	printf("\nTHE TOPOLOGICAL SORT IS:\n");
	for(int i=top;i>=0;i--)
	 printf("-->%c ", stack[i]+65);
	
 }
 	free(g);
 }

void ploter(int k)
{
 FILE *f1,*f2;
 f1=fopen("Topo_best_list.txt","a");
 f2=fopen("Topo_worst_list.txt","a");
 for(int i=1;i<=10;i++)
 {
 int n=i;

 struct Graph* g=creategraph(n);
 Node temp;
 int key;

if(k==0)
{
 for(int i=0;i<g->vertices;i++)
{
	for(int j=0;j<g->vertices;j++)
	 {

 	if(i!=g->vertices-1-j)
 	{
	 Node nn=create(g->vertices-j-1);
	 nn->next = g->adjLists[i];
	 g->adjLists[i] = nn;
 	}
 	}
}
}
if(k==1)
{
 for(int i=0;i<g->vertices-1;i++)
 {
 	Node nn=create(i+1);
 	nn->next = g->adjLists[i];
	g->adjLists[i] = nn;
 }
}
 count=0;
 dcount=0;
 dfs(g,0);
 int start=1;
 while(count!=g->vertices)
 {
 	if(g->visit[start]!=1)
 	{
	 printf("\n");
 	 dfs(g,start);
 	}
 	start++;
 }
	
 if(k==0)
	 fprintf(f2,"%d\t%d\n",n,dcount);
 else
 	fprintf(f1,"%d\t%d\n",n,dcount);
 free(g);
 }
fclose(f1);
fclose(f2);
}
void main()
{
 for(;;)
 {
 int key;
 printf("\nENTER THE CHOICE\n1.TO TEST \n2.TO PLOT\nOTHER TO EXIT\n");
 scanf("%d",&key);

 switch(key)
 {
 	case 1:tester();break;
	case 2:for(int i=0;i<2;i++)
 		ploter(i);
	       break;
 	default:exit(1);
 }
 }
}

