#include<stdio.h>
#include<stdlib.h>
int matrix[40][40];
int count;

void creategraph(int n)
{
	for(int i=0;i<n;i++)
	{
	   for(int j=0;j<n;j++){
	      if(i==j) matrix[i][j]=0;
              else matrix[i][j]=rand();
	  }
 	}
}
void Floyd(int n)
{
	for (int k = 0; k < n; k++) {
    	   for (int i = 0; i < n; i++) {
       		  int temp = matrix[i][k];
                  for (int j = 0; j < n; j++) {
            		if (matrix[i][j] > temp) {
               			count++;
               		if (temp + matrix[k][j] < matrix[i][j])
                		matrix[i][j] = temp + matrix[k][j];
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
        Floyd(n);
	printf("\nApplying Floyd's algorithm\n");
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
void plotter()
{
        FILE *f=fopen("Floyd_general.txt","w");
        for(int i=2;i<12;i++)
        {
		int n=i;
		creategraph(n);
		Floyd(n);
                fprintf(f,"%d\t%d\n",n,count);
        }
        fclose(f);
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
			case 1: tester();
				break;
			case 2: plotter();
				break;
			default: exit(1);
		}
	}
	return 0;
}
