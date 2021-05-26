#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX		10          // ��� ������ �迭�� �ִ� ũ�⸦ 10���� ����
#define FALSE       0
#define TRUE        1


typedef struct graphNode {          // ���� ����Ʈ�� ��� ������ ����ü�� ����
	int vertex;                     // ������ ǥ���ϴ� ������ ������ vertex ����
	struct graphNode* link;         // ���� ���� ������ �����ϴ� ��ũ
} graphNode;


typedef struct graphType{               // �׷����� ���� ����Ʈ�� ǥ���ϱ� ���� ����ü�� ����
    int n;                              // �׷����� ���� ����
    graphNode* adjList_H[MAX_VERTEX];   // �׷��� ������ ���� ��� ������ �迭
    int visited[MAX_VERTEX];             // ������ ���� �湮�� ǥ���ϱ� ���� �迭
} graphType;

typedef int element;                    // ���� ������ �ڷ����� int�� ����

typedef struct stackNode{               // ������ ��带 ����ü�� ����
    int data;
    struct stackNode *link;
}stackNode;

stackNode* top;                         // ������ top ��带 �����ϱ� ���� ������  top ����

int isEmpty(){                          // ������ ���� �������� Ȯ��
    if(top == NULL) return 1;
    else return 0;
}

typedef struct QNode{                   // ����ť�� ��带 ����ü�� ����
    int data;
    struct QNode *link;
}QNode;

typedef struct{                         // ����ť���� ����ϴ� ������ front�� rear�� ����ü�� ����
    QNode *front, *rear;
}LQueueType;

void initializeGraph(graphType* g);             // �׷����� �����ϸ鼭 �ʱ�ȭ�ϴ� �Լ�
void insertVertex(graphType* g, int v);         // Vertex�� �����ϴ� �Լ�
void insertEdge(graphType* g, int u, int v);    // �׷����� ������ �����ϴ� �Լ�
void printGraph(graphType* g);                  // �׷����� ����ϴ� �Լ�
void push(int item);                            // ������ top�� ���Ҹ� �����ϴ� �Լ�
int pop();                                      // ������ top�� ���Ҹ� �����ϴ� �Լ�
void DFS_adjList(graphType* g, int v);          // �׷��� g�� ���� v�� ���� Deapth First Search �Լ�
LQueueType *createLinkedQueue();                // ���� ���� ť�� �����ϴ� �Լ�
int isEmptyQueue(LQueueType *LQ);               // ť�� ����˻��ϴ� �Լ�
void enQueue(LQueueType *LQ, int item);         // ť�� ���Ҹ� �����ϴ� �Լ�
int deQueue(LQueueType *LQ);                    // ť�� ���Ҹ� �����ϴ� �Լ�
void BFS_adjList(graphType* g, int v);

int main()
{
	char command;
	int i, u;
    int vertex;
    graphType* g = NULL;
    g = (graphType *)malloc(sizeof(graphType));


	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                       Graph Searches                           \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v      Insert Edge                  = e \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeGraph(g);
			break;

		case 'q': case 'Q':
		 	break;

		case 'v': case 'V':
			printf("������ ���� �� �Է� = ");
            scanf("%d",&vertex);
            for (i=0; i<vertex; i++)
			    insertVertex(g, i);
            
			break;

		 case 'd': case 'D':
            printf("���� �켱 Ž�� = ");
            DFS_adjList(g, 0);
            getchar();
			break;

		case 'p': case 'P':
			printGraph(g);
			break;

		case 'e': case 'E':
            printf("���� �Է�(ex) 0 2 ) = ");
            scanf("%d%d",&u,&i);
			insertEdge(g, u, i);
			break;

		case 'b': case 'B':
		    printf("�ʺ� �켱 Ž�� = ");
            BFS_adjList(g, 0);
            getchar();
			break;
			break;

		default:
			printf("\n       >>>>>   �޴��� ���� �׸��� �����Ͽ����ϴ�   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


void initializeGraph(graphType* g) {        // Ž���� ���� �ʱ⿡ ���� �׷����� �����ϸ鼭 �ʱ�ȭ�ϴ� �Լ�
    int v;
    g-> n = 0;                              // �׷����� ���� ������ 0���� �ʱ�ȭ
    for(v = 0; v<MAX_VERTEX; v++){
    g-> visited[v] = FALSE;                 // �׷����� visited �迭�� FALSE�� �ʱ�ȭ
    g-> adjList_H[v] = NULL;                // �׷����� ������ ���� ��� ������ �迭 NULL�� �ʱ�ȭ
    }

}

void insertVertex(graphType* g, int v)      // Vertex�� �����ϴ� �Լ�
{
  if(((g->n) +1 )>MAX_VERTEX){              // 10���� vertex���� ũ�� return �Ѵ�
         printf("\n �׷��� ������ ������ �ʰ��Ͽ����ϴ�!");
         return;
    }
    g -> n++;
}

void insertEdge(graphType* g, int u, int v)     // �׷����� ������ �����ϴ� �Լ�
{
  graphNode* node;

  if(u >= g->n || v >= g -> n){                 // �׷����� ������ �������� ū ������ �Է��� ��
      printf("\n �׷����� ���� �����Դϴ�!");
      return;
  }

  node = (graphNode *)malloc(sizeof(graphNode));    // ���� u�� �μӵ� ������ �����ϱ� ���� node��� �̸��� �߰� ��� �Ҵ�
  node -> vertex = v;                               // �� ����� ������ �ʵ忡 ��������(v) ����
  node -> link = g ->adjList_H[u];                  // �� ��尡 ���� u�� ����Ű�� �ִ� ���� ����Ű�� ����
  g->adjList_H[u] = node;                           // �� ��带 ���� u�� ���� ����Ʈ�� ù ��° ���� ����
}

void printGraph(graphType* g)               // �׷����� ����ϴ� �Լ�
{
    int i;
    graphNode* p;
    for(i = 0; i<g->n; i++){
        printf("\n\t\t���� %c�� ���� ����Ʈ", i+65);    // �׷����� �������� A,B,C�� ����, �ش� ������ ����Ѵ�.
        p = g->adjList_H[i];
        while(p){
            printf("-> %c", p->vertex+65);              // �ش� �����϶����� ���� ������ ����Ʈ�� ����Ѵ�.
            p = p->link;                                // ��ũ���� �̵��Ѵ�.
        }
    }
}

void push(int item){                                // ������ top�� item�� push�ϴ� �Լ�
    stackNode* temp = (stackNode *)malloc(sizeof(stackNode));
    temp -> data = item;
    temp -> link = top;                                 // ���� ��带 top�� ���� push
    top = temp;                                         // top ��ġ�� push�� �Լ��� �̵�
}

int pop(){                                          // ������ top item�� pop�ϴ� �Լ�
    int item;
    stackNode* temp = top;

    if(isEmpty()){                                    // ������ �����Ͻ�
        printf("\n\n ������ ��� �ֽ��ϴ�.\n");
        return 0;
    }
    else{                                               // ������ ������ �ƴҰ��
        item = temp -> data;
        top = temp -> link;                             // top�� �Ʒ� ���� �̵�
        free(temp);                                     // ������ ��� �޸� �Ҵ� ����
        return item;
    }
}

void DFS_adjList(graphType* g, int v){                  // �׷��� g�� ���� v�� ���� Deapth First Search �Լ�
    graphNode* w;
    top = NULL;
    push(v);
    g -> visited[v] = TRUE;                             // ���� v�� �湮�Ͽ��⶧���� TRUE�� ����
    printf(" %c", v + 65);                              // ���� ���

    while (!isEmpty()){                                 // ������ ������ �ƴҰ�� Deapth First Search
        v = pop();
        w = g->adjList_H[v];

        while(w){
            if(!g->visited[w->vertex]){                 // ������ �湮���� �ʾ��� ���
                if(isEmpty()) push(v);                  // ������ ��� push
                push(w->vertex);                        // w�� push
                g->visited[w->vertex] = TRUE;           // w�� TRUE�� ����
                printf(" %c", w-> vertex + 65);
                v = w ->vertex;                         // ���� ���� �̵��� ���� v�� ����
                w = g->adjList_H[v];                    // v�� ���� ������带 w�� ���� 194�࿡�� �ٽ� ����
            }
            else w = w->link;
        }
    }
}

LQueueType *createLinkedQueue(){                        // ���� ���� ť�� �����ϴ� �Լ�
    LQueueType *LQ;
    LQ =(LQueueType *)malloc(sizeof(LQueueType));       // LQ��� ���� ť ����
    LQ -> front = NULL;                                 // �ʱ� ť�̹Ƿ� fornt NULL
    LQ -> rear = NULL;                                  // �ʱ� ť�̹Ƿ� rear NULL
    return LQ;
}

int isEmptyQueue(LQueueType *LQ){                       // ť�� ����˻��ϴ� �Լ�
    if(LQ -> front == NULL){
        printf("\n Linked Queue is empty! \n");
        return 1;
    }
    else return 0;
}

void enQueue(LQueueType *LQ, int item){                 // ť�� ���Ҹ� �����ϴ� �Լ�
    QNode *newNode = (QNode *)malloc(sizeof(QNode));    // ������ �� ��� �Ҵ�
    newNode -> data = item;                             // �� ��忡 ���� �޸� �Ҵ�, ������ �ʵ忡 ������ item����
    newNode -> link = NULL;                             // ������ ����̹Ƿ�  NULL
    if(LQ -> front == NULL){                            // ����ť�� ����������� �˻� ������ ��� front, rear �Ѵ� �� ��带 ����Ű���� ����
        LQ -> front = newNode;
        LQ -> rear = newNode;
    }
    else{
        LQ ->rear ->link = newNode;                     // ������ ��尡 �� ��带 ����Ű���� ����
        LQ ->rear = newNode;
    }
}

int deQueue(LQueueType *LQ){                            // ť�� ���Ҹ� �����ϴ� �Լ�
    QNode *old = LQ -> front;
    int item;
    if (isEmptyQueue(LQ)) return 0;
    else{
        item = old -> data;                             // ������ ���Ҹ� old�� ����Ű�� �Ͽ� ������ ��� ����
        LQ -> front = LQ ->front -> link;               // front �缳��
        if(LQ->front == NULL)
            LQ -> rear = NULL;
        free(old);
        return item;
    }
}

void BFS_adjList(graphType* g, int v){                  // �׷��� g�� ���� v�� ���� Breath First Search �Լ�
    graphNode* w;
    LQueueType* Q;                                      // ť ����
    Q = createLinkedQueue();
    g -> visited[v] = TRUE;                             // ���� ���� TRUE�� ����
    printf(" %c", v + 65);
    enQueue(Q, v);

    while(!isEmptyQueue(Q)){                            // ������ �ƴҰ�� �ݺ�
        v = deQueue(Q);
        for(w = g->adjList_H[v]; w; w = w->link)
        if(!g -> visited[w ->vertex]){                  // �湮���� ���� �����ϰ��
            g->visited[w->vertex] = TRUE;               // TRUE�� ����
            printf(" %c", w -> vertex + 65);
            enQueue(Q, w->vertex);
        }
    }
}