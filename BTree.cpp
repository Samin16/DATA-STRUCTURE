#include <bits/stdc++.h>
using namespace std;

class TreeNode      // Represents node of a BTree
{
    int *keys;      // An array of keys
    int t;          // Minimum degree (defines range for number of keys and children)
    TreeNode **C;   // An array of child pointers
    int n;          // Current number of keys
    bool leaf;      // Is a leaf node or not

public:
    TreeNode(int temp, bool bool_leaf);     // Constructor to initialize the node
    void insertNotFull(int k);              // Function to insert a new key in a subtree if number of keys in the node n in n<2t-1
    void splitChild(int i, TreeNode *y);    // Splits child y at position i of the node
    void traverse();                        // Inorder traversal of all nodes
    TreeNode *search(int k);                // Search for a key k
    int findKey(int k);                     // Find the position of the first key greater than or equal to k
    void deletion(int k);                   // To delete a specific key k
    void removeFromLeaf(int idx);           // Remove key present at index idx from the leaf node
    void removeFromNonLeaf(int idx);        // Remove key present at index idx from the non-leaf node
    int getPredecessor(int idx);            // Get the predecessor of the key present at idx
    int getSuccessor(int idx);              // Get the successor of the key present at idx
    void fill(int idx);                     // Fill child node present at idx
    void borrowFromPrev(int idx);           // Borrow a key from the previous child node present at idx
    void borrowFromNext(int idx);           // Borrow a key from the next child node present at idx
    void merge(int idx);                    // Merge child node present at idx with the next child node
    friend class BTree;
};

class BTree
{
    TreeNode *root;                   // Pointer to the root node of BTree
    int t;                            // Minimum degree of the BTree

public:
    BTree(int temp)                   // Initializes the Btree    
    {
        root = NULL;
        t = temp;
    }
    void traverse()                  // Inorder traversal of the BTree
    {
        if (root != NULL)
        {
            root->traverse();
        }
    }
    TreeNode *search(int k)         // Search for a key k
    {
        return (root == NULL) ? NULL : root->search(k);
    }
    void insert(int k);             // Insert a key k
    void deletion(int k);           // Delete a key k
};

TreeNode::TreeNode(int temp, bool bool_leaf)        // Initialize a TreeNode of a BTree
{
    t = temp;
    leaf = bool_leaf;
    keys = new int[2 * t - 1];                      // At most 2t-1 keys
    C = new TreeNode *[2 * t];                      // At most 2t children
    n = 0;
}

void TreeNode::traverse()
{
    int i;
    for (i = 0; i < n; i++)                      // Traverse through n keys and n+1 children
    {
        if (leaf == false)
        {
            C[i]->traverse();
        }
        cout << " " << keys[i];
    }
    if (leaf == false)                         // Traverse through the last child
    {
        C[i]->traverse();
    }
}

TreeNode *TreeNode::search(int k)      
{
    int i = 0;
    while (i < n && k > keys[i])               // Find the first key greater than or equal to k
    {
        i++;
    }
    if (keys[i] == k)                          // If the key is found return it
    {
        return this;
    }
    if (leaf == true)                          // If the node is a leaf node return NULL
    {
        return NULL;
    }
    return C[i]->search(k);                    // Search in the child node recursively
}

void BTree::insert(int k)
{
    if (root == NULL)                          // If the tree is empty create a new node and mark it as root
    {
        root = new TreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else                                      // If the tree is not empty
    {
        if (root->n == 2 * t - 1)             // If root is full, then split the root and increase the height of the tree      
        {
            TreeNode *s = new TreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k)
            {
                i++;
            }
            s->C[i]->insertNotFull(k);
            root = s;
        }
        else                               // If root is not full, then insert the key in root
        {
            root->insertNotFull(k);
        }
    }
}

void TreeNode::insertNotFull(int k)
{
    int i = n - 1;
    if (leaf == true)                  // If the node is leaf node insert the key at correct position
    {
        while (i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n += 1;
    }
    else
    {
        while (i >= 0 && keys[i] > k)     // If not a leaf node, find the child which is going to have the new key
        {                                 // and insert the key in the child
            i--;
        }
        if (C[i + 1]->n == 2 * t - 1)
        {
            splitChild(i + 1, C[i + 1]);
            if (keys[i + 1] < k)
            {
                i++;
            }
        }
        C[i + 1]->insertNotFull(k);
    }
}

void TreeNode::splitChild(int i, TreeNode *y)
{
    TreeNode *z = new TreeNode(y->t, y->leaf);     // Create a node z which is going to store (t-1) keys of y
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++)                // Process: t=2
    {                                              //         (3      ,      8    ,    13)
        z->keys[j] = y->keys[j + t];               //        |        |           |       |
    }                                              //     (1,2)   (4,5,6,7)   (9,10,11)  (14,15,16)
    if (y->leaf == false)                          //             Split that
    {                                              // After Splitting :
        for (int j = 0; j < t; j++)                //        (3     ,   5    ,   8    ,    13)
        {                                          //        |      |        |        |       |
            z->C[j] = y->C[j + t];                 //       (1,2)  (4)    (6,7)    (9,10,11)  (14,15,16)
        }
    }                                              //      Now split (3,5,8,13) to maintain the BTree property
    y->n = t - 1;                                          
    for (int j = n; j >= i + 1; j--)               //                   (  5  )
    {                                              //                  |       |
        C[j + 1] = C[j];                           //                 (3)  (8    ,  13)
    }                                              //                 |    |     |    |
    C[i + 1] = z;                                  //              (1,2) (6,7) (9,10,11) (14,15,16)
    for (int j = n - 1; j >= i; j--)
    {
        keys[j + 1] = keys[j];
    }
    keys[i] = y->keys[t - 1];
    n += 1;
}

int TreeNode::findKey(int k)            
{
    int idx = 0;
    while (idx < n && keys[idx] < k)      // Find the first key greater than or equal to k
    {
        idx++;
    }
    return idx;
}

void TreeNode::deletion(int k)
{
    int idx = findKey(k);                // Find the index of the node to be deleted
    if (idx < n && keys[idx] == k)       // If node found at index idx
    {
        if (leaf)                        // Delete from leaf node
        {
            removeFromLeaf(idx);
        }
        else
        {
            removeFromNonLeaf(idx);      // If not a leaf node
        }
    }
    else
    {
        if (leaf)           // If already at leaf node no need to search further for the key to be deleted
        {
            cout << "The key " << k << " does not exist in the tree"<<endl;
            return;
        }
        bool flag = ((idx == n) ? true : false);     // Flag to check if the key is present in the last child
        if (C[idx]->n < t)                           // If node to be deleted present at a node where 
        {                                            // # of keys<t , so fill it to satisfy condition for BTree
            fill(idx);
        }
        if (flag && idx > n)
        {
            C[idx - 1]->deletion(k);         // If the key is present in the last child, delete it from the last child
        }
        else                                 // If the key present at a child node but not a leaf node
        {
            C[idx]->deletion(k);
        }
        return;
    }
}

void TreeNode::removeFromLeaf(int idx)
{
    for (int i = idx + 1; i < n; i++)      // Simply shift left all keys after index idx
    {
        keys[i - 1] = keys[i];
    }
    n--;                                   // and reduce n(# of keys) by 1
    return;
}

void TreeNode::removeFromNonLeaf(int idx)
{
    int k = keys[idx];
    if (C[idx]->n >= t)                  // If the idx position child's n>=t then find the Predecessor
    {                                    // and replace the key at idx by predecessor and delete the predecessor
        int pred = getPredecessor(idx);
        keys[idx] = pred;
        C[idx]->deletion(pred);
    }
    else if (C[idx + 1]->n >= t)         // If the idx+1 position child's n>=t then find the Successor
    {                                    // and replace the key at idx by successor and delete the successor
        int succ = getSuccessor(idx);
        keys[idx + 1] = succ;
        C[idx+1]->deletion(succ);
    }
    else
    {
        merge(idx);                      // If both children have less than t keys then merge the idx and idx+1 children
        C[idx]->deletion(k);
    }
    return;
}

int TreeNode::getPredecessor(int idx)
{                                       // Finds the last key in the last child of subtree rooted at C[idx]
    TreeNode *cur = C[idx];
    while (cur->leaf == false)
    {
        cur = cur->C[cur->n];
    }
    return cur->keys[cur->n - 1];
}

int TreeNode::getSuccessor(int idx)
{                                     // Finds the first key in the last child of subtree rooted at C[idx+1]
    TreeNode *cur = C[idx + 1];
    while (cur->leaf == false)
    {
        cur = cur->C[0];
    }
    return cur->keys[0];
}

void TreeNode::fill(int idx)         // Function to fill child node if it has less than t keys
{
    if (idx != 0 && C[idx - 1]->n >= t)
    {
        borrowFromPrev(idx);            // If the previous child has more than t keys and it's not the starting node , borrow a key from it
    }
    else if (idx != n && C[idx + 1]->n >= t)
    {
        borrowFromNext(idx);            // If the next child has more than t keys and it's not the last node , borrow a key from it
    }
    else                    // If both children has less than t keys then merge them
    {
        if (idx != n)       // If idx is not the last child then merge idx and idx+1 children              
        {
            merge(idx);
        }
        else                // If idx is the last child then merge idx-1 and idx children
        {
            merge(idx - 1);
        }
    }
    return;
}

void TreeNode::borrowFromPrev(int idx)       // Borrow a key from the previous child node present at idx
{
    TreeNode *child = C[idx];
    TreeNode *sibling = C[idx - 1];
    for (int i = child->n - 1; i >= 0; i--)
    {                                          // Process: t=2
        child->keys[i + 1] = child->keys[i];   //      (4    ,   8    ,   13)
    }                                          //     |      |        |      |  
    if (!child->leaf)                          //   (1,2,3) (5)      (9,10) (14,15,16)
    {
        for (int i = child->n; i >= 0; i--)   //  Borrow from previous child
        {
            child->C[i + 1] = child->C[i];    //      (3     ,   8    ,   13)
        }                                     //     |       |        |      |
    }                                         //     (1,2) (4,5)    (9,10) (14,15,16)
    child->keys[0] = keys[idx - 1];
    if (child->leaf == false)
    {
        child->C[0] = sibling->C[sibling->n];
    }
    keys[idx - 1] = sibling->keys[sibling->n - 1];
    child->n += 1;
    sibling->n -= 1;
    return;
}

void TreeNode::borrowFromNext(int idx)      // Borrow a key from the next child node present at idx
{
    TreeNode *child = C[idx];
    TreeNode *sibling = C[idx + 1];
    child->keys[child->n] = keys[idx];
    if (child->leaf == false)
    {
        child->C[(child->n) + 1] = sibling->C[0];
    }                                               // Process: t=2
    keys[idx] = sibling->keys[0];                   //      (4     ,    8     ,      13)
    for (int i = 1; i < sibling->n; i++)            //      |      |          |         |
    {                                               //     (1)  (5,6,7)    (9,10,11) (14,15,16)
        sibling->keys[i - 1] = sibling->keys[i];
    }                                               // Borrow from next child
    if (sibling->leaf == false)
    {                                               //     (5      ,    8    ,      13)
        for (int i = 1; i <= sibling->n; i++)       //    |        |         |         |
        {                                           //  (1,4)    (6,7)    (9,10,11) (14,15,16)
            sibling->C[i - 1] = sibling->C[i];
        }
    }
    child->n += 1;
    sibling->n -= 1;
    return;
}

void TreeNode::merge(int idx)        // Merge child node present at idx with the next child node
{
    TreeNode *child = C[idx];
    TreeNode *sibling = C[idx + 1];
    child->keys[t - 1] = keys[idx];
    for (int i = 0; i < sibling->n; i++)          // Process : t=2
    {                                             //      (4    ,     8    ,    13)
        child->keys[i + t] = sibling->keys[i];    //     |      |         |        |
    }                                             //     (1)    (5)   (9,10,11) (14,15,16)
    if (child->leaf == false)
    {
        for (int i = 0; i <= sibling->n; i++)     // Merge (1) and (5) to maintain the BTree property
        {
            child->C[i + t] = sibling->C[i];      //          (8       ,      13)
        }                                         //         |         |         |
    }                                             //      (1,4,5)  (9,10,11) (14,15,16)
    for (int i = idx + 1; i < n; i++)
    {
        keys[i - 1] = keys[i];
    }
    for (int i = idx + 2; i <= n; i++)
    {
        C[i - 1] = C[i];
    }
    child->n += sibling->n + 1;
    n--;
    delete (sibling);
    return;
}

void BTree::deletion(int k)
{
    if (!root)                            // If the tree is empty
    {
        cout << "Tree is empty" << endl;
        return;
    }
    root->deletion(k);                    // Call the deletion function
    if (root->n == 0)
    {
        TreeNode *temp = root;            // If the root node has 0 keys then make its first child as the new root
        if (root->leaf)                   // If the root is a leaf node then make the root as NULL             
        {
            root = NULL;
        }
        else                              // If the root is not a leaf node then make the first child as the new root
        {
            root = root->C[0];
        }
        delete (temp);
    }
    return;
}

int main()
{
    BTree t(3);
    t.insert(8);
    t.insert(9);
    t.insert(10);
    t.insert(11);
    t.insert(15);
    t.insert(16);
    t.insert(17);
    t.insert(18);
    t.insert(20);
    t.insert(23);
    cout << "B Tree : ";
    t.traverse();
    int k = 10;
    (t.search(k) != NULL) ? (cout << "\n"
                                  << k << " " << "is found" << endl)
                          : (cout << k << " not found");
    k = 2;
    (t.search(k) != NULL) ? (cout << k << " " << "is found" << endl) : (cout << k << " not found");

    t.deletion(15);
    t.traverse();
    t.deletion(20);

    cout << "\nThe B-tree is: ";
    t.traverse();
    cout<<"\n";
    t.deletion(8);
    t.traverse();
}


// Output  :   B Tree :  8 9 10 11 15 16 17 18 20 23
//                 10 is found
//                 2 not found 8 9 10 11 16 17 18 20 23
//                 The B-tree is:  8 9 10 11 16 17 18 23
//                 9 10 11 16 17 18 23 