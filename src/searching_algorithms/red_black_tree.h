
typedef enum { RED, BLACK } color;
typedef enum { false, true } bool;

typedef struct Node{
  char key;
  color C;
  int N;
  struct Node* left;
  struct Node* right;
}Node;

typedef struct{
  Node* root;
}RB_Tree;

RB_Tree* createTree();
void put(RB_Tree* tree, char key);
Node* _put(Node* node, char key);
Node* rotateLeft(Node* node);
Node* rotateRight(Node* node);
void flipColor(Node* node);
bool isRed(Node* node);
int size(Node* node);
void flipColor(Node* node);
void printTree(RB_Tree* tree);
void printNode(Node* node);

