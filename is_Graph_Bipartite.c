#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Queue {
    int front;
    int rear;
    int* data;
} Queue;

// Function to initialize a queue
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    queue->data = (int*)malloc(capacity * sizeof(int));
    return queue;
}

// Function to check if a queue is empty
bool isQueueEmpty(Queue* queue) {
    return (queue->front == -1);
}

// Function to enqueue an element into the queue
void enqueue(Queue* queue, int element) {
    if (isQueueEmpty(queue)) {
        queue->front = 0;
    }
    queue->rear++;
    queue->data[queue->rear] = element;
}

// Function to dequeue an element from the queue
int dequeue(Queue* queue) {
    int element = queue->data[queue->front];
    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front++;
    }
    return element;
}

// Function to check if a graph is bipartite
bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    int* color = (int*)malloc(graphSize * sizeof(int));

    for (int i = 0; i < graphSize; i++) {
        color[i] = 0;
    }

    Queue* queue = createQueue(graphSize);

    for (int start = 0; start < graphSize; start++) {
        if (color[start] != 0) {
            continue;
        }

        color[start] = 1;
        enqueue(queue, start);

        while (!isQueueEmpty(queue)) {
            int current = dequeue(queue);

            for (int i = 0; i < graphColSize[current]; i++) {
                int neighbor = graph[current][i];
                if (color[neighbor] == 0) {
                    color[neighbor] = 3 - color[current];
                    enqueue(queue, neighbor);
                } else if (color[neighbor] == color[current]) {
                    free(color);
                    free(queue->data);
                    free(queue);
                    return false;
                }
            }
        }
    }

    free(color);
    free(queue->data);
    free(queue);
    return true;
}

int main() {
    int graphSize = 4;
    int graphColSize[] = {2, 2, 2, 2};
    int** graph = (int**)malloc(graphSize * sizeof(int*));
    for (int i = 0; i < graphSize; i++) {
        graph[i] = (int*)malloc(graphColSize[i] * sizeof(int));
    }

    // Define the graph connections
    graph[0][0] = 1;
    graph[0][1] = 3;

    graph[1][0] = 0;
    graph[1][1] = 2;

    graph[2][0] = 1;
    graph[2][1] = 3;

    graph[3][0] = 0;
    graph[3][1] = 2;

    bool isBipartiteGraph = isBipartite(graph, graphSize, graphColSize);

    if (isBipartiteGraph) {
        printf("The graph is bipartite.\n");
    } else {
        printf("The graph is not bipartite.\n");
    }

    // Clean up memory
    for (int i = 0; i < graphSize; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
