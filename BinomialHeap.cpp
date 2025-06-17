#include<bits/stdc++.h>
using namespace std;

struct Node         // Node of a binomial tree
{
    int key;        // Value of a node
    Node* parent;   // Parent of the node
    Node* child;    // Leftmost child of the node
    Node* sibling;  // Sibling of the node
    int degree;     // Degree of the node
    Node(int val):parent(nullptr),child(nullptr),sibling(nullptr),degree(0)  // Constructor to initialize a node
    {
        this->key=val;
    }
};

class BinomialHeap
{
    Node* head;           // Head of the root list of Binomial Heap
                        
    // Helper Methods
    Node* mergeRoots(Node* h1,Node* h2)   // Method to connect two heaps in increasing order of their
    {                                     // binomial trees orders like, H1->B0->B2->B3 ,H2->B1->B2->B4
        if(h1==nullptr)                   // Result : NewH->B0->B1->B2->B2->B3->B4
        {
            return h2;
        }
        if(h2==nullptr)
        {
            return h1;
        }
        Node* head=nullptr;
        Node** pos=&head;
        while(h1 && h2)
        {
            if(h1->degree<=h2->degree)
            {
                *pos=h1;
                h1=h1->sibling;
            }
            else
            {
                *pos=h2;
                h2=h2->sibling;
            }
            pos=&((*pos)->sibling);
        }
        if(h1!=nullptr)
        {
            *pos=h1;
        }
        else
        {
            *pos=h2;
        }
        return head;
    }
    void linkTrees(Node* y,Node* z)      // Links two trees of same degree Like H2,H2=>H4
    {
        y->parent=z;
        y->sibling=z->child;
        z->child=y;
        z->degree++;
    }
    Node* unionHeaps(Node* h1,Node* h2)     // Merges two heaps to get a new heap
    {
        Node* newHead=mergeRoots(h1,h2);
        if(newHead==nullptr)
        {
            return nullptr;
        }
        Node *prev=nullptr,*curr=newHead,*next=curr->sibling;
        while(next!=nullptr)
        {
            if(curr->degree!=next->degree || (next->sibling && next->sibling->degree==curr->degree))
            {
                prev=curr;
                curr=next;
            }
            else 
            {
                if(curr->key<=next->key)
                {
                    curr->sibling=next->sibling;
                    linkTrees(next,curr);
                }
                else
                {
                    if(!prev)
                    {
                        newHead=next;
                    }
                    else
                    {
                        prev->sibling=next;
                    }
                    linkTrees(curr,next);
                    curr=next;
                }
            }
            next=curr->sibling;
        }
        return newHead;
    }
    Node* findNode(Node* root,int target)     // Finds the target node in the binomial heap
    {
        if(root==nullptr)
        {
            return nullptr;
        }
        if(root->key==target)
        {
            return root;
        }
        Node* found=findNode(root->child,target);
        if(found)
        {
            return found;
        }
        return findNode(root->sibling,target);
    }
    void reverseList(Node*& node)      // Disconnects the node and its siblings from the parent and rearranges 
    {                                  // the subtrees like the node and siblings in increasing order of degree
        Node* prev=nullptr;
        while(node!=nullptr)
        {
            Node* next=node->sibling;
            node->sibling=prev;
            node->parent=nullptr;
            prev=node;
            node=next;
        }
        node=prev;
    }
    void printTreeLevelWise(Node* root,int level=0)    // Prints one heap tree level wise
    {
        if(root==nullptr)
        {
            return;
        }
        cout<<"Level "<<level<<" : "<<root->key<<"\n";
        if(!root->child)
        {
            return;
        }
        level++;
        Node *curr=root->child,*temp=curr;
        while(curr!=nullptr)
        {
            cout<<"Level "<<level<<" : ";
            while(temp!=nullptr) 
            {
                cout<<temp->key<<" ";
                temp=temp->sibling;
            }
            curr=curr->child;
            temp=curr;
            cout<<"\n";
            level++;
        }
    }
public:
    BinomialHeap():head(nullptr){}      // Constructor to initialize binomial heap
    void insert(int key)                // Insertion in a heap. First make a node as B0 
    {                                   // which is itself a heap then merges it with H
        Node* node=new Node(key);
        head=unionHeaps(head,node);
    }
    int findMin()                   // Finds the minimum element in the binomial heap(present in the root list)
    {
        int minKey=INT_MAX;
        Node* curr=head;
        while(curr!=nullptr)
        {
            minKey=min(minKey,curr->key);
            curr=curr->sibling;
        }
        return minKey;
    }
    int extractMin()           // Extracts the minimum element and deletes it from root list. Then the deleted node's child   
    {                          // and child's siblings are connected in increasing order to make a heap. Then merges it with
        if(head==nullptr)      // actual heap
        {
            return INT_MIN;
        }
        Node *minNode=head,*minPrev=nullptr;
        Node *curr=head,*prev=nullptr;
        int minKey=head->key;
        while(curr!=nullptr)
        {
            if(curr->key<minKey)
            {
                minKey=curr->key;
                minNode=curr;
                minPrev=prev;
            }
            prev=curr;
            curr=curr->sibling;
        }
        if(minPrev)
        {
            minPrev->sibling=minNode->sibling;
        }
        else
        {
            head=minNode->sibling;
        }
        Node* child=minNode->child;
        reverseList(child);
        head=unionHeaps(head,child);
        delete minNode;
        return minKey;
    }
    void updateKey(int oldKey,int newKey)   // Finds the node containing old key and then decreases the node's value and maintains
    {                                       // min heap property
        Node* node=findNode(head,oldKey);
        if(node==nullptr || oldKey<=newKey)
        {
            return;
        }
        node->key=newKey;
        Node* y=node;
        Node* z=y->parent;
        while(z!=nullptr && y->key<z->key)
        {
            swap(y->key,z->key);
            y=z;
            z=y->parent;
        }
    }
    void removeKey(int key)            // Removes the key by decreasing the key to a minimum
    {                                  // and then extract min
        updateKey(key,INT_MIN);
        extractMin();
    }
    void print()                       // Prints all tree of the heap
    {
        cout<<"Printing Binomial Heap...\n";
        Node* curr=head;
        while(curr!=nullptr)
        {
            cout<<"Binomial Tree, B"<<curr->degree<<"\n";
            printTreeLevelWise(curr,0);
            curr=curr->sibling;
        }
    }
};

int main() 
{
    BinomialHeap bh;

    bh.insert(5);
    bh.insert(2);
    bh.print();  

    bh.insert(10);
    bh.print();  

    int minVal = bh.findMin();
    cout << "Find Min returned: " << minVal << endl;

    minVal = bh.extractMin();
    cout << "Extract Min returned: " << minVal << endl;
    bh.print();  

    bh.insert(3);
    bh.insert(20);
    bh.print();  

    bh.updateKey(10, 1);  
    bh.print();

    bh.insert(16);
    bh.print();  

    bh.removeKey(20);
    bh.print();  

    return 0;
}

// Output  :   Printing Binomial Heap...
//             Binomial Tree, B1
//             Level 0 : 2
//             Level 1 : 5 
//             Printing Binomial Heap...
//             Binomial Tree, B0
//             Level 0 : 10
//             Binomial Tree, B1
//             Level 0 : 2
//             Level 1 : 5
//             Find Min returned: 2
//             Extract Min returned: 2
//             Printing Binomial Heap...
//             Binomial Tree, B1
//             Level 0 : 5
//             Level 1 : 10
//             Printing Binomial Heap...
//             Binomial Tree, B2
//             Level 0 : 3
//             Level 1 : 5 20
//             Level 2 : 10
//             Printing Binomial Heap...
//             Binomial Tree, B2
//             Level 0 : 1
//             Level 1 : 3 20
//             Level 2 : 5
//             Printing Binomial Heap...
//             Binomial Tree, B0
//             Level 0 : 16
//             Binomial Tree, B2
//             Level 0 : 1
//             Level 1 : 3 20
//             Level 2 : 5
//             Printing Binomial Heap...
//             Binomial Tree, B2
//             Level 0 : 1
//             Level 1 : 3 16
//             Level 2 : 5