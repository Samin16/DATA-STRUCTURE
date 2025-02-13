// Stack using Array

#include<bits/stdc++.h>
using namespace std;

#define MAX 10

template<typename T>
class Stack                // Stack of size 10 (limited space)
{
        int top;
    public:
        T a[MAX];
        Stack()
        {
            top=-1;
        }
        void push(T x);
        T pop();
        T peek();
        bool isEmpty();
        bool isFull();
};

template<typename T>
void Stack<T>::push(T x)        // Pushes an elemnt on top of stack
{
    if(top>=(MAX-1))
    {
        cout<<"Stack overflow"<<endl;
        return;
    }
    top++;
    a[top]=x;
    return;
}

template<typename T>
T Stack<T>::pop()           // Pops up the last pushed element
{
    if(top<0)
    {
        cout<<"Stack underflow"<<endl;
        return 0;
    }
    T x=a[top];
    top--;
    return x;
}

template<typename T>
T Stack<T>::peek()          // Returns the top element without popping it up
{
    if(top<0)
    {
        cout<<"Stack is empty"<<endl;
        return 0;
    }
    T x=a[top];
    return x;
}

template<typename T>
bool Stack<T>::isEmpty()       // If top position is at 0
{
    return (top<0);
}

template<typename T>
bool Stack<T>::isFull()        // The array which we used to implement stack reached its limit
{
    return (top==MAX-1);
}

int main()
{
    Stack<int> s;
    for(int i=1;i<10;i++)
    {
        s.push(i);
    }
    cout<<"Popped element : ";
    cout<<s.pop()<<endl;
    cout<<"Top element : "<<s.peek()<<endl;
    while(!s.isEmpty())
    {
        cout<<s.peek()<<" ";
        s.pop();
    }
    return 0;
}

// Output : Popped element : 9
//          Top element : 8
//          8 7 6 5 4 3 2 1 