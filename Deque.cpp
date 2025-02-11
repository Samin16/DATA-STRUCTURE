//Dequeue Implementation


#include<bits/stdc++.h>
using namespace std;

template<typename T>
class Deque
{
    int n;
    T* arr;
    int front;
    int rear;
    int size;
public:
    Deque(int n)
    {
        this->n=n;
        rear=0;
        front=-1;
        arr=new int[n];
    }
    ~Deque()
    {
        delete[] arr;
    }
    void insertFront(T key);
    void insertRear(T key);
    void deleteFront();
    void deleteRear();
    bool isFull();
    bool isEmpty();
    T getFront();
    T getRear();
};

template<typename T>
bool Deque<T>::isFull()
{
    if((front==0 && rear==n-1) || rear+1==front)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T>
bool Deque<T>::isEmpty()
{
    return front==-1;
}

template<typename T>
void Deque<T>::insertFront(T key)        // Inserts at front position
{
    if(isFull())
    {
        cout<<"Overflowed"<<"\n";
        return;
    }
    if(front==-1)
    {
        front=0;
        rear=0;
    }
    else if(front==0)
    {
        front=n-1;
    }
    else
    {
        front=front-1;
    }
    arr[front]=key;
}

template<typename T>
void Deque<T>::insertRear(T key)       // Inserts at rear position
{
    if(isFull())
    {
        cout<<"Overflowed\n";
        return;
    }
    if(front==-1)
    {
        front=0;
        rear=0;
    }
    else if(rear==n-1)
    {
        rear=0;
    }
    else
    {
        rear=rear+1;
    }
    arr[rear]=key;
}

template<typename T>
void Deque<T>::deleteFront()         // Delete from front position
{
    if(isEmpty())
    {
        cout<<"Queue underflow\n";
        return;
    }
    if(front==rear)
    {
        front=-1;
        rear=-1;
    }
    else if(front==n-1)
    {
        front=0;
    }
    else
    {
        front=front+1;
    }
}

template<typename T>
void Deque<T>::deleteRear()         // Delete from rear position
{
    if(isEmpty())
    {
        cout<<"Queue underflow\n";
        return;
    }
    if(front==rear)
    {
        front=-1;
        rear=-1;
    }
    else if(rear==0)
    {
        rear=n-1;
    }
    else
    {
        rear=rear-1;
    }
}

template<typename T>
T Deque<T>::getFront()
{
    if(isEmpty())
    {
        cout<<"Underflow"<<endl;
        return -1;
    }
    return arr[front];
}

template<typename T>
T Deque<T>::getRear()
{
    if(isEmpty() || rear<0)
    {
        cout<<"Underflow\n";
        return -1;
    }
    return arr[rear];
}

int main()
{
    Deque<int> dq(4);
    dq.insertRear(5);
    dq.insertRear(11);
    cout<<dq.getRear()<<endl;
    dq.deleteRear();
    cout<<dq.getRear()<<endl;
    cout<<dq.getFront()<<endl;
    dq.insertFront(8);
    cout<<dq.getFront()<<endl;
    dq.deleteFront();
    cout<<dq.getFront()<<endl;
    return 0;
}

// Output : 11
//          5
//          5
//          8
//          5