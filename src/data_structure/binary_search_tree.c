#include <stdlib.h>
#include <stdio.h>
#include "binary_search_tree.h"

BST* createTree(){
	BST* tree = malloc(sizeof(BST));
	tree->root = NULL;
	return tree;
}

int size(Node* node){
	if(node==NULL){
		return 0;
	}else{
		return node->N;
	}
}

void put(BST* tree, char key, int value){
	tree->root = putNode(tree->root, key, value);
}

Node* putNode(Node* node, char key, int value){
	if(node==NULL){
		Node* newNode = malloc(sizeof(Node));
		newNode->key = key;
		newNode->value = value;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->N = 1; // set self size to 1;
		return newNode;
	}
	if(node->key > key){
		node->left = putNode(node->left, key, value);
	}else if(node->key < key){
		node->right = putNode(node->right, key, value);
	}else{
		node->value = value;
	}
	node->N = size(node->left) + size(node->right) + 1;
	return node;
}

void printNode(Node* node){
	if(node == NULL)
		return;
	printNode(node->left);
	// printf("key is %c, value is %i, size is %i\n", node->key, node->value, node->N);
	printf("%c ->", node->key);
	printNode(node->right);
}

void printTree(BST* tree){
	Node* root = tree->root;
	printNode(root);
	printf("\n");
}

Node* min(Node* node){
	if(node->left == NULL){
		return node;
	}else{
		return min(node->left);
	}
}

Node* deleteMin(Node* node){
	if(node->left == NULL)
		return node->right;

	node->left = deleteMin(node->left);
	node->N = size(node->left) + size(node->right) + 1;
	return node;
}

void delete(BST* tree, char key){
	tree->root = _delete(tree->root, key);
}

Node* _delete(Node* node, char key){
	if(node == NULL)
		return NULL;
	if(node->key > key){
		node->left = _delete(node->left, key);
	}else if(node->key < key){
		node->right = _delete(node->right, key);
	}else{
		printf("find match key is %c\n", node->key);
		if(node->left == NULL)
			return node->right;
		if(node->right == NULL)
			return node->left;
		Node* t = node;
		node = min(t->right);
		printf("now target change to the min of right tree %c\n", node->key);
		node->right = deleteMin(t->right);
		node->left = t->left;
	}
	node->N = size(node->left) + size(node->right) + 1;
	return node;
}

Node* floorOf(BST* tree, char key){
	return _floor(tree->root, key);
}

Node* _floor(Node* x, char key){
	if((x == NULL) || (x->key == key))
		return x;
	if(x->key > key){
		return _floor(x->left, key);
	}
	Node* t = _floor(x->right, key);
	if(t == NULL){
		return x;
	}else{
		return t;
	}
}

Node* ceiling(BST* tree, char key){
	return _ceiling(tree->root, key);
}

Node* _ceiling(Node* t, char key){
	if((t==NULL) || (t->key == key))
		return t;
	if(t->key < key){
		return _ceiling(t->right, key);
	}
	Node* x = _ceiling(t->left, key);
	if(x==NULL){
		return t;
	}else{
		return x;
	}
}

Node* select(BST* tree, int r){
	return _select(tree->root, r);
}

Node* _select(Node* node, int r){

	if ((node == NULL) || (size(node->left) == r))
		return node;

	if(size(node->left) > r){
		return _select(node->left, r);
	}else{
		return _select(node->right, r - 1 - size(node->left));
	}

}

int main(){
	char keys[] = {'S', 'E', 'A', 'R', 'C', 'H', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
	BST* tree = createTree();
	for(int i = 0; i< (int)(sizeof(keys)/sizeof(char)); i++)
		put(tree, keys[i], i);

	// delete(tree, 'E');
	printTree(tree);

	// char k = 'B';
	// Node* t = floorOf(tree, k);
	// printf("floor for %c is %c\n", k, t->key);

	// char k2 = 'N';
	// Node* t2 = ceiling(tree, k2);
	// printf("ceiling for %c is %c\n", k2, t2->key);

	int r = -1;
	Node* t = select(tree, r);
	if(t == NULL){
		printf("can not find key for %i\n", r);
	}else{
		printf("rank for %i is %c\n", r, t->key);
	}

	return 1;
}
