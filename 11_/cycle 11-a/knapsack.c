#include<stdio.h>
#include<stdlib.h>
int n,m,w[100],v[100],t[100][100],cnt;
int max(int a,int b)
{
	return (a>b)?a:b;
}
int knap(int n,int m)
{
	cnt=0;
	for(int i=0;i<n+1;i++)
	{
		for(int j=0;j<m+1;j++)
		{
			
			if(i==0||j==0)
				t[i][j]=0;
			else
			{
				cnt++;
				if(j<w[i])
                                	t[i][j]=t[i-1][j];
				else{
	//				cnt++;
					t[i][j]=max(t[i-1][j],v[i]+t[i-1][j-w[i]]);
				}
			}
		}
	}
 	return t[n][m];
}
void tester()
{
	cnt=0;
	printf("\nEnter the number of items: ");
	scanf("%d",&n);
	printf("\nEnter the capacity: ");
        scanf("%d",&m);
	printf("Weight\tValue\n");
	for(int i=1;i<n+1;i++)
	{
		scanf("%d\t%d",&w[i],&v[i]);
	}
	printf("Max value %d\n",knap(n,m));
	for(int i=0;i<n+1;i++)
	{
		for(int j=0;j<m+1;j++)
			printf("%d ",t[i][j]);
		printf("\n");
	}
	printf("Composition:\n");
	for(int i=n;i>0;i--)
	{
		if(t[i][m]!=t[i-1][m])
		{
			printf("%d\t",i);
			m=m-w[i];
		}
	}
	printf("\n");
	

}
void plotter()
{
	FILE *f1;
	f1=fopen("knapsackgraph.txt","a");
	int ch;
	while(1)
 	{
		printf("\nEnter choice 1 to continue and 0 to exit\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:tester();
			       fprintf(f1,"%d\t%d\n",n,cnt);
			       break;
			default:exit(0);
		}
 	}
	fclose(f1);
}
int main()
{
	int choice;
	for(;;)
	{
		printf("\nEnter the choice:\n1.To Test\n2.To Plot\nother to exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:tester();
			       break;
			case 2:plotter();
			       break;
			default:exit(1);

		}
	}
	return 0;
}
