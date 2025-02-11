// Stack using queue (Better than using three Queues)

#include<bits/stdc++.h>
using namespace std;

template<typename T>       // T can be any type
class Queue
{
    T* items;
    int front;            // To track deleting index
    int rear;             // To track inserting index
    int numItems;         // Total number of items Queue can hold
public:
    Queue(int numItems):numItems(numItems)
    {
        items=new T[numItems];
        front=-1;
        rear=-1;
    }
    bool isFull()    // If the queue has front=0 and rear=last_index or inserting_index+1==deleting index
    {                // then the queue is full
        if((front==0 && rear==numItems-1)||(rear+1==front))
        {
            return true;
        }
        return false;
    }
    bool isEmpty()
    {
        return front==-1;
    }
    void enqueue(T item)      // Enqueue at rear as per FIFO rule
    {
        if(isFull())
        {
            return;
        }
        if(front==-1)
        {
            front=0;
        }
        rear=(rear+1)%numItems;
        items[rear]=item;
    }
    T dequeue()              // Delete from front Position
    {
        if(isEmpty())
        {
            return (T)(-1);
        }
        T item=items[front];
        if(front==rear)      // If the Queue has only one element
        {
            front=-1;
            rear=-1;
        }
        else
        {
            front=(front+1)%numItems;
        }
        return item;
    }
    T peek()
    {
        if(isEmpty())
        {
            return (T)-1;
        }
        int item=items[front];
        return item;
    }
    int size()
    {
        if(front==-1)
        {
            return 0;
        }
        if(rear>=front)
        {
            return rear-front+1;
        }
        return numItems-front+rear+1;
    }
    // Not a Queue method , Only to debug
    void display()
    {
        if (isEmpty())
        {
            return;
        }
        int i;
        for (i = front; i != rear; i=(i+1)%numItems)
        {
            cout << items[i] << " ";
        }
        cout<<items[rear]<<endl;
    }
};

class Stack
{
    Queue<int> q;
    int stackSize;
    int stackCapacity;
public:
    Stack(int size):q(size)
    {
        stackCapacity=size;
        stackSize=0;
    }
    void push(int item)
    {
        int size1=q.size();
        q.enqueue(item);
        for(int i=0;i<size1;i++)    // Converts last inserted element to first elment to be popped
        {                           // to use the queue as stack
            q.enqueue(q.peek());
            q.dequeue();
        }
        stackSize++;
    }
    int pop()
    {
        if(stackSize<=0)
        {
            return -1;
        }
        int k=q.dequeue();
        return k;
    }
    int top()
    {
        if(stackSize<=0)
        {
            return -1;
        }
        return q.peek();
    }
    void print()
    {
        q.display();
    }
};

int main()
{
    Stack s(5);
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.print();
    s.pop();
    s.print();
    cout<<s.top()<<endl;
    return 0;
}


// Output  :   40 30 20 10
//             30 20 10
//             30