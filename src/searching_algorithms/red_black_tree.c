#include <stdlib.h>
#include <stdio.h>
#include "./red_black_tree.h"

RB_Tree* createTree(){
  RB_Tree* tree = malloc(sizeof(RB_Tree));
  tree->root = NULL;
  return tree;
}

void put(RB_Tree* tree, char key){
  tree->root = _put(tree->root, key);
  tree->root->C = BLACK;
}

Node* _put(Node* node, char key){
  if(node == NULL){
    Node* new_node = malloc(sizeof(Node));
    new_node->key = key;
    new_node->C = RED;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
  }else{
    if(key > node->key){
      node->right = _put(node->right, key);
    }else if(key < node->key){
      node->left = _put(node->left, key);
    }else{
      // update value;
    }

    if( isRed(node->right) && !isRed(node->left) ) {
      node = rotateLeft(node);
    }
    if( isRed(node->left) && isRed(node->left->left) ) {
      node = rotateRight(node);
    }
    if( isRed(node->right) && isRed(node->left) ) {
      flipColor(node);
    }
    node->N = 1 + size(node->left) + size(node->right);
    return node;
  }
}

Node* rotateRight(Node* h){
  Node* x = h->left;
  h->left = x->right;
  x->right = h;
  x->C = h->C;
  h->C = RED;
  x->N = h->N;
  h->N = 1+size(h->left)+size(h->right);
  return x;
}

Node* rotateLeft(Node* h){
  Node* x = h->right;
  h->right = x->left;
  x->left = h;
  x->C = h->C;
  h->C = RED;
  x->N = h->N;
  h->N = 1+size(h->left)+size(h->right);
  return x;
}

bool isRed(Node* node){
  if(node==NULL){
    return false;
  }else{
    if(node->C == RED){
      return true;
    }else{
      return false;
    }
  }
}

void flipColor(Node* node){
  node->left->C = BLACK;
  node->right->C = BLACK;
  node->C = RED;
}

int size(Node* node){
  if(node==NULL){
    return 0;
  }else{
    return node->N;
  }
}

void printTree(RB_Tree* tree){
  Node* root = tree->root;
  printNode(root);
  printf("\n");
}

void printNode(Node* node){
  if(node == NULL)
    return;
  printNode(node->left);
  // printf("key is %c, size is %i\n", node->key, node->N);
  printf("key %c color (%i) \n", node->key, node->C);
  printNode(node->right);
}

int main(){
  char keys[] = {'S', 'E', 'A', 'R', 'C', 'H', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
  RB_Tree* tree = createTree();
  for(int i = 0; i< (int)(sizeof(keys)/sizeof(char)); i++)
    put(tree, keys[i]);

  printTree(tree);
  return 0;
}
