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
Node* min(Node* node);
void delete(BST* tree, char key);
Node* _delete(Node* node, char key);
Node* deleteMin(Node* node);
Node* floorOf(BST* tree, char key);
Node* _floor(Node* node, char key);
Node* ceiling(BST* tree, char key);
Node* _ceiling(Node* node, char key);
Node* select(BST* tree, int c);
Node* _select(Node* node, int c);
void keysBetween(BST* tree, char lo, char hi);
void _keys(Node* node, char lo, char hi);
