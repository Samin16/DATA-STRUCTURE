// Stack Using Three Simple Queues

#include<bits/stdc++.h>
using namespace std;

class Queue
{
    int *items;
    int front;
    int rear;
    int numItems;

public:
    Queue() {}
    Queue(int n)
    {
        numItems = n;
        items = new int[numItems];
        front = -1;
        rear = -1;
    }
    Queue &operator=(const Queue &q)             // q = q1                                           
    {                                            // q1 = q2
        if (this == &q)                          // q2 = q  Needed for those Operations
            return *this;

        delete[] items;
        numItems = q.numItems;
        items = new int[numItems];
        front = q.front;
        rear = q.rear;

        for (int i = front; i <= rear; i++)
        {
            items[i] = q.items[i];
        }

        return *this;
    }
    ~Queue()
    {
        delete[] items;
    }
    bool isEmpty()
    {
        if (front == -1)
        {
            return true;
        }
        return false;
    }
    bool isFull()
    {
        if (rear == numItems - 1)
        {
            return true;
        }
        return false;
    }
    void enqueue(int element)
    {
        if (isFull())
        {
            return;
        }
        if (front == -1)
        {
            front = 0;
        }
        rear++;
        items[rear] = element;
    }
    int dequeue()
    {
        if (isEmpty())
        {
            return -1;
        }
        int element = items[front];
        if (front >= rear)
        {
            front = -1;
            rear = -1;
        }
        else
           front++;
        return element;
    }
    int peek()
    {
        if (front == -1)
        {
            return -1;
        }
        return items[front];
    }
    void display()
    {
        if (isEmpty())
        {
            return;
        }
        for (int i = front; i <= rear; i++)
        {
            cout << items[i] << " ";
        }
        cout << endl;
    }
};

class Stack
{
    Queue q1, q2 , q;            // Three Queues to Implement Stack(Not space friendly)
    int stackSize;
    int currentSize;

public:
    Stack(int n) : q1(n), q2(n) ,q(n)
    {
        stackSize = n;
        currentSize = 0;
    }
    void push(int element)          // Converts last inserted element to first elment to be popped
    {                               // to use the queue as stack
        if (currentSize == stackSize)
        {
            return;
        }
        q2.enqueue(element);
        currentSize++;
        while (!q1.isEmpty())
        {
            q2.enqueue(q1.peek());
            q1.dequeue();
        }
        q = q1;
        q1 = q2;
        q2 = q;
    }
    int pop()
    {
        if (q1.isEmpty())
        {
            return -1;
        }
        int k = q1.dequeue();
        currentSize--;
        return k;
    }
    int top()
    {
        if (q1.isEmpty())
        {
            return -1;
        }
        return q1.peek();
    }
    int size()
    {
        return currentSize;
    }
    void print()
    {
        q1.display();
    }
};

int main()
{
    Stack s(5);
    s.push(10);
    s.print();
    s.push(20);
    s.print();
    s.push(30);
    s.push(40);
    s.print();
    cout << s.top() << endl;
    s.pop();
    s.print();
    return 0;
}


// Output :  10 
//           20 10 
//           40 30 20 10 
//           40
//           30 20 10