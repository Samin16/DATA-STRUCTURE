// Circular Linked List
// Author : Samin Yasar

#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Node // Node of a circular linked list
{
public:
    int data;
    Node *next;
};

template <typename T>
class CircularLinkedList      
{
    Node<T> *last;        // Last node to track update of the list

public:
    CircularLinkedList()    // Initialization
    {
        last=NULL;
    }
    void addToEmpty(T newData)   // Add data to to an empty list
    {
        if (last != NULL)
        {
            return;
        }
        Node<T> *newNode = new Node<T>();
        newNode->data = newData;
        last = newNode;
        last->next = last;
        return;
    }

    void Push(T newData)        // Add data at front a list
    {
        if (last == NULL)
        {
            addToEmpty( newData);
            return;
        }
        Node<T> *newNode = new Node<T>();
        newNode->data = newData;
        newNode->next = last->next;
        last->next = newNode;
        return;
    }

    void traverse()          // Traversing from the next node of last
    {
        Node<T> *temp;
        if (last == NULL)
        {
            cout << "List is empty" << endl;
            return;
        }
        temp = last->next;
        do
        {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != last->next);
        cout << endl;
    }

    void addAfter(T newData, T num)   // Add a node after the node with a given value
    {
        if (last == NULL)
        {
            return;
        }
        Node<T> *newNode, *p;
        p = last->next;
        do
        {
            if (p->data == num)
            {
                newNode = new Node<T>();
                newNode->data = newData;
                newNode->next = p->next;
                p->next = newNode;
                if (p == last)
                {
                    last = newNode;
                }
                return;
            }
            p = p->next;
        } while (p != last->next);
        cout << "Given node is not present" << endl;
        return;
    }

    void append(T newData)         // Add a node at last of list and mark it as last
    {
        if (last == NULL)
        {
            addToEmpty(newData);
            return;
        }
        Node<T> *newNode = new Node<T>();
        newNode->data = newData;
        newNode->next = last->next;
        last->next = newNode;
        last = newNode;
    }

    void deleteNode(T d)          // Delete a node with given value (d here)
    {
        if ((last) == NULL)       // If the list is empty
        {
            return;
        }
        if ((last)->data == d && (last)->next == (last))   // If the list has only one node
        {
            free(last);
            (last) = NULL;
            return;
        }
        Node<T> *temp = (last), *k;
        if ((last)->data == d)              // If the last node is the node to be deleted
        {
            while (temp->next != (last))
            {
                temp = temp->next;
            }
            temp->next = (last)->next;
            free(last);
            last = temp;
        }
        while (temp->next != (last) && temp->next->data != d)  // Otherwise
        {
            temp = temp->next;
        }
        if (temp->next->data == d)
        {
            k = temp->next;
            temp->next = k->next;
            free(k);
        }
    }
};

int main()
{
    CircularLinkedList<int> cll;
    for(int i=1;i<=10;i++)
    {
        cll.Push(i);
    }
    cll.traverse();
    cll.addAfter(12,4);
    cll.traverse();
    cll.deleteNode(1);
    cll.deleteNode(6);
    cll.traverse();
    for(int i=1;i<=10;i++)
    {
        cll.append(i);
    }
    cll.traverse();
    return 0;
}


// Output : 10 9 8 7 6 5 4 3 2 1 
//          10 9 8 7 6 5 4 12 3 2 1 
//          10 9 8 7 5 4 12 3 2 
//          10 9 8 7 5 4 12 3 2 1 2 3 4 5 6 7 8 9 10 