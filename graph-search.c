#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX		10          // 헤드 포인터 배열의 최대 크기를 10으로 지정
#define FALSE       0
#define TRUE        1


typedef struct graphNode {          // 인접 리스트의 노드 구조를 구조체로 정의
	int vertex;                     // 정점을 표시하는 데이터 값으로 vertex 정의
	struct graphNode* link;         // 다음 인접 정점을 연결하는 링크
} graphNode;


typedef struct graphType{               // 그래프를 인접 리스트로 표현하기 위한 구조체로 정의
    int n;                              // 그래프의 정점 개수
    graphNode* adjList_H[MAX_VERTEX];   // 그래프 정점에 대한 헤드 포인터 배열
    int visited[MAX_VERTEX];             // 정점에 대한 방문을 표시하기 위한 배열
} graphType;

typedef int element;                    // 스택 원소의 자료형을 int로 정의

typedef struct stackNode{               // 스택의 노드를 구조체로 정의
    int data;
    struct stackNode *link;
}stackNode;

stackNode* top;                         // 스택의 top 노드를 지정하기 위해 포인터  top 선언

int isEmpty(){                          // 스택이 공백 상태인지 확인
    if(top == NULL) return 1;
    else return 0;
}

typedef struct QNode{                   // 연결큐의 노드를 구조체로 정의
    int data;
    struct QNode *link;
}QNode;

typedef struct{                         // 연결큐에서 사용하는 포인터 front와 rear를 구조체로 정의
    QNode *front, *rear;
}LQueueType;

void initializeGraph(graphType* g);             // 그래프를 생성하면서 초기화하는 함수
void insertVertex(graphType* g, int v);         // Vertex를 삽입하는 함수
void insertEdge(graphType* g, int u, int v);    // 그래프의 간선을 삽입하는 함수
void printGraph(graphType* g);                  // 그래프를 출력하는 함수
void push(int item);                            // 스택의 top에 원소를 삽입하는 함수
int pop();                                      // 스택의 top에 원소를 삭제하는 함수
void DFS_adjList(graphType* g, int v);          // 그래프 g의 정점 v에 대한 Deapth First Search 함수
LQueueType *createLinkedQueue();                // 공백 연결 큐를 생성하는 함수
int isEmptyQueue(LQueueType *LQ);               // 큐의 공백검사하는 함수
void enQueue(LQueueType *LQ, int item);         // 큐에 원소를 삽입하는 함수
int deQueue(LQueueType *LQ);                    // 큐에 원소를 삭제하는 함수
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
			printf("생성할 정점 수 입력 = ");
            scanf("%d",&vertex);
            for (i=0; i<vertex; i++)
			    insertVertex(g, i);
            
			break;

		 case 'd': case 'D':
            printf("깊이 우선 탐색 = ");
            DFS_adjList(g, 0);
            getchar();
			break;

		case 'p': case 'P':
			printGraph(g);
			break;

		case 'e': case 'E':
            printf("간선 입력(ex) 0 2 ) = ");
            scanf("%d%d",&u,&i);
			insertEdge(g, u, i);
			break;

		case 'b': case 'B':
		    printf("너비 우선 탐색 = ");
            BFS_adjList(g, 0);
            getchar();
			break;
			break;

		default:
			printf("\n       >>>>>   메뉴에 없는 항목을 선택하였습니다   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


void initializeGraph(graphType* g) {        // 탐색을 위해 초기에 공백 그래프로 생성하면서 초기화하는 함수
    int v;
    g-> n = 0;                              // 그래프의 정점 개수를 0으로 초기화
    for(v = 0; v<MAX_VERTEX; v++){
    g-> visited[v] = FALSE;                 // 그래프의 visited 배열을 FALSE로 초기화
    g-> adjList_H[v] = NULL;                // 그래프의 정점에 대한 헤드 포인터 배열 NULL로 초기화
    }

}

void insertVertex(graphType* g, int v)      // Vertex를 삽입하는 함수
{
  if(((g->n) +1 )>MAX_VERTEX){              // 10개의 vertex보다 크면 return 한다
         printf("\n 그래프 정점의 개수를 초과하였습니다!");
         return;
    }
    g -> n++;
}

void insertEdge(graphType* g, int u, int v)     // 그래프의 간선을 삽입하는 함수
{
  graphNode* node;

  if(u >= g->n || v >= g -> n){                 // 그래프의 정점의 개수보다 큰 간선을 입력할 시
      printf("\n 그래프에 없는 정점입니다!");
      return;
  }

  node = (graphNode *)malloc(sizeof(graphNode));    // 정점 u에 부속된 간선을 삽입하기 위해 node라는 이름의 추가 노드 할당
  node -> vertex = v;                               // 새 노드의 데이터 필드에 인접정점(v) 저장
  node -> link = g ->adjList_H[u];                  // 새 노드가 정점 u가 가리키고 있는 곳을 가리키게 지정
  g->adjList_H[u] = node;                           // 새 노드를 정점 u의 인접 리스트에 첫 번째 노드로 연결
}

void printGraph(graphType* g)               // 그래프를 출력하는 함수
{
    int i;
    graphNode* p;
    for(i = 0; i<g->n; i++){
        printf("\n\t\t정점 %c의 인접 리스트", i+65);    // 그래프의 정점들을 A,B,C로 지정, 해당 정점을 출력한다.
        p = g->adjList_H[i];
        while(p){
            printf("-> %c", p->vertex+65);              // 해당 정점일때까지 인접 정점을 리스트로 출력한다.
            p = p->link;                                // 링크따라 이동한다.
        }
    }
}

void push(int item){                                // 스택의 top에 item을 push하는 함수
    stackNode* temp = (stackNode *)malloc(sizeof(stackNode));
    temp -> data = item;
    temp -> link = top;                                 // 삽입 노드를 top의 위에 push
    top = temp;                                         // top 위치를 push한 함수로 이동
}

int pop(){                                          // 스택의 top item을 pop하는 함수
    int item;
    stackNode* temp = top;

    if(isEmpty()){                                    // 스택이 공백일시
        printf("\n\n 스택이 비어 있습니다.\n");
        return 0;
    }
    else{                                               // 스택이 공백이 아닐경우
        item = temp -> data;
        top = temp -> link;                             // top을 아래 노드로 이동
        free(temp);                                     // 삭제된 노드 메모리 할당 해제
        return item;
    }
}

void DFS_adjList(graphType* g, int v){                  // 그래프 g의 정점 v에 대한 Deapth First Search 함수
    graphNode* w;
    top = NULL;
    push(v);
    g -> visited[v] = TRUE;                             // 정점 v는 방문하였기때문에 TRUE로 설정
    printf(" %c", v + 65);                              // 정점 출력

    while (!isEmpty()){                                 // 스택이 공백이 아닐경우 Deapth First Search
        v = pop();
        w = g->adjList_H[v];

        while(w){
            if(!g->visited[w->vertex]){                 // 정점을 방문하지 않았을 경우
                if(isEmpty()) push(v);                  // 공백일 경우 push
                push(w->vertex);                        // w를 push
                g->visited[w->vertex] = TRUE;           // w를 TRUE로 지정
                printf(" %c", w-> vertex + 65);
                v = w ->vertex;                         // 다음 정점 이동을 위해 v로 설정
                w = g->adjList_H[v];                    // v에 대한 인접노드를 w로 지정 194행에서 다시 실행
            }
            else w = w->link;
        }
    }
}

LQueueType *createLinkedQueue(){                        // 공백 연결 큐를 생성하는 함수
    LQueueType *LQ;
    LQ =(LQueueType *)malloc(sizeof(LQueueType));       // LQ라는 연결 큐 생성
    LQ -> front = NULL;                                 // 초기 큐이므로 fornt NULL
    LQ -> rear = NULL;                                  // 초기 큐이므로 rear NULL
    return LQ;
}

int isEmptyQueue(LQueueType *LQ){                       // 큐의 공백검사하는 함수
    if(LQ -> front == NULL){
        printf("\n Linked Queue is empty! \n");
        return 1;
    }
    else return 0;
}

void enQueue(LQueueType *LQ, int item){                 // 큐에 원소를 삽입하는 함수
    QNode *newNode = (QNode *)malloc(sizeof(QNode));    // 삽입할 새 노드 할당
    newNode -> data = item;                             // 새 노드에 대한 메모리 할당, 데이터 필드에 삽입할 item저장
    newNode -> link = NULL;                             // 마지막 노드이므로  NULL
    if(LQ -> front == NULL){                            // 연결큐가 공백상태인지 검사 공백일 경우 front, rear 둘다 새 노드를 가리키도록 설정
        LQ -> front = newNode;
        LQ -> rear = newNode;
    }
    else{
        LQ ->rear ->link = newNode;                     // 마지막 노드가 새 노드를 가리키도록 설정
        LQ ->rear = newNode;
    }
}

int deQueue(LQueueType *LQ){                            // 큐에 원소를 삭제하는 함수
    QNode *old = LQ -> front;
    int item;
    if (isEmptyQueue(LQ)) return 0;
    else{
        item = old -> data;                             // 삭제할 원소를 old가 가리키게 하여 삭제할 노드 지정
        LQ -> front = LQ ->front -> link;               // front 재설정
        if(LQ->front == NULL)
            LQ -> rear = NULL;
        free(old);
        return item;
    }
}

void BFS_adjList(graphType* g, int v){                  // 그래프 g의 정점 v에 대한 Breath First Search 함수
    graphNode* w;
    LQueueType* Q;                                      // 큐 생성
    Q = createLinkedQueue();
    g -> visited[v] = TRUE;                             // 시작 정점 TRUE로 지정
    printf(" %c", v + 65);
    enQueue(Q, v);

    while(!isEmptyQueue(Q)){                            // 공백이 아닐경우 반복
        v = deQueue(Q);
        for(w = g->adjList_H[v]; w; w = w->link)
        if(!g -> visited[w ->vertex]){                  // 방문하지 않은 정점일경우
            g->visited[w->vertex] = TRUE;               // TRUE로 지정
            printf(" %c", w -> vertex + 65);
            enQueue(Q, w->vertex);
        }
    }
}