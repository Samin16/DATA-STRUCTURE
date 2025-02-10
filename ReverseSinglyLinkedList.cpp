// Reverse Methods of LinkedList


// Method 1: Using curr,Prev,Next node
#include<bits/stdc++.h>
using namespace std;

class Node
{
    public:
        int data;
        Node* next;
};

void append(Node** node,int newData)
{
    Node* newNode=new Node();
    newNode->data=newData;
    newNode->next=NULL;
    if((*node)==NULL)
    {
        (*node)=newNode;
        return;
    }
    Node* last=(*node);
    while(last->next!=NULL)
    {
        last=last->next;
    }
    last->next=newNode;
}

void reverse(Node** node)         // Reverse the node through three Pointers
{
    Node* current=*node;          // To point to the current node
    Node* next=NULL;              // The next node of the current node in RLL
    Node* prev=NULL;              // To store the node for which reverse op. is done
    while(current!=NULL)
    {
        next=current->next;
        current->next=prev;
        prev=current;
        current=next;
    }
    *node=prev;
}

void printList(Node* node)
{
    Node* temp=node;
    while(temp!=NULL)
    {
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}

int main()
{
    Node* head=new Node();
    head=NULL;
    append(&head,1);
    append(&head,2);
    append(&head,3);
    append(&head,4);
    printList(head);
    reverse(&head);
    printList(head);
    return 0;
}

//     Output:  1 2 3 4 
//              4 3 2 1





// Method 2: Recursive method
// #include<bits/stdc++.h>
// using namespace std;

// class Node
// {
//     public:
//         int data;
//         Node* next;
// };

// void append(Node** node,int newData)
// {
//     Node* newNode=new Node();
//     newNode->data=newData;
//     newNode->next=NULL;
//     if((*node)==NULL)
//     {
//         (*node)=newNode;
//         return;
//     }
//     Node* last=(*node);
//     while(last->next!=NULL)
//     {
//         last=last->next;
//     }
//     last->next=newNode;
// }

// Node* reverseRecursion(Node* node)
// {
//     if(node==NULL || (node)->next==NULL)
//     {
//         return node;
//     }
//     Node* rest=reverseRecursion((node)->next);
//     (node)->next->next=node;
//     (node)->next=NULL;
//     return rest;
// }

// void printList(Node* node)
// {
//     Node* temp=node;
//     while(temp!=NULL)
//     {
//         cout<<temp->data<<" ";
//         temp=temp->next;
//     }
//     cout<<endl;
// }

// int main()
// {
//     Node* head=new Node();
//     head=NULL;
//     append(&head,1);
//     append(&head,2);
//     append(&head,3);
//     append(&head,4);
//     printList(head);
//     Node* node=reverseRecursion(head);
//     printList(node);
//     return 0;
// }

//     Output:  1 2 3 4 
//              4 3 2 1





// Method 3 : Reverse using curr,prev and next but with different concept

// #include<bits/stdc++.h>
// using namespace std;

// class Node
// {
//     public:
//         int data;
//         Node* next;
// };

// void reverseUtil(Node* curr,Node* prev,Node** head);

// void reverse(Node** head)
// {
//     if(!head)
//     {
//         return;
//     }
//     reverseUtil(*head,NULL,head);
// }

// void reverseUtil(Node* curr,Node* prev,Node** head)
// {
//     if(!curr->next)
//     {
//         *head=curr;
//         curr->next=prev;
//         return;
//     }
//     Node* next=curr->next;
//     curr->next=prev;
//     reverseUtil(next,curr,head);
// }

// void append(Node** head,int newData)
// {
//     Node* newNode=new Node();
//     newNode->data=newData;
//     newNode->next=NULL;
//     if((*head)==NULL)
//     {
//         (*head)=newNode;
//         return;
//     }
//     Node* last=(*head);
//     while(last->next!=NULL)
//     {
//         last=last->next;
//     }
//     last->next=newNode;
//     return;
// }

// void printList(Node* node)
// {
//     Node* temp=node;
//     while(temp!=NULL)
//     {
//         cout<<temp->data<<" ";
//         temp=temp->next;
//     }
//     cout<<endl;
// }

// int main()
// {
//     Node* head=new Node();
//     head=NULL;
//     for(int i=1;i<=4;i++)
//     {
//         append(&head,i);
//     }
//     printList(head);
//     reverse(&head);
//     printList(head);
//     return 0;
// }

//     Output:  1 2 3 4 
//              4 3 2 1





// Method 4 : Reverse Using Stack

// #include<bits/stdc++.h>
// using namespace std;

// class Node
// {
//     public:
//     int data;
//     Node* next;
// };

// void append(Node** node,int newData)
// {
//     Node* newNode=new Node();
//     newNode->data=newData;
//     newNode->next=NULL;
//     if((*node)==NULL)
//     {
//         (*node)=newNode;
//         return;
//     }
//     Node* last=(*node);
//     while(last->next!=NULL)
//     {
//         last=last->next;
//     }
//     last->next=newNode;
//     return;
// }

// void reverseList(Node** head)
// {
//     stack<Node*> s;
//     Node* temp=(*head);
//     while(temp->next!=NULL)
//     {
//         s.push(temp);
//         temp=temp->next;
//     }
//     (*head)=temp;
//     while(!s.empty())
//     {
//         temp->next=s.top();
//         s.pop();
//         temp=temp->next;
//     }
//     temp->next=NULL;
// }

// void printList(Node* head)
// {
//     Node* temp=head;
//     while(temp!=NULL)
//     {
//         cout<<temp->data<<" ";
//         temp=temp->next;
//     }
//     cout<<endl;
// }

// int main()
// {
//     Node* head=new Node;
//     head=NULL;
//     for(int i=1;i<=4;i++)
//     {
//         append(&head,i);
//     }
//     printList(head);
//     reverseList(&head);
//     printList(head);
//     return 0;
// }

//     Output:  1 2 3 4 
//              4 3 2 1