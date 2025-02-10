#include <bits/stdc++.h>
using namespace std;

class Node // Node in a linked list
{
public:
    int data;
    Node *next;
};

void push(Node **node, int newData) // Inserting node in front of LList
{
    Node *newNode = new Node();
    newNode->data = newData;
    newNode->next = (*node);
    (*node) = newNode;
}

void append(Node **node, int newData) // Inserting node at the end of LList
{
    Node *newNode = new Node();
    newNode->data = newData;
    newNode->next = NULL;
    if ((*node) == NULL)
    {
        (*node) = newNode;
        return;
    }
    Node *last = (*node);
    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = newNode;
}

void insertAfter(Node *node, int newData) // Inserting a node after a given node
{
    if (node == NULL)
    {
        cout << "Previous node caannot be NULL" << endl;
        return;
    }
    Node *newNode = new Node();
    newNode->data = newData;
    newNode->next = node->next;
    node->next = newNode;
}

void deleteN(Node **node, int index) // Deletes the element at given index
{
    if ((*node) == NULL)
    {
        cout << "No element in the linked list" << endl;
        return;
    }
    Node *temp = (*node);
    if (index == 0)
    {
        (*node) = temp->next;
        free(temp);
        return;
    }
    for (int i = 0; i < index - 1; i++)
    {
        temp = temp->next;
    }
    if (temp == NULL || (temp->next) == NULL)
    {
        return;
    }
    Node *next = temp->next->next;
    temp->next = next;
}

void deleteNRecur(Node *&node, int element) // Recursively deletes a node which value(data) is given
{
    if (node == NULL)
    {
        cout << "Element not found" << endl;
        return;
    }
    if (node->data == element)
    {
        Node *temp = node;
        node = node->next;
        delete (temp);
        return;
    }
    deleteNRecur(node->next, element);
}

int length(Node *head) // Calculates the length of LList chain
{
    int count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}

Node *deleteEndFrom(Node *node, int n) // Deletes nth element from end
{
    int Length = length((node));
    int indexFromBegin = Length - n + 1;
    Node *prev = NULL;
    Node *temp = node;
    for (int i = 1; i < indexFromBegin; i++)
    {
        prev = temp;
        temp = temp->next;
    }
    if (prev == NULL)
    {
        node = node->next;
        return node;
    }
    prev->next = prev->next->next;
    return node;
}

Node *deleteNodeLastTwoPointers(Node *head, int n) // Deletes n th element from LList without calculating length
{
    if (head == NULL)
    {
        cout << "Linked list is empty" << endl;
        return head;
    }
    if (n <= 0)
    {
        cout << "n must be positive" << endl;
        return head;
    }

    Node *fast = head;
    Node *slow = head;

    // Move the fast pointer n steps ahead
    for (int i = 0; i < n; i++)
    {
        if (fast == NULL)
        {
            cout << "n is greater than the length of the linked list" << endl;
            return head; // n is greater than the length, do nothing
        }
        fast = fast->next;
    }

    // If fast is NULL, it means we need to delete the head node
    if (fast == NULL)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    // Move both pointers until fast reaches the end
    while (fast->next != NULL)
    {
        fast = fast->next;
        slow = slow->next;
    }

    // Now, slow is pointing to the node just before the node to be deleted
    Node *temp = slow->next;
    slow->next = slow->next->next;
    delete temp;

    return head;
}

void printList(Node *node) // Prints the whole LList
{
    while (node != NULL)
    {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

// Test 1
int main()
{
    Node* head=new Node();
    head=NULL;
    append(&head,1);
    append(&head,2);
    append(&head,3);
    append(&head,4);
    push(&head,5);
    insertAfter(head,6);
    printList(head);
}


// Test1
// Output : 5 6 1 2 3 4

// Test2
// int main()
// {
//     Node *head = NULL;

//     // Test append function
//     append(&head, 1);
//     append(&head, 2);
//     append(&head, 3);
//     cout << "After appending 1, 2, 3: ";
//     printList(head);

//     // Test push function
//     push(&head, 0);
//     cout << "After pushing 0: ";
//     printList(head);

//     // Test insertAfter function
//     insertAfter(head->next, 5);
//     cout << "After inserting 5 after the second node: ";
//     printList(head);

//     // Test deleteN function
//     deleteN(&head, 2);
//     cout << "After deleting node at index 2: ";
//     printList(head);

//     // Test deleteNRecur function
//     deleteNRecur(head, 2);
//     cout << "After deleting node with value 2 recursively: ";
//     printList(head);

//     // Test length function
//     cout << "Length of the linked list: " << length(head) << endl;

//     // Test deleteEndFrom function
//     head = deleteEndFrom(head, 2);
//     cout << "After deleting 2nd node from the end: ";
//     printList(head);

//     // Test deleteNodeLastTwoPointers function
//     head = deleteNodeLastTwoPointers(head, 1);
//     cout << "After deleting 1st node from the end using two pointers: ";
//     printList(head);

//     return 0;
// }


//  Test2
//  Output : After appending 1, 2, 3: 1 2 3 
//           After pushing 0: 0 1 2 3 
//           After inserting 5 after the second node: 0 1 5 2 3 
//           After deleting node at index 2: 0 1 2 3 
//           After deleting node with value 2 recursively: 0 1 3
//           Length of the linked list: 3
//           After deleting 2nd node from the end: 0 3
//           After deleting 1st node from the end using two pointers: 0