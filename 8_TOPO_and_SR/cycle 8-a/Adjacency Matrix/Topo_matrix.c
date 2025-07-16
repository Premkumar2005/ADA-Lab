#include<stdio.h>
#include<stdlib.h>
int graph[100][100];
int visit[100];
int c=0;
int st[100],top=-1;
int path[100];
int count;
void dfs(int n,int start)
{
	visit[start]=1;
	path[start]=1;
	for(int i=0;i<n;i++)
	{
		count++;
		// count is for plotter
		if(graph[start][i] && visit[i] && path[i])
			c=1;
		if(graph[start][i] && (!visit[i]))
		{
			dfs(n,i);
		}
	}
	path[start]=0;
	st[++top]=start;
}
void tester()
{
	int n;
	printf("Enter the number of vertices \n");
	scanf("%d",&n);
	printf("Enter the adjacency matrix:\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			scanf("%d",&graph[i][j]);
		}
		visit[i]=0;
	}
	for(int i=0;i<n;i++)
	{
		if(!visit[i])
		dfs(n,i);
	}
	if(c)
	{
		printf("The graph is cyclic . Topological order cannot be obtained\n");
		return;
	}
	printf("\n Topological order : \n");
	for(int i=top;i>=0;i--)
	{
		printf("-->%c ",st[i]+65);
	}

}
void plotter(int k)
{
    FILE* f1 = fopen("Topo_best.txt", "a");
    FILE* f2 = fopen("Topo_worst.txt", "a");
    int v;

    for (int i = 1; i <= 10; i++) {
        v = i;


        if (k == 0)
	{
            for (int x = 0; x < v; x++)
                for (int y = 0; y < v; y++)
                    graph[x][y] = (x != y) ? 1 : 0;
        }
	else
	{
            for (int x = 0; x < v; x++)
                for (int y = 0; y < v; y++)
                    graph[x][y] = 0;
            for (int x = 0; x < v - 1; x++)
                graph[x][x + 1] = 1;
        }
        for (int x = 0; x < v; x++)
            visit[x] = 0;

        count = 0;
        for (int x = 0; x < v; x++) {
            if (!visit[x])
                dfs(v,x);
        }
        if (k == 0)
            fprintf(f2, "%d\t%d\n", v,count);
        else
            fprintf(f1, "%d\t%d\n", v,count);
    }

    fclose(f1);
    fclose(f2);
}
void main()
{
	int key;
	for(;;)
	{
		printf("Enter the choice:\n1. To test\n2. To plot\nOther to exit\n");
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
