#include "findingPath.h"
#include "utils.h"
#include "globals.h"

typedef struct queueNode {
    data key;
    struct queueNode* next;
}queueNode;

typedef struct queue {
    queueNode* front, * rear;
}queuee;


queueNode* newNode(data k) {
    queueNode* tmp = (queueNode*)malloc(sizeof(queueNode));
    tmp->key = k;
    tmp->next = NULL;
    return tmp;
}

queuee* createQueue() {
    queuee* tmp = (queuee*)malloc(sizeof(queuee));
    tmp->front = tmp->rear = NULL;
    return tmp;
}

void enQueue(queuee* q, data k) {
    queueNode* tmp = newNode(k);
    if (q->rear == NULL) {
        q->front = q->rear = tmp;
        return;
    }
    q->rear->next = tmp;
    q->rear = tmp;
}

void deQueue(queuee* q) {
    if (q->front == NULL)
        return;

    queueNode* temp = q->front;

    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
}

bool isEmpty(queuee* q) {
    return q->front == NULL;
}


bool isValid(int row, int col){
    return (row >= 0) && (row < dims) &&
        (col >= 0) && (col < dims);
}



int BFS(Point src, Point dest)
{
    for (int i = 0; i < dims; i++) 
        for (int j = 0; j < dims; j++)
            visitedArr[i][j] = false;

 
    visitedArr[src.x][src.y] = true;
    int rowNum[] = { -1, 0, 0, 1 };
    int colNum[] = { 0, -1, 1, 0 };


    queuee* q = createQueue();
    data s = { src, 0 };
    enQueue(q,s);

    while (!isEmpty(q))
    {
        data curr = q->front->key;
        Point pt = curr.pt;

        if (pt.x == dest.x && pt.y == dest.y) {
            return curr.distanceFromStart;
        }

        deQueue(q);

        for (int i = 0; i < 4; i++)
        {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];

            if (isValid(row, col) && gameArr[row][col]==notBall &&
                !visitedArr[row][col])
            {
                visitedArr[row][col] = true;
                parentsArr[row][col] = pt;
                data adjCell = { {row, col},curr.distanceFromStart + 1 };
                enQueue(q,adjCell);
            }
        }
    }

    

    return DESTINATION_CANNOT_BE_REACHED;
}



