#include<bits/stdc++.h>
using namespace std;

class Queue
{
    int* items;             // Queue Container
    int front;              // Tracks deleting index
    int rear;               // Tracks inserting index
    int size;
public:
    Queue(int size)
    {
        this->size=size;
        items=new int[size];
        front=-1;
        rear=-1;
    }
    bool isFull()         // Is the queue full or not
    {
        if(rear==size-1)
        {
            return true;
        }
        return false;
    }
    bool isEmpty()        // Queue has no element
    {
        if(front==-1)
        {
            return true;
        }
        return false;
    }
    void enQueue(int element)    // Enqueue maintaining FIFO rule
    {
        if(isFull())
        {
            cout<<"The queue is full"<<endl;
            return;
        }
        if(front==-1)
        {
            front=0;
        }
        rear++;
        items[rear]=element;
        cout<<"Inserted : "<<element<<endl;
    }
    int deQueue()          // Dequeue maintaining FIFO rule
    {
        int element;
        if(isEmpty())
        {
            cout<<"Queue is empty"<<endl;
            return (-1);
        }
        element=items[front];
        if(front>=rear)
        {
            rear=-1;
            front=-1;
        }
        else
        {
            front++;
        }
        cout<<"Deleted : "<<element<<endl;
        return element;
    }
    // Debug Section
    void display()
    {
        int i;
        if(isEmpty())
        {
            cout<<"Queue is empty"<<endl;
            return;
        }
        cout<<"Front index : "<<front<<endl;
        cout<<"Items : ";
        for(i=front;i<=rear;i++)
        {
            cout<<items[i]<<" ";
        }
        cout<<"\nRear index : "<<rear<<endl;
    }
};

int main()
{
    Queue q(5);
    for(int i=1;i<=5;i++)
    {
        q.enQueue(i);
    }
    q.enQueue(6);
    q.display();
    q.deQueue();
    q.display();
    return 0;
}


// Output : Inserted : 1
//          Inserted : 2
//          Inserted : 3
//          Inserted : 4
//          Inserted : 5
//          The queue is full
//          Front index : 0
//          Items : 1 2 3 4 5
//          Rear index : 4
//          Deleted : 1
//          Front index : 1
//          Items : 2 3 4 5
//          Rear index : 4