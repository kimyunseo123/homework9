// Binary Search Tree #1
#include <stdio.h>
#include <stdlib.h>

typedef struct node { // (typedef를 사용하여) Node 구조체 생성
	int key;
	struct node *left;
	struct node *right;
} Node;

// 함수 리스트
void inorderTraversal(Node* ptr);	  // 순환적 중위순회
void preorderTraversal(Node* ptr);    // 순환적 전위순회
void postorderTraversal(Node* ptr);	  // 순환적 후위순회

int insert(Node* head, int key);           // tree에 노드 삽입
int deleteLeafNode(Node* head, int key);  // leaf 노드 삭제

Node* searchRecursive(Node* ptr, int key);   // BST 탐색
Node* searchIterative(Node* head, int key);  // BST 탐색

int initializeBST(Node** h); // BST 초기화
int freeBST(Node* head);     // BST 메모리 해제

void freeNode(Node* ptr); // 노드 해제

int main()
{
	char command; // 변수 command
	int key; // 변수 key
	Node* head = NULL;
	Node* ptr = NULL;	// temp

	do{
        printf("[----- [Kim Yun Seo]  [2020021016] -----]");
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // command 값 받기

		switch(command) {
		case 'z': case 'Z': // command 값이 z 또는  일 경우
			initializeBST(&head);
			break;
		case 'q': case 'Q': // command 값이 q 또는 Q 일 경우
			freeBST(head);
			break;
		case 'n': case 'N': // command 값이 n 또는 N 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
			insert(head, key);
			break;
		case 'd': case 'D': // command 값이 d 또는 D 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F': // command 값이 f 또는 F 일 경우
			printf("Your Key = "); 
			scanf("%d", &key); // key 값 받기
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S': // command 값이 s 또는 S 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I': // command 값이 i 또는 I 일 경우
			inorderTraversal(head->left);
			break;
		case 'p': case 'P': // command 값이 p 또는 P 일 경우
			preorderTraversal(head->left);
			break;
		case 't': case 'T': // command 값이 t 또는 T 일 경우
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // 입력받은 command 값이 q 또는 Q 이 아닐 경우 동안 진행

	return 1;
}

// Binary Search Tree 초기화
int initializeBST(Node** h) {

	if(*h != NULL) // tree가 NULL이 아닐 경우
		freeBST(*h); // BST에 할당된 모든 메모리 해제

	// head node 생성
	*h = (Node*)malloc(sizeof(Node)); // *h에 'Node' 타입으로 주소 받기
	(*h)->left = NULL; // root
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

// 순환적 중위순회
void inorderTraversal(Node* ptr)
{
	if(ptr) { // 중위 트리 순회
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

// 순환적 전위순회
void preorderTraversal(Node* ptr)
{
	if(ptr) { // 전위 트리 순회
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

// 순환적 후위순회
void postorderTraversal(Node* ptr)
{
	if(ptr) { // 후위 트리 순회
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}

// tree에 노드 삽입
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // newNode에 'Node' 타입으로 주소 받기
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) { // NULL일 경우
		head->left = newNode;
		return 1;
	}

	Node* ptr = head->left; // 'head->left' is the root
	Node* parentNode = NULL;

	while(ptr != NULL) { // NULL이 아닐 경우

        // key에 대한 node가 있을 경우
		if(ptr->key == key) return 1; 

		// children nodes를 이동시켜 parentNode를 추적
		parentNode = ptr;

		// key comparison
		if(ptr->key < key) // 현재 key가 입력받은 key보다 클 경우
			ptr = ptr->right; // 오른쪽 트리에 삽입
		else
			ptr = ptr->left; // 왼쪽 트리에 삽입
	}

	// 새로운 node를 parentNode에 연결
	if(parentNode->key > key)
		parentNode->left = newNode; 
	else
		parentNode->right = newNode;
	return 1;
}

// leaf 노드 삭제
int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) { // head가 NULL일 경우
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { // head->left가 NULL일 경우
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* ptr = head->left; // 'head->left' is the root


	// children nodes를 이동시켜 parentNode를 추적
	Node* parentNode = head;

	while(ptr != NULL) { // ptr이 NULL이 아닐 경우

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {

				// root node일 경우
				if(parentNode == head)
					head->left = NULL;

				// left node 또는 right node일 경우
				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr); // 노드 해제
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		// parentNode 유지
		parentNode = ptr;

		// key comparison
		if(ptr->key < key) // 현재 key가 입력받은 key보다 클 경우
			ptr = ptr->right; // 오른쪽 트리에 삽입
		else
			ptr = ptr->left; // 왼쪽 트리에 삽입
	}

	printf("Cannot find the node for key [%d]\n ", key);
	return 1;
}

// BST 탐색
Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) // ptr이 NULL일 경우
		return NULL;

	if(ptr->key < key) // 현재 key가 입력받은 key보다 클 경우
		ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key) // 현재 key가 입력받은 key보다 작을 경우
		ptr = searchRecursive(ptr->left, key);

	return ptr; // 현재 key와 입력받은 key가 같을 경우

}

Node* searchIterative(Node* head, int key)
{
	// root node
	Node* ptr = head->left;

	while(ptr != NULL) // ptr이 NULL이 아닐 경우
	{
		if(ptr->key == key) // 현재 key와 입력받은 key가 같을 경우
			return ptr;

		if(ptr->key < key) ptr = ptr->right; // 현재 key가 입력받은 key보다 클 경우
		else
			ptr = ptr->left;
	}
	return NULL;
}

// 노드 해제
void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

// BST 메모리 해제
int freeBST(Node* head)
{
	if(head->left == head) 
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p); // node 해제
	free(head); // head 헤제
    
	return 1;
}
