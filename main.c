#include <stdio.h>
#include <stdlib.h>
#include "./sllist.h"
#include "./queue.h"

typedef struct MyMatrics {
        int X;
        int **matrix;
} MyMatrix;

typedef struct NodeMyLinks {
        int node;
        int links;
} NodeMyLinks;

MyMatrix *main_matrix(const int X)
{
        MyMatrix *sequence_matrix = (MyMatrix *)malloc(sizeof(MyMatrix));
        sequence_matrix->X = X;
        sequence_matrix->matrix = (int **)malloc(X * sizeof(int *));
        for (int i = 0; i < X; i++)
                sequence_matrix->matrix[i] = (int *)malloc(X * sizeof(int));
        for (int i = 0; i < X; i++) {
                for (int j = 0; j < X; j++) {
                        sequence_matrix->matrix[i][j] = 0;
                }
        }

        return sequence_matrix;
}

void printedMatrix(MyMatrix *matrix)
{
        for (int i = 0; i < matrix->X; i++) {
                for (int j = 0; j < matrix->X; j++) {
                        printf("%3d", matrix->matrix[i][j]);
                }
                printf("\n");
        }
}

int unvisitNode(MyMatrix *graphs, int currentNode, int *visitedNode)
{
        for (int i = 0; i < graphs->X; i++) {
                if (graphs->matrix[currentNode][i] == 1 && visitedNode[i] == 0) {
                        return i;
                }
        }
        return -1;
}

void graphsDepthBypassing(MyMatrix *graphs)
{
        int nextNode;
        int *visitedNode = (int *)malloc(graphs->X * sizeof(int));
        SLList *stack = (SLList *)malloc(sizeof(SLList));
        initialList(stack);

        visitedNode[0] = 1;
        printf("%3d", 0);
        push(stack, 0);

        while (stack->size > 0) {
                nextNode = unvisitNode(graphs, stack->head->data, visitedNode);
                if (nextNode == -1) {
                        pop(stack);
                } else {
                        visitedNode[nextNode] = 1;
                        printf("%3d", nextNode);
                        push(stack, nextNode);
                }
        }
        printf("\n");
        freeList(stack);
        free(visitedNode);
}

NodeLinks **linksCount(const int X)
{
        NodeLinks **nodeLinks = (NodeLinks **)malloc(X * sizeof(NodeLinks *));
        for (int i = 0; i < X; i++)
                nodeLinks[i] = (NodeLinks *)malloc(sizeof(NodeLinks));
        for (int i = 0; i < X; i++) {
                nodeLinks[i]->links = 0;
                nodeLinks[i]->node = i;
        }

        return nodeLinks;
}

void recursiveCountLinks(MyMatrix *graphs, int node, NodeLinks **links)
{
        if (node >= graphs->X)
                return;
        for (int i = 0; i < graphs->X; i++) {
                if (node != i && graphs->matrix[node][i] == 1) {
                        links[node]->links++;
                }
        }
        recursiveCountLinks(graphs, node + 1, links);
}

void sortLinks(NodeLinks **links, const int size)
{
        NodeLinks *value;

        for (int i = 0; i < size; i++) {
                value = links[i];
                int j;
                for (j = i; j > 0 && links[j - 1]->links < value->links; j--)
                        links[j] = links[j - 1];
                links[j] = value;
        }
}

void freeCountLinks(NodeLinks **links, const int size)
{
        for (int i = 0; i < size; i++)
                free(links[i]);
        free(links);
}

void queueCountLinks(MyMatrix *graphs, int node, NodeLinks **links)
{
        Queue *queue = queueData(graphs->X);
        int *visitedNode = (int *)malloc(graph->X * sizeof(int));

        enqueue(queue, node);
        while (queue->point >= 0) {
                int idx = dequeue(queue);
                if (visitedNode[idx] == 1)
                        continue;
                visitedNode[idx] = 1;
                for (int i = 0; i < graphs->X; ++i) {
                        if (graphs->matrix[idx][i] == 1) {
                                if (i != idx) {
                                        links[idx]->links++;
                                }
                                if (visitedNode[i] == 0) {
                                        enqueue(queue, i);
                                }
                        }
                }
        }
        free(visitedNode);
        freeQueue(queue);
}

void printedCountLinks(NodeLinks **links, const int size)
{
        printf("node(links): ");
        for (int i = 0; i < size; i++)
                printf("%d(%d) ", links[i]->node, links[i]->links);
        printf("\n");
}

int main()
{
        const int X = 9;

        MyMatrix *graphs = main_matrix(X);
        if (graphs == NULL)
                return 1;

        graphs->matrix[0][1] = 1;
        graphs->matrix[0][2] = 1;
        graphs->matrix[1][0] = 1;
        graphs->matrix[1][3] = 1;
        graphs->matrix[1][6] = 1;
        graphs->matrix[2][0] = 1;
        graphs->matrix[2][2] = 1;
        graphs->matrix[2][7] = 1;
        graphs->matrix[3][1] = 1;
        graphs->matrix[3][4] = 1;
        graphs->matrix[3][5] = 1;
        graphs->matrix[4][3] = 1;
        graphs->matrix[5][3] = 1;
        graphs->matrix[6][1] = 1;
        graphs->matrix[6][6] = 1;
        graphs->matrix[7][2] = 1;
        graphs->matrix[7][8] = 1;
        graphs->matrix[8][7] = 1;
        graphs->matrix[8][8] = 1;

        printedMatrix(graphs);
        printf("Depth-first bypassing using a stack:\n");
        graphsDepthBypassing(graphs);

        NodeLinks **links = links_count(X);
        recursiveCountLinks(graphs, 0, links);
        sortLinks(links, X);
        printf("Traversing a graph with a recursive function:\n");
        printedCountLinks(links, X);
        freeCountLinks(links, X);

        NodeLinks **linksX = linksCount(X);
        queueCountLinks(graphs, 0, linksX);
        sortLinks(linksX, X);
        printf("Graph traversal by adjacency matrix:\n");
        printedCountLinks(linksX, X);
        freeCountLinks(linksX, X);

        return 0;
}
