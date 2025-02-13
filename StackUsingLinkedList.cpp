// Using linked list

#include<bits/stdc++.h>
using namespace std;

class StackNode         // A linked list node to store staack elements
{
    public:
        int data;
        StackNode* next;
};

StackNode* newNode(int newData)
{
    StackNode* newStackNode=new StackNode();
    newStackNode->data=newData;
    newStackNode->next=NULL;
    return newStackNode;
}

bool isEmpty(StackNode* root)
{
    return (!root);
}

void push(StackNode** root,int newData)     // Push data at head position of linked list
{
    StackNode* newStackNode=newNode(newData);
    newStackNode->next=(*root);
    (*root)=newStackNode;
}

int pop(StackNode** root)       // Pop from first of linked list
{
    if(isEmpty(*root))
    {
        return INT_MIN;
    }
    StackNode* temp=(*root);
    (*root)=(*root)->next;
    int popped=temp->data;
    free(temp);
    return popped;
}

int peek(StackNode* root)      // Gives the head element's value
{
    if(isEmpty(root))
    {
        return INT_MIN;
    }
    return root->data;
}

int main()
{
    StackNode* root=NULL;
    for(int i=10;i<=100;i+=10)
    {
        push(&root,i);
    }
    cout<<"Popped element : "<<pop(&root)<<endl;
    cout<<"Top element : "<<peek(root)<<endl;
    cout<<"Elements in stack : "<<endl;
    while(!isEmpty(root))
    {
        cout<<peek(root)<<" ";
        pop(&root);
    }
    return 0;
}

// Output : Popped element : 100
//          Top element : 90
//          Elements in stack : 
//          90 80 70 60 50 40 30 20 10 