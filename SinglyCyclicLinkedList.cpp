// Singly Cyclic Linked List
// Author : Samin Yasar

#include<bits/stdc++.h>
using namespace std;

template<typename T>
class Node                 // Node of a singly linked list
{
public:
    T data;
    Node* next;
};

template<typename T>
class LinkedList
{
    Node<T>* head;          // Linked list head
public:
    LinkedList()
    {
        head=NULL;
    }
    void insertFront(T val)            // Push a node in front of Linked List
    {
        Node<T>* newNode=new Node<T>();
        newNode->data=val;
        newNode->next=head;
        head=newNode;
    }
    void insertEnd(T val)              // Append a node at last of a Linked List
    {
        Node<T>* newNode=new Node<T>();
        newNode->data=val;
        newNode->next=NULL;
        if(head==NULL)
        {
            head=newNode;
            return;
        }
        Node<T>* temp=head;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newNode;
    }
    bool hasCycleAndTraverse()        // Method to find cycle and traverse the list
    {
        Node<T> *fast=head,*slow=head;      // Fast and slow pointer
        bool isCycle=false;
        while(fast!=NULL && fast->next!=NULL)    // Traverse until fast is NULL
        {
            fast=fast->next->next;           // Increment fast double than slow
            slow=slow->next;
            if(fast==slow)                   // If fast==slow then we find a cycle
            {
                isCycle=true;
                break;
            }
        }
        if(!isCycle)                  // If not cycle simply traverse
        {
            Node<T>* temp=head;
            while(temp!=NULL)
            {
                cout<<temp->data<<" ";
                temp=temp->next;
            }
            cout<<"\n";
        }
        else                         // If linked list has a cycle then
        {
            Node<T> *temp=head,*temp1=head;
            while(temp1!=slow)             // Find the last node in chain not in a cycle
            {                              // Here temp and slow meets at the node in cycle
                temp1=temp1->next;         // just after chain
                slow=slow->next;
            }
            while(temp!=temp1)             // Traverse the chain
            {
                cout<<temp->data<<" ";
                temp=temp->next;
            }
            cout<<" Cycle : ";            // Traverse the cycle
            do
            {
                cout<<temp1->data<<" ";
                temp1=temp1->next;
            } while (temp1!=slow);
            cout<<"\n";
        }
        return isCycle;
    }
    void createCycle(int pos)         // Create a cycle at position pos
    {                                 // For a singly linked list the only way to 
        if (pos < 0) return;          // make a cycle is to connect the last node 
                                      // with the node at specified position
        Node<T>* temp = head;
        Node<T>* cycleNode = NULL;
        int count = 0;

        while (temp->next != NULL)
        {
            if (count == pos)
            {
                cycleNode = temp;
            }
            temp = temp->next;
            count++;
        }

        if (cycleNode != NULL)
        {
            temp->next = cycleNode;
        }
    }
};

int main()                      // Main / Driver function
{
    LinkedList<int> llist;
    llist.insertEnd(10);
    llist.insertEnd(20);
    llist.insertEnd(30);
    llist.insertEnd(40);
    llist.insertEnd(50);

    llist.createCycle(2);

    bool hasCycle = llist.hasCycleAndTraverse();

    if (hasCycle)
    {
        cout << "The linked list has a cycle.\n";
    }
    else
    {
        cout << "The linked list does not have a cycle.\n";
    }

    return 0;
}

// Output : 10 20  Cycle : 30 40 50 
//          The linked list has a cycle.

// If llist.createCycle(2); is commented
// Output : 10 20 30 40 50 
//          The linked list does not have a cycle.