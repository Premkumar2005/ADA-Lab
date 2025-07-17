#include<stdio.h>
#include<stdlib.h>
int sort[10];
int count;
typedef struct queue
{
	int f;
	int r;
	int *arr;
	int cnt;
}queue;
void Indegree(int** a,int n,int inq[],queue* q)
{
	for(int i=0;i<n;i++)
 	{
 	  for(int j=0;j<n;j++)
 	  {
 		if(a[j][i]==1)
 		inq[i]=inq[i]+1;
 	  }
 		if(inq[i]==0)
 		{
		 q->r=(q->r+1)%n;
		 q->arr[q->r]=i;
		 q->cnt++;
 		}
 	}
}
void SourceRemove(int** a,int n,int inq[],queue* q)
{
	int cnt=0;
	count=0;
	while(q->cnt)
	{
		
		int source=q->arr[q->f];
		q->f=(q->f+1)%n;
		sort[cnt]=source;
		q->cnt--;
		cnt++;
		for(int i=0;i<n;i++)
		{
			count++;
			if (a[source][i]) {
			    inq[i]--;
    			if (inq[i] == 0) {
        			q->r = (q->r + 1) % n;
        			q->arr[q->r] = i;
        			q->cnt++;
        			
    			}
			}

		}
	}
	if(cnt!=n)
	{
		 printf("Cycles exist no topological sorting possible\n");
	}
/*	else
	{
		printf("The topological sorting is\n");
		for(int i=0;i<n;i++)
		printf("%c ",sort[i]+65);

	}
*/
	//only for tester
}
void tester()
{
	int n;
	printf("Enter the number of vertices\n");
	scanf("%d",&n);
	int **arr = malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
    	arr[i] = malloc(n * sizeof(int));

	printf("Enter the adjacency matrix\n");
	for(int i=0;i<n;i++)
	{

		for(int j=0;j<n;j++)
		{
			scanf("%d",&arr[i][j]);
		}
	}
	printf("The adjacency matrix : \n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}
	queue q;
	q.f=0;
	q.r=-1;
	q.arr=(int*)malloc(n*sizeof(int));
	q.cnt=0;
	int* inq=(int*)malloc(n*sizeof(int));

	for(int i=0;i<n;i++)
	{
		inq[i]=0;
	}
	Indegree(arr,n,inq,&q);
	SourceRemove(arr,n,inq,&q);
	for (int i = 0; i < n; i++) free(arr[i]);
	free(arr);
	free(inq);

	free(q.arr);
}
void plotter(int k) {
    FILE *f1 = fopen("Topo_Best_BFS.txt", "a");
    FILE *f2 = fopen("Topo_Worst_BFS.txt", "a");

    for (int v = 1; v <= 10; v++) {
        int **arr =malloc(v * sizeof(int*));
        for (int i = 0; i < v; i++)
            arr[i] = malloc(v * sizeof(int));

        if (k == 1) {
            
            for (int i = 0; i < v - 1; i++)
                arr[i][i + 1] = 1;
        } else {
            for (int i = 0; i < v; i++)
                for (int j = 0; j < v; j++)
                    arr[i][j] = (i < j) ? 1 : 0;
        }
        queue q;
        q.f = 0;
        q.r = -1;
        q.cnt = 0;
        q.arr = malloc(v * sizeof(int));
        int *inq = calloc(v, sizeof(int));
	Indegree(arr,v,inq,&q);
	SourceRemove(arr,v,inq,&q);
	if (k == 1) fprintf(f1, "%d\t%d\n", v, count);
        else fprintf(f2, "%d\t%d\n", v, count);    
        for (int i = 0; i < v; i++) free(arr[i]);
        free(arr);
        free(inq);
        free(q.arr);
    }

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
