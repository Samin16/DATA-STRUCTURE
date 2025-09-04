// Splay Tree Implementation in CPP
// Author : Samin Yasar

#include <bits/stdc++.h>
using namespace std;

// ---------------- Node definition ----------------
class Node
{
    int key;
    Node *left, *right;

public:
    Node(int k)
    {
        key = k;
        left = right = nullptr;
    }
    friend class SplayTree;
};

// ---------------- Splay Tree ----------------
class SplayTree
{
    Node *root;

    // Left rotation:
    //   x             y
    //  / \           / \
    // A   y    =>   x   C
    //    / \       / \
    //   B   C     A   B
    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    // Right rotation:
    //     x          y
    //    / \   =>   / \
    //   y   C      A   x
    //  / \            / \
    // A   B          B   C
    Node *rightRotate(Node *x)
    {
        Node *y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    // ---------------- Splay operation ----------------
    // Bring the key to root if it exists,
    // or bring the last accessed node (closest to target key) to root.
    Node *splay(Node *root, int key)
    {
        if (root == nullptr || root->key == key)
            return root;

        // Case 1: Key in left subtree
        if (key < root->key)
        {
            if (root->left == nullptr)
                return root;

            // Zig-Zig (Left Left)
            if (key < root->left->key)
            {
                root->left->left = splay(root->left->left, key);
                root = rightRotate(root);
            }
            // Zig-Zag (Left Right)
            else if (key > root->left->key)
            {
                root->left->right = splay(root->left->right, key);
                if (root->left->right != nullptr)
                    root->left = leftRotate(root->left);
            }
            return (root->left == nullptr) ? root : rightRotate(root);
        }
        // Case 2: Key in right subtree
        else
        {
            if (root->right == nullptr)
                return root;

            // Zig-Zig (Right Right)
            if (key > root->right->key)
            {
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            }
            // Zig-Zag (Right Left)
            else if (key < root->right->key)
            {
                root->right->left = splay(root->right->left, key);
                if (root->right->left != nullptr)
                    root->right = rightRotate(root->right);
            }
            return (root->right == nullptr) ? root : leftRotate(root);
        }
    }

public:
    SplayTree() { root = nullptr; }

    // ---------------- Insert operation ----------------
    void insert(int key)
    {
        if (root == nullptr)
        {
            root = new Node(key);
            return;
        }

        root = splay(root, key);

        // If key already exists, do nothing
        if (root->key == key)
            return;

        Node *newNode = new Node(key);
        if (key < root->key)
        {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
        }
        else
        {
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
        }
        root = newNode;
    }

    // ---------------- Delete operation ----------------
    void deleteKey(int key)
    {
        if (root == nullptr)
            return;

        root = splay(root, key);

        // Key not found
        if (root->key != key)
            return;

        Node *temp = root;
        if (root->right == nullptr)
        {
            root = root->left; // Replace with left child
        }
        else
        {
            // Bring the smallest node in right subtree to root
            root = splay(root->right, key);
            root->left = temp->left;
        }
        delete temp;
    }

    // ---------------- Search operation ----------------
    bool search(int key)
    {
        if (root == nullptr)
            return false;
        root = splay(root, key);
        return (root->key == key);
    }

    // ---------------- Utility: Inorder traversal ----------------
    void inorder(Node *node)
    {
        if (node == nullptr)
            return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

    void printInorder()
    {
        inorder(root);
        cout << "\n";
    }
};

// ---------------- Main to test ----------------
int main()
{
    SplayTree st;

    // Insert keys
    st.insert(10);
    st.insert(20);
    st.insert(30);
    st.insert(40);
    st.insert(50);
    st.insert(25);

    cout << "Inorder traversal after inserts: ";
    st.printInorder();

    // Search
    cout << "Searching 20 -> " << (st.search(20) ? "Found" : "Not Found") << "\n";
    cout << "Searching 60 -> " << (st.search(60) ? "Found" : "Not Found") << "\n";

    // Delete
    st.deleteKey(20);
    cout << "Inorder after deleting 20: ";
    st.printInorder();

    st.deleteKey(30);
    cout << "Inorder after deleting 30: ";
    st.printInorder();

    return 0;
}


// Output : 
// Inorder traversal after inserts: 10 20 25 30 40 50 
// Searching 20 -> Found
// Searching 60 -> Not Found
// Inorder after deleting 20: 10 25 30 40 50 
// Inorder after deleting 30: 10 25 40 50 