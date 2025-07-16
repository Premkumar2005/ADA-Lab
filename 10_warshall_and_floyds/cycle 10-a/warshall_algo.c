#include<stdio.h>
#include<stdlib.h>
int matrix[10][10];
int count;
void warshall(int n)
{
	for(int k=0;k<n;k++)
	{
		for(int i=0;i<n;i++)
		{
			if(matrix[i][k] != 0) {
            			for(int j = 0; j < n; j++) {
                			matrix[i][j] = (matrix[i][j] || (matrix[i][k] && matrix[k][j]));
                			count++;
            			}
			}
		}
	}
}
void tester()
{
	int n;
	printf("\nEnter the number of vertices\n");
	scanf("%d",&n);
	printf("Enter the Adjacency Matrix:\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			scanf("%d",&matrix[i][j]);
	}
	warshall(n);
	printf("\nAdjacency matrix:\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			printf("%d  ",matrix[i][j]);
		}
		printf("\n");
	}
}
void plotter(int k)
{
	FILE *f1=fopen("Warshall_best.txt","a");
	FILE *f2=fopen("Warshall_worst.txt","a");
	for(int i=1;i<=10;i++)
	{
		int n=i;
		if(k==0)
		{
			for(int i = 0; i < n; i++)
			{
    				for(int j = 0; j < n; j++) matrix[i][j] = 0;
			}
			for(int i = 0; i < n - 1; i++) 
			{
    				matrix[i][i + 1] = 1;
			}
			matrix[n - 1][0] = 1;
		}
		if(k==1)
		{
			for(int i = 0; i < n; i++)
			{
    				for(int j = 0; j < n; j++) 
				{
        				if(i != j) matrix[i][j] = 1;
        				else matrix[i][j] = 0;
    				}
			}
		}
		count=0;
		warshall(n);
		if(k==0)
			fprintf(f1,"%d\t%d\n",n,count);
		else
			fprintf(f2,"%d\t%d\n",n,count);

	}
	fclose(f1);
	fclose(f2);

}
int main()
{
	int choice;
	for(;;)
	{
		printf("Enter the choice:\n1.To Test\n2.To plot\nOther to exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:tester();
			       break;
			case 2:for(int i=0;i<2;i++)
				       plotter(i);
			       break;
			default:exit(1);
		}
	}
	return 0;
}
