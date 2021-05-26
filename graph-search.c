#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX		10          // ��� ������ �迭�� �ִ� ũ�⸦ 10���� ����


typedef struct graphNode {          // ���� ����Ʈ�� ��� ������ ����ü�� ����
	int vertex;                     // ������ ǥ���ϴ� ������ ������ vertex ����
	struct graphNode* link;         // ���� ���� ������ �����ϴ� ��ũ
} graphNode;


typedef struct graphType{               // �׷����� ���� ����Ʈ�� ǥ���ϱ� ���� ����ü�� ����
    int n;                              // �׷����� ���� ����
    graphNode* adjList_H[MAX_VERTEX];   // �׷��� ������ ���� ��� ������ �迭
} graphType;



void initializeGraph(graphType* g);             // �׷����� �����ϸ鼭 �ʱ�ȭ�ϴ� �Լ�
void insertVertex(graphType* g, int v);         // Vertex�� �����ϴ� �Լ�
void insertEdge(graphType* g, int u, int v);    // �׷����� ������ �����ϴ� �Լ�
void printGraph(graphType* g);                  // �׷����� ����ϴ� �Լ�


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
			printf("������ ���� �� �Է� = ");
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
            printf("���� �Է�(ex) 0 2 ) = ");
            scanf("%d%d",&u,&i);
			insertEdge(g, u, i);
			break;

		case 'b': case 'B':
		
			break;

		default:
			printf("\n       >>>>>   �޴��� ���� �׸��� �����Ͽ����ϴ�   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void initializeGraph(graphType* g) {        // �׷����� �����ϸ鼭 �ʱ�ȭ�ϴ� �Լ�
    int v;
    g-> n = 0;                              // �׷����� ���� ������ 0���� �ʱ�ȭ
    for(v = 0; v<MAX_VERTEX; v++)
    g-> adjList_H[v] = NULL;                // �׷����� ������ ���� ��� ������ �迭 NULL�� �ʱ�ȭ

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
