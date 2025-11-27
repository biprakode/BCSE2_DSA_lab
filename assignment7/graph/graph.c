#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node for adjacency list
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

// Adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// Graph structure
struct Graph {
    int numVertices;
    struct AdjList* array;
};

// Queue for BFS
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

// Create a new adjacency list node
struct AdjListNode* createAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Create a graph with given number of vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    
    graph->array = (struct AdjList*)malloc(numVertices * sizeof(struct AdjList));
    
    for (int i = 0; i < numVertices; i++) {
        graph->array[i].head = NULL;
    }
    
    return graph;
}

// Add an edge to undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add edge from src to dest
    struct AdjListNode* newNode = createAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    
    // Add edge from dest to src (undirected graph)
    newNode = createAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Create a queue
struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(capacity * sizeof(int));
    return queue;
}

// Check if queue is full
bool isQueueFull(struct Queue* queue) {
    return (queue->size == queue->capacity);
}

// Check if queue is empty
bool isQueueEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

// Add item to queue
void enqueue(struct Queue* queue, int item) {
    if (isQueueFull(queue)) return;
    
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size++;
}

// Remove item from queue
int dequeue(struct Queue* queue) {
    if (isQueueEmpty(queue)) return -1;
    
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

// i) Check if there's a path between two vertices
bool Connected(struct Graph* graph, int v1, int v2) {
    if (v1 == v2) return true;
    
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = false;
    }
    
    struct Queue* queue = createQueue(graph->numVertices);
    visited[v1] = true;
    enqueue(queue, v1);
    
    while (!isQueueEmpty(queue)) {
        int current = dequeue(queue);
        
        struct AdjListNode* temp = graph->array[current].head;
        while (temp != NULL) {
            int neighbor = temp->dest;
            
            if (neighbor == v2) {
                free(visited);
                free(queue->array);
                free(queue);
                return true;
            }
            
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                enqueue(queue, neighbor);
            }
            temp = temp->next;
        }
    }
    
    free(visited);
    free(queue->array);
    free(queue);
    return false;
}

void bfs(struct Graph* graph, int start, int** distances, int** previous) {
    *distances = (int*)malloc(graph->numVertices * sizeof(int));
    *previous = (int*)malloc(graph->numVertices * sizeof(int));
    
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    
    for (int i = 0; i < graph->numVertices; i++) {
        (*distances)[i] = -1;  // -1 means unreachable
        (*previous)[i] = -1;   // -1 means no previous vertex
        visited[i] = false;
    }
    
    (*distances)[start] = 0;
    visited[start] = true;
    
    struct Queue* queue = createQueue(graph->numVertices);
    enqueue(queue, start);
    
    while (!isQueueEmpty(queue)) {
        int current = dequeue(queue);
        
        struct AdjListNode* temp = graph->array[current].head;
        while (temp != NULL) {
            int neighbor = temp->dest;
            
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                (*distances)[neighbor] = (*distances)[current] + 1;
                (*previous)[neighbor] = current;
                enqueue(queue, neighbor);
            }
            temp = temp->next;
        }
    }
    
    free(visited);
    free(queue->array);
    free(queue);
}

// iii) Distance between two vertices
int distance(struct Graph* graph, int v1, int v2) {
    if (v1 == v2) return 0;
    
    int* distances = NULL;
    int* previous = NULL;
    
    bfs(graph, v1, &distances, &previous);
    
    int dist = distances[v2];
    
    free(distances);
    free(previous);
    
    return dist;
}

// DFS helper function
void dfsUtil(struct Graph* graph, int current, bool* visited, int* distances, int* previous, int currentDistance) {
    visited[current] = true;
    
    struct AdjListNode* temp = graph->array[current].head;
    while (temp != NULL) {
        int neighbor = temp->dest;
        
        if (!visited[neighbor]) {
            distances[neighbor] = currentDistance + 1;
            previous[neighbor] = current;
            dfsUtil(graph, neighbor, visited, distances, previous, currentDistance + 1);
        }
        temp = temp->next;
    }
}

// iv) DFS - returns distances and previous vertices
void dfs(struct Graph* graph, int start, int** distances, int** previous) {
    *distances = (int*)malloc(graph->numVertices * sizeof(int));
    *previous = (int*)malloc(graph->numVertices * sizeof(int));
    
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    
    for (int i = 0; i < graph->numVertices; i++) {
        (*distances)[i] = -1;  // -1 means unreachable
        (*previous)[i] = -1;   // -1 means no previous vertex
        visited[i] = false;
    }
    
    (*distances)[start] = 0;
    dfsUtil(graph, start, visited, *distances, *previous, 0);
    
    free(visited);
}

// Print the graph
void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Vertex %d:", i);
        struct AdjListNode* temp = graph->array[i].head;
        while (temp != NULL) {
            printf(" -> %d", temp->dest);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Print BFS/DFS results
void printResults(int* distances, int* previous, int numVertices, const char* algorithm) {
    printf("\n%s Results:\n", algorithm);
    printf("Vertex\tDistance\tPrevious\n");
    for (int i = 0; i < numVertices; i++) {
        printf("%d\t%d\t\t%d\n", i, distances[i], previous[i]);
    }
}

// Test the implementation
int main() {
    // Create a graph with 7 vertices
    struct Graph* graph = createGraph(7);
    
    // Add edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 3, 6);
    
    printf("Graph structure:\n");
    printGraph(graph);
    
    // Test Connected function
    printf("\nTesting Connected function:\n");
    printf("Is there a path from 0 to 6? %s\n", Connected(graph, 0, 6) ? "Yes" : "No");
    printf("Is there a path from 0 to 4? %s\n", Connected(graph, 0, 4) ? "Yes" : "No");
    
    // Test BFS
    int* bfsDistances = NULL;
    int* bfsPrevious = NULL;
    bfs(graph, 0, &bfsDistances, &bfsPrevious);
    printResults(bfsDistances, bfsPrevious, graph->numVertices, "BFS");
    
    // Test Distance function
    printf("\nTesting Distance function:\n");
    printf("Distance from 0 to 6: %d\n", distance(graph, 0, 6));
    printf("Distance from 0 to 4: %d\n", distance(graph, 0, 4));
    printf("Distance from 0 to 0: %d\n", distance(graph, 0, 0));
    
    // Test DFS
    int* dfsDistances = NULL;
    int* dfsPrevious = NULL;
    dfs(graph, 0, &dfsDistances, &dfsPrevious);
    printResults(dfsDistances, dfsPrevious, graph->numVertices, "DFS");
    
    // Free memory
    free(bfsDistances);
    free(bfsPrevious);
    free(dfsDistances);
    free(dfsPrevious);
    
    free(graph->array);
    free(graph);
    
    return 0;
}