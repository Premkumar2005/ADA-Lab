#include<stdio.h>
#include<stdlib.h>
int ordercount=0;
int cyclic=0;
int count=0;
int graph[100][100],visited[100];
void dfs(int n, int start, int parent) {
 	visited[start] = 1;
 	count++;
	printf("--> %c ", start+65);
	// print statement only for tester
   for(int i=0; i<n; i++) {
  	ordercount++;
   if(i!=parent && graph[start][i] && visited[i])
 	cyclic = 1;
   if(graph[start][i] && visited[i]==0)
 	dfs(n, i, start);
 }
}
void tester()
{
        int n;
        printf("Enter the number of vertices : \n");
        scanf("%d",&n);
        int start;
        printf("Enter the adjacency matrix \n");
        for(int i=0;i<n;i++)
        {
                for(int j=0;j<n;j++)
                {
                        scanf("%d",&graph[i][j]);
                }
                visited[i]=0;
        }
        printf("The adjacency matrix \n");
        for(int i=0;i<n;i++)
        {
                for(int j=0;j<n;j++)
                {
                        printf("%d ",graph[i][j]);
                }
                printf("\n");
        }
        cyclic=0;
        count=0;
        dfs(n,0,-1);
        if(n==count)
                printf("\nThe graph is connected\n");
        else
        {
                printf("\nThe graph is not connected\n");
                start=1;
                while(n!=count)
                {
                        if(visited[start]!=1)
                        {
                                dfs(n,start,-1);
                        }
                        start++;
                }
        }
        if(cyclic)
                printf("\nThe graph is cyclic\n");
        else
                printf("\nThe graph is acyclic\n");

}

void plotter(int k)
{
    FILE* f1 = fopen("DFS_Best_Matrix.txt", "a");
    FILE* f2 = fopen("DFS_Worst_Matrix.txt", "a");
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
            visited[x] = 0;

        count = 0;
        ordercount = 0;
        for (int x = 0; x < v; x++) {
            if (!visited[x])
                dfs(v, x, -1);
        }
        if (k == 0)
            fprintf(f2, "%d\t%d\n", v, ordercount);
        else
            fprintf(f1, "%d\t%d\n", v, ordercount);
    }

    fclose(f1);
    fclose(f2);
}

void main()
{
        for(;;)
        {
                int key;
                printf("Enter your choice:\n1.To Test\n2.To Plot\nOther to exit\n");
                scanf("%d",&key);
                switch(key)
                {
                        case 1: tester();
                                break;
                        case 2: for(int i=0;i<2;i++)
                                        plotter(i);
                                break;
                        default: exit(1);
                }
        }
}

