#include<stdio.h>
#include<stdlib.h>
int ordercount=0;
int cyclic=0;
int count=0;
int graph[100][100],visited[100];
void bfs(int n,int start)
{
	int rear=-1,front=-1,parentnode;
	visited[start]=1;
	count++;
	int queue[n],parent[n];
	queue[++rear]=start;
	parent[rear]=-1;
 	while(rear!=front)
        {
                start=queue[++front];
                parentnode=parent[front];
                printf("-->%c ",start+65); 
		// it is only for tester
                for(int i=0;i<n;i++)
                {
		    ordercount++;
		    // order count is for plotter
                      if( parentnode!=i && graph[start][i] && visited[i])
			      cyclic=1;
		        
                        if(graph[start][i] && (visited[i]==0))
                        {
                                visited[i]=1;
                		count++;            
                                queue[++rear]=i;
                                parent[rear]=start;
                        }
			
                }
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
        bfs(n,0);
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
                                bfs(n,start);
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
	FILE*  f1=fopen("BFS_Best.txt","a");
	FILE*  f2=fopen("BFS_Worst.txt","a");
	int v,start;
	for(int i=1;i<=10;i++)
	{
		v=i;
		for(int j=0;j<v;j++)
		{
			if(k==0)
			{
				for(int x=0;x<v;x++)
				{
					for(int y=0;y<v;y++)
					{
						if(x!=y)
							graph[x][y]=1;
						else
							graph[x][y]=0;
					}
				}
			}
			else
			{
				for(int x=0;x<v;x++)
				{
					for(int y=0;y<v;y++)
						graph[x][y]=0;
				}
				for(int x=0;x<v-1;x++)
				{
					graph[x][x+1]=1;
				}
			}

	for (int a = 0; a < v; a++)
            visited[a] = 0;
	ordercount=0;
	bfs(v,0);
	if(k==0)
	{
		fprintf(f2,"%d\t%d\n",v,ordercount);

	}
	else
	{
		fprintf(f1,"%d\t%d\n",v,ordercount);
	}
	}	
	fclose(f1);
	fclose(f2);
	}
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

