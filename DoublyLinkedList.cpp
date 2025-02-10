#include<bits/stdc++.h>
using namespace std;

class Node               // Node has both next and previous nodes address
{
    public:
        int data;
        Node* prev;
        Node* next;
};

void push(Node** head,int newData)     // Insert node at head position
{
    Node* newNode=new Node();
    newNode->data=newData;
    newNode->next=(*head);
    newNode->prev=NULL;
    if((*head)!=NULL)
    {
        (*head)->prev=newNode;
    }
    (*head)=newNode;
}

void append(Node** head,int newData)     // Insert node at last position
{
    Node* newNode=new Node();
    newNode->data=newData;
    newNode->next=NULL;
    if(*head==NULL)
    {
        newNode->prev=NULL;
        (*head)=newNode;
        return;
    }
    Node* temp=(*head);
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=newNode;
    newNode->prev=temp;
}

void insertAfter(Node* prevNode,int newData)    // Insert a node after a given node
{
    if(prevNode==NULL)
    {
        cout<<"prevNode cannot be NULL"<<endl;
        return;
    }
    Node* newNode=new Node();
    newNode->data=newData;
    newNode->next=prevNode->next;
    prevNode->next=newNode;
    newNode->prev=prevNode;
    if(newNode->next!=NULL)
    {
        newNode->next->prev=newNode;
    }
    return;
}

void deleteFirst(Node** head,Node* delNode)   // Deletes the head node and resets head
{
    if(delNode==(*head))
    {
        (*head)=delNode->next;
    }
    if(delNode->prev!=NULL)
    {
        delNode->prev->next=delNode->next;
    }
    free(delNode);
}

void deleteInner(Node* delNode)         // Deletes an inner node and resets prev and next
{
    if(delNode->next!=NULL)
    {
        delNode->next->prev=delNode->prev;
    }
    if(delNode->prev!=NULL)
    {
        delNode->prev->next=delNode->next;
    }
    free(delNode);
}

void deleteLast(Node* delNode)            // Deletes the last node
{
    if(delNode->prev!=NULL)
    {
        delNode->prev->next=delNode->next;
    }
    free(delNode);
}

void printList(Node* head)
{
    Node* temp=head;
    while(temp!=NULL)
    {
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}

void freeList(Node* head)        // Free memories
{
    Node* temp=head;
    while(head!=NULL)
    {
        temp=head->next;
        delete head;
        head=temp;
    }
}

int main()
{
    Node* head=new Node();
    head=NULL;
    for(int i=10;i<=100;i+=10)
    {
        append(&head,i);
    }
    printList(head);
    insertAfter(head,15);
    printList(head);
    push(&head,5);
    printList(head);
    deleteFirst(&head,head);
    printList(head);
    int index;
    cout<<"Enter index : ";
    cin>>index;
    Node* temp=head;
    for(int i=0;i<index;i++)
    {
        temp=temp->next;
    }
    deleteInner(temp);
    printList(head);
    Node* temp1=head;
    while(temp1->next!=NULL)
    {
        temp1=temp1->next;
    }
    deleteLast(temp1);
    printList(head);
    freeList(head);
    return 0;
}


//  Output :  10 20 30 40 50 60 70 80 90 100 
//            10 15 20 30 40 50 60 70 80 90 100 
//            5 10 15 20 30 40 50 60 70 80 90 100 
//            10 15 20 30 40 50 60 70 80 90 100 
//            Enter index : 5                      // Input
//            10 15 20 30 40 60 70 80 90 100 
//            10 15 20 30 40 60 70 80 90