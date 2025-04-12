/*parcurgerge  graf cu DFS/BFS*/
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

typedef struct Graphx
{
    int vertices;
    int *visited;
    NODE **adjacency;
} GRAPH;

NODE *create_node(int value)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

GRAPH *create_graph(int vertices)
{
    GRAPH *graph = malloc(sizeof(GRAPH));

    graph->vertices = vertices + 1;
    graph->adjacency = malloc((vertices + 1) * sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * (vertices + 1));

    for (int i = 0; i < graph->vertices; i++)
    {
        graph->adjacency[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void add_edge(GRAPH *graph, int source, int destination)
{
    NODE *new_node = create_node(destination);

    new_node->next = graph->adjacency[source];
    graph->adjacency[source] = new_node;

    new_node = create_node(source);
    new_node->next = graph->adjacency[destination];
    graph->adjacency[destination] = new_node;
}
void *insert_edges(int nr_of_vertices, int nr_of_edges, GRAPH *graph)
{
    int source, destination;
    printf("Adauga %d muchii (de la 1 la %d)\n", nr_of_edges, nr_of_vertices);
    for (int i = 0; i < nr_of_edges; i++)
    {
        scanf("%d%d", &source, &destination);
        add_edge(graph, source, destination);
    }
}

int is_empty(NODE *queue)
{
    return queue == NULL;
}

void enqueue(NODE **queue, int data)
{
    NODE *new_node = create_node(data);

    if (is_empty(*queue))
    {
        *queue = new_node;
    }
    else
    {
        NODE *temp = *queue;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE **queue)
{
    int data = (*queue)->data;
    NODE *temp = *queue;

    *queue = (*queue)->next;
    free(temp);

    return data;
}

void print_graph(GRAPH *graph)
{
    for (int i = 1; i < graph->vertices; i++)
    {
        printf("Nodul %d",i);
        NODE *temp = graph->adjacency[i];
        while (temp)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void print_queue(NODE *queue)
{
    printf("The queue: ");
    while (queue != NULL)
    {
        printf("%d ", queue->data);
        queue = queue->next;
    }
}

void wipe_visited(GRAPH *graph)
{
    for (int i = 0; i < graph->vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

void DFS(GRAPH *graph, int vertex_nr)
{
    NODE *adj_list = graph->adjacency[vertex_nr];
    NODE *temp = adj_list;

    graph->visited[vertex_nr] = 1;
    printf("%d", vertex_nr);

    while (temp != NULL)
    {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0)
        {
            printf("->");
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(GRAPH *graph, int start)
{
    NODE *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    int first=1;
    while (!is_empty(queue))
    {
        int current = dequeue(&queue);
        if (!first)
        {
            printf("->");
        }
        printf("%d", current);
        first=0;
        NODE *temp = graph->adjacency[current];

        while (temp)
        {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
        temp = temp->next;
        }
    }
}

int main()
{
    int nr_of_vertices;
    int nr_of_edges;
    int starting_vertex;

    printf("Cate noduri are graful?" );
    scanf("%d", &nr_of_vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &nr_of_edges);

    GRAPH *graph = create_graph(nr_of_vertices);
    insert_edges(nr_of_vertices, nr_of_edges, graph);

    printf("De unde plecam in DFS?");
    scanf("%d", &starting_vertex);

    printf("Parcurgere cu DFS:");
    DFS(graph, starting_vertex);

    wipe_visited(graph);
    printf("\n");

    printf("De unde plecam in BFS?");
    scanf("%d", &starting_vertex);

    printf("Parcurgere cu BFS:");
    BFS(graph, starting_vertex);

    return 0;
}