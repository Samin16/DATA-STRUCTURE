// AVL Tree 


#include<iostream>
using namespace std;

class Node           // Node for a AVL tree
{
    public:
        int key;
        Node* left;
        Node* right;
        int height;      // height is needed to balance tree
};

int max(int a,int b)
{
    return (a>b)?a:b;
}

int height(Node* N)       // Returns height of a node
{
    if(N==NULL)
    {
        return 0;
    }
    return N->height;
}

Node* newNode(int data)     // Creates a new node
{
    Node* node=new Node();
    node->key=data;
    node->left=node->right=NULL;
    node->height=1;
    return node;
}

Node* rightRotate(Node* y)   //Rotates Right
{
    Node* x=y->left;
    Node* T1=x->right;
    x->right=y;
    y->left=T1;
    y->height=max(height(y->left),height(y->right))+1;
    x->height=max(height(x->left),height(x->right))+1;
    return x;
}

Node* leftRotate(Node* x)     //Rotates Left
{
    Node* y=x->right;
    Node* T2=y->left;
    y->left=x;
    x->right=T2;
    x->height=max(height(x->left),height(x->right))+1;
    y->height=max(height(y->left),height(y->right))+1;
    return y;
}

int getBalanceFactor(Node* N)        // Calculates difference between height of left and right subtree
{
    if(N==NULL)
    {
        return 0;
    }
    return (height(N->left)-height(N->right));
}

Node* insertNode(Node* node,int key)      // Inserts a node maintaining balance
{
    if(node==NULL)
    {
        return newNode(key);
    }
    if(key<node->key)
    {
        node->left=insertNode(node->left,key);
    }
    else if(key>node->key)
    {
        node->right=insertNode(node->right,key);
    }
    else
    {
        return node;
    }
    node->height=1+max(height(node->left),height(node->right));
    int balanceFactor=getBalanceFactor(node);
    if(balanceFactor>1)        // If left subtree height is greater than right subtree height rotate left to right
    {
        if(key<node->left->key)
        {
            return rightRotate(node);
        }
        else if(key>node->left->key)
        {
            node->left=leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if(balanceFactor<-1)     // If right subtree height is greater than left subtree height rotate right to left
    {
        if(key>node->right->key)
        {
            return leftRotate(node);
        }
        else if(key<node->right->key)
        {
            node->right=rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

Node* nodeWithMinimumValue(Node* node)    // Leftmost children of a subtree having "node" as root
{
    Node* current=node;
    while(current->left!=NULL)
    {
        current=current->left;
    }
    return current;
}

Node* deleteNode(Node* root,int key)      // Deletes a node and rebalances the tree
{
    if(root==NULL)
    {
        return root;
    }
    if(key<root->key)
    {
        root->left=deleteNode(root->left,key);
    }
    else if(key>root->key)
    {
        root->right=deleteNode(root->right,key);
    }
    else
    {
        if(root->left==NULL || root->right==NULL)    // If node to be deleted is leaf or has one of its children
        {
            Node* temp=(root->left)?root->left:root->right;
            if(temp==NULL)
            {
                temp=root;
                root=NULL;
            }
            else
            *root=(*temp);
            free(temp);
        }
        else
        {
            Node* temp=nodeWithMinimumValue(root->right);  // If not a leaf and has both children
            root->key=temp->key;
            root->right=deleteNode(root->right,temp->key);
        }
    }
    if(root==NULL)
    {
        return root;
    }
    root->height=1+max(height(root->left),height(root->right));
    int balanceFactor=getBalanceFactor(root);
    if(balanceFactor>1)
    {
        if(getBalanceFactor(root->left)>=0)
        {
            return rightRotate(root);
        }
        else
        {
            root->left=leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if(balanceFactor<-1)
    {
        if(getBalanceFactor(root->right)<=0)
        {
            return leftRotate(root);
        }
        else
        {
            root->right=rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

void printTree(Node* root,string indent,bool last)       // Prints the tree
{
    if(root!=nullptr)
    {
        cout<<indent;
        if(last)
        {
            cout<<"R----";
            indent+="  ";
        }
        else
        {
            cout<<"L----";
            indent+="|  ";
        }
        cout<<root->key<<endl;
        printTree(root->left,indent,false);
        printTree(root->right,indent,true);
    }
}

int main()
{
    Node* root=NULL;
    root=insertNode(root,33);
    root=insertNode(root,13);
    root=insertNode(root,53);
    root=insertNode(root,9);
    root=insertNode(root,21);
    root=insertNode(root,61);
    root=insertNode(root,8);
    root=insertNode(root,11);
    printTree(root,"",true);
    root=deleteNode(root,13);
    cout<<"After deleting 13 : \n";
    printTree(root,"",true);
    return 0;
}

//       Output : R----33
//                  L----13
//                  |  L----9
//                  |  |  L----8
//                  |  |  R----11
//                  |  R----21
//                  R----53
//                    R----61
//                After deleting 13 : 
//                R----33
//                  L----9
//                  |  L----8
//                  |  R----21
//                  |    L----11
//                  R----53
//                    R----61