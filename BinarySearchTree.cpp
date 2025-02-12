// Binary Search Tree

#include<iostream>
using namespace std;

struct Node
{
    int key;
    Node *left,*right;
};

                                 // Creates a node
Node* newNode(int data)          // by allocating space for it
{
    Node* temp=(Node*)malloc(sizeof(Node));
    temp->key=data;
    temp->left=temp->right=NULL;
    return temp;
} 

void inOrder(Node* root)          //InOrder Traversal
{
    if(root!=NULL)
    {
        inOrder(root->left);
        cout<<" "<<root->key;
        inOrder(root->right);
    }
}

void preOrder(Node* root)        // PreOrder Traversal
{
    if(root==NULL)
    {
        return;
    }
    cout<<root->key<<" ";
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(Node* root)        // PostOrder Traversal
{
    if(root==NULL)
    {
        return;
    }
    preOrder(root->left);
    preOrder(root->right);
    cout<<root->key<<" ";
}

Node* insert(Node* node,int key)     //Inserts a node
{
    if(node==NULL)
    {
        return newNode(key);
    }
    if(key<node->key)         // If current node key>given key then go left
    {
        node->left=insert(node->left,key);
    }
    else                     // Otherwise, go right
    {
        node->right=insert(node->right,key);
    }
    return node;
}

Node* minValueNode(Node* node)       //FINDS THE INORDER SUCCESSOR
{
    Node* current=node;
    while(current && current->left!=NULL)
    {
        current=current->left;
    }
    return current;
}

Node* deleteNode(Node* root,int key)     //Deleting a node
{
    if(root==NULL)
    {
        return root;
    }
    if(key<root->key)         // Recurs until finds the specified position
    {
        root->left=deleteNode(root->left,key);
    }
    else if(key>root->key)
    {
        root->right=deleteNode(root->right,key);
    }
    else                     // If found check if any leaf of the node is missing
    {                        // then fill the deleted position with the leaf that exists
        if(root->left==NULL) // If the node is a leaf node then simply delete it
        {
            Node* temp=root->right;     
            free(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            Node* temp=root->left;
            free(root);
            return temp;
        }
        Node* temp=minValueNode(root->right);  // If both leaves are present then find the smallest node
        root->key=temp->key;                   // in right subtree and replace it to the deleted position
        root->right=deleteNode(root->right,temp->key);
    }
    return root;
}

int main()
{
    Node* root=NULL;
    root=insert(root,8);
    root=insert(root,3);
    root=insert(root,1);
    root=insert(root,6);
    root=insert(root,7);
    root=insert(root,10);
    root=insert(root,14);
    root=insert(root,4);
    cout<<"In Order : ";
    inOrder(root);
    cout<<endl;
    cout<<"Pre Order : ";
    preOrder(root);
    cout<<endl;
    cout<<"Post Order : ";
    postOrder(root);
    cout<<endl;
    root=deleteNode(root,8);
    root=deleteNode(root,10);
    root=deleteNode(root,14);
    cout<<"In Order : ";
    inOrder(root);
    cout<<endl;
    cout<<"Pre Order : ";
    preOrder(root);
    cout<<endl;
    cout<<"Post Order : ";
    postOrder(root);
    cout<<endl;
    return 0;
}


// Output : In Order :  1 3 4 6 7 8 10 14
//                      Pre Order : 8 3 1 6 4 7 10 14 
//                      Post Order : 3 1 6 4 7 10 14 8 
//                      In Order :  1 3 4 6 7                     
//                      Pre Order : 3 1 6 4 7
//                      Post Order : 1 6 4 7 3