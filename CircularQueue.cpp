// Generic Circular Queue Implementation

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


int main()
{
    Queue<int> q(5);
    for(int i=0;i<5;i++)
    {
        q.enqueue(i);
    }
    cout<<"Front-----Rear\n";
    q.display();
    q.dequeue();
    cout<<"Front-----Rear\n";
    q.display();
    q.enqueue(6);
    cout<<"Front-----Rear\n";
    q.display();
    cout<<"Deque Until Queue is Empty\n";
    while(!q.isEmpty())
    {
        cout<<q.peek()<<" ";
        q.dequeue();
    }
    return 0;
}

// Output  :  Front-----Rear
//            0 1 2 3 4
//            Front-----Rear
//            1 2 3 4
//            Front-----Rear
//            1 2 3 4 6
//            Deque Until Queue is Empty
//            1 2 3 4 6

// int main()
// {
//     Queue<char> q(5);
//     for(char i='A';i<='E';i++)
//     {
//         q.enqueue(i);
//     }
//     cout<<"Front-----Rear\n";
//     q.display();
//     q.dequeue();
//     cout<<"Front-----Rear\n";
//     q.display();
//     q.enqueue('F');
//     cout<<"Front-----Rear\n";
//     q.display();
//     cout<<"Deque Until Queue is Empty\n";
//     while(!q.isEmpty())
//     {
//         cout<<q.peek()<<" ";
//         q.dequeue();
//     }
//     return 0;
// }

// Output  :   Front-----Rear
//             A B C D E
//             Front-----Rear
//             B C D E
//             Front-----Rear
//             B C D E F
//             Deque Until Queue is Empty
//             B C D E F