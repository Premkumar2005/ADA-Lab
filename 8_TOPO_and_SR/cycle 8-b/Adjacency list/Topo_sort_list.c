#include<stdio.h>
#include<stdlib.h>
int count1,count2,count3;
int sort[100];
struct node
{
	int info;
	struct node *next;
};
typedef struct node* Node;
struct Graph
{
	int vertices;
	struct node** adjLists;
};
Node create(int data)
{
	Node new=(Node)malloc(sizeof(struct node));
	new->info=data;
	new->next=NULL;
	return new;
}
struct Graph* creategraph(int vertices)
{
	struct Graph* graph = malloc(sizeof(struct Graph));
	graph->vertices = vertices;
	graph->adjLists = malloc(vertices * sizeof(struct node*));
	for (int i = 0; i < vertices; i++) 
	{
		graph->adjLists[i]= NULL;
	}
 	return graph;
}
typedef struct queue
{
	int r;
	int f;
	int* arr;
	int cnt;
}queue;
void Indegree(struct Graph* g, int inq[], queue* q) {
    Node adj;
    for (int i = 0; i < g->vertices; i++) {
        adj = g->adjLists[i];
        while (adj != NULL) {
            inq[adj->info]++;
            adj = adj->next;
            count1++;
        }
        count1++;
    }

    for (int i = 0; i < g->vertices; i++) {
        if (inq[i] == 0) {
            q->r = (q->r + 1) % g->vertices;
            q->arr[q->r] = i;
            q->cnt++;
        }
        count2++;
    }
}
void SourceRemove(struct Graph* g,int inq[],queue* q) {
    int cnt = 0;

    while (q->cnt != 0) {
        int source = q->arr[q->f];
        q->f = (q->f + 1) % g->vertices;
        sort[cnt++] = source;
        q->cnt--;

        Node adj = g->adjLists[source];
        while (adj != NULL) {
            int k = adj->info;
            inq[k]--;
            adj = adj->next;
            count3++;

            if (inq[k] == 0) {
                q->r = (q->r + 1) % g->vertices;
                q->arr[q->r] = k;
                q->cnt++;
                
            }
        }
        count3++;
    }
  /*  if(cnt!=g->vertices)
    {
 	printf("Cycles exist no topological sorting possible\n");
    }
    else
    {
 	printf("The topological sorting is\n");
 	for(int i=0;i<g->vertices;i++)
	printf("%c ",sort[i]+65);

    }
    only for tester
    */
}
int max(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}
void tester()
{
	int n;
	printf("\nEnter the number of vertices :\n");
	scanf("%d",&n);
	struct Graph* g=creategraph(n);
	Node temp;
	int key;
	printf("Enter the adjacency list\n");
	for(int i=0;i<g->vertices;i++)
	{
		printf("\nEnter 1 fo the vertices adjacent to vertex %c\n",i+65);
		for(int j=0;j<g->vertices;j++)
		{
			printf("\nVertex %c : ",g->vertices-j-1+65);
			scanf("%d",&key);
			if(key!=0)
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
 		printf("THE VERTEX ADJACENT TO %c : ",i+65);
		while(temp!=NULL)
 		{
 			printf("%c ",temp->info+65);
	 		temp=temp->next;
	 	}
 		printf("\n");
 	}
	queue q;
	q.f=0;
	q.r=-1;
	q.cnt=0;
	q.arr=(int*)malloc(g->vertices * sizeof(int));
	int *inq=(int*)malloc(g->vertices * sizeof(int));
	for(int i=0;i<g->vertices;i++)
		inq[i]=0;
	Indegree(g,inq,&q);
	SourceRemove(g,inq,&q);
	free(g);

}
void plotter(int k) {
    FILE *fdata = fopen("Graph_data.txt", "a");
    FILE *f1 = fopen("Topo_sort_best.txt", "a");
    FILE *f2 = fopen("Topo_sort_worst.txt", "a");

    for (int i = 1; i <= 20; i++) {
        int n = i;
        struct Graph* g = creategraph(n);
        if (k == 0) {
            for (int i = 0; i < g->vertices; i++) {
                for (int j = 0; j < g->vertices; j++) {
                    if (i != g->vertices - 1 - j) {
                        Node nn = create(g->vertices - 1 - j);
                        nn->next = g->adjLists[i];
                        g->adjLists[i] = nn;
                    }
                }
            }
        } 
	if (k == 1) {
            for (int i = 0; i < g->vertices - 1; i++) {
                Node nn = create(i + 1);
                nn->next = g->adjLists[i];
                g->adjLists[i] = nn;
            }
        }
        count1 = count2 = count3 = 0;
        queue q;
	q.f=0;
	q.r=-1;
	q.arr=(int*)malloc(sizeof(int) * g->vertices);
	q.cnt=0;
        int *inq = calloc(n, sizeof(int));
	for(int x=0;x<g->vertices;x++)
		inq[x]=0;
        Indegree(g, inq, &q);
        SourceRemove(g,inq,&q);

        int max1 = max(count1, count2, count3);
        fprintf(fdata, "%d\t%d\t%d\t%d\n", n, count1, count2, count3);

        if (k == 1)
            fprintf(f1, "%d\t%d\n", n, max1);
        else
            fprintf(f2, "%d\t%d\n",n, max1);

        free(g);
    }

    fclose(fdata);
    fclose(f1);
    fclose(f2);
}
void main()
{
	int key;
        for(;;)
        {
                printf("\nEnter the choice:\n1,To Test\n2.To Plot\nOther to exit\n");
                scanf("%d",&key);
                switch(key)
                {
                        case 1:tester();
                               break;
                        case 2:for(int i=0;i<2;i++)
                                plotter(i);
                                break;
				
                        default:exit(1);
                }
        }

}
