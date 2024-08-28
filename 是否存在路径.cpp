#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

Node* createNode(int v);
Queue* createQueue(unsigned capacity);
int isFull(Queue* queue);
int isEmpty(Queue* queue);
void enqueue(Queue* queue, int item);
int dequeue(Queue* queue);
void addEdge(Node** graph, int src, int dest);
int bfs(Node** graph, int start, int end, int n);

int main() {
    int n, e, source, destination;
    scanf("%d %d", &n, &e);

    Node** graph = (Node**)malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) {
        graph[i] = NULL;
    }

    for (int i = 0; i < e; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
        addEdge(graph, dest, src); 
    }

    scanf("%d %d", &source, &destination);

    if (bfs(graph, source, destination, n)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    free(graph);
    return 0;
}

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

int isEmpty(Queue* queue) {
    return (queue->size == 0);
}

void enqueue(Queue* queue, int item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(Queue* queue) {
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

void addEdge(Node** graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph[src];
    graph[src] = newNode;
}

int bfs(Node** graph, int start, int end, int n) {
    int visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    Queue* queue = createQueue(n);

    visited[start] = 1;
    enqueue(queue, start);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        Node* temp = graph[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;

            if (adjVertex == end) {
                return 1;
            }

            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }

    return 0;
}
