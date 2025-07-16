// ...existing code...
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int info;
    struct node *next;
};

struct Graph
{
    int vertices;
    int edges;
    int *visit;
    struct node **adjLists;
};

typedef struct node *Node;

Node createnode(int n)
{
    Node nn = (Node)malloc(sizeof(struct node));
    nn->info = n;
    nn->next = NULL;
    return nn;
}

struct Graph *createGraph(int vertices)
{
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(struct node *));
    graph->visit = malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++)
    {
        graph->adjLists[i] = NULL;
        graph->visit[i] = 0;
    }
    return graph;
}

int count = 0, iscyclic = 0, gcount = 0;

void DFS(struct Graph *graph, int vertex, int parent)
{
    struct node *temp = graph->adjLists[vertex];
    count++;
    graph->visit[vertex] = 1;
    printf("-->%c ", vertex + 65);
    while (temp != NULL)
    {
        gcount++;
        int connectedVertex = temp->info;
        if (graph->visit[connectedVertex] == 1 && connectedVertex != parent)
        {
            iscyclic = 1;
        }
        if (graph->visit[connectedVertex] == 0)
            DFS(graph, connectedVertex, vertex);
        temp = temp->next;
    }
    gcount++;
}

void ploter(int k)
{
    FILE *fp1 = fopen("dfsbest.txt", "a");
    FILE *fp2 = fopen("dfsworst.txt", "a");
    for (int i = 1; i <= 10; i++)
    {
        int n = i;
        struct Graph *g = createGraph(n);
        Node temp;
        if (k == 0)
        {
            for (int j = 0; j < g->vertices - 1; j++)
            {
                Node nn = createnode(j + 1);
                nn->next = g->adjLists[j];
                g->adjLists[j] = nn;
            }
        }
        if (k == 1)
        {
            for (int j = 0; j < g->vertices; j++)
            {
                for (int l = 0; l < g->vertices; l++)
                {
                    if (j != g->vertices - l - 1)
                    {
                        Node nn = createnode(g->vertices - l - 1);
                        nn->next = g->adjLists[j];
                        g->adjLists[j] = nn;
                    }
                }
            }
        }
        printf("\n");
        for (int j = 0; j < g->vertices; j++)
        {
            temp = g->adjLists[j];
            printf("THE VERTEX ADJACENT TO %c : ", j + 65);
            while (temp != NULL)
            {
                printf("%c ", temp->info + 65);
                temp = temp->next;
            }
            printf("\n");
        }
        gcount = 0;
        iscyclic = 0;
        count = 0;
        printf("\nDFS TRAVERSAL STARTING FROM NODE %C\n", 65);
        DFS(g, 0, -1);
        if (count == g->vertices)
            printf("\n THE GRAPH IS CONNECTED\n");
        else
        {
            printf("\nTHE GRAPH IS NOT CONNECTED\n");
            int start = 1;
            while (count != g->vertices)
            {
                if (g->visit[start] != 1)
                {
                    printf("\n");
                    DFS(g, start, -1);
                }
                start++;
            }
        }
        if (iscyclic)
            printf("THE GRAPH HAS A CYCLE\n");
        else
            printf("THE GRAPH does not have A CYCLE\n");
        if (k == 0)
            fprintf(fp1, "%d\t%d\n", n, gcount);
        else
            fprintf(fp2, "%d\t%d\n", n, gcount);

        // Free memory (optional, but recommended)
        for (int j = 0; j < g->vertices; j++)
        {
            Node curr = g->adjLists[j];
            while (curr)
            {
                Node next = curr->next;
                free(curr);
                curr = next;
            }
        }
        free(g->adjLists);
        free(g->visit);
        free(g);
    }
    fclose(fp1);
    fclose(fp2);
}

int main()
{
    for (int i = 0; i < 2; i++)
        ploter(i);
    return 0;
}
// ...existing code...