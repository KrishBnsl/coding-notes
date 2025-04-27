<img src="https://r2cdn.perplexity.ai/pplx-full-logo-primary-dark%402x.png" class="logo" width="120"/>

# Data Structures and Algorithms: Comprehensive Notes

This document provides detailed notes covering Trees, Searching and Sorting algorithms, Graphs, and File Structures with implementations in C language.

## Trees: Fundamental Concepts and Implementations

### Basic Tree Terminology

A tree is a non-linear hierarchical data structure consisting of nodes connected by edges. It is a recursive data structure where each node can have zero or more child nodes.

**Core Tree Terminology**:

- **Node**: An individual element in a tree that stores actual data and links to other nodes
- **Root**: The first node in the tree (origin); every tree has exactly one root node
- **Edge**: The connecting link between any two nodes; with N nodes, there are maximum N-1 edges
- **Parent**: A node that has one or more child nodes
- **Child**: A node directly connected to another node when moving away from the root
- **Leaf Node**: A node with no children
- **Internal Node**: Any node that has at least one child (non-leaf node)
- **Height of Tree**: Maximum number of edges from root to a leaf node
- **Depth of Node**: Number of edges from root to that node
- **Siblings**: Nodes that share the same parent
- **Subtree**: A tree consisting of a node and all its descendants[^19]


### Binary Trees and Their Representation

A binary tree is a tree data structure where each node has at most two children, referred to as left child and right child.

**Binary Tree Representations**:

1. **Array Representation**:
    - Uses a one-dimensional array
    - For a node at index i:
        - Left child is at index 2i + 1
        - Right child is at index 2i + 2
        - Parent is at index (i-1)/2
    - For a binary tree of depth 'n', maximum array size needed is 2^(n+1) - 1[^2]
2. **Linked List Representation**:
    - Each node contains three fields:
        - Data field
        - Pointer to left child
        - Pointer to right child

**C Implementation of Binary Tree**:

```c
// Binary Tree Node Structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode-&gt;data = data;
    newNode-&gt;left = NULL;
    newNode-&gt;right = NULL;
    return newNode;
}

// Example usage
int main() {
    // Creating a simple binary tree
    struct Node* root = createNode(1);
    root-&gt;left = createNode(2);
    root-&gt;right = createNode(3);
    root-&gt;left-&gt;left = createNode(4);
    root-&gt;left-&gt;right = createNode(5);
    
    return 0;
}
```


### Binary Search Trees (BST)

A Binary Search Tree is a binary tree with the following properties:

- All nodes in the left subtree have values less than the node's value
- All nodes in the right subtree have values greater than the node's value
- Both left and right subtrees are also BSTs[^5][^6]

**BST Implementation in C**:

```c
// BST Node structure
struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
};

// Function to create a new BST node
struct BSTNode* createNode(int data) {
    struct BSTNode* newNode = (struct BSTNode*)malloc(sizeof(struct BSTNode));
    newNode-&gt;data = data;
    newNode-&gt;left = newNode-&gt;right = NULL;
    return newNode;
}
```


#### BST Operations

1. **Searching in BST**:
```c
// Function to search for a value in BST
struct BSTNode* search(struct BSTNode* root, int key) {
    // Base case: root is NULL or key is present at root
    if (root == NULL || root-&gt;data == key)
        return root;
    
    // Key is greater than root's data
    if (root-&gt;data &lt; key)
        return search(root-&gt;right, key);
    
    // Key is smaller than root's data
    return search(root-&gt;left, key);
}
```

2. **Insertion in BST**:
```c
// Function to insert a new value in BST
struct BSTNode* insert(struct BSTNode* root, int key) {
    // If the tree is empty, return a new node
    if (root == NULL)
        return createNode(key);
    
    // Otherwise, recur down the tree
    if (key &lt; root-&gt;data)
        root-&gt;left = insert(root-&gt;left, key);
    else if (key &gt; root-&gt;data)
        root-&gt;right = insert(root-&gt;right, key);
    
    // Return the unchanged node pointer
    return root;
}
```

3. **Deletion in BST**:
```c
// Function to find the minimum value node in a BST
struct BSTNode* minValueNode(struct BSTNode* node) {
    struct BSTNode* current = node;
    
    // Find the leftmost leaf
    while (current &amp;&amp; current-&gt;left != NULL)
        current = current-&gt;left;
    
    return current;
}

// Function to delete a node with given key
struct BSTNode* deleteNode(struct BSTNode* root, int key) {
    // Base case
    if (root == NULL) return root;
    
    // If key is smaller than root's key, it's in left subtree
    if (key &lt; root-&gt;data)
        root-&gt;left = deleteNode(root-&gt;left, key);
    
    // If key is greater than root's key, it's in right subtree
    else if (key &gt; root-&gt;data)
        root-&gt;right = deleteNode(root-&gt;right, key);
    
    // If key is same as root's key, this is the node to be deleted
    else {
        // Node with only one child or no child
        if (root-&gt;left == NULL) {
            struct BSTNode* temp = root-&gt;right;
            free(root);
            return temp;
        }
        else if (root-&gt;right == NULL) {
            struct BSTNode* temp = root-&gt;left;
            free(root);
            return temp;
        }
        
        // Node with two children: Get the inorder successor
        struct BSTNode* temp = minValueNode(root-&gt;right);
        
        // Copy the inorder successor's content to this node
        root-&gt;data = temp-&gt;data;
        
        // Delete the inorder successor
        root-&gt;right = deleteNode(root-&gt;right, temp-&gt;data);
    }
    return root;
}
```

4. **BST Traversal**:
```c
// Inorder traversal
void inorderTraversal(struct BSTNode* root) {
    if (root != NULL) {
        inorderTraversal(root-&gt;left);
        printf("%d ", root-&gt;data);
        inorderTraversal(root-&gt;right);
    }
}

// Preorder traversal
void preorderTraversal(struct BSTNode* root) {
    if (root != NULL) {
        printf("%d ", root-&gt;data);
        preorderTraversal(root-&gt;left);
        preorderTraversal(root-&gt;right);
    }
}

// Postorder traversal
void postorderTraversal(struct BSTNode* root) {
    if (root != NULL) {
        postorderTraversal(root-&gt;left);
        postorderTraversal(root-&gt;right);
        printf("%d ", root-&gt;data);
    }
}
```


### Applications of Binary Search Trees

Binary Search Trees are widely used in various applications:

1. **Indexing databases**: Efficient retrieval, insertion, and deletion operations
2. **Priority queues**: Implementation using a BST allows for efficient operations[^6]
3. **Sorting algorithms**: Used in tree sort
4. **Symbol tables in compilers**: Fast lookups for variable names
5. **Hierarchical data representation**: File systems, organizational charts

### Complete Binary Trees

A complete binary tree is a binary tree in which:

- All levels are completely filled except possibly the lowest one
- All nodes in the last level are as far left as possible[^7]

Key properties:

- In a complete binary tree with n nodes, height is ⌊log₂(n)⌋
- Efficient for array-based implementation (heap data structure)
- If a node is at index i, left child is at 2i+1, right child at 2i+2

**C Implementation to Check if a Binary Tree is Complete**:

```c
// Function to count nodes in a binary tree
int countNodes(struct Node* root) {
    if (root == NULL)
        return 0;
    return (1 + countNodes(root-&gt;left) + countNodes(root-&gt;right));
}

// Function to check if a binary tree is complete
int isComplete(struct Node* root, int index, int nodeCount) {
    // Empty tree is complete
    if (root == NULL)
        return 1;
    
    // If index assigned to current node is &gt;= number of nodes,
    // then tree is not complete
    if (index &gt;= nodeCount)
        return 0;
    
    // Recursively check for left and right subtrees
    return (isComplete(root-&gt;left, 2*index + 1, nodeCount) &amp;&amp;
            isComplete(root-&gt;right, 2*index + 2, nodeCount));
}

// Wrapper function
int isCompleteTree(struct Node* root) {
    int count = countNodes(root);
    int index = 0;
    return isComplete(root, index, count);
}
```


### Extended Binary Trees

An extended binary tree (also called a 2-tree or proper binary tree) is a tree where every node has either 0 or 2 children. It is formed by adding external nodes (null pointers or sentinel nodes) to make every node have exactly two children[^4][^8].

Properties:

- All internal nodes have exactly two children
- External nodes (also called virtual nodes) have no children
- Used for uniformity in algorithms and theoretical analysis

**C Implementation of Extended Binary Tree**:

```c
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;

struct Node {
    int data;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp-&gt;data = data;
    temp-&gt;left = temp-&gt;right = NULL;
    return temp;
}

// Function for inorder traversal with external nodes
void traverse(struct Node* root) {
    if (root != NULL) {
        traverse(root-&gt;left);
        printf("%d ", root-&gt;data);
        traverse(root-&gt;right);
    }
    else {
        // Create an external node with value -1
        root = newNode(-1);
        printf("%d ", root-&gt;data);
        free(root);
    }
}

int main() {
    struct Node* root = newNode(1);
    root-&gt;left = newNode(2);
    root-&gt;right = newNode(3);
    root-&gt;left-&gt;left = newNode(5);
    root-&gt;right-&gt;right = newNode(4);
    
    printf("Inorder traversal with external nodes: ");
    traverse(root);
    return 0;
}
```


### General Trees

A general tree is a tree data structure where a node can have any number of children. Unlike binary trees that are restricted to at most two children per node, general trees allow unlimited branching[^12].

**C Implementation of General Tree**:

```c
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;

typedef struct Node {
    int data;
    struct Node **children; // Array of pointers to children
    int childCount;         // Number of children
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode-&gt;data = data;
    newNode-&gt;children = NULL;
    newNode-&gt;childCount = 0;
    return newNode;
}

// Function to add a child to a node
void addChild(Node* parent, Node* child) {
    parent-&gt;childCount++;
    parent-&gt;children = (Node**)realloc(parent-&gt;children, 
                                      parent-&gt;childCount * sizeof(Node*));
    parent-&gt;children[parent-&gt;childCount - 1] = child;
}

// Function to print the tree (pre-order traversal)
void printTree(Node* root, int level) {
    if (root == NULL) return;
    
    // Print indentation
    for (int i = 0; i &lt; level; i++) 
        printf("  ");
    
    printf("%d\n", root-&gt;data);
    
    // Print all children
    for (int i = 0; i &lt; root-&gt;childCount; i++) {
        printTree(root-&gt;children[i], level + 1);
    }
}

int main() {
    Node* root = createNode(1);
    Node* child1 = createNode(2);
    Node* child2 = createNode(3);
    
    addChild(root, child1);
    addChild(root, child2);
    addChild(child1, createNode(4));
    addChild(child1, createNode(5));
    addChild(child2, createNode(6));
    
    printf("General Tree:\n");
    printTree(root, 0);
    
    return 0;
}
```


### AVL Trees

AVL trees are self-balancing binary search trees where the difference between heights of left and right subtrees cannot be more than one for all nodes. After any operation that might unbalance the tree, rebalancing is done to maintain this property[^9].

Key operations in AVL trees:

- Left rotation
- Right rotation
- Left-Right rotation
- Right-Left rotation

**C Implementation of AVL Tree**:

```c
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;

// An AVL tree node
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int height;
};

// Function to get the height of the tree
int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N-&gt;height;
}

// Function to get maximum of two integers
int max(int a, int b) {
    return (a &gt; b) ? a : b;
}

// Function to create a new AVL tree node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node-&gt;data = data;
    node-&gt;left = NULL;
    node-&gt;right = NULL;
    node-&gt;height = 1; // New node is initially at height 1
    return node;
}

// Function to right rotate subtree rooted with y
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y-&gt;left;
    struct Node *T2 = x-&gt;right;

    // Perform rotation
    x-&gt;right = y;
    y-&gt;left = T2;

    // Update heights
    y-&gt;height = max(height(y-&gt;left), height(y-&gt;right)) + 1;
    x-&gt;height = max(height(x-&gt;left), height(x-&gt;right)) + 1;

    // Return new root
    return x;
}

// Function to left rotate subtree rooted with x
struct Node *leftRotate(struct Node *x) {
    struct Node *y = x-&gt;right;
    struct Node *T2 = y-&gt;left;

    // Perform rotation
    y-&gt;left = x;
    x-&gt;right = T2;

    // Update heights
    x-&gt;height = max(height(x-&gt;left), height(x-&gt;right)) + 1;
    y-&gt;height = max(height(y-&gt;left), height(y-&gt;right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N-&gt;left) - height(N-&gt;right);
}

// Function to insert a node into AVL tree
struct Node* insert(struct Node* node, int data) {
    // 1. Perform normal BST insertion
    if (node == NULL)
        return newNode(data);

    if (data &lt; node-&gt;data)
        node-&gt;left = insert(node-&gt;left, data);
    else if (data &gt; node-&gt;data)
        node-&gt;right = insert(node-&gt;right, data);
    else // Equal keys not allowed
        return node;

    // 2. Update height of this ancestor node
    node-&gt;height = 1 + max(height(node-&gt;left), height(node-&gt;right));

    // 3. Get the balance factor
    int balance = getBalance(node);

    // If unbalanced, try 4 cases

    // Left Left Case
    if (balance &gt; 1 &amp;&amp; data &lt; node-&gt;left-&gt;data)
        return rightRotate(node);

    // Right Right Case
    if (balance &lt; -1 &amp;&amp; data &gt; node-&gt;right-&gt;data)
        return leftRotate(node);

    // Left Right Case
    if (balance &gt; 1 &amp;&amp; data &gt; node-&gt;left-&gt;data) {
        node-&gt;left = leftRotate(node-&gt;left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance &lt; -1 &amp;&amp; data &lt; node-&gt;right-&gt;data) {
        node-&gt;right = rightRotate(node-&gt;right);
        return leftRotate(node);
    }

    // return the unchanged node pointer
    return node;
}

// Function to print preorder traversal of the tree
void preOrder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root-&gt;data);
        preOrder(root-&gt;left);
        preOrder(root-&gt;right);
    }
}

int main() {
    struct Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Preorder traversal of the AVL tree: ");
    preOrder(root);

    return 0;
}
```


### Threaded Binary Trees

A threaded binary tree is a binary tree where null pointers are replaced by "threads" that point to the inorder predecessor or successor of the node. This optimization allows for efficient traversal without using a stack or recursion[^10].

Types of threaded binary trees:

1. **Single threaded**: Each node has a thread to either its predecessor or successor
2. **Double threaded**: Each node has threads to both its predecessor and successor

**C Implementation of a Single Threaded Binary Tree**:

```c
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;

typedef enum {
    thread, link
} boolean;

struct node {
    struct node *left_ptr;
    boolean left;
    int info;
    boolean right;
    struct node *right_ptr;
};

// Function to insert into a threaded binary tree
struct node *insert_threaded(struct node *root, int ikey) {
    struct node *curr, *temp, *ptr;
    int found = 0;

    ptr = (struct node *)malloc(sizeof(struct node));
    ptr-&gt;info = ikey;
    ptr-&gt;left = thread;
    ptr-&gt;right = thread;

    if (root == NULL) {
        root = ptr;
        ptr-&gt;left_ptr = NULL;
        ptr-&gt;right_ptr = NULL;
    } else {
        curr = root;
        while (!found) {
            if (ikey &lt; curr-&gt;info) {
                if (curr-&gt;left == link) {
                    curr = curr-&gt;left_ptr;
                } else {
                    found = 1;
                    ptr-&gt;left_ptr = curr-&gt;left_ptr;
                    ptr-&gt;right_ptr = curr;
                    curr-&gt;left = link;
                    curr-&gt;left_ptr = ptr;
                }
            } else {
                if (curr-&gt;right == link) {
                    curr = curr-&gt;right_ptr;
                } else {
                    found = 1;
                    ptr-&gt;right_ptr = curr-&gt;right_ptr;
                    ptr-&gt;left_ptr = curr;
                    curr-&gt;right = link;
                    curr-&gt;right_ptr = ptr;
                }
            }
        }
    }
    return root;
}

// Function for inorder traversal
void inorder_traversal(struct node *root) {
    struct node *ptr;
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    
    // Find the leftmost node
    ptr = root;
    while (ptr-&gt;left == link) {
        ptr = ptr-&gt;left_ptr;
    }
    
    // Traverse the tree
    while (ptr != NULL) {
        printf("%d ", ptr-&gt;info);
        if (ptr-&gt;right == thread) {
            ptr = ptr-&gt;right_ptr;
        } else {
            ptr = ptr-&gt;right_ptr;
            while (ptr-&gt;left == link) {
                ptr = ptr-&gt;left_ptr;
            }
        }
    }
    printf("\n");
}
```


### B-Trees

B-Tree is a self-balancing search tree optimized for systems that read and write large blocks of data. Unlike binary trees, a B-tree node can have more than two children. B-trees are commonly used in databases and file systems[^11].

Properties of a B-tree of order m:

- Every node has at most m children
- Every non-leaf node (except root) has at least ⌈m/2⌉ children
- The root has at least two children if it is not a leaf
- All leaf nodes are at the same level
- A non-leaf node with k children contains k-1 keys

**C Implementation of B-Tree**:

```c
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;

#define MAX 3 // Order of B-tree
#define MIN 2

struct BTreeNode {
    int val[MAX + 1], count;
    struct BTreeNode *link[MAX + 1];
};

struct BTreeNode *root;

// Create a node
struct BTreeNode *createNode(int val, struct BTreeNode *child) {
    struct BTreeNode *newNode;
    newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    newNode-&gt;val[^1] = val;
    newNode-&gt;count = 1;
    newNode-&gt;link[^0] = root;
    newNode-&gt;link[^1] = child;
    return newNode;
}

// Insert node
void insertNode(int val, int pos, struct BTreeNode *node,
                struct BTreeNode *child) {
    int j = node-&gt;count;
    while (j &gt; pos) {
        node-&gt;val[j + 1] = node-&gt;val[j];
        node-&gt;link[j + 1] = node-&gt;link[j];
        j--;
    }
    node-&gt;val[j + 1] = val;
    node-&gt;link[j + 1] = child;
    node-&gt;count++;
}

// Split node
void splitNode(int val, int *pval, int pos, struct BTreeNode *node,
             struct BTreeNode *child, struct BTreeNode **newNode) {
    int median, j;

    if (pos &gt; MIN)
        median = MIN + 1;
    else
        median = MIN;

    *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    j = median + 1;
    while (j &lt;= MAX) {
        (*newNode)-&gt;val[j - median] = node-&gt;val[j];
        (*newNode)-&gt;link[j - median] = node-&gt;link[j];
        j++;
    }
    node-&gt;count = median;
    (*newNode)-&gt;count = MAX - median;

    if (pos &lt;= MIN) {
        insertNode(val, pos, node, child);
    } else {
        insertNode(val, pos - median, *newNode, child);
    }
    *pval = node-&gt;val[node-&gt;count];
    (*newNode)-&gt;link[^0] = node-&gt;link[node-&gt;count];
    node-&gt;count--;
}

// Set the value
int setValue(int val, int *pval,
           struct BTreeNode *node, struct BTreeNode **child) {
    int pos;
    if (!node) {
        *pval = val;
        *child = NULL;
        return 1;
    }

    if (val &lt; node-&gt;val[^1]) {
        pos = 0;
    } else {
        for (pos = node-&gt;count;
             (val &lt; node-&gt;val[pos] &amp;&amp; pos &gt; 1); pos--)
            ;
        if (val == node-&gt;val[pos]) {
            printf("Duplicates not allowed\n");
            return 0;
        }
    }
    if (setValue(val, pval, node-&gt;link[pos], child)) {
        if (node-&gt;count &lt; MAX) {
            insertNode(*pval, pos, node, *child);
        } else {
            splitNode(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

// Insert the value
void insertion(int val) {
    int flag, i;
    struct BTreeNode *child;

    flag = setValue(val, &amp;i, root, &amp;child);
    if (flag)
        root = createNode(i, child);
}

// Search node
void search(int val, int *pos, struct BTreeNode *myNode) {
    if (!myNode) {
        return;
    }

    if (val &lt; myNode-&gt;val[^1]) {
        *pos = 0;
    } else {
        for (*pos = myNode-&gt;count;
            (val &lt; myNode-&gt;val[*pos] &amp;&amp; *pos &gt; 1); (*pos)--)
            ;
        if (val == myNode-&gt;val[*pos]) {
            printf("Found\n");
            return;
        }
    }
    search(val, pos, myNode-&gt;link[*pos]);
    return;
}

// Traverse tree
void traversal(struct BTreeNode *myNode) {
    int i;
    if (myNode) {
        for (i = 0; i &lt; myNode-&gt;count; i++) {
            traversal(myNode-&gt;link[i]);
            printf("%d ", myNode-&gt;val[i + 1]);
        }
        traversal(myNode-&gt;link[i]);
    }
}

int main() {
    int val, ch;
    
    root = NULL;
    
    // Sample operations
    insertion(8);
    insertion(9);
    insertion(10);
    insertion(11);
    insertion(15);
    insertion(16);
    insertion(17);
    insertion(18);
    insertion(20);
    insertion(23);
    
    printf("Traversal of the B-tree: ");
    traversal(root);
    
    printf("\nEnter a value to search: ");
    scanf("%d", &amp;val);
    int pos;
    search(val, &amp;pos, root);
    
    return 0;
}
```


## Searching and Sorting

### Linear Search

Linear search is the simplest searching algorithm that checks each element sequentially until the target element is found or the end of the array is reached.

**C Implementation of Linear Search**:

```c
#include &lt;stdio.h&gt;

// Linear search function
int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i &lt; n; i++) {
        if (arr[i] == key)
            return i; // Return index if key found
    }
    return -1; // Return -1 if key not found
}

int main() {
    int arr[] = {10, 20, 80, 30, 60, 50, 110, 100, 130, 170};
    int n = sizeof(arr) / sizeof(arr[^0]);
    int key = 110;
    
    int result = linearSearch(arr, n, key);
    
    if (result == -1)
        printf("Element %d not found in the array\n", key);
    else
        printf("Element %d found at index %d\n", key, result);
    
    return 0;
}
```

Time Complexity: O(n)

### Binary Search

Binary search is an efficient algorithm that works on sorted arrays by repeatedly dividing the search interval in half.

**C Implementation of Binary Search**:

```c
#include &lt;stdio.h&gt;

// Iterative binary search
int binarySearch(int arr[], int left, int right, int key) {
    while (left &lt;= right) {
        int mid = left + (right - left) / 2;
        
        // Check if key is present at mid
        if (arr[mid] == key)
            return mid;
        
        // If key is greater, ignore left half
        if (arr[mid] &lt; key)
            left = mid + 1;
        // If key is smaller, ignore right half
        else
            right = mid - 1;
    }
    
    // Key not found
    return -1;
}

// Recursive binary search
int recursiveBinarySearch(int arr[], int left, int right, int key) {
    if (right &gt;= left) {
        int mid = left + (right - left) / 2;
        
        // If the element is present at the middle
        if (arr[mid] == key)
            return mid;
        
        // If element is smaller than mid, search in left subarray
        if (arr[mid] &gt; key)
            return recursiveBinarySearch(arr, left, mid - 1, key);
        
        // Else search in right subarray
        return recursiveBinarySearch(arr, mid + 1, right, key);
    }
    
    // Element is not present in array
    return -1;
}

int main() {
    int arr[] = {10, 20, 30, 50, 60, 80, 110, 130, 140, 170};
    int n = sizeof(arr) / sizeof(arr[^0]);
    int key = 110;
    
    // Using iterative binary search
    int result = binarySearch(arr, 0, n - 1, key);
    
    if (result == -1)
        printf("Element %d not found in the array\n", key);
    else
        printf("Element %d found at index %d\n", key, result);
    
    return 0;
}
```

Time Complexity: O(log n)

### Interpolation Search

Interpolation search is an improved variant of binary search that works better for uniformly distributed data. It estimates the position of the target value by using the formula:

pos = low + ((key - arr[low]) * (high - low)) / (arr[high] - arr[low])

**C Implementation of Interpolation Search**:

```c
#include &lt;stdio.h&gt;

int interpolationSearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    
    while (low &lt;= high &amp;&amp; key &gt;= arr[low] &amp;&amp; key &lt;= arr[high]) {
        if (low == high) {
            if (arr[low] == key) return low;
            return -1;
        }
        
        // Probing the position with uniform distribution
        int pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (key - arr[low]));
        
        // Target found
        if (arr[pos] == key)
            return pos;
        
        // If key is larger, key is in upper part
        if (arr[pos] &lt; key)
            low = pos + 1;
        // If key is smaller, key is in lower part
        else
            high = pos - 1;
    }
    return -1;
}

int main() {
    int arr[] = {10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47};
    int n = sizeof(arr) / sizeof(arr[^0]);
    int key = 18;
    
    int index = interpolationSearch(arr, n, key);
    
    if (index != -1)
        printf("Element %d found at index %d\n", key, index);
    else
        printf("Element %d not found in the array\n", key);
    
    return 0;
}
```

Time Complexity: O(log log n) for uniformly distributed data, O(n) in worst case[^14]

### Insertion Sort

Insertion sort is a simple sorting algorithm that builds the final sorted array one item at a time. It's efficient for small data sets and mostly sorted arrays.

**C Implementation of Insertion Sort**:

```c
#include &lt;stdio.h&gt;

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i &lt; n; i++) {
        key = arr[i];
        j = i - 1;
        
        // Move elements that are greater than key
        // to one position ahead of their current position
        while (j &gt;= 0 &amp;&amp; arr[j] &gt; key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i &lt; n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[^0]);
    
    printf("Original array: ");
    printArray(arr, n);
    
    insertionSort(arr, n);
    
    printf("Sorted array: ");
    printArray(arr, n);
    
    return 0;
}
```

Time Complexity: O(n²) in worst and average cases, O(n) in best case

### Quick Sort

Quick sort is a highly efficient sorting algorithm based on the divide-and-conquer paradigm. It selects a 'pivot' element and partitions the array around it.

**C Implementation of Quick Sort**:

```c
#include &lt;stdio.h&gt;

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choosing the last element as pivot
    int i = (low - 1); // Index of smaller element
    
    for (int j = low; j &lt;= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] &lt;= pivot) {
            i++; // Increment index of smaller element
            swap(&amp;arr[i], &amp;arr[j]);
        }
    }
    swap(&amp;arr[i + 1], &amp;arr[high]);
    return (i + 1);
}

// Quick sort function
void quickSort(int arr[], int low, int high) {
    if (low &lt; high) {
        // pi is partitioning index
        int pi = partition(arr, low, high);
        
        // Separately sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i &lt; size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[^0]);
    
    printf("Original array: ");
    printArray(arr, n);
    
    quickSort(arr, 0, n - 1);
    
    printf("Sorted array: ");
    printArray(arr, n);
    
    return 0;
}
```

Time Complexity: O(n²) in worst case, O(n log n) on average

### Merge Sort

Merge sort is a divide-and-conquer algorithm that divides the input array into two halves, sorts them separately, and then merges them.

**C Implementation of Merge Sort**:

```c
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;

// Merge two subarrays
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    // Create temporary arrays
    int L[n1], R[n2];
    
    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i &lt; n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j &lt; n2; j++)
        R[j] = arr[m + 1 + j];
    
    // Merge the temporary arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i &lt; n1 &amp;&amp; j &lt; n2) {
        if (L[i] &lt;= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copy the remaining elements of L[]
    while (i &lt; n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy the remaining elements of R[]
    while (j &lt; n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Main merge sort function
void mergeSort(int arr[], int l, int r) {
    if (l &lt; r) {
        // Find the middle point
        int m = l + (r - l) / 2;
        
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        
        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i &lt; size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[^0]);
    
    printf("Original array: ");
    printArray(arr, n);
    
    mergeSort(arr, 0, n - 1);
    
    printf("Sorted array: ");
    printArray(arr, n);
    
    return 0;
}
```

Time Complexity: O(n log n) in all cases

### Heap Sort

Heap sort is a comparison-based sorting algorithm using a binary heap data structure. It divides the input into a sorted and unsorted region and iteratively shrinks the unsorted region by extracting the largest element.

**C Implementation of Heap Sort**:

```c
#include &lt;stdio.h&gt;

// To heapify a subtree rooted with node i
void heapify(int arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // Left child
    int right = 2 * i + 2; // Right child
    
    // If left child is larger than root
    if (left &lt; n &amp;&amp; arr[left] &gt; arr[largest])
        largest = left;
    
    // If right child is larger than largest so far
    if (right &lt; n &amp;&amp; arr[right] &gt; arr[largest])
        largest = right;
    
    // If largest is not root
    if (largest != i) {
        int swap = arr[i];
        arr[i] = arr[largest];
        arr[largest] = swap;
        
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main heap sort function
void heapSort(int arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i &gt;= 0; i--)
        heapify(arr, n, i);
    
    // Extract elements from heap one by one
    for (int i = n - 1; i &gt; 0; i--) {
        // Move current root to end
        int temp = arr[^0];
        arr[^0] = arr[i];
        arr[i] = temp;
        
        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i &lt; n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[^0]);
    
    printf("Original array: ");
    printArray(arr, n);
    
    heapSort(arr, n);
    
    printf("Sorted array: ");
    printArray(arr, n);
    
    return 0;
}
```

Time Complexity: O(n log n) in all cases

### Sorting on Different Keys

When dealing with structured data (like records), we often need to sort based on specific fields (keys). We can modify the existing algorithms to compare based on the selected key.

**C Implementation of Sorting Records by Multiple Keys**:

```c
#include &lt;stdio.h&gt;
#include &lt;string.h&gt;

struct Student {
    int id;
    char name[^50];
    float gpa;
};

// Function to sort students by ID
void sortById(struct Student arr[], int n) {
    struct Student temp;
    for (int i = 0; i &lt; n - 1; i++) {
        for (int j = 0; j &lt; n - i - 1; j++) {
            if (arr[j].id &gt; arr[j + 1].id) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to sort students by Name
void sortByName(struct Student arr[], int n) {
    struct Student temp;
    for (int i = 0; i &lt; n - 1; i++) {
        for (int j = 0; j &lt; n - i - 1; j++) {
            if (strcmp(arr[j].name, arr[j + 1].name) &gt; 0) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to sort students by GPA (descending)
void sortByGPA(struct Student arr[], int n) {
    struct Student temp;
    for (int i = 0; i &lt; n - 1; i++) {
        for (int j = 0; j &lt; n - i - 1; j++) {
            if (arr[j].gpa &lt; arr[j + 1].gpa) { // Note: descending order
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to print students
void printStudents(struct Student arr[], int n) {
    printf("ID\tName\t\tGPA\n");
    printf("-----------------------------------\n");
    for (int i = 0; i &lt; n; i++) {
        printf("%d\t%s\t\t%.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }
    printf("\n");
}

int main() {
    struct Student students[] = {
        {101, "Alice", 3.8},
        {103, "Bob", 3.6},
        {102, "Charlie", 3.9},
        {105, "David", 3.5},
        {104, "Eve", 4.0}
    };
    int n = sizeof(students) / sizeof(students[^0]);
    
    printf("Original Student Records:\n");
    printStudents(students, n);
    
    // Sort by ID
    sortById(students, n);
    printf("Sorted by ID:\n");
    printStudents(students, n);
    
    // Sort by Name
    sortByName(students, n);
    printf("Sorted by Name:\n");
    printStudents(students, n);
    
    // Sort by GPA (descending)
    sortByGPA(students, n);
    printf("Sorted by GPA (descending):\n");
    printStudents(students, n);
    
    return 0;
}
```


### External Sorting

External sorting is used when data doesn't fit into memory. It involves dividing data into manageable chunks, sorting them individually in memory, and then merging the sorted chunks.

**C Implementation of External Merge Sort (Simplified)**:

```c
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;limits.h&gt;

#define RUN_SIZE 10000
#define NUM_RUNS 10
#define TOTAL_SIZE (RUN_SIZE * NUM_RUNS)

// Merge function
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    int L[n1], R[n2];
    
    for (i = 0; i &lt; n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j &lt; n2; j++)
        R[j] = arr[m + 1 + j];
    
    i = 0;
    j = 0;
    k = l;
    while (i &lt; n1 &amp;&amp; j &lt; n2) {
        if (L[i] &lt;= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i &lt; n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j &lt; n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Insertion sort for small arrays
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i &lt; n; i++) {
        key = arr[i];
        j = i - 1;
        
        while (j &gt;= 0 &amp;&amp; arr[j] &gt; key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Main function for external sort simulation
void externalSort() {
    FILE *input, *output, *temp[NUM_RUNS];
    char tempFileName[^20];
    int i, j, chunk[RUN_SIZE], minVal, minIndex, count[NUM_RUNS];
    int next[NUM_RUNS], vals[NUM_RUNS];
    
    // Create input file with random numbers
    input = fopen("input.txt", "w");
    for (i = 0; i &lt; TOTAL_SIZE; i++) {
        fprintf(input, "%d\n", rand() % 100000);
    }
    fclose(input);
    
    // Phase 1: Sort individual chunks and store in temporary files
    input = fopen("input.txt", "r");
    for (i = 0; i &lt; NUM_RUNS; i++) {
        // Read chunk
        for (j = 0; j &lt; RUN_SIZE; j++) {
            if (fscanf(input, "%d", &amp;chunk[j]) != 1) {
                break;
            }
        }
        
        // Sort chunk
        insertionSort(chunk, j);
        
        // Write sorted chunk to temporary file
        sprintf(tempFileName, "temp%d.txt", i);
        temp[i] = fopen(tempFileName, "w");
        for (int k = 0; k &lt; j; k++) {
            fprintf(temp[i], "%d\n", chunk[k]);
        }
        fclose(temp[i]);
    }
    fclose(input);
    
    // Phase 2: Merge chunks
    output = fopen("output.txt", "w");
    
    // Open all temporary files for reading
    for (i = 0; i &lt; NUM_RUNS; i++) {
        sprintf(tempFileName, "temp%d.txt", i);
        temp[i] = fopen(tempFileName, "r");
        count[i] = 0;
        next[i] = 1; // 1 means there are more elements
        
        // Read first element from each file
        if (fscanf(temp[i], "%d", &amp;vals[i]) != 1) {
            next[i] = 0; // No elements in this file
        }
    }
    
    // Merge until all files are empty
    while (1) {
        minVal = INT_MAX;
        minIndex = -1;
        
        // Find minimum value across all files
        for (i = 0; i &lt; NUM_RUNS; i++) {
            if (next[i] &amp;&amp; vals[i] &lt; minVal) {
                minVal = vals[i];
                minIndex = i;
            }
        }
        
        if (minIndex == -1) break; // All files are empty
        
        // Write minimum value to output
        fprintf(output, "%d\n", minVal);
        
        // Read next value from the file that had the minimum
        if (fscanf(temp[minIndex], "%d", &amp;vals[minIndex]) != 1) {
            next[minIndex] = 0; // No more elements in this file
        }
    }
    
    // Close all files
    fclose(output);
    for (i = 0; i &lt; NUM_RUNS; i++) {
        fclose(temp[i]);
        sprintf(tempFileName, "temp%d.txt", i);
        remove(tempFileName); // Clean up temporary files
    }
    
    printf("External sort completed. Sorted data in 'output.txt'\n");
}

int main() {
    externalSort();
    return 0;
}
```

Time Complexity: O(n log n) where n is the total number of records

## Graphs

### Terminology and Representations

A graph is a non-linear data structure consisting of vertices (or nodes) connected by edges. Graphs are used to represent networks of communication, data organization, computational devices, flow of computation, etc.

**Basic Graph Terminology**:

- **Vertex**: Basic element of a graph, also called a node
- **Edge**: Link between two vertices
- **Adjacent**: Two vertices are adjacent if there is an edge connecting them
- **Path**: Sequence of vertices where each adjacent pair is connected by an edge
- **Directed Graph**: Edges have directions
- **Undirected Graph**: Edges have no directions
- **Weighted Graph**: Edges have weights/values assigned to them
- **Cycle**: Path that starts and ends at the same vertex
- **Connected Graph**: There is a path between every pair of vertices
- **Complete Graph**: There is an edge between every pair of vertices
- **Tree**: Connected graph with no cycles
- **Forest**: Disjoint set of trees
- **Spanning Tree**: Subset of graph containing all vertices with minimum possible edges
- **Bipartite Graph**: Vertices can be divided into two disjoint sets such that no two vertices within the same set are adjacent

**Graph Representations**:

1. **Adjacency Matrix**:
    - 2D array of size V×V where V is the number of vertices
    - Matrix[i][j] = 1 if there is an edge from vertex i to vertex j, otherwise 0
    - For weighted graphs, Matrix[i][j] = weight of the edge from i to j
2. **Adjacency List**:
    - Array of linked lists
    - Size of the array is equal to number of vertices
    - Array[i] represents the list of vertices adjacent to the ith vertex

**C Implementation of Graph Representation**:

```c
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;

// Adjacency Matrix Representation
struct GraphMatrix {
    int V;           // Number of vertices
    int E;           // Number of edges
    int **adjMatrix; // Adjacency matrix
};

// Function to create a graph with adjacency matrix
struct GraphMatrix* createGraphMatrix(int V) {
    struct GraphMatrix* graph = (struct GraphMatrix*)malloc(sizeof(struct GraphMatrix));
    graph-&gt;V = V;
    graph-&gt;E = 0;
    
    // Allocate memory for adjacency matrix
    graph-&gt;adjMatrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i &lt; V; i++) {
        graph-&gt;adjMatrix[i] = (int*)calloc(V, sizeof(int));
    }
    
    return graph;
}

// Function to add an edge to an undirected graph with adjacency matrix
void addEdgeMatrix(struct GraphMatrix* graph, int src, int dest) {
    // Add edge from src to dest
    graph-&gt;adjMatrix[src][dest] = 1;
    
    // Add edge from dest to src for undirected graph
    graph-&gt;adjMatrix[dest][src] = 1;
    
    graph-&gt;E++;
}

// Function to print adjacency matrix
void printGraphMatrix(struct GraphMatrix* graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i &lt; graph-&gt;V; i++) {
        for (int j = 0; j &lt; graph-&gt;V; j++) {
            printf("%d ", graph-&gt;adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Adjacency List Representation
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode* head;
};

struct GraphList {
    int V;                  // Number of vertices
    int E;                  // Number of edges
    struct AdjList* array;  // Array of adjacency lists
};

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode-&gt;dest = dest;
    newNode-&gt;next = NULL;
    return newNode;
}

// Function to create a graph with adjacency list
struct GraphList* createGraphList(int V) {
    struct GraphList* graph = (struct GraphList*)malloc(sizeof(struct GraphList));
    graph-&gt;V = V;
    graph-&gt;E = 0;
    
    // Create an array of adjacency lists
    graph-&gt;array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    
    // Initialize each adjacency list as empty
    for (int i = 0; i &lt; V; i++) {
        graph-&gt;array[i].head = NULL;
    }
    
    return graph;
}

// Function to add an edge to an undirected graph with adjacency list
void addEdgeList(struct GraphList* graph, int src, int dest) {
    // Add an edge from src to dest
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode-&gt;next = graph-&gt;array[src].head;
    graph-&gt;array[src].head = newNode;
    
    // Add an edge from dest to src for undirected graph
    newNode = newAdjListNode(src);
    newNode-&gt;next = graph-&gt;array[dest].head;
    graph-&gt;array[dest].head = newNode;
    
    graph-&gt;E++;
}

// Function to print adjacency list
void printGraphList(struct GraphList* graph) {
    printf("Adjacency List:\n");
    for (int v = 0; v &lt; graph-&gt;V; v++) {
        struct AdjListNode* temp = graph-&gt;array[v].head;
        printf("Vertex %d: ", v);
        while (temp) {
            printf("%d -&gt; ", temp-&gt;dest);
            temp = temp-&gt;next;
        }
        printf("NULL\n");
    }
}

int main() {
    // Example using adjacency matrix
    int V = 5;
    struct GraphMatrix* graphMatrix = createGraphMatrix(V);
    addEdgeMatrix(graphMatrix, 0, 1);
    addEdgeMatrix(graphMatrix, 0, 4);
    addEdgeMatrix(graphMatrix, 1, 2);
    addEdgeMatrix(graphMatrix, 1, 3);
    addEdgeMatrix(graphMatrix, 1, 4);
    addEdgeMatrix(graphMatrix, 2, 3);
    addEdgeMatrix(graphMatrix, 3, 4);
    
    printGraphMatrix(graphMatrix);
    
    // Example using adjacency list
    struct GraphList* graphList = createGraphList(V);
    addEdgeList(graphList, 0, 1);
    addEdgeList(graphList, 0, 4);
    addEdgeList(graphList, 1, 2);
    addEdgeList(graphList, 1, 3);
    addEdgeList(graphList, 1, 4);
    addEdgeList(graphList, 2, 3);
    addEdgeList(graphList, 3, 4);
    
    printGraphList(graphList);
    
    return 0;
}
```


### Graph Traversal

1. **Breadth-First Search (BFS)**:
    - Starting from a selected node, visit all neighbors at the current depth level before moving to nodes at the next depth level
    - Uses a queue data structure
2. **Depth-First Search (DFS)**:
    - Starting from a selected node, explore as far as possible along each branch before backtracking
    - Uses a stack data structure or recursion

**C Implementation of Graph Traversal**:

```c
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;

// Queue for BFS
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

// Create a queue
struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue-&gt;capacity = capacity;
    queue-&gt;front = queue-&gt;size = 0;
    queue-&gt;rear = capacity - 1;
    queue-&gt;array = (int*)malloc(queue-&gt;capacity * sizeof(int));
    return queue;
}

// Check if queue is full
int isFull(struct Queue* queue) {
    return (queue-&gt;size == queue-&gt;capacity);
}

// Check if queue is empty
int isEmpty(struct Queue* queue) {
    return (queue-&gt;size == 0);
}

// Add an item to queue
void enqueue(struct Queue* queue, int item) {
    if (isFull(queue)) return;
    queue-&gt;rear = (queue-&gt;rear + 1) % queue-&gt;capacity;
    queue-&gt;array[queue-&gt;rear] = item;
    queue-&gt;size = queue-&gt;size + 1;
}

// Remove an item from queue
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) return -1;
    int item = queue-&gt;array[queue-&gt;front];
    queue-&gt;front = (queue-&gt;front + 1) % queue-&gt;capacity;
    queue-&gt;size = queue-&gt;size - 1;
    return item;
}

// Graph structure
struct Graph {
    int V;
    int** adjMatrix;
};

// Create a graph
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph-&gt;V = V;
    
    graph-&gt;adjMatrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i &lt; V; i++) {
        graph-&gt;adjMatrix[i] = (int*)calloc(V, sizeof(int));
    }
    
    return graph;
}

// Add edge to graph
void addEdge(struct Graph* graph, int src, int dest) {
    graph-&gt;adjMatrix[src][dest] = 1;
    graph-&gt;adjMatrix[dest][src] = 1; // For undirected graph
}

// BFS traversal
void BFS(struct Graph* graph, int startVertex) {
    // Mark all vertices as not visited
    int* visited = (int*)calloc(graph-&gt;V, sizeof(int));
    
    // Create a queue for BFS
    struct Queue* queue = createQueue(graph-&gt;V);
    
    // Mark the current node as visited and enqueue it
    visited[startVertex] = 1;
    enqueue(queue, startVertex);
    
    printf("BFS traversal starting from vertex %d: ", startVertex);
    
    while (!isEmpty(queue)) {
        // Dequeue a vertex and print it
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);
        
        // Get all adjacent vertices of the dequeued vertex
        // If an adjacent has not been visited, mark it visited and enqueue it
        for (int i = 0; i &lt; graph-&gt;V; i++) {
            if (graph-&gt;adjMatrix[currentVertex][i] &amp;&amp; !visited[i]) {
                visited[i] = 1;
                enqueue(queue, i);
            }
        }
    }
    printf("\n");
    
    free(visited);
    free(queue-&gt;array);
    free(queue);
}

// DFS traversal (recursive)
void DFSUtil(struct Graph* graph, int vertex, int* visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);
    
    for (int i = 0; i &lt; graph-&gt;V; i++) {
        if (graph-&gt;adjMatrix[vertex][i] &amp;&amp; !visited[i]) {
            DFSUtil(graph, i, visited);
        }
    }
}

// DFS traversal
void DFS(struct Graph* graph, int startVertex) {
    // Mark all vertices as not visited
    int* visited = (int*)calloc(graph-&gt;V, sizeof(int));
    
    printf("DFS traversal starting from vertex %d: ", startVertex);
    DFSUtil(graph, startVertex, visited);
    printf("\n");
    
    free(visited);
}

int main() {
    int V = 5;
    struct Graph* graph = createGraph(V);
    
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    
    BFS(graph, 0);
    DFS(graph, 0);
    
    return 0;
}
```


### Spanning Trees and Minimum Spanning Trees

A spanning tree is a subset of a graph where all vertices are included with the minimum possible number of edges. A minimum spanning tree (MST) is a spanning tree with minimum total edge weight.

Two common algorithms for finding MST:

1. **Kruskal's Algorithm**: Sort edges by weight and add them if they don't create a cycle
2. **Prim's Algorithm**: Start from any vertex and keep adding the minimum weight edge that connects a visited vertex to an unvisited one

**C Implementation of Kruskal's Algorithm**:

```c
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int V, E;
    struct Edge* edge;
};

// Structure for subset for union-find
struct Subset {
    int parent;
    int rank;
};

// Create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph-&gt;V = V;
    graph-&gt;E = E;
    graph-&gt;edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// Find set of an element i (using path compression)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union of two sets (using rank)
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    
    // Attach smaller rank tree under root of high rank tree
    if (subsets[xroot].rank &lt; subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank &gt; subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        // If ranks are same, make one as root and increment its rank
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare function for qsort
int compareEdges(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1-&gt;weight &gt; b1-&gt;weight;
}

// Kruskal's algorithm to find MST
void KruskalMST(struct Graph* graph) {
    int V = graph-&gt;V;
    struct Edge result[V]; // Store resultant MST
    int e = 0; // Index for result[]
    int i = 0; // Index for sorted edges
    
    // Step 1: Sort all edges in non-decreasing order of weight
    qsort(graph-&gt;edge, graph-&gt;E, sizeof(graph-&gt;edge[^0]), compareEdges);
    
    // Allocate memory for subsets
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
    
    // Create V subsets with single elements
    for (int v = 0; v &lt; V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    
    // Number of edges to be taken is V-1
    while (e &lt; V - 1 &amp;&amp; i &lt; graph-&gt;E) {
        // Step 2: Pick the smallest edge. Increment index for next iteration
        struct Edge next_edge = graph-&gt;edge[i++];
        
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
        
        // If including this edge doesn't cause cycle, include it in result
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }
    
    // Print the constructed MST
    printf("Edges in the Minimum Spanning Tree:\n");
    int minimumCost = 0;
    for (i = 0; i &lt; e; i++) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("Total cost of MST: %d\n", minimumCost);
    
    free(subsets);
}

int main() {
    int V = 4; // Number of vertices
    int E = 5; // Number of edges
    struct Graph* graph = createGraph(V, E);
    
    // Add edge 0-1
    graph-&gt;edge[^0].src = 0;
    graph-&gt;edge[^0].dest = 1;
    graph-&gt;edge[^0].weight = 10;
    
    // Add edge 0-2
    graph-&gt;edge[^1].src = 0;
    graph-&gt;edge[^1].dest = 2;
    graph-&gt;edge[^1].weight = 6;
    
    // Add edge 0-3
    graph-&gt;edge[^2].src = 0;
    graph-&gt;edge[^2].dest = 3;
    graph-&gt;edge[^2].weight = 5;
    
    // Add edge 1-3
    graph-&gt;edge[^3].src = 1;
    graph-&gt;edge[^3].dest = 3;
    graph-&gt;edge[^3].weight = 15;
    
    // Add edge 2-3
    graph-&gt;edge[^4].src = 2;
    graph-&gt;edge[^4].dest = 3;
    graph-&gt;edge[^4].weight = 4;
    
    KruskalMST(graph);
    
    return 0;
}
```


### Shortest Path Algorithms

1. **Dijkstra's Algorithm**: Used to find the shortest path from a source vertex to all other vertices in a weighted graph with non-negative edge weights
2. **Bellman-Ford Algorithm**: Used to find the shortest path from a source vertex to all other vertices in a weighted graph, even with negative edge weights

**C Implementation of Dijkstra's Algorithm**:

```c
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;limits.h&gt;

// Number of vertices in the graph
#define V 9

// Function to find the vertex with minimum distance value
int minDistance(int dist[], int sptSet[]) {
    // Initialize min value
    int min = INT_MAX, min_index;
    
    for (int v = 0; v &lt; V; v++) {
        if (sptSet[v] == 0 &amp;&amp; dist[v] &lt;= min) {
            min = dist[v];
            min_index = v;
        }
    }
    
    return min_index;
}

// Function to print the constructed distance array
void printSolution(int dist[]) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i &lt; V; i++) {
        printf("%d \t %d\n", i, dist[i]);
    }
}

// Dijkstra's algorithm for a graph represented using adjacency matrix
void dijkstra(int graph[V][V], int src) {
    int dist[V];     // The output array. dist[i] will hold the shortest
                     // distance from src to i
    
    int sptSet[V];   // sptSet[i] will be true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized
    
    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i &lt; V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }
    
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
    
    // Find shortest path for all vertices
    for (int count = 0; count &lt; V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);
        
        // Mark the picked vertex as processed
        sptSet[u] = 1;
        
        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v &lt; V; v++) {
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] &amp;&amp; graph[u][v] &amp;&amp; dist[u] != INT_MAX
                &amp;&amp; dist[u] + graph[u][v] &lt; dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    
    // Print the constructed distance array
    printSolution(dist);
}

int main() {
    // Example graph (adjacency matrix)
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };
    
    dijkstra(graph, 0);
    
    return 0;
}
```


### Topological Sort

Topological sorting is a linear ordering of vertices such that for every directed edge (u,v), vertex u comes before vertex v in the ordering. Topological sort is only possible for Directed Acyclic Graphs (DAGs).

**C Implementation of Topological Sort**:

```c
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;

struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode *head;
};

struct Graph {
    int V;
    struct AdjList* array;
};

// Create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode-&gt;dest = dest;
    newNode-&gt;next = NULL;
    return newNode;
}

// Create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph-&gt;V = V;
    
    // Create an array of adjacency lists
    graph-&gt;array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    
    // Initialize each adjacency list as empty
    for (int i = 0; i &lt; V; i++) {
        graph-&gt;array[i].head = NULL;
    }
    
    return graph;
}

// Add an edge to a directed graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode-&gt;next = graph-&gt;array[src].head;
    graph-&gt;array[src].head = newNode;
}

// Recursive function used by topologicalSort
void topologicalSortUtil(struct Graph* graph, int v, int visited[], int* stack, int* index) {
    // Mark the current node as visited
    visited[v] = 1;
    
    // Recur for all adjacent vertices
    struct AdjListNode* temp = graph-&gt;array[v].head;
    while (temp) {
        if (!visited[temp-&gt;dest]) {
            topologicalSortUtil(graph, temp-&gt;dest, visited, stack, index);
        }
        temp = temp-&gt;next;
    }
    
    // Push current vertex to stack which stores result
    stack[(*index)++] = v;
}

// Function to do Topological Sort
void topologicalSort(struct Graph* graph) {
    int* visited = (int*)calloc(graph-&gt;V, sizeof(int));
    int* stack = (int*)malloc(graph-&gt;V * sizeof(int));
    int index = 0;
    
    // Call the recursive helper function to store Topological Sort
    // starting from all vertices one by one
    for (int i = 0; i &lt; graph-&gt;V; i++) {
        if (!visited[i]) {
            topologicalSortUtil(graph, i, visited, stack, &amp;index);
        }
    }
    
    // Print contents of stack
    printf("Topological Sort Order: ");
    for (int i = graph-&gt;V - 1; i &gt;= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");
    
    free(visited);
    free(stack);
}

int main() {
    struct Graph* graph = createGraph(6);
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);
    
    printf("Following is a Topological Sort of the given graph:\n");
    topologicalSort(graph);
    
    return 0;
}
```


## File Structure

### File Organization

File organization refers to the way data is stored in files. Common file organizations include:

1. **Sequential Organization**: Records stored in contiguous blocks in a specific order
2. **Direct/Random Organization**: Records stored based on an address calculation
3. **Indexed Sequential Organization**: Combines sequential access with indexed access

**C Implementation of Simple Sequential File Organization**:

```c
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

#define MAX_NAME 50

struct Student {
    int id;
    char name[MAX_NAME];
    float gpa;
};

// Write multiple records to a sequential file
void writeToFile(struct Student students[], int n, const char* filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    
    fwrite(students, sizeof(struct Student), n, file);
    fclose(file);
    printf("%d records written to %s\n", n, filename);
}

// Read all records from a sequential file
void readFromFile(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }
    
    struct Student student;
    int count = 0;
    
    printf("Records in file:\n");
    printf("ID\tName\t\tGPA\n");
    printf("-----------------------------------\n");
    
    while (fread(&amp;student, sizeof(struct Student), 1, file)) {
        printf("%d\t%s\t\t%.2f\n", student.id, student.name, student.gpa);
        count++;
    }
    
    fclose(file);
    printf("\nTotal %d records read from file.\n", count);
}

// Update a record in the sequential file
void updateRecord(int id, const char* filename, float newGPA) {
    FILE *file = fopen(filename, "rb+");
    if (file == NULL) {
        printf("Error opening file for updating!\n");
        return;
    }
    
    struct Student student;
    int found = 0;
    
    while (fread(&amp;student, sizeof(struct Student), 1, file)) {
        if (student.id == id) {
            student.gpa = newGPA;
            // Move file pointer back to update this record
            fseek(file, -sizeof(struct Student), SEEK_CUR);
            fwrite(&amp;student, sizeof(struct Student), 1, file);
            found = 1;
            break;
        }
    }
    
    fclose(file);
    
    if (found) {
        printf("Record with ID %d updated.\n", id);
    } else {
        printf("Record with ID %d not found.\n", id);
    }
}

int main() {
    struct Student students[] = {
        {101, "Alice", 3.8},
        {102, "Bob", 3.2},
        {103, "Charlie", 3.9},
        {104, "David", 3.5},
        {105, "Eve", 3.7}
    };
    int n = sizeof(students) / sizeof(students[^0]);
    
    const char* filename = "students.dat";
    
    // Write records to file
    writeToFile(students, n, filename);
    
    // Read and display records
    readFromFile(filename);
    
    // Update a record
    updateRecord(103, filename, 4.0);
    
    // Read updated records
    readFromFile(filename);
    
    return 0;
}
```


### Indexing \& Hashing

Indexing and hashing are techniques used to optimize data storage and retrieval.

#### Indexing

An index is a data structure that improves the speed of data retrieval operations. It works like a book index, providing a map to find data quickly.

**Types of Indexes**:

- **Primary Index**: Created on the ordered data field (usually the primary key)
- **Secondary Index**: Created on non-ordered fields
- **Clustering Index**: Created when data is physically ordered on a non-key field

**C Implementation of Simple Primary Index**:

```c
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

#define MAX_NAME 50
#define INDEX_FILE "student_index.idx"
#define DATA_FILE "student_data.dat"

struct Student {
    int id;
    char name[MAX_NAME];
    float gpa;
};

struct IndexEntry {
    int key;         // Student ID
    long position;   // Position in data file
};

// Create the data file and index file
void createFiles(struct Student students[], int n) {
    FILE *dataFile = fopen(DATA_FILE, "wb");
    FILE *indexFile = fopen(INDEX_FILE, "wb");
    
    if (dataFile == NULL || indexFile == NULL) {
        printf("Error opening files for writing!\n");
        return;
    }
    
    struct IndexEntry entry;
    
    for (int i = 0; i &lt; n; i++) {
        // Write data to data file and remember position
        long pos = ftell(dataFile);
        fwrite(&amp;students[i], sizeof(struct Student), 1, dataFile);
        
        // Create index entry
        entry.key = students[i].id;
        entry.position = pos;
        
        // Write index entry to index file
        fwrite(&amp;entry, sizeof(struct IndexEntry), 1, indexFile);
    }
    
    fclose(dataFile);
    fclose(indexFile);
    printf("Data and index files created successfully.\n");
}

// Search using the index
void searchByID(int id) {
    FILE *indexFile = fopen(INDEX_FILE, "rb");
    FILE *dataFile = fopen(DATA_FILE, "rb");
    
    if (indexFile == NULL || dataFile == NULL) {
        printf("Error opening files for reading!\n");
        return;
    }
    
    struct IndexEntry entry;
    struct Student student;
    int found = 0;
    
    // Search through index file
    while (fread(&amp;entry, sizeof(struct IndexEntry), 1, indexFile)) {
        if (entry.key == id) {
            // Found the index entry, now get the data
            fseek(dataFile, entry.position, SEEK_SET);
            fread(&amp;student, sizeof(struct Student), 1, dataFile);
            
            printf("Student found:\n");
            printf("ID: %d\n", student.id);
            printf("Name: %s\n", student.name);
            printf("GPA: %.2f\n", student.gpa);
            
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }
    
    fclose(indexFile);
    fclose(dataFile);
}

int main() {
    struct Student students[] = {
        {101, "Alice", 3.8},
        {102, "Bob", 3.2},
        {103, "Charlie", 3.9},
        {104, "David", 3.5},
        {105, "Eve", 3.7}
    };
    int n = sizeof(students) / sizeof(students[^0]);
    
    // Create data and index files
    createFiles(students, n);
    
    // Search for students by ID
    searchByID(103);
    searchByID(107); // This ID doesn't exist
    
    return 0;
}
```


### Hash Functions

A hash function maps data of arbitrary size to fixed-size values (hash codes). In file structures, hash functions are used to calculate the direct address of a record.

**Common Hash Functions**:

1. **Division Method**: h(k) = k % m
2. **Multiplication Method**: h(k) = floor(m * (k * A mod 1))
3. **Folding Method**: Divide the key into parts and combine them using operations like addition
4. **Mid-Square Method**: Square the key and take the middle digits

**C Implementation of a Simple Hash Table**:

```c
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

#define TABLE_SIZE 10
#define MAX_NAME 50

struct Student {
    int id;
    char name[MAX_NAME];
    float gpa;
    int isOccupied; // Flag to check if the slot is occupied
};

// Hash function using division method
int hash(int key) {
    return key % TABLE_SIZE;
}

// Initialize hash table
void initHashTable(struct Student hashTable[]) {
    for (int i = 0; i &lt; TABLE_SIZE; i++) {
        hashTable[i].isOccupied = 0; // Mark all slots as empty
    }
}

// Insert a student into hash table (linear probing for collision resolution)
void insert(struct Student hashTable[], struct Student student) {
    int index = hash(student.id);
    int originalIndex = index;
    
    // Linear probing
    while (hashTable[index].isOccupied) {
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            printf("Hash table is full, cannot insert student %d\n", student.id);
            return;
        }
    }
    
    hashTable[index] = student;
    hashTable[index].isOccupied = 1;
    printf("Student %d inserted at index %d\n", student.id, index);
}

// Search for a student in hash table
void search(struct Student hashTable[], int id) {
    int index = hash(id);
    int originalIndex = index;
    
    while (hashTable[index].isOccupied) {
        if (hashTable[index].id == id) {
            printf("Student found at index %d:\n", index);
            printf("ID: %d\n", hashTable[index].id);
            printf("Name: %s\n", hashTable[index].name);
            printf("GPA: %.2f\n", hashTable[index].gpa);
            return;
        }
        
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            break;
        }
    }
    
    printf("Student with ID %d not found.\n", id);
}

// Display hash table
void displayHashTable(struct Student hashTable[]) {
    printf("\nHash Table Contents:\n");
    printf("Index\tID\tName\t\tGPA\n");
    printf("------------------------------------------\n");
    
    for (int i = 0; i &lt; TABLE_SIZE; i++) {
        if (hashTable[i].isOccupied) {
            printf("%d\t%d\t%s\t\t%.2f\n", i, hashTable[i].id, hashTable[i].name, hashTable[i].gpa);
        } else {
            printf("%d\t-\t-\t\t-\n", i);
        }
    }
}

int main() {
    struct Student hashTable[TABLE_SIZE];
    initHashTable(hashTable);
    
    // Create some student records
    struct Student students[] = {
        {101, "Alice", 3.8, 1},
        {112, "Bob", 3.2, 1},
        {123, "Charlie", 3.9, 1},
        {134, "David", 3.5, 1},
        {145, "Eve", 3.7, 1},
        {156, "Frank", 3.3, 1},
        {167, "Grace", 3.6, 1}
    };
    int n = sizeof(students) / sizeof(students[^0]);
    
    // Insert students into hash table
    for (int i = 0; i &lt; n; i++) {
        insert(hashTable, students[i]);
    }
    
    // Display hash table
    displayHashTable(hashTable);
    
    // Search for students
    printf("\nSearching for students:\n");
    search(hashTable, 123);  // Should be found
    search(hashTable, 999);  // Should not be found
    
    return 0;
}
```


### Collision Resolution Techniques

When two or more keys hash to the same location, a collision occurs. Several techniques are used to handle collisions:

1. **Open Addressing**:
    - **Linear Probing**: Check the next slot sequentially
    - **Quadratic Probing**: Check slots at quadratic intervals
    - **Double Hashing**: Use a second hash function
2. **Chaining**: Maintain a linked list of records that hash to the same location

**C Implementation of Chaining**:

```c
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;

#define TABLE_SIZE 10
#define MAX_NAME 50

struct Student {
    int id;
    char name[MAX_NAME];
    float gpa;
    struct Student* next;
};

struct HashTable {
    struct Student* buckets[TABLE_SIZE];
};

// Hash function
int hash(int key) {
    return key % TABLE_SIZE;
}

// Initialize hash table
struct HashTable* createHashTable() {
    struct HashTable* table = (struct HashTable*)malloc(sizeof(struct HashTable));
    for (int i = 0; i &lt; TABLE_SIZE; i++) {
        table-&gt;buckets[i] = NULL;
    }
    return table;
}

// Create a new student node
struct Student* createStudent(int id, const char* name, float gpa) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    newStudent-&gt;id = id;
    strncpy(newStudent-&gt;name, name, MAX_NAME - 1);
    newStudent-&gt;name[MAX_NAME - 1] = '\0';
    newStudent-&gt;gpa = gpa;
    newStudent-&gt;next = NULL;
    return newStudent;
}

// Insert a student into hash table using chaining
void insert(struct HashTable* table, int id, const char* name, float gpa) {
    int index = hash(id);
    
    // Create new student
    struct Student* newStudent = createStudent(id, name, gpa);
    
    // If bucket is empty
    if (table-&gt;buckets[index] == NULL) {
        table-&gt;buckets[index] = newStudent;
    } else {
        // Add at the beginning of the chain
        newStudent-&gt;next = table-&gt;buckets[index];
        table-&gt;buckets[index] = newStudent;
    }
    
    printf("Student %d inserted at index %d\n", id, index);
}

// Search for a student in hash table
void search(struct HashTable* table, int id) {
    int index = hash(id);
    struct Student* current = table-&gt;buckets[index];
    
    while (current != NULL) {
        if (current-&gt;id == id) {
            printf("Student found at index %d:\n", index);
            printf("ID: %d\n", current-&gt;id);
            printf("Name: %s\n", current-&gt;name);
            printf("GPA: %.2f\n", current-&gt;gpa);
            return;
        }
        current = current-&gt;next;
    }
    
    printf("Student with ID %d not found.\n", id);
}

// Display hash table
void displayHashTable(struct HashTable* table) {
    printf("\nHash Table Contents:\n");
    
    for (int i = 0; i &lt; TABLE_SIZE; i++) {
        printf("Bucket %d: ", i);
        
        if (table-&gt;buckets[i] == NULL) {
            printf("Empty\n");
        } else {
            struct Student* current = table-&gt;buckets[i];
            while (current != NULL) {
                printf("[%d: %s] -&gt; ", current-&gt;id, current-&gt;name);
                current = current-&gt;next;
            }
            printf("NULL\n");
        }
    }
}

// Free memory allocated for hash table
void destroyHashTable(struct HashTable* table) {
    for (int i = 0; i &lt; TABLE_SIZE; i++) {
        struct Student* current = table-&gt;buckets[i];
        while (current != NULL) {
            struct Student* temp = current;
            current = current-&gt;next;
            free(temp);
        }
    }
    free(table);
}

int main() {
    struct HashTable* table = createHashTable();
    
    // Insert students
    insert(table, 101, "Alice", 3.8);
    insert(table, 201, "Bob", 3.2);    // Will hash to same bucket as 101
    insert(table, 123, "Charlie", 3.9);
    insert(table, 134, "David", 3.5);
    insert(table, 145, "Eve", 3.7);
    insert(table, 301, "Frank", 3.3);  // Will hash to same bucket as 101 and 201
    insert(table, 167, "Grace", 3.6);
    
    // Display hash table
    displayHashTable(table);
    
    // Search for students
    printf("\nSearching for students:\n");
    search(table, 201);  // Should be found
    search(table, 999);  // Should not be found
    
    // Clean up
    destroyHashTable(table);
    
    return 0;
}
```


## Conclusion

This comprehensive guide covers the fundamental data structures and algorithms in computer science, including trees, searching and sorting techniques, graphs, and file structures. Each topic includes detailed explanations, implementations in C language, and relevant examples to provide a solid understanding of these concepts.

These data structures and algorithms form the building blocks of efficient software design and are essential for solving complex computational problems. By understanding and applying these concepts, developers can create optimized and robust solutions for a wide range of applications.

The implementations provided focus on clarity and educational value, but in real-world applications, you might need to modify them to meet specific requirements and handle edge cases more comprehensively.

<div style="text-align: center">⁂</div>

[^1]: https://pubmed.ncbi.nlm.nih.gov/18958630/

[^2]: http://www.btechsmartclass.com/data_structures/binary-tree-representations.html

[^3]: https://www.scaler.com/topics/binary-search-tree-program-in-c/

[^4]: https://blog.heycoach.in/extended-binary-tree-in-data-structure/

[^5]: https://www.programiz.com/dsa/binary-search-tree

[^6]: https://en.wikipedia.org/wiki/Binary_search_tree

[^7]: https://www.programiz.com/dsa/complete-binary-tree

[^8]: https://edurev.in/t/248543/Extended-Binary-Tree

[^9]: https://www.sanfoundry.com/c-program-implement-avl-tree/

[^10]: https://www.sanfoundry.com/c-program-implement-threaded-binary-tree/

[^11]: https://github.com/tidwall/btree.c

[^12]: https://blog.heycoach.in/general-tree-implementation-in-c/

[^13]: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC7069974/

[^14]: https://www.sanfoundry.com/c-program-implement-interpolation-search-array-integers/

[^15]: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC7460123/

[^16]: https://www.semanticscholar.org/paper/b1228c464fa03db5e68ca625c7e1f37e84ce94a0

[^17]: https://arxiv.org/abs/1508.05388

[^18]: https://pubmed.ncbi.nlm.nih.gov/16221896/

[^19]: http://www.btechsmartclass.com/data_structures/tree-terminology.html

[^20]: https://www.w3schools.com/dsa/dsa_theory_trees.php

[^21]: https://www.semanticscholar.org/paper/e0ab9ec3238109c19f9b61b0ec146e3b5e48f389

[^22]: https://www.semanticscholar.org/paper/6f17a39d4ce096c55cc31176ea03d131adc72c09

[^23]: https://aits-tpt.edu.in/wp-content/uploads/2018/08/DS-Unit-3.pdf

[^24]: https://en.wikipedia.org/wiki/Tree_(abstract_data_type)

[^25]: https://www.hello-algo.com/en/chapter_tree/array_representation_of_tree/

[^26]: https://www.sanfoundry.com/c-program-implement-search-in-binary-search-tree/

[^27]: https://edurev.in/t/248543/Extended-Binary-Tree

[^28]: https://sbme-tutorials.github.io/2020/data-structure-FALL/notes/week08.html

[^29]: https://www.pvpsiddhartha.ac.in/dep_it/lecture%20notes/CDS/unit4.pdf

[^30]: https://xlinux.nist.gov/dads/HTML/binaryTreeRepofTree.html

[^31]: https://www.programiz.com/dsa/binary-search-tree

[^32]: https://www.programiz.com/dsa/complete-binary-tree

[^33]: https://www.cs.cmu.edu/~clo/www/CMU/DataStructures/Lessons/lesson4_1.htm

[^34]: https://www.codechef.com/learn/course/trees/TREES/problems/DSCPP77

[^35]: https://pubmed.ncbi.nlm.nih.gov/30824541/

[^36]: https://pubmed.ncbi.nlm.nih.gov/15677791/

[^37]: https://www.youtube.com/watch?v=cySVml6e_Fc

[^38]: https://leetcode.com/problems/delete-node-in-a-bst/

[^39]: https://www.javaguides.net/2023/09/c-program-to-perform-inorder-preorder-postorder-binary-tree.html

[^40]: https://teachics.org/data-structure-c-tutorial/binary-search-tree-operations/

[^41]: https://www.shiksha.com/online-courses/articles/complete-binary-tree/

[^42]: https://blog.heycoach.in/extended-binary-tree-in-data-structure/

[^43]: https://scaler.com/topics/images/deletion-operation-on-leaf-node.webp?sa=X\&ved=2ahUKEwiGkPX06_iMAxVBkK8BHSrQOXUQ_B16BAgBEAI

[^44]: https://en.wikipedia.org/wiki/Tree_traversal

[^45]: https://www.scaler.com/topics/binary-search-tree-program-in-c/

[^46]: https://builtin.com/data-science/full-tree

[^47]: https://easytechnotes.com/extended-binary-search-tree-in-data-structure/

[^48]: https://www.freecodecamp.org/news/binary-search-tree-traversal-inorder-preorder-post-order-for-bst/

[^49]: https://www.semanticscholar.org/paper/d755b53350dd4ed56751a40611c41ef00d312908

[^50]: https://www.semanticscholar.org/paper/0fb9f4517f5de4fc087c075609c555f186bda79a

[^51]: https://www.programiz.com/dsa/avl-tree

[^52]: https://www.w3schools.com/dsa/dsa_data_avltrees.php

[^53]: https://www.youtube.com/watch?v=Wdy36bumttg

[^54]: https://opendsa-server.cs.vt.edu/ODSA/Books/CS3/html/GenTreeIntro.html

[^55]: https://www.wscubetech.com/resources/dsa/avl-tree

[^56]: https://www.mycompiler.io/view/7e2zasGh9Wj

[^57]: https://www.programiz.com/dsa/b-tree

[^58]: https://opendsa-server.cs.vt.edu/ODSA/Books/Everything/html/GenTreeImplement.html

[^59]: https://github.com/xieqing/avl-tree

[^60]: https://www.sathyabama.ac.in/sites/default/files/course-material/2020-10/unit2_5.pdf

[^61]: https://github.com/KhaledAshrafH/B-Tree

[^62]: https://stackoverflow.com/questions/67884199/problem-with-general-tree-implementation-in-c

[^63]: https://www.semanticscholar.org/paper/ecd4cc5f2177dbfb108f070194f38dcaca628a14

[^64]: https://arxiv.org/abs/1807.02441

[^65]: https://www.ccbp.in/blog/articles/linear-search-in-c

[^66]: https://www.simplilearn.com/tutorials/c-tutorial/program-for-linear-search-in-c

[^67]: https://www.scaler.com/topics/heap-sort-program-in-c/

[^68]: https://github.com/chiendo97/external-sort-cpp

[^69]: https://www.w3schools.com/dsa/dsa_algo_linearsearch.php

[^70]: https://www.programiz.com/dsa/binary-search

[^71]: https://en.wikipedia.org/wiki/Interpolation_search

[^72]: https://www.youtube.com/watch?v=Tz7vBodZqo8

[^73]: https://www.programiz.com/dsa/quick-sort

[^74]: https://en.wikipedia.org/wiki/Merge_sort

[^75]: https://www.sanfoundry.com/c-program-heap-sort-algorithm/

[^76]: https://en.wikipedia.org/wiki/External_sorting

[^77]: https://www.semanticscholar.org/paper/b8404126ad55cea5e72e8672c08d151d77e2c179

[^78]: https://www.semanticscholar.org/paper/73d1a4230e29978d906db3058ad73d1cb0e52c1f

[^79]: https://www.programiz.com/dsa/heap-sort

[^80]: https://en.wikipedia.org/wiki/Heapsort

[^81]: https://takeuforward.org/data-structure/heap-sort

[^82]: https://www.shiksha.com/online-courses/articles/all-about-heap-sort-technique/

[^83]: https://www.ccbp.in/blog/articles/heap-sort-in-data-structure

[^84]: https://www.boardinfinity.com/blog/heap-sort-algorithm/

[^85]: https://users.cs.fiu.edu/~prabakar/cop4722/Common/SortingIllustration.pdf

[^86]: https://answers.microsoft.com/en-us/msoffice/forum/all/multiple-keys-when-sorting/f2681adb-d5dd-4457-99dc-65d47cba33d4

[^87]: https://opendsa-server.cs.vt.edu/ODSA/Books/CS3/html/ExternalSort.html

[^88]: https://stackoverflow.com/questions/47030279/quick-sort-with-multiple-keys

[^89]: https://www.youtube.com/watch?v=Bp7fGofslng

[^90]: https://cboard.cprogramming.com/c-programming/71409-sort-array-multiple-keys.html

[^91]: https://www.semanticscholar.org/paper/fb1cae61c1703a0913d002de555a052230525f54

[^92]: https://www.semanticscholar.org/paper/5549e0cf6ef050070a64ee92b69b679ff2f2a9e9

[^93]: https://www.wscubetech.com/resources/dsa/graph-data-structure

[^94]: https://sites.radford.edu/~nokie/classes/360/graphs-terms.html

[^95]: https://en.wikipedia.org/wiki/Adjacency_list

[^96]: https://www.ccbp.in/blog/articles/dfs-program-in-c

[^97]: https://www.programiz.com/dsa/dijkstra-algorithm

[^98]: http://msitprogramming.blogspot.com/2017/08/bellman-ford-algorithm-and.html

[^99]: https://www.tutorialspoint.com/data_structures_algorithms/graph_data_structure.htm

[^100]: https://github.com/bradtraversy/traversy-js-challenges/blob/main/08-binary-trees-graphs/11-adjacency-matrix-adjacency-list/readme.md

[^101]: https://blog.garybricks.com/bfs-and-dfs-beginners-overview-in-c

[^102]: https://www.w3resource.com/c-programming-exercises/graph/c-graph-exercises-9.php

[^103]: https://www.w3schools.com/dsa/dsa_algo_graphs_bellmanford.php

[^104]: https://www.pvpsiddhartha.ac.in/dep_it/lecture%20notes/CDS/unit5.pdf

[^105]: https://pubmed.ncbi.nlm.nih.gov/27977900/

[^106]: https://www.semanticscholar.org/paper/518c5bd48b9d99fc83407d79ab1a374c9db545a8

[^107]: https://www.w3schools.com/c/c_files.php

[^108]: https://stackoverflow.com/questions/47919/organization-of-c-files

[^109]: https://ece353.engr.wisc.edu/c-programming-language-basics/c-code-organization/

[^110]: http://avanthioslab.blogspot.com/2016/08/file-organization-techniques.html

[^111]: https://web.itu.edu.tr/bkurt/Courses/blg341/lectures_full_6spp.pdf

[^112]: https://stackoverflow.com/questions/10623549/hashing-for-array-indices

[^113]: https://stackoverflow.com/questions/7666509/hash-function-for-string

[^114]: https://www.vibrantpublishers.com/blogs/blogs-on-programming/collision-resolution-with-hashing

[^115]: https://www.lucavall.in/blog/how-to-structure-c-projects-my-experience-best-practices

[^116]: https://planetmainframe.com/2023/06/hashing-and-indexing-mainframe-data/

[^117]: https://gist.github.com/9ba382a0049f6ee885f68621ae86079b

[^118]: https://www.mycompiler.io/view/KMA6mGrot3r

[^119]: https://pubmed.ncbi.nlm.nih.gov/19020688/

[^120]: https://www.semanticscholar.org/paper/cf7eb431e457e24269b9bea7ff2c1f24bd5cdf01

[^121]: https://www.semanticscholar.org/paper/b47a083a1f14e92c7fbe948a6f5f925e917b45db

[^122]: https://www.slideshare.net/slideshow/terminology-of-tree/250594345

[^123]: https://www.thedshandbook.com/trees/

[^124]: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC8218941/

[^125]: https://pubmed.ncbi.nlm.nih.gov/20713727/

[^126]: https://pubmed.ncbi.nlm.nih.gov/15016346/

[^127]: https://pubmed.ncbi.nlm.nih.gov/11213892/

[^128]: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC9260103/

[^129]: https://pubmed.ncbi.nlm.nih.gov/35705320/

[^130]: https://arxiv.org/abs/2208.05412

[^131]: https://arxiv.org/abs/2209.08688

[^132]: https://www.w3schools.com/dsa/dsa_data_binarysearchtrees.php

[^133]: https://www.log2base2.com/data-structures/tree/insert-a-node-in-binary-search-tree.html

[^134]: https://www.youtube.com/watch?v=qqzaCS3s3Ac

[^135]: https://www.log2base2.com/data-structures/tree/inorder-traversal-of-binary-search-tree.html

[^136]: https://www.semanticscholar.org/paper/84b995b844249526d801878b43b1a2e4e7b55557

[^137]: https://www.semanticscholar.org/paper/26ab0def19f7fe901b29b2d66462866def70e447

[^138]: https://www.semanticscholar.org/paper/2c9f75a62d18702731bb0fe84b733ecf0f412b9e

[^139]: https://www.semanticscholar.org/paper/b41fda678ca848a1ca3276bb02a62d1f02cae354

[^140]: https://www.semanticscholar.org/paper/83c7900f9974e478a9dd057bd5084dca7270a874

[^141]: https://www.semanticscholar.org/paper/d08e642ed05256f892e13ac46092532422a195c4

[^142]: https://www.semanticscholar.org/paper/1a1882c2b8373894054d670e8175d1f30a842e05

[^143]: https://www.semanticscholar.org/paper/2f8c61f9606ff16bfae9b6aa0b4aab3107d8aef5

[^144]: https://www.w3resource.com/c-programming-exercises/tree/c-tree-exercises-10.php

[^145]: https://github.com/greensky00/avltree

[^146]: http://www.btechsmartclass.com/data_structures/threaded-binary-trees.html

[^147]: https://www.sanfoundry.com/c-program-btree/

[^148]: https://www.semanticscholar.org/paper/c978836463bd7e7a72dd68d3496d585bc675d3fd

[^149]: https://arxiv.org/abs/1901.09829

[^150]: https://arxiv.org/abs/1903.06547

[^151]: https://www.semanticscholar.org/paper/71f76c5c8f3d91c9f2fd1e7e8bcd523a18c8e0fb

[^152]: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC4935596/

[^153]: https://pubmed.ncbi.nlm.nih.gov/31478707/

[^154]: https://www.semanticscholar.org/paper/634fce4c5c550297dee6f7ccd101a661b4c82948

[^155]: https://www.programiz.com/dsa/linear-search

[^156]: https://jagiroadcollegelive.co.in/attendence/classnotes/files/1590387486.pdf

[^157]: https://www.shiksha.com/online-courses/articles/linear-search-algorithm/

[^158]: https://jagiroadcollegelive.co.in/attendence/classnotes/files/1590387518.pdf

[^159]: https://www.programiz.com/dsa/insertion-sort

[^160]: https://www.scaler.com/topics/quick-sort-c-program/

[^161]: https://www.scaler.com/topics/merge-sort-in-c/

[^162]: https://www.semanticscholar.org/paper/2e384d242a5b4989015565e40ec97c781aefa676

[^163]: https://arxiv.org/abs/1203.1250

[^164]: https://www.semanticscholar.org/paper/6c7dee07a64ec120e4228b247bc3496e422fe805

[^165]: https://www.semanticscholar.org/paper/06bca2637d8fc61ef02336a8d3c76af24f3806bf

[^166]: https://www.semanticscholar.org/paper/d843104be156ed33e5dd6225c8b1098f3e02912f

[^167]: https://www.semanticscholar.org/paper/30931fa84a7d0e9ed4928942345cf01842b1534b

[^168]: https://www.semanticscholar.org/paper/74e2b9b515d269142fef7e779a73d6442f2d22c5

[^169]: https://www.semanticscholar.org/paper/75048e70abb5bffdfb496140e6e74873d4690c7c

[^170]: https://learn.microsoft.com/en-us/dotnet/standard/linq/sort-elements-multiple-keys

[^171]: https://www.includehelp.com/algorithms/external-merge-sorting.aspx

[^172]: https://code365.in/sorting-on-multiple-keys/

[^173]: https://stackoverflow.com/questions/20802396/how-external-merge-sort-algorithm-works

[^174]: https://docs.oracle.com/cd/F30718_01/RR/sorting_with_Multiple_Keys.html

[^175]: https://www.semanticscholar.org/paper/82f77d3294ab1d2a00e4f706dadd687f5a948b09

[^176]: https://www.semanticscholar.org/paper/ebdd53f80011f7c294f4a267031b047efb25fa21

[^177]: https://www.semanticscholar.org/paper/431f29011d647fe154f2936b57918da3ceb23d6c

[^178]: https://arxiv.org/abs/2111.03725

[^179]: https://www.semanticscholar.org/paper/ae6098e92ef8c88bfdb2d3bbc2dc52a8e8507c2d

[^180]: https://www.semanticscholar.org/paper/022e09c8d5d394dfdd3decafcec0b821447a9e95

[^181]: https://www.semanticscholar.org/paper/d1c0133065f979e47939ddf65971e24d3d29a0fb

[^182]: https://arxiv.org/abs/2310.14959

[^183]: https://www.w3schools.com/dsa/dsa_theory_graphs.php

[^184]: https://www.simplilearn.com/tutorials/data-structure-tutorial/graphs-in-data-structure

[^185]: http://www.btechsmartclass.com/data_structures/introduction-to-graphs.html

[^186]: https://takeuforward.org/graph/introduction-to-graph/

[^187]: https://www.sanfoundry.com/c-program-implement-adjacency-list/

[^188]: https://www.sanfoundry.com/c-program-implement-bfs/

[^189]: https://www.w3schools.com/dsa/dsa_algo_graphs_dijkstra.php

[^190]: https://www.sanfoundry.com/c-program-implement-bellmanford-algorithm/

[^191]: https://www.semanticscholar.org/paper/2a2446d47ecc135cdcd2a06d294477473935389a

[^192]: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5210513/

[^193]: https://www.semanticscholar.org/paper/8d6036fd45411090b9eb4a80871c6c1ddd91e102

[^194]: https://pubmed.ncbi.nlm.nih.gov/24762786/

[^195]: https://www.semanticscholar.org/paper/e2d5d8428d0493b3bfc2e8a83d3ab7bcee32dbf5

[^196]: https://www.semanticscholar.org/paper/b85a03e012d2b11d578f92bbaf59c356b52516e8

[^197]: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC10307938/

[^198]: https://www.semanticscholar.org/paper/c1e0a143fc80b7a5b3072a1db9a6f8d70387b3a4

[^199]: https://erp.metbhujbalknowledgecity.ac.in/StudyMaterial/01PD092008003290053.pdf

[^200]: https://www.log2base2.com/algorithms/searching/hashing-in-c-data-structure.html

[^201]: https://benhoyt.com/writings/hash-table-in-c/

[^202]: https://cse.poriyaan.in/topic/collision-resolution-techniques-50572/

[^203]: https://blog.heycoach.in/hierarchical-file-organization-in-c-applications/

[^204]: https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus

[^205]: https://en.wikipedia.org/wiki/Hash_function

[^206]: https://www.w3resource.com/c-programming-exercises/hash/c-hash-exercises-8.php

