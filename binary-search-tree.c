/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	printf("[----- [Yongho Bae] [2020039008] -----]\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr) {//비어있는 tree인지 확인
		inorderTraversal(ptr->left); //왼쪽에 자식이 있으면 왼쪽 자식을 인자로 inorderTraversal 실행
		printf(" [%d] ", ptr->key); //현재 노드의 key 출력
		inorderTraversal(ptr->right); //오른쪽에 자식이 있으면 오른쪽 자식을 인자로 inorderTraversal 실행
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr) {//비어있는 tree인지 확인
		printf(" [%d] ", ptr->key); //현재 노드의 key 출력
		preorderTraversal(ptr->left); //왼쪽에 자식이 있으면 왼쪽 자식을 인자로 preorderTraversal 실행
		preorderTraversal(ptr->right); //오른쪽에 자식이 있으면 오른쪽 자식을 인자로 preorderTraversal 실행
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr) {
		postorderTraversal(ptr->left); //왼쪽에 자식이 있으면 왼쪽 자식을 인자로 postorderTraversal 실행
		postorderTraversal(ptr->right); //오른쪽에 자식이 있으면 오른쪽 자식을 인자로 postorderTraversal 실행
		printf(" [%d] ", ptr->key); //현재 노드의 key 출력
	}
}


int insert(Node* head, int key)
{
	/*삽입할 노드 생성 및 초기화*/
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;
	/*비어있을 경우*/
	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	/*비어있을 경우 종료*/
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left;


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;

	while(ptr != NULL) {

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {

				/* root node case */
				if(parentNode == head)
					head->left = NULL;

				/* left node case or right case*/
				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	/*비어있는 경우*/
	if(ptr == NULL)
		return NULL;
	/*ptr이 가리키는 key값보다 key이 클 경우 오른쪽 자식을 인자로 재귀, 작을 경우 왼쪽 자식을 인자로 재귀*/
	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	/* if ptr->key == key */
	return ptr;

}
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;
	/*ptr이 NULL이 아닐 때까지 반복*/
	while(ptr != NULL)
	{
		/*key와 현재 노드의 key가 같으면 종료*/
		if(ptr->key == key)
			return ptr;
		/*ptr이 가리키는 key값보다 key이 클 경우 ptr=오른쪽 자식, 작을 경우 ptr=왼쪽 자식*/
		if(ptr->key < key) ptr = ptr->right;
		else
			ptr = ptr->left;
	}
	/*비어있는 경우*/
	return NULL;
}

void freeNode(Node* ptr)
{
	if(ptr) {//ptr이 null이 아닐 경우
		freeNode(ptr->left); //왼쪽 자식노드 재귀
		freeNode(ptr->right); //오른쪽 자식노드 재귀
		free(ptr); //마지막 남은 노드 해제
	}
}

int freeBST(Node* head)
{
	/*비어있을 경우 head노드 메모리할당해제 후 종료*/
	if(head->left == head)
	{
		free(head);
		return 1;
	}
	/*모든 노드 메모리할당 해제*/
	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



