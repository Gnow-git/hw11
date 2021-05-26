#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX		10          // 헤드 포인터 배열의 최대 크기를 10으로 지정


typedef struct graphNode {          // 인접 리스트의 노드 구조를 구조체로 정의
	int vertex;                     // 정점을 표시하는 데이터 값으로 vertex 정의
	struct graphNode* link;         // 다음 인접 정점을 연결하는 링크
} graphNode;


typedef struct graphType{               // 그래프를 인접 리스트로 표현하기 위한 구조체로 정의
    int n;                              // 그래프의 정점 개수
    graphNode* adjList_H[MAX_VERTEX];   // 그래프 정점에 대한 헤드 포인터 배열
} graphType;



void initializeGraph(graphType* g);             // 그래프를 생성하면서 초기화하는 함수
void insertVertex(graphType* g, int v);         // Vertex를 삽입하는 함수
void insertEdge(graphType* g, int u, int v);    // 그래프의 간선을 삽입하는 함수
void printGraph(graphType* g);                  // 그래프를 출력하는 함수


int main()
{
	char command;
	int i;
    int vertex;
    int u;
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
		
			break;

		default:
			printf("\n       >>>>>   메뉴에 없는 항목을 선택하였습니다   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void initializeGraph(graphType* g) {        // 그래프를 생성하면서 초기화하는 함수
    int v;
    g-> n = 0;                              // 그래프의 정점 개수를 0으로 초기화
    for(v = 0; v<MAX_VERTEX; v++)
    g-> adjList_H[v] = NULL;                // 그래프의 정점에 대한 헤드 포인터 배열 NULL로 초기화

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
