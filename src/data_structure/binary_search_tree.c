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
	printf("key is %c, value is %i, size is %i\n", node->key, node->value, node->N);
	printNode(node->right);
}

void printTree(BST* tree){
	Node* root = tree->root;
	printNode(root);
}

// Node* deleteNode(Node* node, char key){
// 	if(node==NULL)
// 		return;
// 	if(node->key > key){
// 		node->left = deleteNode(node->left, key);
// 	}else if(node->key < key){
// 		node->right = deleteNode(node->right, key);
// 	}else{
// 		Node* x = node;
// 		Node* successor = min(node);
// 		if(node->left == NULL)
// 	}
// }

// void delete(BST* tree, char key){
// 	tree->root = deleteNode(tree->node, key);
// }

int main(){
	char keys[] = {'S', 'E', 'A', 'R', 'C', 'H', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
	BST* tree = createTree();
	for(int i = 0; i< (int)(sizeof(keys)/sizeof(char)); i++)
		put(tree, keys[i], i);
	printf("tree size is %i\n", tree->root->N);
	printTree(tree);
	return 1;
}