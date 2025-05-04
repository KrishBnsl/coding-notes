#include <stdio.h>
#include <stdlib.h>

#define size 100;

typedef struct node{
int data;
struct node * left;
struct node * right;
}node;

node * init(int data){
node * root = malloc(sizeof(node));

root->data = data;
root->left = NULL;
root->right = NULL;

return root;
}

node * create_node(int data){
node * newnode = malloc(sizeof(node));
newnode ->data = data;

newnode->left = NULL;
newnode ->right = NULL;

return newnode;
}

node * add (node * root, node * newnode)
{
if(root == NULL){
return 0;
}

if(root->data > newnode->data){
root->right = add(root->right,newnode);
}

if(root->data<newnode->data){
root->right = add(root->left,newnode);
}

return root;

}

void preorder(node * root){
if(root == NULL){
return;
}

printf("%d",root->data);

preorder(root->left);
preorder(root->right);
}

int main(){
return 0;
}