// Red Black Tree Implementation
// Author : Samin Yasar

#include <bits/stdc++.h>
using namespace std;

class RedBlackTree       // All methods and Node structure of RED BLACK tree
{
private:
    class Node           // Node of a red black tree 
    {
    public:
        int data;
        Node *left;
        Node *right;     // Left and right child of the node
        Node *parent;    // Parent of the node
        int color;       // color 1 for red, 0 for black

        Node(int val) : data(val), left(nullptr), right(nullptr), parent(nullptr), color(1) {}
    };

    Node *root;          // Root of the red black tree

    // Helper functions
    void leftRotate(Node *x)      // Left rotation at Node x
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *x)       // Right rotation at Node x
    {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != nullptr)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void insertFixup(Node *z)         // Fix the red-black tree properties after insertion
    {
        while (z->parent != nullptr && z->parent->color == 1)   // While z's parent is red Fix the tree
        {
            if (z->parent == z->parent->parent->left)           // If z's parent is its grandparent's left child
            {
                Node *y = z->parent->parent->right;             // then z's grandparent's right child, y is uncle of z
                if (y != nullptr && y->color == 1)              // If uncle is red
                {
                    z->parent->color = 0;
                    y->color = 0;
                    z->parent->parent->color = 1;
                    z = z->parent->parent;
                }
                else                                    // If uncle is black
                {
                    if (z == z->parent->right)          // and z, z's parent and z's grandparent forms a triangle
                    {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = 0;               // z, z's parent and z's grandparent forms a line
                    z->parent->parent->color = 1;
                    rightRotate(z->parent->parent);
                }
            }
            else                  // If z's parent is its grandparent's right child
            {
                Node *y = z->parent->parent->left;    // then z's grandparent's left child, y is uncle of z
                if (y != nullptr && y->color == 1)    // If uncle is red
                {
                    z->parent->color = 0;
                    y->color = 0;
                    z->parent->parent->color = 1;
                    z = z->parent->parent;
                }
                else                             // If uncle is black
                {
                    if (z == z->parent->left)    // and z, z's parent and z's grandparent forms a triangle
                    {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = 0;        // and z, z's parent and z's grandparent forms a line
                    z->parent->parent->color = 1;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = 0;           // Set the root to black
    }

    void transplant(Node *u, Node *v)    // Replace the subtree rooted at u with the subtree rooted at v
    {
        if (u->parent == nullptr)        // If u is root
        {
            root = v;
        }
        else if (u == u->parent->left)   // If u is its parent's left child
        {
            u->parent->left = v;
        }
        else                             // If u is its parent's right child
        {
            u->parent->right = v;
        }
        if (v != nullptr)                // If v is not null set v's parent to u's parent
        {
            v->parent = u->parent;
        }
    }

    Node *minimum(Node *x)               // Find the minimum node in the subtree rooted at x
    {
        while (x->left != nullptr)
        {
            x = x->left;
        }
        return x;
    }

    void deleteFixup(Node *x)      // Fix the red-black tree properties after deletion
    {
        while (x != root && (x == nullptr || x->color == 0))  // While x is black
        {
            if (x == x->parent->left)         // If x is its parent's left child
            {
                Node *w = x->parent->right;   // then x's sibling w is its parent's right child
                if (w->color == 1)            // If sibling is red
                {
                    w->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }                                     // If sibling is black and both of its children are black
                if ((w->left == nullptr || w->left->color == 0) && (w->right == nullptr || w->right->color == 0))
                {
                    w->color = 1;
                    x = x->parent;
                }
                else                               
                {
                    if (w->right == nullptr || w->right->color == 0)   // If sibling is black and its right child is black
                    {
                        if (w->left != nullptr)
                            w->left->color = 0;
                        w->color = 1;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;          // If sibling is black and its right child is red
                    x->parent->color = 0;
                    if (w->right != nullptr)
                        w->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else                // If x is its parent's right child
            {
                Node *w = x->parent->left;    // then x's sibling w is its parent's left child       
                if (w->color == 1)            // If sibling is red
                {
                    w->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }                             // If sibling is black and both of its children are black
                if ((w->right == nullptr || w->right->color == 0) && (w->left == nullptr || w->left->color == 0))
                {
                    w->color = 1;
                    x = x->parent;
                }
                else                     
                {
                    if (w->left == nullptr || w->left->color == 0)    // If sibling is black and its left child is black
                    {
                        if (w->right != nullptr)
                            w->right->color = 0;
                        w->color = 1;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;        // If sibling is black and its left child is red
                    x->parent->color = 0;
                    if (w->left != nullptr)
                        w->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        if (x != nullptr)        // If x is not null set x's color to black
            x->color = 0;
    }

public:
    RedBlackTree() : root(nullptr) {}     // Constructor to initialize the root to null
    ~RedBlackTree() { delete root; }      // Destructor to delete the tree
    void insert(int data)                 // Insert a new node with the given data
    {
        Node *z = new Node(data);
        Node *y = nullptr;
        Node *x = root;

        while (x != nullptr)              // Search for correct position to insert the new node
        {
            y = x;
            if (z->data < x->data)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }
                               // If a position is found, set the parent of the new node to y
        z->parent = y;          
        if (y == nullptr)      // If the tree was empty, set new node as root
        {
            root = z;
        }
        else if (z->data < y->data)   // If the new node is less than y , set y's left child to z
        {
            y->left = z;
        }
        else                    // If the new node is greater than y , set y's right child to z
        {
            y->right = z;
        }

        insertFixup(z);         // Fix the red-black tree properties after insertion
    }

    void deleteNode(int data)   // Delete the node with the given data
    {
        Node *z = root;
        while (z != nullptr)       // Search for the node to be deleted
        {
            if (z->data == data)
            {
                break;
            }
            else if (data < z->data)
            {
                z = z->left;
            }
            else
            {
                z = z->right;
            }
        }

        if (z == nullptr)     // If the node is not found, return
        {
            cout << "Node not found" << endl;
            return;
        }

        Node *y = z;
        Node *x = nullptr;
        int yOriginalColor = y->color;

        if (z->left == nullptr)        // If the node to be deleted has no left child
        {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == nullptr)  // If the node to be deleted has no right child
        {
            x = z->left;
            transplant(z, z->left);
        }
        else                         // If the node to be deleted has both children
        {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;

            if (y->parent == z)
            {
                if (x != nullptr)
                    x->parent = y;
            }
            else
            {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (yOriginalColor == 0 && x != nullptr)   // If the deleted node was black and x is not null
        {
            deleteFixup(x);                        // then fix the red-black tree properties
        }
    }

    bool search(int data)            // Search for the node with the given data
    {
        Node *temp = root;
        while (temp != nullptr)
        {
            if (temp->data == data)
            {
                return true;
            }
            else if (data < temp->data)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        return false;         // If the node is not found, return false
    }

    void printTree()                      // Prints the level order traversal of the tree
    {
        if (root == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *temp = q.front();
            q.pop();
            cout << temp->data << " Color: " << (temp->color == 0 ? "Black" : "Red") << "\n";
            if (temp->left != nullptr)
            {
                q.push(temp->left);
            }
            if (temp->right != nullptr)
            {
                q.push(temp->right);
            }
        }
    }
};

int main()
{
    RedBlackTree rbt;
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(15);
    rbt.insert(25);
    rbt.insert(5);

    cout << "Red Black Tree after insertion:\n";
    rbt.printTree();

    cout << "Searching for 15: " << (rbt.search(15) ? "Found" : "Not Found") << endl;
    cout << "Searching for 100: " << (rbt.search(100) ? "Found" : "Not Found") << endl;

    rbt.deleteNode(20);
    cout << "Red Black Tree after deletion:\n";
    rbt.printTree();

    return 0;
}

// Output : Red Black Tree after insertion:
//          20 Color: Black
//          10 Color: Black
//          30 Color: Black
//          5 Color: Red
//          15 Color: Red
//          25 Color: Red
//          Searching for 15: Found
//          Searching for 100: Not Found
//          Red Black Tree after deletion:
//          25 Color: Black
//          10 Color: Black
//          30 Color: Black
//          5 Color: Red
//          15 Color: Red