#include <stdio.h>
#include <stdlib.h>

#define size 100;

typedef struct node{
  int data;
  struct node *  left;
  struct node * right;
}node;

node * init(int data){

  node * root = malloc(sizeof(node));

  root->data = data;
  root->left = NULL;
  root->right = NULL;

  return root;

  
}

int main(){
	printf("hello world");
	return 0;
}
