typedef struct Node{
	int N;
	char key;
	int value;
	struct Node* left;
	struct Node* right;
}Node;

typedef struct{
	struct Node* root;
}BST;

BST* createTree();
void put(BST* tree, char key, int value);
int size(Node* node);
Node* putNode(Node* node, char key, int value);
void delete(BST* tree, char key);